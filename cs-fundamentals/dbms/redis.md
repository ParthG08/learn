# Redis

## What Redis is
- In-memory key-value data store — single-threaded command execution (fast, no race on simple ops).
- Used for: caching, rate limiting, leaderboards, queues, session storage, pub/sub, distributed locks.
- Latency in microseconds; data lives in RAM, durability via snapshots/AOF (optional).

## Data structures & when to use them

| Type | Example | Use case |
|---|---|---|
| **String** | `SET user:1:name "parth"` | Caching, counters, sessions, rate-limit tokens |
| **Hash** | `HSET user:1 name parth age 30` | Objects/entities — better than one string per field |
| **List** | `LPUSH queue ...` `BRPOP queue 0` | Simple queues, message buffers, timelines |
| **Set** | `SADD tags:x "a"` | Uniqueness, membership, intersections (tags, likes) |
| **Sorted Set (ZSET)** | `ZADD scores 100 "alice"` | Leaderboards, ranking, "score range" queries |
| **Bitmap** | `SETBIT` | Presence tracking (daily active users), efficient flags |
| **HyperLogLog** | `PFADD` | Approximate unique counts (memory-cheap) |
| **Stream** | `XADD`, `XREADGROUP` | Event log / message queue with consumer groups |

### Strings
```bash
SET key value [EX 60 | PX 60000 | NX | XX]
GET key
INCR counter          # atomic increment
SETEX key 60 value    # set + expire in one call
```
- `INCR`/`DECR` are atomic — perfect for counters without race conditions.

### Hashes
```bash
HSET user:1 name "parth" email "p@x.com"
HGETALL user:1
HINCRBY user:1 visits 1
```

### Lists
```bash
LPUSH queue job:1      # push
BRPOP queue 0          # blocking pop (waits for item) — job workers
LRANGE timeline 0 99   # paging
```

### Sorted sets
```bash
ZADD leaderboard 1200 "alice" 950 "bob"
ZREVRANGE leaderboard 0 9      # top 10
ZRANGEBYSCORE ... 500 1000     # range by score
ZINCRBY leaderboard 100 "alice"
```

### Sets
```bash
SADD tags:python "flask"
SISMEMBER tags:python "flask"
SINTER tag:a tag:b   # intersection → common items
```

### Streams
```bash
XADD events '*' type order-created order_id 42
XGROUP CREATE events workers 0
XREADGROUP GROUP workers c1 COUNT 10 STREAMS events '>'
XACK events workers id
```

---

## Caching patterns

### Cache-aside (read-through by app)
```
GET key → miss → read DB → SET key (with TTL) → return
```
- On write: invalidate (`DEL key`) rather than updating cache — avoids stale-data races.

### Write-through
- Write to cache AND DB together. Cache always fresh, but adds latency to every write.

### Write-behind
- Write to cache, async flush to DB. Fast, but risk of data loss on crash.

### Cache stampede / thundering herd
- 1000 requests miss simultaneously → all hit DB. Fix: **single-flight / request coalescing**, or **stale-while-revalidate** (serve old value while refreshing).

### TTL strategy
- Every cached key needs a TTL — no TTL = stale data forever + memory leak.
- Add small **jitter** to TTL so keys don't expire in a herd at the same instant.

---

## Eviction policies (`maxmemory-policy`)
When memory is full, Redis evicts per policy:

| Policy | Behavior |
|---|---|
| `noeviction` | Errors on writes (default) |
| `allkeys-lru` | Evict least-recently-used from ALL keys |
| `volatile-lru` | LRU among keys **with TTL** |
| `allkeys-lfu` | Least-frequently-used (fits "hot" workloads) |
| `allkeys-random` | Random eviction |
| `volatile-ttl` | Evict the key with the soonest expiry |

- `LRU` suits generic caches; `LFU` suits skewed/zipf workloads.

---

## Persistence: RDB vs AOF

| | **RDB (snapshot)** | **AOF (append-only file)** |
|---|---|---|
| What | Point-in-time binary dump | Every write command appended to a log |
| Speed | Faster (bulk) | Slower per-write (can batch with `appendfsync everysec`) |
| Data loss | Up to the last snapshot (can lose recent writes) | At most 1s (with everysec); 0 with always |
| File size | Compact | Larger (rewrite/compact periodically) |
| When | Default; great for restarts, backups | When you can't afford RDB's data loss window |
| Recovery | Fast | Slower (replays commands) |

- **Best practice:** RDB for backups + AOF for durability; or use Redis as a pure cache (no persistence) if loss is fine.
- `BGSAVE` forks and snapshots without blocking the main thread.

---

## Redis Cluster basics
- Shards keys across **hash slots** (0–16383). `HASH SLOT = CRC16(key) % 16384`.
- Each shard = a master + replicas. Master failure → replica promoted (failover).
- Client must handle `MOVED`/`ASK` redirects — keys live on different nodes.
- **Multi-key operations only work if keys land in the same slot** — use hash tags `{user:42}:cart`, `{user:42}:orders` to co-locate.
- Cross-slot transactions/commands fail — a common gotcha when going from single Redis to Cluster.

## Pub/Sub
```bash
SUBSCRIBE channel
PUBLISH channel "message"
```
- Fire-and-forget, no persistence, no replay. For real queuing use Streams/Lists.

## Distributed locks (Redlock caveat)
- `SET lock:key token NX PX 30000` — acquire only if not exists, expires in 30s.
- Release must verify the token (own lock) — use a Lua script to check-and-del atomically.
- Redlock (multi-instance) is controversial (Martin Kleppmann vs. antirez) — for most apps a single-instance lock with TTL + fencing tokens is enough.

---

## Scan (don't use KEYS in prod)
```bash
KEYS user:*      # BLOCKS the single-threaded server — dangerous
SCAN 0 MATCH user:* COUNT 100   # cursor-based, non-blocking
```

---

## Practice ideas
- Use the **official Try Redis** (try.redis.io) to drill every data structure's commands.
- Run a local `redis-server` + `redis-cli MONITOR` to watch commands.
- Build: a leaderboard with ZADD/ZREVRANGE; a job queue with BRPOP; rate limiting with INCR+EXPIRE.
- Deliberately trigger eviction (tiny maxmemory) and observe each policy.
