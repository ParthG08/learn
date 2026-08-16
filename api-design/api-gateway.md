# API Gateway

## What it is
A gateway is a **single entry point** in front of your services that handles cross-cutting concerns so individual services don't each reinvent them.

```
clients ──▶ API GATEWAY ──▶ service A
                    │──▶ service B
                    │──▶ service C
```

## Gateway vs. direct client-to-service

| Concern | Direct | Gateway |
|---|---|---|
| Client complexity | Client must know every service + handle auth/retries itself | One URL, one auth path |
| Cross-cutting logic | Duplicated per service | Centralized once |
| Service exposure | Services exposed to the internet | Services hidden behind gateway |
| Routing | Client picks the service | Gateway routes by path |
| Failure handling | Each client must implement retries/circuit breaking | Centralized |
| Latency | Minimal (no hop) | +1 hop |
| Coupling | Client ↔ service versioning tightly coupled | Client ↔ gateway contract only |

- **When direct:** small internal/private services, latency-critical paths, no cross-cutting needs.
- **When gateway:** many services, mobile/web clients, auth/rate-limit/observability needed centrally, security boundary.

---

## Core gateway responsibilities

### 1. Routing
- Map public paths → internal services: `GET /orders` → order-service, `GET /products` → catalog-service.
- Path-based or host-based routing. Supports blue-green/canary by routing % of traffic.

### 2. Aggregation
- **Backend-for-frontend / API composition**: the gateway calls multiple services and merges responses into one payload for the client (fewer round-trips).
- Example: `GET /checkout-summary` = cart-service + pricing-service + inventory-service → one response.
- Trade-off: gateway becomes a choke point and can get fat — keep aggregation logic thin.

### 3. Authentication offloading
- Validate tokens (JWT/OAuth2) once at the gateway, pass verified identity (user id, scopes) to downstream services.
- Downstream services trust the gateway (mutual TLS or signed headers) and skip their own authn.
- Keeps auth logic in ONE place — consistent and easy to update.

### 4. Rate limiting
- Enforce per-client limits at the edge before requests hit services (see rate-limiting.md).
- Token bucket / sliding window, keyed by IP, API key, or user.

### 5. Other common concerns
- **TLS termination** — decrypt once at the edge.
- **Request/response transformation** — protocol translation, header injection.
- **Caching** — cache common GET responses.
- **Observability** — request logging, tracing (correlation IDs), metrics for every call.
- **Circuit breaking / retries** — protect downstream services.
- **CORS** handling for web clients.
- **WebSocket / gRPC passthrough** when needed.

---

## Popular gateway implementations

| Tool | Type | Notes |
|---|---|---|
| **Kong** | Standalone (Nginx-based) | Plugin ecosystem, DB-backed, self-hosted |
| **Traefik** | Standalone | K8s-native, auto-discovers services, modern config |
| **NGINX** | Reverse proxy | Rock solid, config-file based, widely used |
| **Envoy** | Data-plane proxy | High perf, the core of service meshes (Istio uses it) |
| **AWS API Gateway** | Managed cloud | Serverless integrations, auth, throttling built-in |
| **Azure API Management / GCP Apigee** | Managed cloud | Enterprise governance, developer portals |

---

## Gateway + service mesh (advanced note)
- A **service mesh** (Istio/Linkerd) moves L4/L7 concerns *between* services (mTLS, retries, traffic shaping) — complementary to an edge gateway.
- Edge gateway = outside-in; mesh = inside (service-to-service).

---

## Design considerations
1. **Keep it thin** — don't let business logic creep into the gateway; it's a routing/protection layer, not a service.
2. **Gateway failure = everything fails** — deploy redundant replicas, keep gateway logic stateless, monitor it first.
3. **Aggregation coupling** — aggregation makes services depend on gateway behavior; document it.
4. **Request size/timeouts** — set limits so one client can't overwhelm downstream.
5. **Versioning** — route `/v1/*` and `/v2/*` to different deployments cleanly at the gateway (see versioning.md).

---

## Practice ideas
- Run a gateway (Traefik or NGINX or Kong) in front of two local demo services; verify routing + path rewriting.
- Add a JWT check plugin/middleware at the gateway and confirm requests without tokens are rejected before reaching the service.
- Configure rate limiting at the gateway and observe 429s.
- Set up a compose file with gateway + 2 services and test aggregation of two endpoints into one response.
