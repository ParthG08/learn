# Indexes

## What an index is
- A sorted data structure (usually B-tree) that lets the DB find rows without scanning the whole table.
- Trade-off: **faster reads, slower writes** (every INSERT/UPDATE/DELETE must maintain the index), more storage.

```sql
CREATE INDEX idx_orders_customer ON orders (customer_id);
CREATE UNIQUE INDEX idx_users_email ON users (email);   -- also enforces uniqueness
DROP INDEX idx_orders_customer;
```

## B-tree basics
- Balanced tree: every leaf is the same distance from the root.
- Nodes hold sorted key values + pointers to child nodes / table rows (heap).
- Lookup cost: **O(log n)** — ~4–5 node reads for millions of rows.
- Leaf nodes are linked in a doubly-linked list → supports **range scans** (`>, <, BETWEEN, ORDER BY`) by walking neighbors instead of re-traversing.
- **Clustered vs. non-clustered:**
  - MySQL/InnoDB: the PK **is** the index; secondary indexes store the PK, then double lookup (index → PK → row).
  - Postgres: everything is a heap; every index stores the row's physical address (TID), one extra hop.

## When an index is used
- Equality: `WHERE col = 5`
- Range: `WHERE col BETWEEN 1 AND 10`, `col > 5`, `col LIKE 'foo%'`
- Ordering: `ORDER BY col` (if it matches index order)
- Uniqueness enforcement (UNIQUE constraint)
- FK lookups: `ON DELETE`/`ON UPDATE` actions need an index on the referencing column

## When an index is NOT used (silently)
This is the highest-leverage knowledge in the list:

1. **Function applied to the column** — index on `created_at`, but `WHERE DATE(created_at) = '2026-01-01'` can't use it.
   - Fix: `WHERE created_at >= '2026-01-01' AND created_at < '2026-01-02'` or a functional index `CREATE INDEX ON users ((lower(email)))`.
2. **Leading `%` wildcard**: `LIKE '%foo%'` — can't walk the B-tree from the middle. `LIKE 'foo%'` works.
3. **Implicit type cast**: `WHERE phone = 123456` where phone is varchar — the column is cast, index skipped.
4. **`NOT IN`, `<>`, `!=`** — generally a scan.
5. **Low selectivity** — if the column has few distinct values (e.g. a boolean), the planner says "meh, just scan"; an index only helps if it narrows down enough rows. Rule of thumb: <~5–10% of rows.
6. **Indexed column order mismatch** with a multi-column index (see below).
7. **Expressions/computations in WHERE**: `WHERE price * qty > 100`.

## Composite (multi-column) indexes
```sql
CREATE INDEX idx_orders_customer_status ON orders (customer_id, status);
```
- **Leftmost-prefix rule:** the index serves queries that use the leading columns in order.
  - `(a, b, c)` serves queries on `a`, on `a,b`, on `a,b,c` — **not** on `b` alone or `b,c`.
- Put the most selective / most-used column first.
- Equality columns first, then the range/order column last — because a range column consumes the rest of the prefix.
- Example: `WHERE customer_id = 5 AND status = 'pending'` → perfect with `(customer_id, status)`.
- Example: `WHERE status = 'pending' AND customer_id = 5` — same index still works if the optimizer reorders (Postgres does); older MySQL may not.

## Covering indexes
An index that contains **every column the query needs** — the query never touches the table (heap).

```sql
-- SELECT amount FROM orders WHERE customer_id = 5 AND status = 'paid';
CREATE INDEX idx_orders_cover ON orders (customer_id, status, amount);
```
- All of customer_id, status, amount are in the index → "index-only scan", much faster.
- Trade-off: index bloat on wide columns; don't overdo it.
- Postgres shows `Index Only Scan` in the plan when this happens.

## Choosing columns to index
1. Columns in `WHERE` (equality first), then `ORDER BY`, then `GROUP BY`.
2. FK columns (join keys).
3. Columns in `SELECT` only when making a covering index.
4. Avoid indexing low-selectivity, write-heavy columns (frequent updates = constant index churn).
5. **Over-indexing costs:** every index slows writes and consumes disk; unused indexes should be dropped.

## Practical verification workflow
1. Write the slow query.
2. `EXPLAIN ANALYZE` → look for `Seq Scan` on a big table.
3. Add index, re-run, confirm it became `Index Scan` / `Index Only Scan` and time dropped.
4. Remove indexes that don't change the plan.

## Practice ideas
- Use `use-the-index-luke.com` — the definitive site; its "SQL where does my query run" drills teach the failure cases.
- Take a slow query from your own app, `EXPLAIN` it, add the right composite index, and measure.
- Test the leftmost-prefix rule yourself with `(a, b, c)` and different WHERE combinations.
