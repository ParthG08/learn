# Idempotency

## What it means
An operation is **idempotent** if calling it multiple times with the same input produces the same result as calling it once. Crucial for retries — networks fail, clients retry, and you must not double-charge / double-create.

- **Naturally idempotent:** GET, PUT, DELETE (by design), PUT (replace).
- **NOT idempotent:** POST (create), non-idempotent PATCH (e.g. "add 1 to counter"), actions like "send email".

## Why it matters
- Payment: retry after a timeout must not charge the card twice.
- Order creation: client retry must not create two orders.
- Webhook redeliveries: the same event may arrive multiple times.

---

## Design approaches

### 1. Idempotency keys (the standard solution for POST)
Client generates a **unique key** per logical operation and sends it in a header; the server keys the operation on it.

```
POST /orders
Idempotency-Key: 550e8400-e29b-41d4-a716-446655440000
```

Server behavior:
1. Check if a result for this key already exists.
2. If **yes** → return the stored result (don't re-execute). Same key + same request = same response.
3. If **no** → execute, store the result keyed by the idempotency key, return it.

Concurrency handling: an atomic "insert if key absent" (unique constraint on the key column) so two simultaneous requests don't both execute.

### 2. Natural keys / unique constraints
Let the data itself be idempotent:
- Unique index on `(client_order_ref, user_id)` → second insert fails or returns the existing row.
- In SQL: `INSERT ... ON CONFLICT DO NOTHING` then `SELECT`.

### 3. PUT semantics
Since PUT replaces a whole resource, retrying is naturally safe — the last call wins.

### 4. ETags / conditional requests
- Client sends `If-Match: <etag>`; server applies the update **only if** the resource still matches — prevents "lost update" overwrites on retry.

---

## Implementation details (Stripe-style)

### Key requirements
- Key must be **unique per client operation** (UUID recommended) and stable across retries.
- The key is **immutable** — a retry with the same key is the same operation; a different key is a different operation.
- Store the idempotency key + the **full request** (or a hash) + the **response**, so a retry can replay the exact stored response.
- Keys should **expire** after some window (e.g. 24h) to bound storage.
- If a retry arrives with the same key but **different payload** → return `422`/`400` (mismatch), don't silently execute.

### Storage sketch
```
idempotency_keys (
  key        text PRIMARY KEY,
  request_sha text NOT NULL,
  status     text,       -- in_progress | complete
  response   jsonb,
  created_at timestamptz,
  expires_at timestamptz
)
```

### Race handling
- Two concurrent requests, same key: use a **unique constraint + upsert** so only one wins the "execute" path; the other waits and then returns the stored response.
- Keep a short timeout: mark `in_progress`, run the op, write result, `complete` — a stuck `in_progress` can be retried after a TTL.

---

## Patterns per scenario

| Scenario | Approach |
|---|---|
| Charge / payment | Idempotency key header + unique `(payment_method, amount, key)` |
| Create order | Unique `(client_ref)` + return existing on conflict |
| Send email | Outbox table; dedupe on `(event_id)` — never send twice |
| Webhook processing | Dedupe by event id; store processed-event ids |
| Counter increment | Use atomic ops (`INCR`/`UPDATE ... SET c = c + 1`) — a plain read-then-write is NOT idempotent under retry |
| File upload | Client-generated content hash / request id as key |

---

## Retry strategy (the other half)
Idempotency only works if retries are well-behaved:
- **Exponential backoff** (1s, 2s, 4s, ...) — don't hammer the server.
- **Add jitter** so retries from many clients don't sync up (thundering herd).
- Cap max attempts (e.g. 5) and surface the error.
- Retry on: network errors, 5xx, 429. Do **not** auto-retry 4xx (client errors) — fix the request.

```python
def request_with_retry(fn, idem_key, attempts=5):
    for i in range(attempts):
        try:
            return fn(idem_key)
        except RetryableError:
            time.sleep(min(2 ** i, 10) + random.uniform(0, 0.5))
    raise MaxRetriesExceeded
```

---

## Practice ideas
- Build a payment-like endpoint with an idempotency-key table; send the same key 3× and verify one charge.
- Test the mismatch case: same key, different payload → correct error.
- Use `curl -w '%{http_code}'` to hit an endpoint with a retry loop and confirm idempotent behavior.
- Read Stripe's docs on idempotency keys (they document this exact design).
