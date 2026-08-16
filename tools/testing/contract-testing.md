# Contract Testing (Pact) — P2

## The problem contract testing solves
Two services (consumer + provider) communicate over an API. Each team tests against its **own assumptions** of the contract → they drift → integration fails only in production.

Contract testing pins the **contract itself** between consumer and provider, so drift is caught in CI before deploy.

## Core idea
- **Consumer** (the caller) records a **contract** = "the requests I make + the responses I expect."
- **Provider** (the API) runs the provider side of each recorded interaction and verifies it can satisfy it.
- Any change that breaks the contract fails **provider CI** → the owning team fixes it before shipping.

## The two roles
| Role | What they produce/do |
|---|---|
| **Consumer** | Generates **Pact file(s)** from its test run — captures real request/response pairs |
| **Provider** | Runs the Pact file against its own test instances — verifies each interaction is satisfiable |

## How Pact works (walk-through)
```
1. Consumer writes an integration-ish test that calls a mocked provider
   → Pact records the exact interaction (request + expected response).
2. Consumer CI publishes the Pact file to a Pact Broker.
3. Provider CI pulls the Pact file for its service and runs `pact verify`
   → spins up its API and replays each recorded request, checking responses match.
4. If mismatched → provider test fails with a clear contract diff.
```

```javascript
// Consumer test (JS / pact-js)
const provider = new Pact({ consumer: 'OrderWeb', provider: 'OrderService' });

await provider.addInteraction({
  state: 'order exists',
  uponReceiving: 'a request for order 1',
  withRequest: { method: 'GET', path: '/orders/1' },
  willRespondWith: {
    status: 200,
    body: { id: 1, status: 'paid' }
  }
});
// ... run the app code that calls GET /orders/1 → Pact records the interaction
```

```ruby
# Provider verification (Ruby / pact-ruby or other)
Pact.service_provider "OrderService" do
  honours_pact_with "OrderWeb" do
    pact_uri ".../pacts/provider/OrderService/consumer/OrderWeb"
  end
end
```

## Key concepts
- **Provider states** — the contract can declare preconditions ("order exists", "order not found"); provider verification sets up that state before each interaction.
- **Pact Broker** — central storage for pact files + version compatibility matrix ("which provider versions satisfy which consumer versions").
- **`can-i-deploy`** — broker command that checks whether it's safe to deploy a version given contract compatibility (deployment gate).

## Language/tooling
| Tool | Notes |
|---|---|
| **Pact** | The standard — pact-js, pact-python, pact-jvm, pact-go |
| **Spring Cloud Contract** | Java/Spring native, generates stubs from Groovy DSL |
| **Schemathesis / Dredd** | Spec-driven testing (different philosophy — validate implementation against OpenAPI) |

## When to use contract testing
- **Service-to-service boundaries you own on both sides** (microservices).
- **Internal APIs with separate teams** — contract = shared interface agreement.
- **Consumer-driven change** — when the consumer needs a new field, they write the contract first, provider verifies/supports it, safe deploy.

### When NOT to bother
- Small monolith — integration tests suffice.
- Public/external APIs you don't control — use OpenAPI + spec compliance instead.
- Prototypes — contract ceremony is overhead until the API is stable.

## Contract testing vs integration tests (Testcontainers)
- **Integration tests** verify your app works against a real dependency (local DB/broker).
- **Contract tests** verify the *agreement* between two independently-deployed services — you don't need both services running, just their contracts.

## FDE relevance
- Client integrations (their API vs your adapter) benefit from a **consumer-style contract** on your side: you pin your assumptions about the client's API and get alerted when the client changes it.
- Combined with defensive parsing / schema-drift handling (see enterprise integration notes) it turns "client broke us silently" into "contract mismatch caught in CI."

---

## Practice ideas
- Set up a consumer (your web app) + provider (your API) with Pact in any language; publish to a local Pact Broker (docker) and verify.
- Break the contract on the provider (change a field type) → run provider verification → observe the failing diff.
- Add `can-i-deploy` to the deploy step and confirm it blocks an incompatible deploy.
