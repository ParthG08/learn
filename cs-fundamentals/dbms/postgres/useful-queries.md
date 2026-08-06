# PostgreSQL Useful Queries — Schema Introspection & Monitoring

A reference set of queries to keep at all times: schema introspection (via `information_schema` + `pg_catalog`) and database monitoring (via `pg_stat_*`). Replace `your_table`, `lead_id`, etc. with your actual names.

## Schema Introspection

### 1. List all columns in a table (with data types)

```sql
SELECT
    ordinal_position,
    column_name,
    data_type,
    is_nullable,
    column_default
FROM information_schema.columns
WHERE table_schema = 'public'
  AND table_name = 'your_table'
ORDER BY ordinal_position;
```

### 2. Find indexes on a table

```sql
SELECT
    indexname,
    indexdef
FROM pg_indexes
WHERE schemaname = 'public'
  AND tablename = 'your_table';
```

### 3. Find detailed index information

```sql
SELECT
    i.relname AS index_name,
    a.attname AS column_name,
    ix.indisunique,
    ix.indisprimary,
    am.amname AS index_type
FROM
    pg_class t,
    pg_class i,
    pg_index ix,
    pg_attribute a,
    pg_am am
WHERE
    t.oid = ix.indrelid
    AND i.oid = ix.indexrelid
    AND a.attrelid = t.oid
    AND a.attnum = ANY(ix.indkey)
    AND i.relam = am.oid
    AND t.relname = 'your_table'
ORDER BY
    index_name;
```

### 4. Find which table contains a column

```sql
SELECT
    table_name,
    column_name
FROM information_schema.columns
WHERE table_schema = 'public'
  AND column_name = 'lead_id';
```

### 5. Find a column by partial name

```sql
SELECT
    table_name,
    column_name
FROM information_schema.columns
WHERE table_schema = 'public'
  AND column_name ILIKE '%lead%';
```

### 6. Find tables by partial name

```sql
SELECT table_name
FROM information_schema.tables
WHERE table_schema = 'public'
  AND table_name ILIKE '%lead%';
```

### 7. Show primary key of a table

```sql
SELECT
    kc.column_name
FROM information_schema.table_constraints tc
JOIN information_schema.key_column_usage kc
ON tc.constraint_name = kc.constraint_name
WHERE tc.constraint_type = 'PRIMARY KEY'
AND tc.table_name = 'your_table';
```

### 8. Show foreign keys of a table

```sql
SELECT
    tc.constraint_name,
    kcu.column_name,
    ccu.table_name AS foreign_table,
    ccu.column_name AS foreign_column
FROM information_schema.table_constraints tc
JOIN information_schema.key_column_usage kcu
ON tc.constraint_name = kcu.constraint_name
JOIN information_schema.constraint_column_usage ccu
ON ccu.constraint_name = tc.constraint_name
WHERE tc.constraint_type = 'FOREIGN KEY'
AND tc.table_name = 'your_table';
```

### 9. Show all constraints

```sql
SELECT
    constraint_name,
    constraint_type
FROM information_schema.table_constraints
WHERE table_name = 'your_table';
```

### 10. Find every foreign key referencing a table

```sql
SELECT
    tc.table_name,
    kcu.column_name,
    ccu.table_name AS referenced_table,
    ccu.column_name AS referenced_column
FROM information_schema.table_constraints tc
JOIN information_schema.key_column_usage kcu
ON tc.constraint_name = kcu.constraint_name
JOIN information_schema.constraint_column_usage ccu
ON tc.constraint_name = ccu.constraint_name
WHERE tc.constraint_type = 'FOREIGN KEY'
AND ccu.table_name = 'your_table';
```

### 11. List all tables

```sql
SELECT table_name
FROM information_schema.tables
WHERE table_schema = 'public'
ORDER BY table_name;
```

### 12. Show estimated row counts

```sql
SELECT
    relname AS table_name,
    pg_size_pretty(pg_total_relation_size(relid)) AS total_size
FROM pg_catalog.pg_statio_user_tables
ORDER BY pg_total_relation_size(relid) DESC;
```

### 13. Find views

```sql
SELECT table_name
FROM information_schema.views
WHERE table_schema = 'public';
```

### 14. Find functions

```sql
SELECT
    routine_name,
    routine_type
FROM information_schema.routines
WHERE routine_schema = 'public';
```

### 15. Show view DDL

```sql
SELECT pg_get_viewdef('your_view'::regclass, true);
```

### 16. Find enum types

```sql
SELECT
    t.typname,
    e.enumlabel
FROM pg_type t
JOIN pg_enum e
ON t.oid = e.enumtypid
ORDER BY t.typname, e.enumsortorder;
```

### 17. Find triggers

```sql
SELECT
    trigger_name,
    event_manipulation,
    action_timing
FROM information_schema.triggers
WHERE event_object_table = 'your_table';
```

### 18. Find sequences

```sql
SELECT sequence_name
FROM information_schema.sequences
WHERE sequence_schema = 'public';
```

### 19. Search everything (table + column)

```sql
SELECT
    table_name,
    column_name,
    data_type
FROM information_schema.columns
WHERE table_schema = 'public'
AND (
    table_name ILIKE '%lead%'
    OR column_name ILIKE '%lead%'
)
ORDER BY table_name;
```

### 20. Show all schemas

```sql
SELECT schema_name
FROM information_schema.schemata;
```

### 21. Show all user-defined indexes in the database

```sql
SELECT
    schemaname,
    tablename,
    indexname,
    indexdef
FROM pg_indexes
WHERE schemaname NOT IN ('pg_catalog', 'information_schema')
ORDER BY tablename, indexname;
```

### 22. Find columns using a specific data type

```sql
SELECT
    table_name,
    column_name
FROM information_schema.columns
WHERE data_type = 'uuid';
```

### 23. Find nullable columns

```sql
SELECT
    table_name,
    column_name
FROM information_schema.columns
WHERE is_nullable = 'YES';
```

### 24. Find columns with default values

```sql
SELECT
    table_name,
    column_name,
    column_default
FROM information_schema.columns
WHERE column_default IS NOT NULL;
```

## Monitoring

### 25. Check the number of connections

```sql
SELECT COUNT(*) AS total_connections
FROM pg_stat_activity;
```

### 26. Check connections by state

```sql
SELECT
    state,
    COUNT(*) AS connections
FROM pg_stat_activity
GROUP BY state
ORDER BY connections DESC;
```

### 27. Check connections by application

```sql
SELECT
    application_name,
    COUNT(*) AS connections
FROM pg_stat_activity
GROUP BY application_name
ORDER BY connections DESC;
```

### 28. Check connections by database user

```sql
SELECT
    usename,
    COUNT(*) AS connections
FROM pg_stat_activity
GROUP BY usename
ORDER BY connections DESC;
```

### 29. Check connections by client IP

```sql
SELECT
    client_addr,
    COUNT(*) AS connections
FROM pg_stat_activity
GROUP BY client_addr
ORDER BY connections DESC;
```

### 30. Show active queries

```sql
SELECT
    pid,
    usename,
    application_name,
    state,
    NOW() - query_start AS duration,
    query
FROM pg_stat_activity
WHERE state = 'active'
ORDER BY duration DESC;
```

### 31. Show long-running transactions

```sql
SELECT
    pid,
    usename,
    application_name,
    state,
    NOW() - xact_start AS transaction_duration,
    query
FROM pg_stat_activity
WHERE xact_start IS NOT NULL
ORDER BY transaction_duration DESC;
```

### 32. Show idle-in-transaction sessions

```sql
SELECT
    pid,
    usename,
    application_name,
    NOW() - xact_start AS idle_duration,
    query
FROM pg_stat_activity
WHERE state = 'idle in transaction'
ORDER BY idle_duration DESC;
```

### 33. Show blocking queries

```sql
SELECT
    blocked.pid AS blocked_pid,
    blocked.query AS blocked_query,
    blocking.pid AS blocking_pid,
    blocking.query AS blocking_query
FROM pg_stat_activity blocked
JOIN pg_stat_activity blocking
ON blocking.pid = ANY(pg_blocking_pids(blocked.pid));
```

### 34. Show current locks

```sql
SELECT
    locktype,
    mode,
    granted,
    COUNT(*) AS count
FROM pg_locks
GROUP BY locktype, mode, granted
ORDER BY count DESC;
```

### 35. Show database size

```sql
SELECT
    pg_size_pretty(pg_database_size(current_database())) AS database_size;
```

### 36. Show largest tables

```sql
SELECT
    schemaname,
    relname AS table_name,
    pg_size_pretty(pg_total_relation_size(relid)) AS total_size
FROM pg_catalog.pg_statio_user_tables
ORDER BY pg_total_relation_size(relid) DESC
LIMIT 20;
```

### 37. Show cache hit ratio

```sql
SELECT
    ROUND(
        SUM(blks_hit) * 100.0 /
        NULLIF(SUM(blks_hit) + SUM(blks_read), 0),
        2
    ) AS cache_hit_ratio
FROM pg_stat_database;
```

### 38. Show tables with the most dead tuples

```sql
SELECT
    relname AS table_name,
    n_live_tup,
    n_dead_tup
FROM pg_stat_user_tables
ORDER BY n_dead_tup DESC
LIMIT 20;
```

### 39. Show tables with the most sequential scans

```sql
SELECT
    relname AS table_name,
    seq_scan,
    idx_scan
FROM pg_stat_user_tables
ORDER BY seq_scan DESC
LIMIT 20;
```

### 40. Show index usage

```sql
SELECT
    relname AS table_name,
    idx_scan
FROM pg_stat_user_tables
ORDER BY idx_scan DESC
LIMIT 20;
```

### 41. Check connection limit usage

```sql
SELECT
    COUNT(*) AS current_connections,
    current_setting('max_connections')::INT AS max_connections,
    ROUND(
        COUNT(*) * 100.0 /
        current_setting('max_connections')::INT,
        2
    ) AS percent_used
FROM pg_stat_activity;
```

### 42. Show slowest queries (requires `pg_stat_statements`)

```sql
SELECT
    calls,
    ROUND(mean_exec_time::NUMERIC, 2) AS avg_execution_ms,
    ROUND(total_exec_time::NUMERIC, 2) AS total_execution_ms,
    query
FROM pg_stat_statements
ORDER BY mean_exec_time DESC
LIMIT 20;
```

### 43. Show most frequently executed queries (requires `pg_stat_statements`)

```sql
SELECT
    calls,
    query
FROM pg_stat_statements
ORDER BY calls DESC
LIMIT 20;
```

### 44. Show queries with the highest total execution time (requires `pg_stat_statements`)

```sql
SELECT
    calls,
    ROUND(total_exec_time::NUMERIC, 2) AS total_execution_ms,
    query
FROM pg_stat_statements
ORDER BY total_exec_time DESC
LIMIT 20;
```
