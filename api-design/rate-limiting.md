# Rate Limiting

## What & why
Rate limiting caps how many requests a client can make in a time window. Protects the service from abuse, runaway clients, and accidental thundering herds; ensures fair usage and cost control.

- **Per client**: by IP, API key, user id, or a combination.
- **Limit shape**: e.g. `100 req/min`, `1000 req/hour`, `5 req/sec`.

## Where to apply
- **API gateway / edge** (first line) — see api-gateway.md.
- **Application layer** (per-user business rules, e.g. 5 login attempts / 10 posts / hour).
- **DB / infra** as backstop for the truly critical paths.

## The two dominant algorithms

### 1. Token bucket
```
capacity = max burst (bucket size), refill_rate = tokens added per second
```
- Every request takes a token; bucket refills continuously up to capacity.
- **Bursts allowed** up to bucket size; sustained rate limited by refill.

```
bucket  ──▶ allowed = tokens > 0
            tokens-- ; refill at rate r/s up to capacity c
```
- Simple, memory-light (store `tokens` + `last_refill_timestamp`), smooths bursts.
- **Most common choice.**

### 2. Sliding window log / counter
- **Sliding window log:** timestamp each request; a request is allowed if the count of timestamps in `[now - window, now]` < limit. Exact but memory-heavy (all timestamps).
- **Sliding window counter (approximation):** counts per fixed sub-window (e.g. 1-min blocks) and interpolates the overlap between two blocks — memory-light and accurate enough. Widely used (Redis-based).

### Others (know the names)
- **Fixed window:** count per fixed bucket (e.g. every minute). Simple but allows 2× bursts at bucket boundaries (59 req at 0:59 + 59 at 1:00).
- **Leaky bucket:** requests drip out at a fixed rate — smooths bursts (shapes traffic), but rejects when full; good for shaping.

---

## Redis implementations

### Fixed window (INCR + EXPIRE)
```
INCR rate:{client}:{minute_bucket}
EXPIRE rate:{client}:{minute_bucket} 60
if count > limit → 429
```

### Sliding window counter (two buckets + interpolation)
```
current = INCR rate:{client}:{cur_minute}
prev    = GET  rate:{client}:{prev_minute}
weight  = (now - start_of_cur_minute) / 60
estimate = current + prev * (1 - weight)
if estimate > limit → 429
```

### Token bucket in Redis (Lua script — atomic)
```lua
local key = KEYS[1]
local capacity = tonumber(ARGV[1])   -- bucket size
local refill   = tonumber(ARGV[2])   -- tokens per second
local now      = tonumber(ARGV[3])

local tokens  = tonumber(redis.call('GET', key) or capacity)
local last    = tonumber(redis.call('GET', key .. ':ts') or now)

tokens = math.min(capacity, tokens + (now - last) * refill)
redis.call('SET', key .. ':ts', now)

if tokens < 1 then
  redis.call('SET', key, 0, 'EX', 60)
  return 0                      -- limited
end
redis.call('SET', key, tokens - 1, 'EX', 60)
return 1                        -- allowed
```

---

## HTTP semantics & client signaling

### 429 Too Many Requests
- When limited, return **`429`** with:
```http
Retry-After: 60        # seconds until the client should retry
X-RateLimit-Limit: 100
X-RateLimit-Remaining: 0
X-RateLimit-Reset: 1755385200   # epoch when the window resets
```

### Retry-After
- The single most important header — lets well-behaved clients back off instead of hammering.
- Could be seconds (integer) or an HTTP-date.

---

## Design decisions

1. **Granularity** — per-IP (cheap, but shared NAT hurts innocent users), per-user (fair), per-API-key (works across IPs, supports tiers). Often combined.
2. **Tiers** — free: `10/min`; paid: `1000/min`. Enforced by the same mechanism, different limits.
3. **Storage** — in-memory (single instance), **Redis** (shared across instances — required for horizontal scaling), or in a gateway.
4. **Atomicity** — check-and-increment must be atomic (Redis Lua / INCR) or you'll let bursts through under concurrency.
5. **Graceful limiting** — consider soft limits (warn via headers) before hard 429.
6. **Distributed systems caveat** — per-instance counters are wrong once you scale; Redis counters fix it, but Redis itself can be a bottleneck → shard keys by client.

---

## Common patterns
- **Login rate limit** (prevent brute force): `5 failed attempts / 15 min`, lockout on exceed.
- **Public API quotas** per key with tiers.
- **Webhook/outbound** rate limit per target domain (slow downstream systems).
- **Per-endpoint vs global** — often both: global safety net + per-endpoint limits.

---

## Practice ideas
- Implement a token bucket in Redis via a Lua script and test burst vs sustained limits with `redis-cli` or a script.
- Set up rate limiting in a gateway (Traefik/Kong) and confirm 429 + Retry-After headers.
- Write a small load-test loop (10 parallel requests) to confirm atomicity (no over-admission).
- Compare fixed-window vs sliding-window behavior at a bucket boundary.
