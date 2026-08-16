# PostgreSQL Internals (P2)

## Architecture overview
- **Process-per-connection** model (each client gets a backend process) + a few background workers (writer, checkpointer, autovacuum, WAL writer, stats collector).
- **Shared buffer cache**: most DBs keep hot pages in shared memory; dirty pages flushed by the checkpointer.
- **Write path:** changes go to the **WAL** first (write-ahead log) → then to the data files. Crash-safe because the WAL is durable before the page is.

## MVCC (Multi-Version Concurrency Control)
Postgres' isolation mechanism — readers see a **snapshot**, writers create new row versions.

### Row layout (heap tuple)
```
[t_xmin | t_xmax | ... | data | ...]
```
- `t_xmin` — transaction ID that **created** this version.
- `t_xmax` — transaction ID that **deleted/updated** it (or 0 = live).
- An UPDATE is really: mark the old tuple deleted (set `t_xmax`) and insert a new tuple. This creates **dead tuples** (old versions nobody sees anymore).
- A transaction's snapshot stores the set of committed/in-progress txids at `BEGIN` (or statement start at Read Committed).

### Visibility rule (simplified)
A tuple version is visible if:
- `t_xmin` committed and ≤ snapshot's oldest active xid, AND
- `t_xmax` is 0, or the deleting tx is not yet committed/visible.
→ Old versions linger until **VACUUM** removes them.

### Consequence: bloat
- Dead tuples occupy space until vacuumed.
- A heavily-updated table without timely vacuum grows far beyond its logical size → slower scans, wasted disk.
- Also means Postgres writes more under updates than an in-place engine (but never blocks readers).

---

## WAL (Write-Ahead Log)
- Every change is first appended to the WAL (in `pg_wal/`), then the data page may be updated later.
- On crash: replay the WAL to bring data files to a consistent state (redo).
- **fsync** of the WAL at commit is what gives **durability** — a commit is only guaranteed once the WAL record is on disk.
- Related settings: `synchronous_commit`, `wal_level`, `max_wal_size`.
- WAL also feeds **streaming replication** (replicas replay it) and **point-in-time recovery** (PITR via WAL archives + base backup).

---

## Vacuum & autovacuum
### What VACUUM does
- Reclaims dead tuples' space (so it can be reused by new inserts).
- Updates the visibility map (enables index-only scans).
- Does **not** return space to the OS by default — it marks it reusable inside the relation (that's why a big table stays "big" on disk until `VACUUM FULL` / `pg_rewrite`).

### `VACUUM` vs `VACUUM FULL`
| | `VACUUM` | `VACUUM FULL` |
|---|---|---|
| Locks | No table lock, runs online | ACCESS EXCLUSIVE lock, blocks everything |
| Space | Reusable internally, disk file stays large | Shrinks the actual file |
| Cost | Cheap, run often | Expensive, run rarely (off-peak) |

### Autovacuum
- Runs automatically; triggers on thresholds (dead-tuple count relative to table size, plus age).
- When it falls behind → **bloat** and transaction-ID wrap risk.
- Tuning knobs: `autovacuum_vacuum_scale_factor`/`threshold`, `autovacuum_work_mem` (increase for big tables with many dead tuples — prevents many small passes).

### Practical checks
```sql
SELECT relname, n_dead_tup, last_autovacuum
FROM pg_stat_user_tables
WHERE n_dead_tup > 0 ORDER BY n_dead_tup DESC;
```
- High `n_dead_tup` with stale `last_autovacuum` → autovacuum falling behind (maybe too many small tables or `vacuum_cost_limit` too low).

---

## Table bloat — causes & fixes

### Causes
1. Frequent UPDATE/DELETE (many dead tuples).
2. Autovacuum too slow / disabled / throttled.
3. Long-running transactions — they pin the snapshot, so vacuum can't remove versions newer than the open transaction's oldest xid (they may be "in the future" of the snapshot).
4. `HOT updates` missing (non-indexed column updated → new index entry needed) → more bloat.
5. Vacuum not reaching due to `vacuum_cost_limit` being very small.

### Detect
```sql
-- approximate bloat via extension
CREATE EXTENSION pgstattuple;
SELECT * FROM pgstattuple('orders');
```
- Or estimate: actual table size (`pg_total_relation_size`) vs. sum of live tuples.

### Fix
1. Ensure autovacuum keeps up (tune `scale_factor` on big tables, raise `work_mem`).
2. `VACUUM FULL` / `pg_rewrite` during a maintenance window (blocks writes).
3. Fix the root cause: shorter transactions, better indexes (enable HOT updates), avoid churning rows.
4. For log-style tables: consider `pg_partman` partitioning so old partitions can be dropped whole instead of DELETE+bloat.

---

## Hot updates (worth knowing)
- If an UPDATE **doesn't change any indexed column**, Postgres can do an **HOT (Heap-Only Tuple)** update: the new version reuses the same index entry. This avoids new index entries and reduces bloat/autovacuum load.
- Keep indexes narrow/covering so routine updates are HOT.

---

## Key config knobs (sane defaults for learning)
| Setting | What it does |
|---|---|
| `shared_buffers` | Shared cache size (typically 25% of RAM) |
| `work_mem` | Memory per sort/hash operation (too low → temp files on disk) |
| `max_connections` | Memory per connection; keep modest |
| `wal_level`, `fsync`, `synchronous_commit` | Durability vs. throughput trade-offs |
| `autovacuum_*` | Bloat management |
| `checkpoint_timeout` / `max_wal_size` | How often checkpoints run; affects write burst behavior |

---

## Practice ideas
- Start a Postgres container, `UPDATE` the same row 100k times in a loop, then check `n_dead_tup` and table size grow — then watch autovacuum clean up.
- Open a long transaction (`BEGIN; SELECT ...;` leave open), run updates in another session, observe bloat that vacuum cannot yet reclaim (pinned snapshot).
- Run `VACUUM FULL` on a bloated test table and compare disk usage before/after.
- Reproduce a HOT vs non-HOT update: update a non-indexed column vs an indexed one, compare `pg_stat_user_tables.n_tup_hot_upd`.
