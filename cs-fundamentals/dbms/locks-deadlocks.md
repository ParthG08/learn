# Locks & Deadlocks

## Why locks exist
- Prevent concurrent transactions from corrupting data (see transactions-isolation.md).
- Locks are the *mechanism*; isolation levels are the *contract*.

## Lock granularity

| Level | Scope | Notes |
|---|---|---|
| **Row-level** | Single rows | InnoDB & Postgres default — high concurrency, most common |
| **Table-level** | Whole table | `LOCK TABLE`, or when many rows locked (DDL) |
| **Page** | Disk page of rows | Rarely exposed to users |
| **Database** | Whole DB | Migration tools |

---

## Row vs. table locks

### Row locks (in Postgres & InnoDB)
- Two flavors in Postgres: **tuple locks** (`SELECT ... FOR UPDATE`/`FOR SHARE`) and **MVCC** (writes).
- InnoDB also has: **shared (S)** and **exclusive (X)** row locks.
  - S lock: readers — multiple S can coexist.
  - X lock: writers — blocks other S and X.

| Lock type | Coexists with | Blocks |
|---|---|---|
| Shared (S) | S | X |
| Exclusive (X) | — | S, X |

### Table locks in Postgres
```
ACCESS SHARE   -- SELECT takes this (weakest)
ROW SHARE      -- SELECT FOR UPDATE
ROW EXCLUSIVE  -- INSERT/UPDATE/DELETE
SHARE UPDATE EXCLUSIVE  -- VACUUM (no concurrent changes)
SHARE          -- CREATE INDEX (concurrent)
SHARE ROW EXCLUSIVE
EXCLUSIVE      -- heavy writes
ACCESS EXCLUSIVE  -- DROP/TRUNCATE/ALTER (strongest — blocks everything)
```
- The lock-mode matrix decides compatibility; most app queries only need ACCESS SHARE / ROW EXCLUSIVE, which don't block each other.

---

## Locking reads

```sql
SELECT ... FOR UPDATE;     -- X lock on returned rows: "no one else modifies these until I commit"
SELECT ... FOR SHARE;      -- S lock: "no one modifies these; others may also read-lock"
SELECT ... FOR UPDATE SKIP LOCKED;  -- grab un-locked rows, skip the rest (job queues!)
```
Use cases:
- **Pessimistic concurrency**: reserving inventory, deducting balances.
- **Job queues**: `SKIP LOCKED` lets N workers split work without contending.
- Deadlock-prone with plain reads when you later update — prefer `FOR UPDATE` up front.

### Row lock queueing
- Locks are granted in FIFO-ish order; a waiting transaction blocks until the holder commits/rolls back.
- **Lock wait timeout** (`lock_timeout` in Postgres) aborts a waiter instead of hanging forever.

---

## Deadlocks

### Definition
Two or more transactions each hold a lock the other needs → circular wait → none can proceed.

```
T1: UPDATE accounts SET balance=... WHERE id=1;   -- locks row 1
T2: UPDATE accounts SET balance=... WHERE id=2;   -- locks row 2
T1: UPDATE accounts SET balance=... WHERE id=2;   -- waits for T2 (holds row 1)
T2: UPDATE accounts SET balance=... WHERE id=1;   -- waits for T1 (holds row 2)
-- DEADLOCK
```

### How the DB handles it
- The DB has a **deadlock detector** (Postgres: `deadlock_timeout`, default 1s).
- It **kills (aborts) one victim**, rolls back its transaction, and lets the other continue.
- The victim's app gets an error like:
  - Postgres: `ERROR: deadlock detected (SQLSTATE 40P01)`
  - MySQL: `ERROR 1213: Deadlock found when trying to get lock; try restarting transaction`
- **Retry the whole transaction** — the killed transaction is fully rolled back.

### Detection commands
```sql
-- Postgres
SELECT * FROM pg_stat_activity WHERE state = 'active';
SELECT pid, wait_event_type, wait_event FROM pg_stat_activity;  -- who's waiting
SELECT pg_blocking_pids(pid);   -- which PIDs block a given pid

-- MySQL / InnoDB
SHOW ENGINE INNODB STATUS;   -- contains LATEST DETECTED DEADLOCK
```

### How to prevent deadlocks
1. **Lock rows in a consistent order** — e.g. always UPDATE by ascending id (the single most effective fix for the bank-transfer pattern).
2. Keep transactions short — fewer locks held, less overlap.
3. Use a **single statement / single lock acquisition** where possible (one `UPDATE` touching all rows instead of multiple).
4. Avoid user interaction inside a transaction (no waiting on the app to type).
5. Use **atomic conditional updates** (`UPDATE ... SET qty = qty - 1 WHERE qty > 0`) instead of read-then-write.
6. Use `SKIP LOCKED` for queue workers so they never wait on each other.
7. If unavoidable, ensure a retry layer exists in the app.

---

## Detecting & resolving locks (operational)
1. Find the stuck query: `pg_stat_activity` where `state='active'` but `wait_event` is a lock wait (`lock/transaction` etc.).
2. Find the blocker: `pg_blocking_pids(pid)`.
3. Decide: let it finish (fast), or `pg_cancel_backend(pid)` / `pg_terminate_backend(pid)`.
4. Long-term fix: shorten the transaction, fix indexing (a missed index turns one-row locks into table-scans locking everything), or reduce concurrency.

---

## Practice ideas
- Open two DB clients, lock row 1 in one and row 2 in the other, then cross-update → trigger a real deadlock and read the error.
- Build a `SKIP LOCKED` worker-queue table and run 4 parallel workers to see no two grab the same row.
- Watch `pg_stat_activity` + `pg_blocking_pids` live while two connections block each other.
