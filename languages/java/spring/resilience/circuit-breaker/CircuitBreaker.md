# CircuitBreaker

# Overview

```java
@CircuitBreaker(name = "user", fallbackMethod = "userAPIFallback")
```

This is the CicuitBreaker that is used in the

src/main/java/com/khatabook/loankhata/auth/AuthService.java

The **@CircuitBreaker** annotation is a mechanism from the **Resilience4j** library (imported on line 11)

```java
import io.github.resilience4j.circuitbreaker.annotation.CircuitBreaker;
```

that prevents a "*failure cascade*" when calling external services.

In short, it works like an electrical circuit breaker:

1. Closed State (Normal): Requests flow through to the external service (khatabook-backend in this case).

2. Open State (Failure): If the external service starts failing (e.g., timing out or returning 500s) above a certain threshold, the circuit "trips" or opens. For a specified period, all subsequent calls fail immediately without even trying to hit the external service.

Fallback: When the circuit is open (or if a call fails), it automatically redirects the execution to the fallbackMethod (defined here as **userAPIFallback** on lines 101-104).

```java
public AuthUser userAPIFallback(String param1, CallNotPermittedException e) {
    log.error("AUTH_SERVICE_CIRCUIT_BREAKER_TRIGGERED: " + param1, e);
    throw new InternalServer("AUTH_SERVICE_CIRCUIT_BREAKER_TRIGGERED: " + e.getMessage());
}
```

## Why use it in AuthService?

**Resilience**: It protects your service from hanging or crashing if the User Service is down or slow.

**Fast Fail**: Instead of waiting for a long timeout on every request when a downstream service is known to be down, it fails fast and executes the fallback logic.

**Graceful Degradation**: In userAPIFallback, you can return a cached value, a default response, or (as seen in line 103) a specific error message that informs the system the circuit is triggered.


