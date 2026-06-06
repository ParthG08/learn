# 2-Month Java & Spring Boot Master Plan

This 8-week schedule is designed to take you from core Java fundamentals to building production-ready Spring Boot applications. It prioritizes the skills most critical for a Forward Deployed Engineer (FDE) and backend roles.

---

## Month 1: Core Java, JVM & Concurrency
*Goal: Build an unshakeable foundation in the Java language, memory management, and multi-threading.*

### Week 1: Core Java & OOP Refresher
Focus on writing clean, idiomatic Java code.
* **Topics**:
  * Java 17+ Features (Records, Pattern Matching, Switch Expressions).
  * Advanced OOP (Interfaces vs. Abstract Classes, Composition over Inheritance).
  * Exception Handling (Checked vs. Unchecked, Custom Exceptions).
  * Enums and basic I/O.
* **Resources**:
  * 📖 *Book*: "Effective Java" by Joshua Bloch (Chapters 2, 4, 8).
  * 🌐 *Article*: [Java 17 Features (Baeldung)](https://www.baeldung.com/java-17-new-features)

### Week 2: Collections, Generics, and Functional Programming
Mastering how data is stored and manipulated in memory.
* **Topics**:
  * Collections Framework (`List`, `Set`, `Map` implementations and their time complexities).
  * Generics (Wildcards, Type Erasure).
  * Functional Interfaces, Lambdas, and the Stream API.
  * `Optional<T>` best practices.
* **Resources**:
  * 🌐 *Article*: [Guide to Java Streams (Baeldung)](https://www.baeldung.com/java-8-streams)
  * 🎥 *Video*: [Venkat Subramaniam: Core Design Principles for Software Developers](https://www.youtube.com/watch?v=llGgO74uXMI)

### Week 3: Concurrency & Multithreading
Crucial for backend performance.
* **Topics**:
  * Thread Lifecycle and synchronization (`synchronized`, `volatile`).
  * `java.util.concurrent` package (Thread Pools, `ExecutorService`, `CountDownLatch`, `ConcurrentHashMap`).
  * `CompletableFuture` for asynchronous programming.
  * Project Loom (Virtual Threads) basics in Java 21+.
* **Resources**:
  * 📖 *Book*: "Java Concurrency in Practice" (A bit old, but foundational concepts remain).
  * 🌐 *Article*: [Guide to java.util.concurrent (Baeldung)](https://www.baeldung.com/java-util-concurrent)
  * 🌐 *Article*: [Project Loom and Virtual Threads (Marco Behler)](https://www.marcobehler.com/guides/java-project-loom)

### Week 4: JVM Internals, Build Tools & Testing
Understanding what runs your code and how to build/test it.
* **Topics**:
  * JVM Memory Model (Heap, Stack, Metaspace).
  * Garbage Collection (G1GC vs ZGC).
  * Build Tools: Maven & Gradle (Lifecycles, Dependency Management).
  * Testing: JUnit 5, Mockito, AssertJ.
* **Resources**:
  * 🌐 *Article*: [JVM Architecture (Baeldung)](https://www.baeldung.com/jvm-architecture)
  * 🌐 *Guide*: [Maven Tutorial (Marco Behler)](https://www.marcobehler.com/guides/mvn-clean-install-a-short-guide-to-maven)

---

## Month 2: Spring Ecosystem & Data Persistence
*Goal: Build scalable, secure REST APIs connected to relational databases using industry standards.*

### Week 5: Spring Core & Spring Boot Autoconfiguration
Understanding the "magic" behind Spring.
* **Topics**:
  * Inversion of Control (IoC) and Dependency Injection (DI).
  * ApplicationContext, Beans Lifecycle, and Scopes.
  * Spring Boot Autoconfiguration (how `@SpringBootApplication` works under the hood).
  * Application properties and profiles (`application.yml`).
* **Resources**:
  * 🌐 *Guide*: [Spring Framework: The Core (Marco Behler)](https://www.marcobehler.com/guides/spring-framework) - *Highly Recommended!*
  * 🌐 *Documentation*: [Spring Core Reference](https://docs.spring.io/spring-framework/reference/core.html)

### Week 6: Data Persistence (Hibernate, JPA, PostgreSQL)
Where most backend performance issues arise.
* **Topics**:
  * JDBC basics vs. JPA/Hibernate.
  * Spring Data JPA (`@Entity`, Repositories).
  * The JPA Lifecycle (Transient, Managed, Detached).
  * Performance tuning: The N+1 Query Problem, Dirty Checking, Fetch Strategies.
  * Transaction Management (`@Transactional` boundaries and propagation).
* **Resources**:
  * 🌐 *Blog*: [Vlad Mihalcea's Blog](https://vladmihalcea.com/) - *The absolute best resource for Java/Hibernate performance.*
  * 🌐 *Blog*: [Thorben Janssen (Hibernate Tips)](https://thorben-janssen.com/)

### Week 7: Building REST APIs (Spring Web)
Creating the actual endpoints customers will hit.
* **Topics**:
  * `@RestController`, `@RequestMapping`, `@PathVariable`, `@RequestBody`.
  * Global Exception Handling (`@ControllerAdvice`).
  * Data Validation (`@Valid`, Hibernate Validator).
  * DTO Pattern (MapStruct or manual mapping) to avoid exposing entities.
  * RestTemplate vs. WebClient (for calling external APIs).
* **Resources**:
  * 🌐 *Article*: [Building a REST API with Spring Boot (Baeldung)](https://www.baeldung.com/rest-with-spring-series)

### Week 8: Security, Docker, & Final Project
Securing the app and preparing it for deployment.
* **Topics**:
  * Spring Security Basics (Authentication vs. Authorization).
  * Implementing JWT (JSON Web Tokens) or basic OAuth2.
  * Dockerizing the Spring Boot application (writing a `Dockerfile`, multi-stage builds).
  * Basic CI/CD (GitHub Actions to build the Docker image).
* **Resources**:
  * 🌐 *Guide*: [Spring Security Architecture (Spring Docs)](https://spring.io/guides/topicals/spring-security-architecture/)
  * 🌐 *Video/Guide*: [Dockerizing a Spring Boot App (Baeldung)](https://www.baeldung.com/dockerizing-spring-boot-application)

---

## 🚀 The Final Project (End of Month 2)
To solidify this, build a small but realistic FDE project:
**A "Customer Onboarding Service"**
- A REST API to create/manage companies and users.
- Connect it to PostgreSQL using Spring Data JPA.
- Secure the endpoints with JWT or Basic Auth.
- Run both the App and the DB locally using `docker-compose.yml`.

Target will be to complete this whole journey by the first week of August 2026.