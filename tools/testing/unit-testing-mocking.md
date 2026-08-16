# Unit Tests + Mocking

## What a unit test is
Tests **one unit of code in isolation** (a function, class, or method), with all external dependencies (DB, HTTP calls, time, filesystem) replaced by fakes. Fast, deterministic, run thousands in seconds.

## The testing vocabulary
| Term | What |
|---|---|
| **Unit test** | Tests a single unit with dependencies stubbed out |
| **SUT** | System Under Test — the unit you're testing |
| **Test double** | Umbrella term: fakes used in place of real dependencies |
| **Stub** | Returns canned values; no logic |
| **Mock** | Records calls; asserts on interactions (did `save()` get called with X?) |
| **Fake** | Working lightweight implementation (e.g. in-memory repo) |
| **Spy** | Real object but records which calls were made |

## Example (Python)
```python
# cart.py
class CartService:
    def __init__(self, repo): self.repo = repo
    def add(self, user_id, item):
        cart = self.repo.get_or_create(user_id)
        cart.items.append(item)
        self.repo.save(cart)
        return cart

# test_cart.py
def test_add_item_appends_to_cart():
    repo = FakeCartRepo()          # fake: real in-memory behavior
    svc = CartService(repo)
    cart = svc.add(1, "widget")
    assert "widget" in cart.items
    assert repo.saved == [cart]

def test_add_calls_save(mocker):   # mock: assert interaction
    repo = mocker.Mock()
    repo.get_or_create.return_value = Cart()
    svc = CartService(repo)
    svc.add(1, "widget")
    repo.save.assert_called_once()
```

## Frameworks by language
| Language | Runner | Mocking |
|---|---|---|
| Java | JUnit 5 | Mockito, Mockito + AssertJ |
| Python | pytest | pytest-mock (wraps unittest.mock) |
| JavaScript/TS | Jest / Vitest | built-in jest.fn / vi.fn |
| Go | testing (stdlib) | no built-in mock — hand-written interfaces / testify/mock |

## Core mocking patterns

### 1. Mock a dependency via its interface
- **Go:** depend on interfaces, not concrete types → trivial to swap a mock at test time.
```go
type Repo interface { Save(c Cart) error }
// real: PostgresRepo; test: mockRepo
```

### 2. Arrange–Act–Assert (AAA)
```
Arrange: set up inputs + mocks' return values
Act:     call the SUT
Assert:  check outputs and/or interactions
```

### 3. Verify interactions, not implementation
- Assert on **observable behavior** (return value, side-effect) over internals.
- Only use interaction asserts (`save was called`) when the call is the point (e.g. "did we notify?").

### 4. Stub only what the test needs
- Don't wire every dependency fully; stub just the paths your test exercises.
- Don't stub the thing you're testing.

### 5. Control the clock
- Time-dependent logic needs an injectable clock (pass `now` in, or a `Clock` interface) so tests are deterministic.

## Test naming & structure conventions
```python
# name: test_<behavior>_when_<condition>_then_<outcome>
def test_returns_error_when_product_out_of_stock():
```
- One logical behavior per test.
- Use **parametrize/table-driven** to cover variants:
```python
@pytest.mark.parametrize("qty,expected", [(0,0),(3,30),(10,100)])
def test_price(qty, expected): ...
```
- Go: table tests with subtests:
```go
tests := []struct{ name string; in Cart; want error }{ ... }
for _, tt := range tests { t.Run(tt.name, func(t *testing.T) { ... }) }
```

## Common pitfalls
1. **Testing mocks, not behavior** — asserting on mocks' interactions more than outputs → brittle, no signal.
2. **Over-mocking** — mocking everything incl. the SUT's own logic; mock only the *boundary*.
3. **Brittle assertions** — exact string/order matching that breaks on refactor; prefer semantic checks.
4. **Testing implementation details** (private helpers) instead of public contract.
5. **Slow unit tests** — if a unit test hits a network/DB, it's not a unit test (move to integration).
6. **Assertion-less tests** — test runs, nothing fails ever → worthless.

## Quality signal: what a good suite gives
- Fails for a **real bug**, passes for correct code.
- Fast (<1s per test).
- Deterministic (no flakiness from order/time/random).
- Readable — a new dev understands the SUT's contract from tests.

## Practice ideas
- Pick a function with a DB + HTTP dependency in your codebase and write unit tests with mocks/fakes for: success, empty input, error from dependency, and retry behavior.
- Deliberately introduce a bug and confirm the test catches it; then add a test for the case you forgot.
- Refactor a test that currently hits the network to use a fake and measure the speedup.
