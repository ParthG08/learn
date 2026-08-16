# Test Pyramid

## The idea
Most tests should be **small, fast unit tests**; fewer **integration tests**; fewest **end-to-end (E2E)** tests. The pyramid shape exists because each layer is slower, more flaky, and more expensive than the one below it.

```
        /E2E\     few — slow, expensive, flaky
       /Inte\     some — real deps, medium
      /Unit\      many — fast, reliable, cheap
```

## Why the shape matters
| Layer | Speed | Reliability | What it catches |
|---|---|---|---|
| Unit | ms | very high | Logic errors, edge cases |
| Integration | seconds | high | Wiring, SQL, contracts with real deps |
| E2E | minutes | medium | The whole system working together (deployment, config, browser flows) |

**Core principle: don't over-invest in E2E.** If your suite is mostly slow E2E tests, you get a brittle, slow feedback loop and tests that fail for reasons unrelated to your code.

## The anti-pattern: inverted pyramid / ice cream cone
- Mostly E2E + a few unit tests → slow CI, flaky failures, long debugging.
- Usually caused by: skipping unit tests, testing everything through the UI, no seams for mocking.

---

## What goes in each layer

### Unit tests (base — the bulk, ~60-70%)
- Pure logic: services, helpers, validation, calculations, transformations.
- No I/O, no real dependencies. Milliseconds each.

### Integration tests (~20-30%)
- App + real DB/queue/cache (see integration-testcontainers.md).
- Repository + migrations, service ↔ DB round-trips, consumer → broker.
- Seconds each; one per key flow, not per edge case.

### E2E (~5-10%)
- The full stack: real app + infra + (often) a browser or real HTTP client driving a user flow.
- "Buy an item end-to-end": UI → API → DB → response.
- Prefer a **few happy-path E2E** that prove wiring, and cover the variants at lower layers.
- Use **smoke tests** in staging as a lighter E2E alternative.

## Trade-off to remember
- **Lower layers = better bug localization.** A failing unit test tells you the exact function; a failing E2E only tells you "the checkout broke somewhere."
- **Higher layers = more confidence the whole thing is wired.** You need enough E2E to trust the deployment, but not so many that CI crawls.

## Guiding questions
1. Can I catch this at the unit level? → write a unit test.
2. Does it need a real dependency (SQL syntax, broker)? → integration test.
3. Does it only matter as a full user flow (login → pay → confirm)? → one E2E, keep it minimal.

## Practical rules of thumb
- New logic → unit test first (it drives the design).
- Every repository/schema change → integration test (catches SQL drift).
- Keep E2E count low and focused on critical journeys.
- Track test **duration** — if the fast layer is slow, something's wrong (unit tests hitting the network, no mocking).
- CI should run unit+integration fast; E2E can be a separate, slower stage (or nightly/staged).

## The testing iceberg for FDE work
- Client integrations: unit-test transformation logic + integration-test against a **local/sandbox** of the external system (webhook fixtures, API mocks, Testcontainers of the client's stack).
- Contract tests (see contract-testing.md) protect the shared boundaries you can't fully control.

---

## Practice ideas
- Take a feature and write it the pyramid way: unit-test the business logic, integration-test the repo, one E2E smoke test of the main flow.
- Measure suite runtime per layer — confirm the pyramid ratio (most time in fewest tests is a red flag).
- Find an existing E2E-heavy suite and identify tests that belong at a lower layer.
