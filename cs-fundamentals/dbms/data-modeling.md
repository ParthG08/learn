# Data Modeling

## Goal
Design a schema that models the domain, stays fast as data grows, and is maintainable. The core trade-off in every decision: **read speed vs. write speed vs. flexibility** — and **normalized consistency vs. denormalized performance**.

---

## Normalization
Remove redundancy so each fact is stored **once**.

### Normal forms (quick)
| NF | Rule |
|---|---|
| **1NF** | Atomic values per column; no repeating groups/arrays |
| **2NF** | 1NF + no partial dependency (non-key column depends on only part of a composite key) |
| **3NF** | 2NF + no transitive dependency (non-key column depends on another non-key column) |
| **BCNF** | Stricter 3NF — every determinant is a candidate key |

### Example
- BAD (1NF): `orders (id, customer_name, customer_email, items)` — repeated customer + array.
- GOOD (3NF): `customers (id, name, email)`, `orders (id, customer_id)`, `order_items (order_id, product_id, qty)`.

### Benefits
- No update anomalies (change a customer's email in ONE place).
- No duplicate data → smaller, consistent.
- `JOIN`s are cheap when indexed.

### Costs
- More tables, more `JOIN`s (slower reads at scale).
- Insert/update across multiple tables needs transactions.

---

## Denormalization
Duplicate data deliberately to make **reads faster** (fewer joins).

| Technique | Example |
|---|---|
| **Precomputed columns** | `order_total` stored on the order row |
| **Redundant columns** | `customer_name` copied onto orders |
| **Materialized views / summary tables** | daily sales totals |
| **Embedded/array fields** (NoSQL) | post with comment list inline |

### When to denormalize
- Read-heavy, high-traffic hot paths (dashboard, feed).
- Reporting/aggregates computed repeatedly.
- Join becomes the bottleneck at scale.
- Trade-off accepted: **write more / keep in sync** for read speed.

### The price
- Update anomalies return (update customer email → must update every order copy).
- Sync is done by app code, triggers, or background jobs — and can drift.
- Rule of thumb: **normalize for writes/consistency, denormalize for reads, and denormalize deliberately (with a sync story), not by accident.**

---

## SQL vs. NoSQL tradeoffs

| Dimension | SQL (Postgres/MySQL) | NoSQL |
|---|---|---|
| Schema | Fixed, enforced | Flexible / schemaless (documents) |
| Relationships | Joins across tables | Embedded or references |
| Transactions | ACID, strong | Often limited (per-document), eventual consistency |
| Scaling | Vertical + read replicas (harder to shard) | Horizontal sharding is native |
| Query | Rich SQL, ad-hoc | Narrower, pre-designed access patterns |
| Consistency | Strong by default | Eventual for multi-node |
| Best fit | Money, complex relations, reporting | High-write scale, flexible schemas, documents/feeds |

### NoSQL families
- **Document** (MongoDB, Couchbase) — JSON-ish, flexible schema, embed vs reference.
- **Key-Value** (Redis, DynamoDB) — blazing lookups by key, no queries.
- **Wide-column** (Cassandra, HBase) — high write throughput, time-series.
- **Graph** (Neo4j) — deep relationship traversal (social, fraud).

### Choosing
- Need joins, transactions, ad-hoc analytics → **Postgres**. (Postgres also has JSONB + extensions, covering much of the "NoSQL" need.)
- Massive write scale with simple access patterns → Cassandra/DynamoDB.
- Flexible evolving documents → MongoDB.
- Cache/hot data → Redis.

---

## Modeling patterns that matter

### 1. Identifying entities & relationships
- Ask: what's a noun in the domain (User, Order, Product)? What's a relationship (User places Order)?
- **1:1** → put on one table (or FK on either side).
- **1:N** → FK on the "many" side (`order.user_id`).
- **N:M** → junction table (`order_products (order_id, product_id)`).

### 2. Keys
- **Surrogate PK** (auto-increment / UUID) vs **natural key** (email, ISBN).
  - Natural keys avoid dupes but can change and are big; UUIDs scale better across systems/sharding.
- **Composite keys** for junction tables (plus a surrogate if needed).

### 3. Time
- Always store **timestamps in UTC** (`timestamptz`), display in local.
- `created_at`, `updated_at` on most tables; `deleted_at` for soft delete.

### 4. Enum vs lookup table
- Small fixed sets → `CHECK`/enum. Evolving values (statuses, categories) → lookup table (FK) for referential integrity + easy additions.

### 5. Star schema for analytics (see dimensional modeling)
- **Fact** table (measures + FKs, high volume) + **dimension** tables (descriptive attributes).
- Billions of fact rows are normal; queries are all about filtering/grouping dimensions.

---

## Common mistakes
1. Storing denormalized data with no sync strategy → silently drifts.
2. `JSONB`/document blob as a "just in case" column → can't index/query inside it, no constraints.
3. No FK constraints in production → orphan rows.
4. Over-indexing (writes slow) or no indexes on FK/join columns (reads slow).
5. Empty-string vs NULL confusion; using NULL for "unknown" vs "not applicable".
6. Modeling `N:M` as a comma-separated string column.

---

## Practice ideas
- Take a real system you use (a blog, an e-commerce checkout) and design its schema from scratch on paper — entities, relationships, FKs.
- Compare your design with the real system's schema.
- Take a denormalized dashboard table and derive the normalized source tables it came from.
- Use dbdiagram.io or draw.io to diagram a 3NF model and a star schema.
