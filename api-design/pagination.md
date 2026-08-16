# Pagination

## Why paginate
Big collections can't be returned in one response — memory, latency, and client overload. Every list endpoint needs pagination.

## Offset-based pagination (page number)
```
GET /users?page=2&limit=50
```
Response:
```json
{ "data": [...], "page": 2, "limit": 50, "total": 4820, "total_pages": 97 }
```
SQL: `SELECT * FROM users ORDER BY id LIMIT 50 OFFSET 100;`

### Pros
- Simple, human-friendly (jump to page 5).
- Random access to any page.

### Cons (why it breaks at scale)
1. **Skips/duplicates under concurrent writes** — offset is positional; rows inserted/deleted between requests shift the window.
2. **Slow deep pages** — `OFFSET 100000` still scans 100k rows to discard them (O(n) per page).
3. **Not stable** — page numbers are meaningless if the dataset changes.

## Cursor-based pagination (keyset / opaque cursor)
```
GET /users?limit=50&cursor=eyJpZCI6MjM0fQ
```
The server returns an **opaque cursor** pointing to the *last item seen*; the next request starts after it.

```
GET /users?limit=50                  → { data: [...], next_cursor: "abc..." }
GET /users?limit=50&cursor=abc...    → next page
```

### How it's implemented
Cursor encodes the position of the last returned row; the query uses a **range over the sort key**:

```sql
-- cursor "after id=234"
SELECT * FROM users
WHERE id > 234
ORDER BY id
LIMIT 50;
```

- Sort key must be **unique and stable** (usually the PK) — that's what makes cursor pagination correct.
- Cursors can be opaque (base64 of a JSON position) or transparent (the raw key).
- Composite cursors for multi-column sorts: encode `(last_name, id)` pairs.

### Pros
- **Stable under writes** — new/removed rows don't shift the window.
- **O(log n) + page size**, not O(page × size) — fast on deep pages.
- What production systems use (Stripe, GitHub, Twitter).

### Cons
- No random access to "page 5" (only forward/backward via prev_cursor).
- Opaque cursors hide the sort logic (a feature — you can change sort without breaking clients).

## Which to use
| | Offset | Cursor |
|---|---|---|
| Scale | Small/medium | Large |
| Deep pages | Slow | Fast |
| Stable under writes | ❌ | ✅ |
| Random page access | ✅ | ❌ |
| Simplicity | ✅ | Slightly more code |
| Default choice | Admin tables, small lists | Production list APIs at scale |

**Rule of thumb: prefer cursor-based for anything that could grow; offset is fine for small/admin/backoffice lists.**

---

## Keyset details (advanced but worth knowing)
Keyset pagination is cursor pagination done with `WHERE key > last` — no `OFFSET` at all:

```sql
-- sort by (created_at, id)
WHERE (created_at, id) > ('2026-01-01T00:00:00Z', 42)
ORDER BY created_at, id
LIMIT 50
```
- Requires an index matching the sort columns → extremely fast.
- Trick: `(a, b) > (x, y)` row-comparison is supported by Postgres.

---

## Common API shapes

### Link header (GitHub style)
```
Link: <https://api.github.com/users?page=2>; rel="next", <...?page=1>; rel="prev"
```

### Keyset with next/prev cursors (Stripe style)
```json
{
  "data": [...],
  "has_more": true,
  "next_cursor": "abc123"
}
```

### Page-based with metadata
```json
{ "data": [], "page": 1, "limit": 50, "total": 4820 }
```
- Compute `total` carefully — it's a `COUNT(*)` scan on huge tables (may need an estimate).

---

## Pitfalls
1. Sorting on a non-unique column without a tiebreaker → rows lost/duplicated between pages (add the PK to the sort).
2. `OFFSET` without `LIMIT`, or unbounded `limit` → allow a max (e.g. 100).
3. Client-supplied arbitrary `order_by` fields → opens slow-query / injection surface; whitelist sortable columns.
4. Forgetting the stable sort key in cursor mode → nondeterministic pages.
5. Deep `OFFSET` + `ORDER BY` on a non-indexed column → full sort each request.

---

## Practice ideas
- Load 10k rows into a table and compare `OFFSET 9990` vs `WHERE id > 9990` timing (EXPLAIN ANALYZE).
- Build both pagination styles; insert/delete rows mid-stream and show offset's skips vs cursor's stability.
- Inspect how a real API (Stripe / GitHub) formats its cursors and pagination headers.
