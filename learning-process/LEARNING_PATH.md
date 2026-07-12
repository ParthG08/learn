# Backend & Cloud Engineer Roadmap — Ordered by Real-World Usage

> Reordered so that what you'll actually touch at work in Week 1 is at the top, and what mostly matters for interviews/deep theory is at the bottom. Priority tags: **P0** = used daily/weekly, **P1** = used regularly, high-leverage, **P2** = situational but valuable, especially for senior roles.

**One important caveat the original plan doesn't address:** if part of the goal of this year is also *getting* the job (not just being good at it once you have it), DSA cannot actually wait until Phase 5. Most US SDE interview loops still gate heavily on DSA regardless of seniority. The ordering below reflects "time spent once employed," not "interview prep priority." Practical fix: run a **light, parallel DSA track from Day 1** (3-4 problems/week, pattern-focused) alongside whatever phase you're in, and only go deep (Phase 5 intensity) in the final 2-3 months pre-interview-season.

**A second caveat, specific to Forward Deployed Engineering:** Phases 1–5 below cover the generic backend/cloud SDE spine. FDE is a meaningfully different job — you're embedded with a client, building and integrating fast, usually into messy/regulated/non-standard environments, with way more emphasis on data engineering, multi-cloud/on-prem ops, enterprise integration, and (increasingly, as of 2026) AI/LLM integration. **Phase 6** below is the FDE-specific delta on top of everything else. Treat it as additive, not a replacement — an FDE still needs the Phase 1–4 spine, just with Phase 6 woven in earlier and more heavily than a pure backend SDE would.

---

## Suggested Pacing (12 months)

| Months | Focus |
|---|---|
| 1–3 | Phase 1 — Daily Engineering Spine |
| 4–5 | Phase 2 — Building Services + start weaving in Phase 6A (Data Engineering) |
| 6–7 | Phase 3 — Production Engineering + Phase 6B (Multi-Cloud/On-Prem) |
| 8–10 | Phase 4 — Architecture & Distributed Systems + Phase 6C–D (Enterprise Integration, AI/LLM) |
| 11–12 | Phase 5 — Foundations + Interview Sprint + Phase 6E–G (Security, Prototyping, Client Skills) |
| Ongoing | DSA, 3-4 problems/week from Month 1 |
| Ongoing | Japanese — daily study (vocab, kanji, grammar, listening) from Day 1; N5 → N4 → N3 → N2 over 2–3 years |

> Note: adding the full FDE track (Phase 6) is genuinely more than 12 months of net-new material on top of Phases 1–5. If you're optimizing for an actual FDE role rather than general SDE breadth, consider lightening Phase 4 (Distributed Systems theory and deep Performance Engineering are lower-frequency for FDE work) to make room.

---

## Phase 1: Daily Engineering Spine

### 1. Git — `tools/git/` (P0)
- [x] Daily flow: clone, branch, commit, push/pull/fetch, merge vs. rebase — `branching-merging.md`, `commits.md`, `remote-workflows.md`, `three-trees.md`
- [x] **Interactive rebase** (squash, reorder, fixup) — `interactive-rebase.md`, `rewriting-history.md`
- [x] Conflict resolution (real conflicts, not toy ones) — `conflict.md`
- [x] Stash, cherry-pick — `patch.md`
- [x] `git bisect` for regression hunting — `bisect.md`
- [x] Reflog (recovering "lost" commits) — `recovery.md`
- [ ] `git blame`, `log -p`, `log --follow` for code archaeology
- [ ] `.gitignore`, pre-commit hooks
- [ ] P2: submodules, worktrees
- **Resources:** *Pro Git* (free, git-scm.com/book), Learn Git Branching (interactive, learngitbranching.js.org)

### 2. Linux & Shell — `tools/cli-tools/bash/` (P0)
- [ ] Filesystem navigation, permissions (`chmod`/`chown`), process management (`ps`, `top`, `kill`, `systemctl`)
- [ ] `grep`/`sed`/`awk` for log parsing — single biggest time-saver when debugging prod
- [x] Piping, redirection, `find` + `xargs` — `find/find-exec.md`
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
- [x] **Query Optimization** — reading `EXPLAIN ANALYZE`, query plans, solving N+1 (P0) — `query-optimization/comparison/warm-cache-compare.md`
- [ ] **Transactions & Isolation Levels** — Read Committed, Repeatable Read, Serializable; dirty/phantom reads (P1)
- [ ] **Locks & Deadlocks** — row vs. table locks, detecting and resolving deadlocks (P1)
- [ ] **Redis** — strings/hashes/sets/sorted sets/lists; caching, rate limiting, leaderboards, pub/sub; eviction policies; RDB vs AOF persistence; Redis Cluster basics (P0)
- [ ] **Data Modeling** — normalization vs. denormalization, SQL vs. NoSQL tradeoffs (P1)
- [ ] **PostgreSQL Internals** — MVCC, WAL, vacuum, table bloat (P2, but a strong senior-engineer signal)
- **Resources:** *Use The Index, Luke!* (free, use-the-index-luke.com), *SQL Performance Explained* (Markus Winand), Redis University (free, redis.com/university), PostgreSQL official docs

### 5. Docker — `tools/cli-tools/docker/` (P0)
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
- *If targeting FDE: this AWS-only scope is not enough — see Phase 6B for multi-cloud/on-prem.*

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
- [x] SOLID principles, applied practically rather than academically — `best-practices/solid-principles.md`, `lld/all-things.md`
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
- [x] Integer overflow & edge-case handling discipline — `best-practices/integer-overflow/integer-overflow.md`
- **Resources:** NeetCode 150 (free, neetcode.io), *Elements of Programming Interviews* (language-specific edition)

### 2. Operating Systems — `cs-fundamentals/os/`
- [x] Processes & threads, scheduling — `intro/virtualization-of-the-cpu.md`, `virtualization/intro/` (process abstraction, creation, data structures), `virtualization/process-api/` (fork, exec, wait, pipe)
- [x] Memory management (paging, virtual memory) — `intro/virtualizing-memory.md`, `virtualization/intro-stack-head.md`
- [x] Concurrency primitives (mutex, semaphore, deadlock conditions) — `intro/concurrency.md`
- **Resources:** *OSTEP — Operating Systems: Three Easy Pieces* (free, ostep.org)

### 3. Computer Networks — `cs-fundamentals/cn/`
- [ ] TCP/IP, the TCP handshake, TCP vs. UDP
- [ ] HTTP/HTTPS, HTTP/2, TLS handshake basics
- [ ] DNS resolution flow
> Only README.md exists in `cs-fundamentals/cn/` — no substantive notes yet
- **Resources:** *High Performance Browser Networking* (free, hpbn.co, Ilya Grigorik) — more practically useful than a textbook for working engineers

### 4. DB Internals — deep dive beyond Phase 1 SQL mastery
- [ ] B-tree / LSM-tree storage internals
- [ ] MVCC implementation details
- [ ] WAL & durability guarantees
- **Resources:** DDIA Part I (already on your list above), *PostgreSQL: Up and Running* (Regina Obe)

---

## Phase 6: Forward Deployed Engineer (FDE) Specialization

This is what's *not* in a normal backend/cloud SDE plan but is core to FDE work. The role's defining trait is: arbitrary client environment + messy client data + tight timeline + you're the one translating "what they need" into "what's running." That shows up as heavier data engineering, infra that isn't just AWS, integration with systems you don't control, and — increasingly — AI/LLM deployment work. The closing section (G) is the one skill on this entire roadmap that genuinely can't be learned from a resource list.

### A. Data Engineering — `data-engineering/` (P0 — often the actual majority of FDE work)
- [ ] **ETL vs. ELT** — batch vs. streaming, when each fits
- [ ] **Apache Spark / PySpark** — DataFrames, partitioning, common performance pitfalls (shuffles, skew)
- [ ] **Orchestration — Apache Airflow** — DAGs, scheduling, retries, sensors
- [ ] **Data transformation — dbt** — models, tests, lineage (the modern standard for "SQL that's actually maintainable")
- [ ] **Data Warehouses** — Snowflake, BigQuery, Redshift — architectural differences and cost models, since clients will already have one of these and you won't get to pick
- [ ] **Data Lakes & table formats** — Parquet, Delta Lake, Apache Iceberg; S3-based lake architecture
- [ ] **Data Quality** — Great Expectations, schema validation, data contracts — client data is never clean, this is not optional
- [ ] **Dimensional Data Modeling** — star schema, slowly changing dimensions
- [ ] P2: streaming data processing — Kafka Streams, Spark Structured Streaming, Flink
- **Resources:** *Fundamentals of Data Engineering* (Reis & Housley) — best modern overview of the whole space, Airflow official docs, dbt Learn (free, learn.getdbt.com), Databricks Academy (free Spark courses)

### B. Multi-Cloud & On-Prem / Hybrid Deployment — `infrastructure/multi-cloud/` (P0 — the single biggest differentiator vs. a normal backend SDE)
- [ ] Don't stop at AWS — get conversational in **Azure** and **GCP** equivalents (compute, storage, IAM concepts map across all three; learn the mapping, not three separate stacks from scratch)
- [ ] On-prem Kubernetes distributions — **OpenShift**, Rancher, bare-metal K8s via `kubeadm`
- [ ] **Air-gapped / disconnected deployment** patterns — offline package mirrors, private image registries with no internet egress (extremely common in defense/gov/finance client environments)
- [ ] Writing Terraform/Helm that isn't hard-locked to one cloud provider
- [ ] VPNs, on-prem-to-cloud connectivity, proxy configuration, operating behind client firewalls
- **Resources:** Azure/GCP free-tier docs (just enough to map AWS concepts across, not full certs), OpenShift docs, *Kubernetes Patterns* (O'Reilly)

### C. Enterprise Integration & Identity — `integration/` (P0/P1)
- [ ] **SSO protocols** — SAML, LDAP/Active Directory, OIDC — almost every enterprise client gates access behind one of these
- [ ] Legacy system integration patterns — SOAP, flat-file/SFTP handoffs (still extremely common in enterprise and government, however dated it sounds)
- [ ] Middleware/ESB concepts, webhook design
- [ ] Working with undocumented or inconsistent client APIs — defensive parsing, handling schema drift gracefully
- **Resources:** Auth0/Okta engineering blogs on SSO protocols, *Enterprise Integration Patterns* (Hohpe & Woolf)

### D. AI/LLM Integration — `ai-integration/` (P0 — central to most FDE roles as of 2026)
- [ ] LLM API integration patterns — prompting, streaming responses, function/tool calling
- [ ] **RAG (Retrieval-Augmented Generation)** architecture — chunking strategy, embeddings, retrieval quality
- [ ] Vector databases — pgvector, Pinecone, Weaviate, Qdrant
- [ ] Agentic workflows / tool-use orchestration
- [ ] Evaluation basics — how to actually tell if an AI integration is working, not just demoing well
- **Resources:** Anthropic's docs and prompt engineering guide (docs.claude.com), LangChain/LlamaIndex docs (useful for the patterns even if you build without the framework)

### E. Security & Compliance Literacy (P1 — especially for regulated clients: gov/defense/finance/healthcare)
- [ ] Secrets management — Vault, cloud-native secrets managers (AWS/Azure/GCP)
- [ ] Audit logging requirements
- [ ] Compliance framework awareness — SOC2, FedRAMP, HIPAA (you're not the auditor, but you need to not violate them by accident)
- [ ] Principle of least privilege, applied in practice not just in theory

### F. Rapid Prototyping & Internal Tooling (P1)
- [ ] Lightweight frontend — enough React (or Streamlit/Retool if you need to move even faster) to build a usable demo UI quickly
- [ ] Notebook-driven development — Jupyter, for live data exploration with a client in the room
- [ ] CLI tool design — `argparse`/`click`/`cobra` — you'll constantly be building one-off tools for client teams

### H. Japan-Specific FDE Skills — `japanese/business-culture/` (P0 for Japan FDE)
> See separate Japanese Language Track below for full language progression. This section covers Japan-specific engineering context.

- [ ] **Japanese Business Culture** — keigo (敬語) levels, email/messaging etiquette, meeting protocol, nemawashi (根回し / consensus-building), honne (本音) vs. tatemae (建前)
- [ ] **Japanese Enterprise Tech Landscape** — domestic cloud providers (Sakura Cloud, IDCF Cloud), common enterprise stacks (Fujitsu, NEC, Hitachi), legacy system patterns in Japanese corporations
- [ ] **Japan-Specific Compliance** — Act on Protection of Personal Information (個人情報保護法 — Japan's GDPR equivalent), My Number (個人番号) system handling, FISC (financial industry security guidelines)
- [ ] **Japanese National IT Qualifications** — 基本情報技術者 (Fundamental IT Engineer), 応用情報技術者 (Applied IT Engineer) — resume differentiators for Japanese companies
- **Resources:** IPA official exam guides (jitec.ipa.go.jp), Japanese government IT standards docs, Okta Japan / Auth0 Japan enterprise case studies

### G. The Skill That Actually Defines the Role (not on any resource list)
- [ ] Requirements-to-prototype translation — turning a vague client conversation into a working demo within days
- [ ] Writing technical docs/design docs a non-technical stakeholder can actually follow
- [ ] Comfort operating with ambiguity and fast-shifting scope
- This isn't something you study from a book — practice it deliberately. After each project elsewhere in this roadmap, write a 1-page doc explaining what you built as if to a non-technical client stakeholder. That habit, repeated, is most of the skill.

---

## Japanese Language Track — `japanese/` (P0 for Japan FDE — ongoing from Day 1)

> This is the single biggest career moat for an FDE in Japan. Business-grade Japanese (N2+) combined with strong engineering skills eliminates 95% of global competition. Target: N5 → N4 → N3 → N2 over 2–3 years. Study daily in parallel with everything else.

### JLPT Progression (2–3 year timeline)

#### N5 (~4 months) — `japanese/n5/`
Foundational. Basic conversations, hiragana/katakana, ~100 kanji, ~800 vocab.
- [ ] Hiragana & Katakana mastered (read and write fluently)
- [ ] Basic sentence structure (Subject-Object-Verb, particles: は、が、を、に、で)
- [ ] Basic verb conjugations (present/past, affirmative/negative, て-form)
- [ ] Basic adjectives (い-adj vs. な-adj) and conjugation
- [ ] Numbers, counters, dates, time expressions
- [ ] Self-introduction, basic conversation patterns
- **Goal:** Pass JLPT N5 practice test

#### N4 (~6 months) — `japanese/n4/`
Everyday Japanese. ~300 kanji, ~1,500 vocab. Can handle daily situations.
- [ ] All verb conjugation forms (potential, volitional, conditional, passive, causative)
- [ ] Compound sentences (から、ので、けど、たら、ば)
- [ ] Giving/receiving expressions (あげる、くれる、もらう) — critical for business contexts
- [ ] Honorific basics (respectful 尊敬語 and humble 謙譲語 introduction)
- [ ] Reading simple news, short passages
- [ ] Listening: NHK Easy News, basic podcasts
- **Goal:** Pass JLPT N4

#### N3 (~8 months) — `japanese/n3/`
Intermediate. ~650 kanji, ~3,750 vocab. Can understand business conversations.
- [ ] Complex sentence patterns (~200 grammar points)
- [ ] Intermediate keigo (敬語) — proper respectful and humble forms
- [ ] Reading business emails and basic technical documentation in Japanese
- [ ] Listening: Native-speed Japanese, news, technical presentations
- [ ] Speaking: Express opinions, participate in meetings at basic level
- **Goal:** Pass JLPT N3 — this is the minimum to function in a Japanese workplace

#### N2 (~8 months) — `japanese/n2/`
Business-proficient. ~1,000 kanji, ~6,000 vocab. This is the career-moat level.
- [ ] Advanced grammar — formal written patterns, academic/business register
- [ ] Fluent keigo across all contexts (client meetings, emails, presentations)
- [ ] Reading technical specifications, architecture docs, legal/compliance docs in Japanese
- [ ] Listening: Meeting discussions, technical talks, client calls at native speed
- [ ] Speaking: Lead technical discussions, present architecture, negotiate scope in Japanese
- **Goal:** Pass JLPT N2 — this, plus engineering skills, is the career differentiator

### Supporting Study Areas (run in parallel with JLPT levels)

#### Kanji — `japanese/kanji/`
- [ ] RTK (Remembering the Kanji) or Wanikani for systematic kanji acquisition
- [ ] Stroke order, radicals, on'yomi vs. kun'yomi readings
- **Resources:** Wanikani (paid, highly effective), Anki kanji decks, Kanji Study app

#### Grammar — `japanese/grammar/`
- [ ] JLPT grammar points per level (N5–N2)
- [ ] Reading comprehension strategies
- **Resources:** Bunpro (SRS-based grammar), Tae Kim's Guide to Japanese, 日本語の森 (YouTube)

#### Vocabulary — `japanese/vocabulary/`
- [ ] Core vocabulary decks per JLPT level
- [ ] Spaced repetition (Anki) daily
- **Resources:** Anki Core 2k/6k decks, iKnow.jp

#### Listening — `japanese/listening/`
- [ ] Daily listening practice (podcasts, news, anime with JP subtitles)
- [ ] Shadowing exercises for pronunciation
- **Resources:** NHK Easy News, Nihongo con Teppei (podcast), Japanese with Shun (YouTube), Netflix with Japanese subtitles

#### Technical Japanese — `japanese/technical/`
Learn CS/IT terminology in Japanese — critical for FDE work in Japanese enterprise environments.
- [ ] Programming/CS terminology in Japanese (API, database, deployment, cloud = データベース, 展開, クラウド, etc.)
- [ ] Reading technical blogs/documentation in Japanese (Qiita, Zenn, 日本語 AWS docs)
- [ ] Writing technical design docs in Japanese
- [ ] JP technical Slack/Discord communities for immersion
- **Resources:** Qiita (qiita.com — Japanese dev blog platform), Zenn (zenn.dev), AWS 日本語ドキュメント, Microsoft Azure 日本語ドキュメント

#### Business Culture — `japanese/business-culture/`
- [ ] Keigo master class — full respectful, humble, and polite forms for business settings
- [ ] Japanese corporate hierarchy and senpai-kohai dynamics
- [ ] Email/chat etiquette in Japanese business context
- [ ] Meeting protocols (opening/closing scripts, agenda handling, nemawashi)
- [ ] How Japanese enterprises evaluate and adopt technology (decision-making flow is different from Western companies)
- [ ] Client presentation and consulting skills in Japanese context

---

### Java/Spring — `languages/java/`
- [x] **Spring Ecosystem** — DI/IoC, Boot autoconfiguration, bean lifecycle, AOP (P0) — `dependency-injection/autowired.md`, `misc/folder-structure/` (DDD architecture, controller/service/repository/components)
- [ ] **Data Persistence** — Hibernate/JPA lifecycle, dirty checking, `@Transactional` propagation, solving N+1 (P0) — `persistence/jpa/` (basic JPA models, repositories, derived queries exist; lifecycle/transactional not covered yet)
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
