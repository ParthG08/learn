# Transactions & Isolation Levels

## What a transaction is
A unit of work with **ACID** guarantees:

| Property | Meaning |
|---|---|
| **Atomicity** | All or nothing — partial work is rolled back |
| **Consistency** | DB moves from one valid state to another (constraints hold) |
| **Isolation** | Concurrent transactions don't interfere per the chosen level |
| **Durability** | Once committed, data survives crashes (via WAL) |

```sql
BEGIN;
UPDATE accounts SET balance = balance - 100 WHERE id = 1;
UPDATE accounts SET balance = balance + 100 WHERE id = 2;
COMMIT;   -- or ROLLBACK;
```

---

## The three read anomalies

1. **Dirty read** — reading data written by an *uncommitted* transaction.
   - Example: T1 moves money, hasn't committed; T2 reads the intermediate balance and acts on it; T1 rolls back.
   - Prevented by **Read Committed** and above.

2. **Non-repeatable read** — same query in one transaction returns *different rows* because another transaction **committed an UPDATE** in between.
   - Example: T1 reads row (balance=100). T2 updates it to 150 and commits. T1 reads again → 150.
   - Prevented by **Repeatable Read** and above.

3. **Phantom read** — same query returns *more/different rows* because another transaction **committed an INSERT/DELETE** that changes the row *set*.
   - Example: T1 counts rows WHERE status='x' → 10. T2 inserts a new matching row and commits. T1 counts again → 11.
   - Prevented by **Serializable** (in Postgres also by Repeatable Read, which uses snapshot isolation).

> Postgres note: Repeatable Read uses MVCC snapshots, so it also prevents phantoms. But in principle the anomaly "belongs" to the Serializable tier.

---

## Isolation levels (SQL standard)

| Level | Dirty read | Non-repeatable read | Phantom read |
|---|---|---|---|
| **Read Uncommitted** | possible | possible | possible |
| **Read Committed** (Postgres default) | prevented | possible | possible |
| **Repeatable Read** | prevented | prevented | possible (prevented in Postgres) |
| **Serializable** | prevented | prevented | prevented |

### Read Committed — default in Postgres
- Each statement sees a fresh snapshot (the latest committed data at statement start).
- Another transaction committing mid-transaction **is visible to your next statement** → non-repeatable reads possible.
- This is the sane default for most apps.

### Repeatable Read
- The transaction takes a **snapshot at BEGIN**; every statement sees the same snapshot.
- Reads are stable — non-repeatable and phantom reads gone (in Postgres).
- Writes still conflict: if two transactions update the same row, one blocks, then the loser gets a **serialization error** on commit.

### Serializable
- Strongest — transactions behave as if executed one after another.
- Postgres implements via **Serializable Snapshot Isolation (SSI)** — detects read/write cycles.
- Cost: more aborts under contention; retry on `40001` errors.

### Read Uncommitted
- In Postgres, behaves the same as Read Committed (Postgres never allows dirty reads). In MySQL it can show dirty data.

---

## How Postgres implements it: MVCC
- **Multi-Version Concurrency Control** — each row has multiple versions (tuples).
- Writers don't block readers, readers don't block writers (they see the old version).
- Each version carries `xmin`/`xmax` (transaction IDs that created/deleted it) → the snapshot decides which version is visible.
- Old versions accumulate until `VACUUM` reclaims them → **bloat** (see postgresql-internals.md).

## MySQL (InnoDB) difference
- InnoDB also uses MVCC; **Repeatable Read is the default** (unlike Postgres).
- Uses **gap locks** to prevent phantoms → more lock contention / deadlock potential.
- At `SERIALIZABLE`, InnoDB converts plain `SELECT`s to `SELECT ... FOR SHARE` (locks read rows).

---

## Practical guidance
- Default **Read Committed** is right for almost all app work — don't reach for stronger levels as a habit.
- Only need Repeatable Read / Serializable when a report or decision must be **self-consistent across multiple queries**.
- Serializable requires a **retry loop** — be ready to handle `SQLSTATE 40001` serialization failures.
- Long transactions = long-held locks + bloat → keep them short.
- Set a statement/transaction timeout in production to avoid stuck transactions.

```sql
-- inspect current isolation level (Postgres)
SHOW transaction_isolation;
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;
```

## Practice ideas
- Open two `psql`/DB clients, run `BEGIN` in both, and reproduce each anomaly at each isolation level.
- Write the classic bank-transfer and show: dirty read at Read Uncommitted (MySQL), non-repeatable at Read Committed, then fix with Repeatable Read.
- Test the Postgres "abort on conflict" behavior when two transactions update the same row at Repeatable Read.
