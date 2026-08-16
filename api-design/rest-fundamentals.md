# REST Fundamentals

## What REST is
Architectural style for APIs built on **resources** + **HTTP verbs** + **status codes**. It uses the HTTP protocol's own semantics instead of inventing a new RPC layer.

## Resource modeling
- A resource = a noun (a thing), identified by a URI.
- Model your API around **resources and their relationships**, not around function names (RPC style).

```
/users              → collection of users
/users/{id}         → a single user
/users/{id}/orders  → sub-resource (orders belonging to a user)
```

- Collections are usually plural nouns.
- Nested routes express "belongs to": `/users/{id}/orders/{orderId}` (but keep nesting shallow — 1 level is plenty; avoid `/a/{id}/b/{id}/c/{id}`).

## HTTP verbs on resources
| Verb | Semantics | Idempotent | Example |
|---|---|---|---|
| `GET` | Read | ✅ | `GET /users/1` |
| `POST` | Create (new resource) / trigger action | ❌ | `POST /users` |
| `PUT` | Full replace | ✅ | `PUT /users/1` |
| `PATCH` | Partial update | ⚠️ (defined by impl) | `PATCH /users/1` |
| `DELETE` | Remove | ✅ | `DELETE /users/1` |
| `HEAD` | Like GET, no body | ✅ | `HEAD /users` |
| `OPTIONS` | CORS preflight / allowed methods | ✅ | `OPTIONS /users` |

### Key distinction
- **POST** creates; **PUT** replaces (must be idempotent — same call twice = same result).
- **PUT vs PATCH**: PUT replaces the whole resource (missing fields reset), PATCH applies partial changes.

### Actions that don't fit CRUD
- Prefer a sub-resource / dedicated endpoint over RPC-ish verbs: `POST /orders/1/cancel` (not `POST /cancelOrder`).
- Keep verbs to the HTTP ones — avoid `GET /getUsers` style naming.

## HTTP status codes

### 2xx — Success
| Code | Meaning |
|---|---|
| `200 OK` | Success (GET/PUT/PATCH/DELETE) |
| `201 Created` | Created (POST) — include `Location` header |
| `202 Accepted` | Accepted for async processing (job queued) |
| `204 No Content` | Success, no body (DELETE) |

### 4xx — Client error
| Code | Meaning |
|---|---|
| `400 Bad Request` | Malformed request / validation failed |
| `401 Unauthorized` | Not authenticated (missing/invalid credentials) |
| `403 Forbidden` | Authenticated but not allowed (authz) |
| `404 Not Found` | Resource doesn't exist |
| `405 Method Not Allowed` | Verb not supported on this resource |
| `409 Conflict` | State conflict (e.g. duplicate email, version clash) |
| `410 Gone` | Resource intentionally removed |
| `422 Unprocessable Entity` | Well-formed but semantically invalid (common for validation) |
| `429 Too Many Requests` | Rate limited (see rate-limiting.md) |

### 5xx — Server error
| Code | Meaning |
|---|---|
| `500 Internal Server Error` | Unexpected server failure |
| `502 Bad Gateway` | Upstream returned invalid response |
| `503 Service Unavailable` | Overloaded / down for maintenance |
| `504 Gateway Timeout` | Upstream didn't respond in time |

### Rules of thumb
- `401` = **who** are you; `403` = **what** you may do.
- Use `404` to avoid leaking resource existence for private resources.
- Never return 500 for something the client caused — 400/422 instead.
- Be consistent: pick one validation error code (400 or 422) and stick to it.

## Request/response conventions
- **JSON** everywhere (unless gRPC — see grpc-protobuf.md). Content-Type: `application/json`.
- **Consistent casing**: `snake_case` or `camelCase`, one or the other.
- **Plural collections**: `GET /users` returns an array `[{...}, ...]`.
- **Field naming**: be explicit and stable — renaming fields later breaks clients.
- **Include `Location`** header on 201 so clients know where the new resource lives.

## Good vs bad examples
```
BAD:
GET /getUser?id=1            # RPC style, verb in URL
POST /users/getAll           # verbs don't belong in URLs
POST /users/update           # use PUT/PATCH
GET /orders?sort=1&filter=x  # magic numbers

GOOD:
GET  /users/1
POST /users
PUT  /users/1
PATCH /users/1
DELETE /users/1
GET  /users/1/orders
```

## Design checklist
- [ ] Resources named as plural nouns
- [ ] Correct verb per action
- [ ] Correct status codes (incl. 201 + Location, 204 on delete)
- [ ] Consistent JSON casing & shapes
- [ ] Idempotency handled for POST (see idempotency.md)
- [ ] Pagination on list endpoints (see pagination.md)
- [ ] Errors use a consistent structure (see error-responses.md)

## Practice ideas
- Take an existing system's DB schema and design a REST API for it on paper (resources, routes, verbs, status codes).
- Compare with a real public API (GitHub, Stripe) — note their resource modeling choices.
- Build a tiny CRUD API in your language of choice and curl it with the correct verbs/status codes.
- Use httpie/curl to poke a public API and observe real status codes for edge cases (404, 401, 429).
