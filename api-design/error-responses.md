# Error Response Conventions

## Why a consistent error format matters
Clients can't write reliable error handling if every endpoint returns errors in a different shape. A **single, documented error contract** is as important as the success shape.

## The goal error shape (JSON:API-ish, pragmatic)
```json
{
  "error": {
    "code": "order_not_found",
    "message": "Order 1234 does not exist",
    "details": { "order_id": 1234 }
  }
}
```

Or flat variant:
```json
{
  "code": "order_not_found",
  "message": "Order 1234 does not exist",
  "request_id": "req_8f2c..."
}
```

### Field semantics
| Field | Purpose |
|---|---|
| `code` | **Machine-readable, stable** error identifier (clients `switch` on this, never on the message text) |
| `message` | **Human-readable** explanation (can be localized, should never be parsed) |
| `details` | Optional structured context (field names, constraint values) |
| `request_id` / `trace_id` | Correlation id so a user can reference the failure in support tickets |

---

## Validation errors (field-level)
```json
{
  "error": {
    "code": "validation_failed",
    "message": "Request failed validation",
    "details": {
      "fields": [
        { "field": "email", "reason": "not_a_valid_email" },
        { "field": "password", "reason": "too_short", "min": 8 }
      ]
    }
  }
}
```
- List **all** failures, not just the first — clients hate fixing one error at a time.
- Each field carries its own machine-readable `reason`.

## Status codes + error codes should map consistently
| HTTP | Typical error codes |
|---|---|
| `400` | `malformed_request`, `validation_failed` |
| `401` | `unauthenticated`, `token_expired`, `token_invalid` |
| `403` | `forbidden`, `insufficient_scope` |
| `404` | `resource_not_found`, `order_not_found` |
| `409` | `conflict`, `duplicate`, `state_conflict`, `version_conflict` |
| `422` | `validation_failed` (if used instead of 400) |
| `429` | `rate_limited` (with Retry-After header) |
| `5xx` | `internal_error`, `upstream_error`, `timeout` |

---

## Rules / best practices
1. **One shape everywhere.** Same JSON structure from every endpoint, every error — enforced by a shared serializer.
2. **Don't leak internals.** No stack traces, SQL dumps, or library exception messages in production responses. Log them, return generic + code.
3. **Never parse `message` in client code** — only `code`. Messages change; codes don't.
4. **Consistent casing + types** — `details.fields` always an array of objects, etc.
5. **Include correlation id** (`request_id`) on both errors and success logs so support can trace.
6. **Return the most specific status code** — a validation problem is `400/422`, not `500`.
7. **Internationalization** — keep `message` in the canonical language and let clients localize by `code` if needed.
8. **Retryable vs not** — 5xx/429 are retryable; 4xx generally are not (see idempotency.md / rate-limiting.md).

## Server-side: map exceptions → error responses (per language)
- **Java/Spring:** `@RestControllerAdvice` + `@ExceptionHandler` → consistent `ApiError` body; catch validation, not-found, and generic last.
- **Python/FastAPI:** `HTTPException` + custom exception handlers → unified `{"error": {...}}`; Pydantic validation errors mapped to the field format.
- **Go:** a shared `http.Error` writer that serializes `{code, message, request_id}` from typed errors.
- **Node/Express:** central error middleware (`(err, req, res, next)`) that formats any thrown error.

```python
# FastAPI example
@app.exception_handler(OrderNotFound)
async def handler(req, exc):
    return JSONResponse(status_code=404, content={
        "error": {"code": exc.code, "message": str(exc), "details": exc.details}
    })
```

## Logging errors (backend ops)
- Log the **full detail server-side** (stack, query params, headers) with the same `request_id` the client saw.
- Correlate: `request_id` in logs = `request_id` in response = traceable.

## Practice ideas
- Write a centralized error handler in your framework of choice and confirm every endpoint returns the same shape.
- Deliberately trigger each error class (400/401/403/404/409/429/500) and verify code + status alignment.
- Add `request_id` generation + logging and trace one failing request end-to-end.
- Check how Stripe/GitHub format errors and steal their field conventions.
