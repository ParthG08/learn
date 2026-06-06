# Hierarchical Cloud & SDE Roadmap

## Phase 1: Daily Development & Execution (The Bread & Butter)
1. [ ] **Version Control**: `tools/git` (Branching, Rebase, Find-Exec).
2. [ ] **Programming Languages**: (See detailed [Language Tracks](#language-specific-tracks) below)
   - [ ] Java/Spring: `languages/java/`
   - [ ] TypeScript: `languages/typescript/`
   - [ ] Golang: `languages/golang/`
   - [ ] Python: `languages/python/`
3. [ ] **DBMS**: `cs-fundamentals/dbms`.
4. [ ] **Docker**: `tools/docker/`.
5. [ ] **Shell Scripting**: `tools/bash`.

## Phase 2: Design & Craftsmanship (The Architecture)
1. [ ] **Low-Level Design**: `system-design/lld/`.
2. [ ] **SOLID Principles**: `best-practices/solid-principles.md`.
3. [ ] **Design Patterns**: `design-patterns/`.
4. [ ] **High-Level Design (HLD)**: `system-design/hld/`.

## Phase 3: Cloud, Operations & Production (The Infrastructure)
1. [ ] **Cloud Fundamentals**: `infrastructure/cloud-fundamentals/` (AWS/GCP).
2. [ ] **CI/CD**: `tools/cicd/`.
3. [ ] **Observability**: `tools/observability/`.
4. [ ] **Orchestration**: `infrastructure/orchestration/kubernetes/`.
5. [ ] **Infrastructure as Code**: `infrastructure/iac/terraform/`.

## Phase 4: Foundational Underpinnings (The Theory)
1. [ ] **Computer Networks**: `cs-fundamentals/cn`.
2. [ ] **DSA**: `dsa/` (Focus on patterns and Integer Overflow practices).
3. [ ] **Operating Systems**: `cs-fundamentals/os`.

---

## Language-Specific Tracks

### Java/Spring Track (`languages/java/`)
- [ ] **JVM Internals**: Memory structure (Heap, Stack, Metaspace), ClassLoaders, JIT Compiler, and Garbage Collection tuning.
- [ ] **Concurrency & Multithreading**: Thread Pools, `ExecutorService`, synchronized/locks, `CompletableFuture`, and Virtual Threads (Project Loom).
- [ ] **Spring Ecosystem**: Dependency Injection/IoC, Spring Boot autoconfiguration, Beans lifecycle, and Spring AOP.
- [ ] **Data Persistence & ORM**: Hibernate/JPA lifecycle, dirty checking, `@Transactional` boundary propagation, caching, and solving the N+1 query problem.
- [ ] **Build & Deploy**: Maven/Gradle, fat JAR packaging, JVM optimization flags.

### TypeScript Track (`languages/typescript/`)
- [ ] **Runtime Execution (Node.js)**: The Event Loop, asynchronous non-blocking I/O, EventEmitters, Streams, and Buffers.
- [ ] **Type System**: Generics, Union/Intersection types, Mapped types, Utility types, Type Guards, and structural typing.
- [ ] **Ecosystem**: NestJS or Express, Prisma/TypeORM, dependency injection patterns.
- [ ] **Concurrency & Scaling**: Worker Threads, Cluster module, and child processes.

### Golang Track (`languages/golang/`)
- [ ] **Concurrency Model**: Goroutines, Channels, `select` statement, and `sync` package (Mutex, WaitGroup, Once, Map).
- [ ] **Memory & Runtime**: Pointers vs. Values, Escape Analysis, Garbage Collection mechanics.
- [ ] **Error Handling**: Explicit error returns, `defer`, and `panic`/`recover` patterns.
- [ ] **Type System**: Implicit interface implementation (duck typing) and composition over inheritance.
- [ ] **Ecosystem**: Go Modules, built-in `net/http` package, testing, and profiling/tracing using `pprof`.

### Python Track (`languages/python/`)
- [ ] **Concurrency & Async**: Global Interpreter Lock (GIL) implications, `asyncio` event loop, `multiprocessing` vs. `threading`.
- [ ] **Language Constructs**: Decorators, Generators (`yield`), Context Managers (`with`), and Metaclasses.
- [ ] **Ecosystem & Frameworks**: FastAPI/Django/Flask, SQLAlchemy or Django ORM, and dependency management (Poetry/Pipenv).
- [ ] **Typing & Validation**: Type hinting, Pydantic schemas, and runtime data parsing.