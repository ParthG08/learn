# gRPC + Protocol Buffers

## What & why
- **gRPC** is a high-performance RPC framework (Google) over **HTTP/2**, using **Protocol Buffers (protobuf)** for serialization by default.
- Where REST = resources + verbs, gRPC = **calling a function on a service** with strongly-typed inputs/outputs.
- Ideal for **internal service-to-service** communication: faster, typed, streaming, bidirectional.

## Key characteristics
| | gRPC | REST/JSON |
|---|---|---|
| Transport | HTTP/2 | HTTP/1.1 |
| Encoding | Binary (protobuf) | Text (JSON) |
| Contract | `.proto` file (strong typing) | OpenAPI (optional) |
| Streaming | ✅ native (4 kinds) | manual (SSE/WebSocket) |
| Human-readable | ❌ (binary) | ✅ |
| Browser support | via gRPC-Web proxy | ✅ native |
| Best for | Internal services, real-time, high-throughput | Public APIs, browsers, simple clients |

---

## Protocol Buffers (`.proto`)
The contract definition — a message schema + RPC service.

```protobuf
syntax = "proto3";

package order.v1;

message Order {
  int64 id = 1;
  string customer_email = 2;
  double total = 3;
  OrderStatus status = 4;
}

enum OrderStatus {
  ORDER_STATUS_UNSPECIFIED = 0;
  ORDER_STATUS_PENDING = 1;
  ORDER_STATUS_PAID = 2;
}

service OrderService {
  rpc GetOrder(GetOrderRequest) returns (Order);
  rpc ListOrders(ListOrdersRequest) returns (stream Order);  // server streaming
  rpc CreateOrder(stream CreateOrderRequest) returns (Order); // client streaming
  rpc Chat(stream Message) returns (stream Message);          // bidi streaming
}
```

### Rules & conventions
- `syntax = "proto3";` — fields are optional by default; no required keyword.
- **Field numbers** (`= 1`) are the wire identity — once shipped, **never reuse/change a field number** (it's how older clients skip unknown fields). Add new fields with new numbers.
- Field numbers 1–15 take 1 byte → use them for hot fields.
- `string`, `int32/int64`, `bool`, `double`, `bytes`, `repeated` (arrays), `map<k,v>`, `enum`, nested messages, `oneof`.
- Naming: messages PascalCase, fields snake_case.
- Every enum should have an `_UNSPECIFIED = 0` first value (proto3 requires 0 first, and 0 is the default).

### Generating code
```bash
protoc --go_out=. --go-grpc_out=. order.proto
protoc --java_out=. --java-grpc_out=. order.proto
```
- Generates typed client + server interfaces in your language.

---

## gRPC call types
| Type | Description |
|---|---|
| **Unary** | Request → response (like a normal function call) |
| **Server streaming** | One request, stream of responses (log tail, progress) |
| **Client streaming** | Stream of requests, one response (upload, batch) |
| **Bidirectional streaming** | Both sides stream concurrently (chat, live collaboration) |

## Streaming vs polling
- gRPC streaming **replaces WebSocket/SSE patterns** for service-to-service and real-time cases.
- Lower latency, less overhead than repeated HTTP polls.

---

## Advanced concepts (know the names)
- **Interceptors** (middleware): auth, logging, metrics, retries on both client & server.
- **Deadlines** (client-side timeout): set `deadline` so a call fails after N seconds — critical, don't rely on defaults.
- **Metadata** — key-value headers for passing auth tokens, correlation IDs, etc.
- **gRPC-Web** — browser clients reach gRPC through a proxy (Envoy/gRPC-Web), since HTTP/2 trailers aren't directly accessible in browsers.
- **Health checks** — `grpc.health.v1.Health` standard service for load balancers.
- **Load balancing** — L7 (per-call) needed; the gateway/envoy/mesh handles it.
- **Error model** — rich status codes (`grpc-status: 5 NOT_FOUND`) + `google.rpc.Status` details.

## Common gRPC status codes
| Code | Number | Meaning |
|---|---|---|
| `OK` | 0 | Success |
| `INVALID_ARGUMENT` | 3 | Bad request |
| `NOT_FOUND` | 5 | Resource missing |
| `DEADLINE_EXCEEDED` | 4 | Call timed out |
| `UNAUTHENTICATED` | 16 | No/expired credentials |
| `PERMISSION_DENIED` | 7 | Authz failed |
| `RESOURCE_EXHAUSTED` | 8 | Rate limited / quota |
| `UNAVAILABLE` | 14 | Service down (retryable) |
| `INTERNAL` | 13 | Server bug |

---

## gRPC vs REST decision
```
Use gRPC:
- Internal service-to-service (microservices)
- High throughput / low latency
- Streaming or bidirectional patterns
- Strongly typed contract shared across teams

Use REST:
- Public/external APIs (browser, mobile, third parties)
- Simple CRUD, human-readable
- Ecosystem/tooling breadth (OpenAPI, SDKs)
```
- Many systems do both: **REST/gateway externally, gRPC internally** (a common, sane architecture).

---

## Practice ideas
- Write a `.proto` for a small service, generate code in Go/Python/Java, and call it from a client.
- Implement all four call types (unary + 3 streaming kinds) and observe latency vs a REST equivalent.
- Set a deadline on a call and a slow server to see `DEADLINE_EXCEEDED`.
- Use grpcurl (curl for gRPC) to hit a running service: `grpcurl -d '{"id": 1}' localhost:50051 order.v1.OrderService/GetOrder`.
