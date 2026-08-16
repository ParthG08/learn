# SQL Mastery

## Joins

### Types
| Join | Keeps rows | Use case |
|---|---|---|
| `INNER JOIN` | Only rows matching in **both** tables | Core relationship query |
| `LEFT JOIN` | All rows from left + matches from right (NULL if no match) | "All X even if no Y" |
| `RIGHT JOIN` | Mirror of LEFT | Rare — flip the tables instead |
| `FULL OUTER JOIN` | All rows from both (NULLs where missing) | Diffing two datasets |
| `CROSS JOIN` | Cartesian product | Generating combinations |

### Syntax
```sql
SELECT o.id, c.name
FROM orders o
JOIN customers c ON o.customer_id = c.id;

-- LEFT join, keep all customers even with no orders
SELECT c.name, COUNT(o.id)
FROM customers c
LEFT JOIN orders o ON o.customer_id = c.id
GROUP BY c.id, c.name;
```

### Mental model
- `JOIN ... ON` produces an intermediate filtered Cartesian product.
- Filter placement matters:
  - `WHERE` filters **after** the join (may drop rows a LEFT JOIN was trying to keep).
  - `ON` for LEFT joins filters the right side **without dropping left rows**.
- A LEFT JOIN that filters right-side rows in `WHERE` behaves like an INNER JOIN — common bug.

### Self-join
```sql
-- employees and their manager
SELECT e.name, m.name AS manager
FROM employees e
LEFT JOIN employees m ON e.manager_id = m.id;
```

---

## Subqueries

### Scalar subquery (returns 1 value)
```sql
SELECT name, (SELECT MAX(price) FROM products) AS max_price FROM categories;
```

### Row subquery
```sql
SELECT * FROM orders
WHERE (customer_id, created_at) = (SELECT customer_id, MAX(created_at) FROM orders);
```

### Table subquery (derived table / inline view)
```sql
SELECT dept, avg_sal
FROM (SELECT dept_id, AVG(salary) AS avg_sal FROM employees GROUP BY dept_id) AS d
JOIN departments dept ON dept.id = d.dept_id;
```

### Correlated subquery (references outer query — runs per row)
```sql
-- employees earning more than their dept average
SELECT e.name, e.salary
FROM employees e
WHERE e.salary > (SELECT AVG(salary) FROM employees WHERE dept_id = e.dept_id);
```
- Expensive if the table is large — often rewrite with window functions or joins.

### `IN` / `EXISTS` / `ANY` / `ALL`
```sql
WHERE id IN (SELECT product_id FROM stock WHERE qty = 0)
WHERE EXISTS (SELECT 1 FROM stock s WHERE s.product_id = p.id AND s.qty = 0)
WHERE salary > ANY (SELECT salary FROM managers)   -- > at least one
WHERE salary > ALL (SELECT salary FROM managers)   -- > all of them
```
- `EXISTS` stops at first match — usually faster than `IN` with big subqueries.
- `IN` with `NULL` behaves surprisingly: `x IN (1, 2, NULL)` never matches when x is not 1 or 2.

---

## Window Functions

Compute values across a set of rows **related to the current row** without collapsing rows (unlike `GROUP BY`).

```sql
SELECT
  name, dept, salary,
  ROW_NUMBER()   OVER (PARTITION BY dept ORDER BY salary DESC) AS rn,
  RANK()         OVER (PARTITION BY dept ORDER BY salary DESC) AS rk,
  DENSE_RANK()   OVER (PARTITION BY dept ORDER BY salary DESC) AS drk,
  AVG(salary)    OVER (PARTITION BY dept)                       AS dept_avg,
  SUM(salary)    OVER (ORDER BY id ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS running_total
FROM employees;
```

### Key clauses
- `PARTITION BY` — grouping (resets per group)
- `ORDER BY` — ordering inside the partition (defines the "window" of frame)
- `ROWS BETWEEN <start> AND <end>` — explicit frame (default: from partition start to current row when ORDER BY present)

### Common functions
| Function | What it gives |
|---|---|
| `ROW_NUMBER()` | 1,2,3... unique per partition |
| `RANK()` | 1,1,3 — gaps after ties |
| `DENSE_RANK()` | 1,1,2 — no gaps |
| `LAG(col, n)` / `LEAD(col, n)` | Value n rows before/after (row-over-row comparisons) |
| `FIRST_VALUE` / `LAST_VALUE` | First/last value in the frame |
| `NTILE(n)` | Bucket rows into n groups |
| `SUM/AVG/COUNT/MIN/MAX OVER` | Running/rolling aggregates |

### Classic patterns
- Row-over-row delta: `price - LAG(price) OVER (ORDER BY day)`
- Top-N per group: wrap in a subquery, filter `WHERE rn <= N`
- Compare to previous day: `LAG` + `CASE` for change direction
- Moving average: `AVG(price) OVER (ORDER BY day ROWS BETWEEN 6 PRECEDING AND CURRENT ROW)`

---

## CTEs (Common Table Expressions)

Named subqueries readable top-down.

```sql
WITH monthly_sales AS (
  SELECT DATE_TRUNC('month', created_at) AS month, SUM(amount) AS total
  FROM orders
  GROUP BY 1
),
growth AS (
  SELECT month, total,
         total - LAG(total) OVER (ORDER BY month) AS delta
  FROM monthly_sales
)
SELECT * FROM growth WHERE delta IS NOT NULL;
```

### Why CTEs win
- Readability — build a query in named steps.
- Reuse the same subquery multiple times (once per reference in some engines; Postgres inlines).
- **Recursive CTEs** — the real superpower (hierarchies, trees, graph traversal):

```sql
WITH RECURSIVE org_tree AS (
  SELECT id, name, manager_id, 1 AS depth FROM employees WHERE manager_id IS NULL
  UNION ALL
  SELECT e.id, e.name, e.manager_id, ot.depth + 1
  FROM employees e JOIN org_tree ot ON e.manager_id = ot.id
)
SELECT * FROM org_tree;
```

- CTEs don't force materialization in modern Postgres (they're inlined), so they aren't a performance shortcut by themselves.

---

## Aggregates

### Core
```sql
SELECT dept_id, COUNT(*), COUNT(DISTINCT role),
       SUM(salary), AVG(salary), MIN(salary), MAX(salary),
       STRING_AGG(name, ', ' ORDER BY name)   -- postgres
FROM employees
GROUP BY dept_id
HAVING AVG(salary) > 5000;
```

### `GROUP BY` semantics
- Every non-aggregated column in `SELECT` must appear in `GROUP BY`.
- `GROUP BY 1` / `GROUP BY 2` = group by column position (fragile, avoid).
- **`WHERE` filters rows before grouping; `HAVING` filters groups after aggregation.**
- `GROUP BY` with `ROLLUP`/`CUBE`/`GROUPING SETS` for subtotals:

```sql
SELECT dept_id, role, SUM(salary)
FROM employees
GROUP BY ROLLUP(dept_id, role);   -- dept subtotals + grand total
```

### Filtered aggregate
```sql
COUNT(*) FILTER (WHERE status = 'paid')
```

### `NULL` behavior
- Aggregate functions ignore `NULL` (except `COUNT(*)` which counts rows).
- `AVG` of all NULLs → NULL.
- `GROUP BY` puts NULLs in their own group.

---

## Execution order (mental model)
```
FROM / JOIN  →  WHERE  →  GROUP BY  →  HAVING  →  SELECT  →  ORDER BY  →  LIMIT
```
- You can't alias a `SELECT` expression in `WHERE` (it doesn't exist yet).
- You can't use window functions in `WHERE` — wrap in a subquery/CTE.

---

## Practice ideas
- Redesign an app query into: JOIN → subquery → CTE → window function — see which reads best.
- Top-N per group, running totals, gaps-between-orders are the classic window drills.
- Use `EXPLAIN ANALYZE` (see `query-optimization/`) after each rewrite to confirm intent matches plan.
