## Warm cache compare

The "**Stabilization**" Method
Instead of trying to find the "first run" time, you want to find the consistent time.

Warm up Query A: Run Query A (without EXPLAIN ANALYZE) 3–5 times. This ensures all relevant data pages are pulled into the database's shared buffers.
Measure Query A: Run **EXPLAIN ANALYZE** on Query A. Record the Execution Time.
Warm up Query B: Run Query B 3–5 times.
Measure Query B: Run **EXPLAIN ANALYZE** on Query B. Record the Execution Time.


##Why this works

By saturating the cache for both queries, you eliminate "**disk I/O jitter**." You are now comparing the CPU efficiency and memory-access logic of the two queries. If Query B is faster in a warm state, it’s because it’s fundamentally more efficient at processing the data structures.

## Key Metrics to Watch (Beyond Time)

Since timing can still fluctuate slightly based on CPU load, look at the Shared Hit Blocks in your EXPLAIN (**ANALYZE, BUFFERS**) output.

Run: EXPLAIN (ANALYZE, BUFFERS) YOUR_QUERY_HERE;

Look for: Buffers: shared hit=X

| Metric         | What it means                   | Better Result                                             |
| -------------- | ------------------------------ | -------------------------------------------------------- |
| Shared Hit     | Data found in RAM (Cache)       | Higher is fine, as long as total blocks are low.          |
| Shared Read    | Data read from Disk             | Lower is better (This is the heavy lifting).              |
| Shared Dirtied | Data modified in the cache      |                                                          |