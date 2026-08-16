# API Versioning

## Why version
Once an API is public, **breaking changes** (removed fields, changed semantics, renamed endpoints) will break existing clients. Versioning gives you a migration path: old clients keep working while you ship new behavior.

## Rule: only version when you must
- Additive changes (new fields, new optional params) are **not** breaking — don't bump a major version for them.
- Reserve version bumps for true breaking changes, and provide migration windows + deprecation notices.

---

## Versioning strategies

### 1. URI path versioning (most common)
```
GET /v1/users/1
GET /v2/users/1
```
**Pros**
- Explicit, visible, cacheable, debuggable (you see the version in the URL/logs).
- Easy to route at the gateway/nginx.

**Cons**
- Semantically, the resource URI changes — `/users/1` "is" versioned even though versioning is about the representation.
- Duplicated route trees / code (usually handled by routing old versions to old controllers).

**Best for:** most public APIs. Default choice.

### 2. Header versioning (Accept header / custom header)
```
GET /users/1
Accept: application/vnd.myapi.v2+json
# or
X-API-Version: 2
```
**Pros**
- URI stays clean/stable — resource identity doesn't change.
- Multiple representations of the same resource.

**Cons**
- Invisible in the URL — harder to debug, cache, and share (screenshot a URL and the version is lost).
- Clients must set the header correctly (more error-prone).

**Best for:** APIs where a clean stable URI is a priority (Stripe uses a hybrid: pinned default + custom).

### 3. Content negotiation (media type with version)
```
Accept: application/json; version=2
Accept: application/vnd.github.v3+json
```
Closely related to header versioning; uses the standard `Accept` mechanism.

### 4. Query parameter versioning
```
GET /users/1?version=2
```
**Pros:** trivial.
**Cons:** easy to omit/mistype, pollutes URLs, not standard — generally avoid.

---

## Comparison

| Strategy | Visible in URL | Standard | Debug-friendly | Cache-friendly | Notes |
|---|---|---|---|---|---|
| **URI path** | ✅ | common | ✅ | ✅ | default choice |
| **Header** | ❌ | — | ❌ | per-representation | clean URIs |
| **Accept/media type** | ❌ | HTTP | ❌ | ✅ | standard-ish |
| **Query param** | ✅ | — | ⚠️ | ⚠️ | avoid |

---

## Practical versioning policies

### Default versioning (Stripe-style)
- New clients get the **latest** version by default; `API-Version` header pins a specific one.
- You can ship a breaking change and give clients a grace window to upgrade.

### Deprecation lifecycle
1. Announce + document the new version and the removal plan.
2. Keep serving old versions with **deprecation warnings** in headers (`Warning: 299 - "Deprecated"` or `Sunset` header).
3. Give a timeline (months), then retire the old route with a 410 Gone and clear error.

```http
Sunset: Sat, 15 Aug 2027 00:00:00 GMT
Deprecation: version="1", date="2026-01-01"
```

### Implementation approaches
- **Route old versions to old code**: `GET /v1/users` → v1 controller (may delegate to a shared core).
- **Backward-compatible transformations**: v2 endpoint converts v1 request/response shapes in middleware.
- **Gateway routing**: gateway sends `/v1/*` and `/v2/*` to different service deployments (see api-gateway.md) — cleanest when a breaking rewrite needs its own deploy.

### Serialization tricks
- Additive changes are safe: new optional fields, new enum values.
- Avoid renaming/removing/retyping fields across versions; if needed, that's a version bump.
- Use explicit `null` vs absent carefully — clients may not handle a new field appearing.

---

## Practice ideas
- Build a small API with `/v1` and `/v2` routes where v2 returns a differently-shaped payload; confirm both coexist.
- Implement a `Sunset`/`Deprecation` header on v1 and test that clients can detect it.
- Design a breaking change (e.g. rename `created_at` → `createdAt`) and plan the v1→v2 migration as an exercise.
- Read how Stripe and GitHub version their APIs (headers vs media type) and note the trade-offs they made.
