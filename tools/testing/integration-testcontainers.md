# Integration Tests (Testcontainers)

## What integration tests are
Tests that exercise **multiple real components together** — your app against a real (or realistic) database, cache, message broker, or external service. They catch what unit tests can't: SQL syntax, schema mismatches, connection handling, ORM quirks, contract drift.

## Unit vs integration (the boundary)
| | Unit | Integration |
|---|---|---|
| Scope | One unit, deps faked | App + real infra |
| Speed | ms | seconds |
| Flakiness | low | higher (real deps) |
| Catches | Logic bugs | Wiring / contract bugs |
| Dependencies | none | DB, Redis, Kafka, etc. |

- Both are needed — this is the middle of the test pyramid (see test-pyramid.md).

---

## Testcontainers
A library that **spins up real Docker containers on-demand for your tests** and tears them down after. The DB/broker is the *real* thing, but isolated per test run.

- **The problem it solves:** "works on my machine" — tests always run against the exact dependency version in a container, no shared local installs, no state leakage.
- How it works: your test requests `PostgreSQLContainer("postgres:16")` → library pulls/starts the container → you get the connection URL → test runs → container is removed.

```java
// Java / JUnit 5
@Container
static PostgreSQLContainer<?> postgres = new PostgreSQLContainer<>("postgres:16");

@Test
void order_repository_round_trip() {
    String url = postgres.getJdbcUrl();
    // connect app to `url`, run a real INSERT + SELECT
}
```

```python
# Python / pytest + testcontainers
from testcontainers.postgres import PostgresContainer

def test_save_and_load():
    with PostgresContainer("postgres:16") as postgres:
        url = postgres.get_connection_url()
        # use url, run app code, assert
```

```go
// Go
func TestRepo(t *testing.T) {
    container, _ := postgres.RunContainer(ctx, testcontainers.WithImage("postgres:16"))
    // get DSN, connect, exercise
}
```

## Language/library support
| Language | Library |
|---|---|
| Java | `org.testcontainers:testcontainers` (JUnit 5 `@Container`) |
| Python | `testcontainers-python` (pytest fixtures) |
| JS/TS | `@testcontainers/*` (official, or Jest + Docker Compose) |
| Go | `testcontainers-go` |
| .NET | `Testcontainers` NuGet |

## Common containers used
- `PostgreSQLContainer`, `MySQLContainer`, `MongoDBContainer`, `RedisContainer`, `KafkaContainer`, `LocalStackContainer` (AWS mock), `RabbitMQContainer`.

---

## What to integration-test
1. **Repository / DAO layers** — real SQL: insert/update/delete, transactions, unique constraints, migrations.
2. **Migrations** — run your actual schema migrations against the container (catches bad SQL before deploy).
3. **Service + DB round-trips** — the flow a unit test stubbed, now against real infra.
4. **Message consumers** — consume from a real Kafka/RabbitMQ container.
5. **HTTP endpoint + DB** — spin the real app, hit an endpoint, verify DB effects (a "vertical slice" integration test).

## Patterns & practices
- **One container per test class/suite** (start once, reuse) — starting a container per test is slow.
- **Clean state between tests** — truncate tables / recreate schema per test (or use transactions + rollback).
- **Use real migrations** — the container is where migration bugs surface.
- **Parallelism carefully** — multiple containers in parallel can exhaust CI resources; balance speed vs. stability.
- **CI needs Docker** — GitHub Actions/Runner has Docker; ensure the daemon is available.
- **Version-match production** — use the same image version as prod (postgres:16 not postgres:latest) to avoid surprise.

## Alternatives (know the trade-offs)
| Option | Pros | Cons |
|---|---|---|
| **Testcontainers** | Real dependency, isolated | Needs Docker in CI, slower |
| **Local dev DB** | Fast | Shared state, version drift |
| **SQLite in-memory** | Fast, no Docker | Different SQL semantics — false confidence |
| **H2 (Java)** | Fast, in-process | Also differs from real Postgres behavior |
| **Testcontainers for most, H2/SQLite only for trivial cases** — the mismatch between test-DB and prod-DB is a classic source of "works in tests, fails in prod." |

---

## Practice ideas
- Add Testcontainers to one project: a Postgres container + a repository integration test that runs your real migrations.
- Deliberately write SQL that works in SQLite but breaks in Postgres to see the value of real-DB testing.
- Containerize the test DB and run the suite twice — verify reproducibility.
- Add a Kafka container and test a consumer end-to-end.
