# Backend & Cloud Engineer Roadmap — Ordered by Real-World Usage
 
> Reordered so that what you'll actually touch at work in Week 1 is at the top, and what mostly matters for interviews/deep theory is at the bottom. Priority tags: **P0** = used daily/weekly, **P1** = used regularly, high-leverage, **P2** = situational but valuable, especially for senior roles.
 
**One important caveat the original plan doesn't address:** if part of the goal of this year is also *getting* the job (not just being good at it once you have it), DSA cannot actually wait until Phase 5. Most US SDE interview loops still gate heavily on DSA regardless of seniority. The ordering below reflects "time spent once employed," not "interview prep priority." Practical fix: run a **light, parallel DSA track from Day 1** (3-4 problems/week, pattern-focused) alongside whatever phase you're in, and only go deep (Phase 5 intensity) in the final 2-3 months pre-interview-season.
 
---
 
## Suggested Pacing (12 months)
 
| Months | Focus |
|---|---|
| 1–3 | Phase 1 — Daily Engineering Spine |
| 4–5 | Phase 2 — Building Services |
| 6–7 | Phase 3 — Production Engineering |
| 8–10 | Phase 4 — Architecture & Distributed Systems |
| 11–12 | Phase 5 — Foundations + Interview Sprint |
| Ongoing | DSA, 3-4 problems/week from Month 1 |
 
---
 
## Phase 1: Daily Engineering Spine
 
### 1. Git — `tools/git/` (P0)
- [ ] Daily flow: clone, branch, commit, push/pull/fetch, merge vs. rebase
- [ ] **Interactive rebase** (squash, reorder, fixup) — used constantly for clean PR history
- [ ] Conflict resolution (real conflicts, not toy ones)
- [ ] Stash, cherry-pick
- [ ] `git bisect` for regression hunting
- [ ] Reflog (recovering "lost" commits)
- [ ] `git blame`, `log -p`, `log --follow` for code archaeology
- [ ] `.gitignore`, pre-commit hooks
- [ ] P2: submodules, worktrees
- **Resources:** *Pro Git* (free, git-scm.com/book), Learn Git Branching (interactive, learngitbranching.js.org)
### 2. Linux & Shell — `tools/bash/` (P0)
- [ ] Filesystem navigation, permissions (`chmod`/`chown`), process management (`ps`, `top`, `kill`, `systemctl`)
- [ ] `grep`/`sed`/`awk` for log parsing — single biggest time-saver when debugging prod
- [ ] Piping, redirection, `find` + `xargs`
- [ ] Bash scripting: variables, loops, conditionals, functions
- [ ] `tail -f`, `journalctl` for live log reading
- [ ] `ssh`, `scp`, `tmux`/`screen`
- **Resources:** *The Linux Command Line* (free PDF, William Shotts), explainshell.com, ShellCheck (linter)
### 3. Programming Language (Primary)
See [Language-Specific Tracks](#language-specific-tracks) at the bottom. Go deep on your primary work language now; treat the others as a lighter pass until you actually need them.
 
### 4. Databases — `cs-fundamentals/dbms/` (P0, split out as requested)
This deserves far more weight than the original generic "DBMS" entry — it's used more than design patterns and most cloud topics combined.
 
- [ ] **SQL Mastery** — joins, subqueries, window functions, CTEs, aggregates (P0, daily)
- [ ] **Indexes** — B-tree basics, composite indexes, covering indexes, when an index silently isn't used (P0)
- [ ] **Query Optimization** — reading `EXPLAIN ANALYZE`, query plans, solving N+1 (P0)
- [ ] **Transactions & Isolation Levels** — Read Committed, Repeatable Read, Serializable; dirty/phantom reads (P1)
- [ ] **Locks & Deadlocks** — row vs. table locks, detecting and resolving deadlocks (P1)
- [ ] **Redis** — strings/hashes/sets/sorted sets/lists; caching, rate limiting, leaderboards, pub/sub; eviction policies; RDB vs AOF persistence; Redis Cluster basics (P0)
- [ ] **Data Modeling** — normalization vs. denormalization, SQL vs. NoSQL tradeoffs (P1)
- [ ] **PostgreSQL Internals** — MVCC, WAL, vacuum, table bloat (P2, but a strong senior-engineer signal)
- **Resources:** *Use The Index, Luke!* (free, use-the-index-luke.com), *SQL Performance Explained* (Markus Winand), Redis University (free, redis.com/university), PostgreSQL official docs
### 5. Docker — `tools/docker/` (P0)
- [ ] Images vs. containers; Dockerfile best practices (multi-stage builds, layer caching)
- [ ] `docker-compose` for local dev environments
- [ ] Volumes & basic networking
- [ ] Debugging running containers (`exec`, `logs`)
- [ ] P2: image size optimization, basic security scanning
- **Resources:** Docker official "Get Started" docs, *Docker Deep Dive* (Nigel Poulton)
### 6. API Design — `api-design/` (P0, **new — biggest gap in the original plan**)
- [ ] REST fundamentals — resource modeling, correct HTTP verbs/status codes
- [ ] **Idempotency** — critical for retries/payments, frequently underestimated
- [ ] **Pagination** — cursor-based vs. offset-based, and why cursor wins at scale
- [ ] **Versioning** strategies (URI, header, content negotiation)
- [ ] **Rate Limiting** — token bucket, sliding window
- [ ] **Authentication** (API keys, OAuth2, JWT) vs. **Authorization** (RBAC, scopes)
- [ ] OpenAPI/Swagger spec writing
- [ ] gRPC + protobuf for internal service-to-service calls
- [ ] Error response conventions
- **Resources:** Stripe API docs (read as a reference implementation), Google API Design Guide (free), grpc.io docs
### 7. Testing (P1)
- [ ] Unit tests + mocking
- [ ] Integration tests (Testcontainers)
- [ ] Test pyramid concept (don't over-invest in E2E)
- [ ] P2: contract testing (Pact)
- **Resources:** Martin Fowler's testing blog, language-native frameworks (JUnit5, pytest, Jest, Go `testing`)
---
 
## Phase 2: Building Services
 
### 1. Framework Mastery (P0)
Whichever stack you're actually shipping in — see Language-Specific Tracks below for Spring/NestJS/FastAPI/Go `net/http` detail.
 
### 2. AuthN/AuthZ (P0)
- [ ] Session-based vs. token-based auth
- [ ] OAuth2 flows (Authorization Code, Client Credentials)
- [ ] JWT structure & pitfalls (storage, revocation, expiry handling)
- [ ] RBAC vs. ABAC
- [ ] P2: SSO basics (SAML/OIDC)
- **Resources:** oauth.net, Auth0's blog (good practical write-ups)
### 3. Caching Strategies (P0)
- [ ] Cache-aside, write-through, write-behind patterns
- [ ] Invalidation strategies (TTL vs. explicit invalidation — "cache invalidation is one of the two hard problems")
- [ ] CDN basics
### 4. Background Jobs / Async Processing (P1)
- [ ] Job queues (Celery, BullMQ, Sidekiq-equivalents per stack)
- [ ] Cron-based vs. event-triggered jobs
- [ ] Idempotent job design, retries with exponential backoff
### 5. Messaging & Kafka — `messaging/` (P0, **new, pulled out of Distributed Systems per request**)
- [ ] Why message queues exist (decoupling, buffering, backpressure)
- [ ] Kafka core concepts: topics, partitions, offsets, consumer groups
- [ ] Delivery guarantees: at-most-once, at-least-once, exactly-once
- [ ] Producer/consumer tuning basics
- [ ] **Dead Letter Queues (DLQs)**
- [ ] RabbitMQ (exchange types) and SQS as alternatives — know the tradeoffs, not just Kafka
- [ ] Event-driven architecture patterns
- **Resources:** *Kafka: The Definitive Guide* (free PDF from Confluent), Confluent's Kafka tutorials
---
 
## Phase 3: Production Engineering
 
### 1. Observability — `tools/observability/` (P0)
- [ ] Structured logging (JSON logs, correlation/trace IDs)
- [ ] Metrics — RED/USE methods, Prometheus + Grafana
- [ ] Distributed tracing — OpenTelemetry, Jaeger
- [ ] Alerting basics — SLOs, error budgets
- **Resources:** Prometheus docs, Grafana docs, *Distributed Systems Observability* (free ebook, Cindy Sridharan)
### 2. CI/CD — `tools/cicd/` (P0)
- [ ] Pipeline stages: build, test, deploy
- [ ] GitHub Actions / GitLab CI fundamentals
- [ ] Blue-green & canary deployments
- [ ] Rollback strategies
### 3. Cloud Fundamentals — `infrastructure/cloud-fundamentals/` (P0, AWS primary)
- [ ] Compute: EC2, Lambda
- [ ] Storage: S3, EBS
- [ ] Networking: VPC, Security Groups, Load Balancers
- [ ] **IAM** (roles, policies) — frequently underweighted, frequently the cause of prod incidents
- [ ] Managed DBs: RDS
- **Resources:** AWS official docs, freeCodeCamp's AWS courses
### 4. Kubernetes — `infrastructure/orchestration/kubernetes/` (P1)
- [ ] Pods, Deployments, Services, Ingress
- [ ] ConfigMaps & Secrets
- [ ] Resource requests/limits, HPA (autoscaling)
- [ ] Daily `kubectl` fluency
- [ ] P2: Helm
- **Resources:** kubernetes.io docs/tutorials, *Kubernetes Up & Running* (Burns et al.), killercoda.com interactive scenarios
### 5. Infrastructure as Code — `infrastructure/iac/terraform/` (P1)
- [ ] Providers, resources, state management
- [ ] Modules for reusability
- [ ] Remote state & locking
- [ ] Plan/apply discipline (never apply blind)
- **Resources:** HashiCorp Learn (free), *Terraform: Up & Running* (Yevgeniy Brikman)
---
 
## Phase 4: Architecture & Design
 
### 1. Low-Level Design — `system-design/lld/` (P1)
- [ ] SOLID principles, applied practically rather than academically
- [ ] Patterns actually seen at work: Factory, Strategy, Observer, Decorator, Builder, Singleton (and its pitfalls)
- [ ] Practice problems: parking lot, rate limiter, elevator system
- **Resources:** refactoring.guru, *Head First Design Patterns*
### 2. High-Level Design — `system-design/hld/` (P1)
- [ ] Load balancing, caching layers, DB scaling (read replicas, sharding)
- [ ] Practice: URL shortener, Twitter-style feed, chat app
- **Resources:** *System Design Interview* Vol. 1 & 2 (Alex Xu), ByteByteGo
### 3. Distributed Systems — `system-design/distributed-systems/` (P1, **new — the biggest missing piece**)
- [ ] CAP theorem & PACELC
- [ ] Consistency models — strong, eventual, causal
- [ ] Replication — leader-follower, leaderless/quorum-based
- [ ] Partitioning / sharding strategies
- [ ] Leader election & Consensus (Raft — conceptual understanding is enough for most roles)
- [ ] Distributed transactions; **Sagas** (compensating transactions)
- [ ] Circuit breakers, retries with backoff + jitter
- [ ] Service discovery
- **Resources:** *Designing Data-Intensive Applications* (Martin Kleppmann) — read this cover to cover, it's the single best ROI book on this list. MIT 6.824 Distributed Systems (free on YouTube). Raft paper ("In Search of an Understandable Consensus Algorithm").
### 4. Performance, Scalability, Reliability (P2)
- [ ] Profiling basics in your primary language
- [ ] Horizontal vs. vertical scaling tradeoffs
- [ ] SLAs / SLOs / SLIs, error budgets
- [ ] P2: chaos engineering basics
---
 
## Phase 5: Foundations
 
### 1. DSA — `dsa/` (interview-critical; run in parallel from Month 1, see pacing note above)
- [ ] Patterns over memorization: two pointers, sliding window, BFS/DFS, DP basics, heaps, intervals
- [ ] Integer overflow & edge-case handling discipline
- **Resources:** NeetCode 150 (free, neetcode.io), *Elements of Programming Interviews* (language-specific edition)
### 2. Operating Systems — `cs-fundamentals/os/`
- [ ] Processes & threads, scheduling
- [ ] Memory management (paging, virtual memory)
- [ ] Concurrency primitives (mutex, semaphore, deadlock conditions)
- **Resources:** *OSTEP — Operating Systems: Three Easy Pieces* (free, ostep.org)
### 3. Computer Networks — `cs-fundamentals/cn/`
- [ ] TCP/IP, the TCP handshake, TCP vs. UDP
- [ ] HTTP/HTTPS, HTTP/2, TLS handshake basics
- [ ] DNS resolution flow
- **Resources:** *High Performance Browser Networking* (free, hpbn.co, Ilya Grigorik) — more practically useful than a textbook for working engineers
### 4. DB Internals — deep dive beyond Phase 1 SQL mastery
- [ ] B-tree / LSM-tree storage internals
- [ ] MVCC implementation details
- [ ] WAL & durability guarantees
- **Resources:** DDIA Part I (already on your list above), *PostgreSQL: Up and Running* (Regina Obe)
---
 
## Language-Specific Tracks
 
### Java/Spring — `languages/java/`
- [ ] **Spring Ecosystem** — DI/IoC, Boot autoconfiguration, bean lifecycle, AOP (P0)
- [ ] **Data Persistence** — Hibernate/JPA lifecycle, dirty checking, `@Transactional` propagation, solving N+1 (P0)
- [ ] **Concurrency** — `ExecutorService`, `CompletableFuture`, synchronized/locks, Virtual Threads/Project Loom (P1)
- [ ] **JVM Internals** — heap/stack/metaspace, ClassLoaders, JIT, GC tuning (P2 — strong debugging/senior signal)
- [ ] Build & Deploy — Maven/Gradle, fat JARs, JVM flags (P1)
- **Resources:** *Effective Java* (Joshua Bloch), Baeldung.com, official Spring guides
### Golang — `languages/golang/`
- [ ] **Concurrency Model** — goroutines, channels, `select`, `sync` package (P0 — this is Go's whole value proposition)
- [ ] **Error Handling** — explicit returns, `defer`, `panic`/`recover` (P0)
- [ ] `net/http` for building APIs without heavy frameworks (P0)
- [ ] **Type System** — implicit interfaces, composition over inheritance (P1)
- [ ] Memory & runtime — pointers vs. values, escape analysis, GC mechanics (P1)
- [ ] Profiling/tracing with `pprof` (P2)
- **Resources:** *The Go Programming Language* (Donovan & Kernighan), Go by Example (gobyexample.com), Effective Go (go.dev)
### Python — `languages/python/`
- [ ] **Ecosystem & Frameworks** — FastAPI/Django/Flask, SQLAlchemy/Django ORM (P0)
- [ ] **Typing & Validation** — type hints, Pydantic schemas (P0 if using FastAPI)
- [ ] **Concurrency & Async** — GIL implications, `asyncio` event loop, `multiprocessing` vs. `threading` (P0)
- [ ] Language constructs — decorators, generators (`yield`), context managers, metaclasses (P1)
- **Resources:** FastAPI official docs (excellent, double as a tutorial), *Fluent Python* (Luciano Ramalho)
### TypeScript — `languages/typescript/`
- [ ] **Ecosystem** — NestJS or Express, Prisma/TypeORM, DI patterns (P0)
- [ ] **Runtime Execution (Node.js)** — event loop, async I/O, EventEmitters, Streams, Buffers (P0)
- [ ] **Type System** — generics, union/intersection, mapped/utility types, type guards (P1)
- [ ] Concurrency & scaling — Worker Threads, Cluster module, child processes (P2)
- **Resources:** TypeScript Handbook (official, free), NestJS docs, Node.js official guides
