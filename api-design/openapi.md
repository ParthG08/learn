# OpenAPI / Swagger Spec Writing

## What it is
- **OpenAPI** (formerly Swagger) is a YAML/JSON spec describing a REST API: paths, methods, parameters, request/response bodies, auth, errors.
- **Swagger** is the older name; the spec is now the **OpenAPI Specification (OAS)** v3.x. Tools:
  - **Swagger UI** — renders interactive documentation.
  - **Swagger Editor** — validate/edit spec online.
  - **Code generators** — generate client SDKs + server stubs from the spec.

## Why write a spec
- **Contract-first design** — agree on the API before coding; both sides build against the same contract.
- Auto-generated docs, client SDKs, mocks, and tests.
- Single source of truth for consumers; catches design gaps early.

---

## Anatomy of an OpenAPI file

```yaml
openapi: 3.0.3
info:
  title: Orders API
  version: 1.0.0
  description: Manage customer orders

servers:
  - url: https://api.example.com/v1

paths:
  /orders:
    get:
      summary: List orders
      parameters:
        - name: limit
          in: query
          schema: { type: integer, maximum: 100 }
      responses:
        '200':
          description: A list of orders
          content:
            application/json:
              schema:
                type: array
                items: { $ref: '#/components/schemas/Order' }
    post:
      summary: Create an order
      requestBody:
        required: true
        content:
          application/json:
            schema: { $ref: '#/components/schemas/NewOrder' }
      responses:
        '201':
          description: Order created
          headers:
            Location:
              schema: { type: string }
        '422':
          description: Validation error

components:
  schemas:
    Order:
      type: object
      required: [id, status]
      properties:
        id: { type: integer }
        status:
          type: string
          enum: [pending, paid, shipped, cancelled]
        total: { type: number, format: float }
```

### Key blocks
| Block | Purpose |
|---|---|
| `openapi` | Spec version |
| `info` | Title, version, description |
| `servers` | Base URLs |
| `paths` | The API surface — each path + operations |
| `components.schemas` | Reusable data models (`$ref` to them) |
| `components.securitySchemes` | Auth definitions |
| `security` | Global/default auth requirements |

### Paths & operations
- Each operation (get/post/put/patch/delete) has: `summary`, `description`, `parameters`, `requestBody`, `responses`.
- `parameters` — `in: query | path | header | cookie`, plus `schema`.
- `responses` — at minimum status codes; document every realistic error (400/401/403/404/422/429/500).

### Reusing components
- `$ref: '#/components/schemas/Order'` avoids duplicating models.
- `allOf` / `oneOf` / `anyOf` for inheritance & unions.

### Defining security
```yaml
components:
  securitySchemes:
    bearerAuth:
      type: http
      scheme: bearer
      bearerFormat: JWT
security:
  - bearerAuth: []
```

---

## Writing good specs (best practices)
1. **Be exhaustive about errors** — a spec that only documents 200s is half a spec. Every 4xx/5xx you can predict.
2. **Name every response** (`description` is mandatory anyway) and reference schemas — don't inline a model twice.
3. **Document examples** (`example:` / `examples:`) — they power docs and generated mocks.
4. **Use `format`** (int64, uuid, date-time, float) so generated clients use the right types.
5. **Nullable vs optional** — be explicit: `nullable: true` vs absent key.
6. **Validate with a linter** — e.g. **Spectral** catches missing descriptions, inconsistent naming.
7. **Keep it in sync** — the spec drifting from reality is the classic failure. Prefer **code-first with generation** (below) to avoid drift.
8. **Version it** alongside API versions (see versioning.md) — `/v1` spec and `/v2` spec.

## Workflows: which order?

### Spec-first (contract-first)
1. Write the OpenAPI spec.
2. Validate (`swagger editor`, Spectral).
3. Generate server stubs (`openapi-generator`) or mock server (`prism`).
4. Implement against the stub.

### Code-first (generate the spec from code)
- Frameworks annotate code → auto-generate the spec:
  - **Java/Spring**: `springdoc-openapi`.
  - **Python/FastAPI**: built-in OpenAPI generation from type hints.
  - **Go**: `swaggo/swag`, `ogen`.
- Pros: spec can't drift from code (generated). Cons: spec quality depends on annotation discipline.

## Tools cheat-sheet
| Tool | Purpose |
|---|---|
| **Swagger Editor** (editor.swagger.io) | Online validation + rendering |
| **Swagger UI** | Browser docs UI |
| **openapi-generator** | Client/server codegen |
| **Prism** | Mock server from spec |
| **Spectral** | Spec linting (quality gate in CI) |
| **Stoplight / Redocly** | Design tooling + docs |

## Practice ideas
- Write a complete OpenAPI spec for a small resource (e.g. a todo API) with errors, auth, and pagination — validate in Swagger Editor.
- Generate a mock server with Prism and exercise the spec end-to-end.
- Generate a client SDK with openapi-generator and use it against a local server.
- Add Spectral as a CI step and fix the warnings it flags.
