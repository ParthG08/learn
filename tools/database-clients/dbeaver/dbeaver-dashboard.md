# DBeaver Dashboard Notes

## Does DBeaver Dashboard Run Queries?

Yes.

DBeaver dashboards are not free. To display metrics and charts, DBeaver periodically executes monitoring queries against the database.

The refresh frequency depends on the dashboard configuration and refresh interval settings.

---

## How DBeaver Dashboard Works

1. User opens the dashboard.
2. DBeaver executes monitoring queries.
3. Results are collected.
4. Charts and graphs are updated.
5. After the configured refresh interval, queries are executed again.
6. Process repeats while the dashboard remains active.

The dashboard essentially acts as a lightweight monitoring client.

---

## Common Metrics Collected

### PostgreSQL
- Active sessions
- Running queries
- Database activity
- Locks
- Transactions
- Database size

Common system views:
- `pg_stat_activity`
- `pg_stat_database`
- `pg_locks`

### MySQL
- Connections
- Query statistics
- Performance metrics

Common sources:
- `information_schema`
- `performance_schema`

### SQL Server
- Dynamic Management Views (DMVs)

### Oracle
- `V$` performance views

---

## Advantages

### Quick Visibility
Provides real-time visibility into database activity.

### Easier Troubleshooting
Useful for:
- Slow query investigations
- Connection spikes
- Lock contention
- Resource monitoring

### No Manual SQL Required
Most monitoring information is available without writing custom queries.

---

## Tradeoffs

### 1. Additional Database Load

Every dashboard refresh generates monitoring queries.

Impact is usually negligible on:
- Local development databases
- Small systems

Impact may be noticeable on:
- Large production systems
- High refresh frequencies
- Multiple users running dashboards simultaneously

---

### 2. Increased Network Traffic

Monitoring data must be transferred from the database server to the DBeaver client.

Usually small, but continuous.

---

### 3. Local Resource Usage

DBeaver consumes:
- CPU
- Memory
- Rendering resources

for storing and displaying charts.

---

### 4. Some Metrics Can Be Expensive

Cost varies by metric.

Cheap:
- Connection counts
- Active session counts

Moderate:
- Lock monitoring
- Transaction statistics

Potentially Expensive:
- Database size calculations
- Complex system aggregations

---

## Recommended Usage

### Development Environment
- Safe to keep dashboards open.
- Use refresh intervals of 10–30 seconds.

### Production Environment
- Use dashboards temporarily during investigations.
- Avoid very aggressive refresh intervals (e.g., 1 second).
- Do not leave dashboards running unnecessarily.

For long-term monitoring, dedicated monitoring stacks are preferred:
- Grafana
- Prometheus

---

## Rule of Thumb

A single DBeaver dashboard is rarely a problem.

The real concern occurs when:
- Many developers keep dashboards open
- Refresh intervals are very short
- The database is already under heavy load
