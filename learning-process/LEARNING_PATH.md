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
| 11–12 | Phase 5 — Foundations + Phase 6E–G (Security, Prototyping, Client Skills) |
| 10–12 | Phase 7 — Projects (build portfolio projects in parallel with Phases 4–5) |
| 10–12 | Phase 8 — Business/Customer Engineering (woven into client-facing practice) |
| 11–12 | Phase 9 — Interview Preparation Sprint |
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
- [ ] **GitHub Workflow** — forking, pull requests (create, review, merge), code review best practices, protected branches, CI integration
- [ ] P2: submodules, worktrees
- **Resources:** *Pro Git* (free, git-scm.com/book), Learn Git Branching (interactive, learngitbranching.js.org), GitHub Docs

### 2. Linux & Shell — `tools/cli-tools/bash/` (P0)
- [x] Filesystem navigation, permissions (`chmod`/`chown`), process management (`ps`, `top`, `kill`, `systemctl`) — `filesystem-navigation.md`, `ownership-permissions.md`, `user-groups-permissions.md`, `process-management.md`
- [x] `grep`/`sed`/`awk` for log parsing — `grep.md`, `sed.md`, `awk.md`
- [x] Piping, redirection, `find` + `xargs` — `find/find-exec.md`
- [x] Bash scripting: variables, loops, conditionals, functions — `bash-scripting.md`
- [x] `tail -f`, `journalctl` for live log reading — `tail-journalctl.md`
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
- [ ] **API Gateway** — gateway vs. direct client-to-service, routing, aggregation, authentication offloading, rate limiting at gateway level
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
- [ ] **Event Streaming** — event sourcing, change data capture (CDC), log compaction, replaying events
- [ ] **CQRS (Command Query Responsibility Segregation)** — separation of read/write models, when to apply, consistency tradeoffs
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

### 6. Backend Operations & Optimization (P1)
- [ ] **Exception Handling** — global error handlers, structured error responses, exception mapping, logging with stack traces
- [ ] **API Optimization** — response compression, connection pooling, keep-alive, lazy loading, batch endpoints, pagination tuning
- [ ] **Performance Optimization** — profiling (CPU, memory, I/O), bottleneck identification, query optimization, caching layers
- [ ] **Production Readiness Review** — runbooks, health checks, startup probes, graceful shutdown, circuit breakers, rate limiting, readiness/liveness endpoints, feature flags, canary releases

---



## Phase 4: Architecture & Design

### 1. Low-Level Design — `system-design/lld/` (P1)
- [x] SOLID principles, applied practically rather than academically — `best-practices/solid-principles.md`, `lld/all-things.md`
- [ ] Patterns actually seen at work: Factory, Strategy, Observer, Decorator, Builder, Singleton (and its pitfalls)
- [ ] Practice problems: parking lot, rate limiter, elevator system
- **Resources:** refactoring.guru, *Head First Design Patterns*

### 2. High-Level Design — `system-design/hld/` (P1)
- [ ] Load balancing, caching layers, DB scaling (read replicas, sharding)
- [ ] **Multi-region architecture** — active-active vs. active-passive, global load balancing, cross-region replication, latency-based routing
- [ ] **Disaster Recovery** — RPO/RTO, backup strategies, failover/failback, disaster recovery drills
- [ ] **Capacity Estimation** — traffic estimation, storage estimation, bandwidth calculation, QPS/TPS estimation, back-of-the-envelope calculations
- [ ] **Design Trade-offs** — consistency vs. availability, latency vs. throughput, cost vs. performance, monolithic vs. microservices
- [ ] Practice: URL shortener, Twitter-style feed, chat app
- [ ] **Whiteboarding** — structured approach: clarify requirements → estimate scale → data model → high-level design → deep dive → tradeoffs
- [ ] **System Design mocks** — practice with peers (Pramp, interviewing.io, Prepfully), target 8-10 mocks before real interviews
- **Resources:** *System Design Interview* Vol. 1 & 2 (Alex Xu), ByteByteGo, System Design Newsletter

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

#### Fundamentals
- [ ] **Arrays** — traversal, rotation, in-place manipulation, subarrays
- [ ] **Strings** — manipulation, palindromes, anagrams, pattern matching (KMP basics)
- [ ] **Hashing** — hash maps/sets, collision handling, custom hash functions
- [ ] **Prefix Sum** — range sum queries, 2D prefix sum, difference arrays
- [ ] **Two Pointers** — opposite-direction, same-direction (fast/slow), partitioning
- [ ] **Sliding Window** — fixed window, variable window, window with auxiliary data structures
- [ ] **Binary Search** — standard, lower/upper bound, rotated array, search in 2D matrix
- [ ] **Linked Lists** — reversal, merge, cycle detection, fast/slow pointer
- [ ] **Stacks** — monotonic stack, expression evaluation, bracket matching
- [ ] **Queues** — circular queue, deque, priority queue usage
- [ ] **Trees** — traversal (in/pre/post/level-order), tree construction from serializations, LCA
- [ ] **Binary Search Trees (BST)** — insertion/deletion/search, validation, in-order properties
- [ ] **Graph Traversal (BFS/DFS)** — adjacency list/matrix, connected components, topological sort via DFS

#### Intermediate
- [ ] **Dynamic Programming** — 0/1 knap, unbounded knap, LIS/LCS, edit distance, grid DP, DP on trees
- [ ] **Heaps** — min/max heap, heapify, top K elements, median from stream
- [ ] **Tries** — insert/search/prefix, autocomplete, word search
- [ ] **Union Find (Disjoint Set Union)** — path compression, union by rank, connected components in dynamic graphs
- [ ] **Topological Sort** — Kahn's algorithm, DFS-based, cycle detection in directed graphs
- [ ] **Advanced Graphs** — Dijkstra, Bellman-Ford, Floyd-Warshall, MST (Prim/Kruskal), strongly connected components

#### Advanced
- [ ] **Graph DP** — DP on DAGs, bitmask DP (TSP), DP with state on graphs
- [ ] **Segment Trees** — range queries, point/range updates, lazy propagation, merge sort tree
- [ ] **Hard LeetCode** — problems tagged "Hard" across all patterns
- [ ] **Advanced contests** — LeetCode Weekly/Biweekly contests, Codeforces problems

#### Practice & Revision
- [ ] **100 LeetCode Questions (Month 1)** — fundamentals mastery
- [ ] **100 LeetCode Questions (Month 2)** — intermediate + advanced patterns
- [ ] **Weekly contests** — consistent contest participation
- [ ] **Timed contests** — simulate real interview pressure
- [ ] **Company-tagged problems** — filter by target company
- [ ] **Pattern recognition** — identify problem patterns on sight
- [ ] **Revision** — spaced repetition of previously solved problems
- [ ] **Mixed interview sets** — solve curated interview sets (NeetCode 150, Grind 75/169, Striver's SDE sheet)
- [ ] **Speed improvement** — time-boxed solving, 20-30 min per medium
- [ ] **Company-specific questions** — LeetCode discuss, Glassdoor, blind

- **Resources:** NeetCode 150 (free, neetcode.io), *Elements of Programming Interviews* (language-specific edition), Striver's SDE Sheet, LeetCode Discuss

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

#### Python — `languages/python/`
- [ ] Python ecosystem for AI/ML — NumPy, pandas, scikit-learn basics
- [ ] Python async for LLM API calls — `asyncio`, `aiohttp`, concurrent request handling
- [ ] Dependency & environment management — `uv`/`poetry`/`pip`, virtual environments, containerized Python for AI workloads

#### Prompt Engineering — `ai-integration/prompt-engineering/`
- [ ] Prompt structure & design — system/user/assistant messages, role prompting, chain-of-thought
- [ ] Few-shot vs. zero-shot prompting, in-context learning
- [ ] Prompt optimization — iterative refinement, A/B testing prompts, prompt versioning
- [ ] Handling model outputs — token limits, response parsing, retry with prompt adjustment

#### OpenAI & LLM APIs — `ai-integration/openai/`
- [ ] OpenAI API patterns — chat completions, streaming, function calling, structured outputs
- [ ] API best practices — retry logic, rate limiting, cost tracking, token counting
- [ ] Multi-provider abstraction — OpenAI, Anthropic, Google Gemini, open-source models (Llama, Mistral)
- [ ] **Structured Outputs** — JSON mode, constrained decoding, function calling for typed returns
- [ ] **Memory** — conversation history management, summarization, sliding window context

#### LangChain & Frameworks — `ai-integration/langchain/`
- [ ] LangChain basics — chains, prompts, LLM wrappers, output parsers
- [ ] LangChain expression language (LCEL)
- [ ] LangGraph for stateful agent workflows
- [ ] Alternative frameworks — LlamaIndex, Haystack, Vercel AI SDK — know the tradeoffs

#### Embeddings & Vector Search — `ai-integration/embeddings/`
- [ ] Embedding models — text-embedding-ada-002, text-embedding-3-small/large, open-source alternatives (BGE, E5, Instructor)
- [ ] Embedding quality — chunk size impact, overlap strategies, multi-representation indexing
- [ ] Vector databases — pgvector (PostgreSQL), Pinecone, Weaviate, Qdrant, Milvus
- [ ] Index types — IVF, HNSW, brute-force; recall vs. latency tradeoffs

#### Retrieval-Augmented Generation (RAG) — `ai-integration/rag/`
- [ ] **RAG architecture** — ingestion pipeline, chunking strategies, embedding, retrieval, generation
- [ ] **Enterprise RAG** — hybrid search (dense + sparse/keyword), re-ranking (Cohere, BGE-reranker), filtering, access controls
- [ ] **Production RAG** — caching (semantic cache like GPTCache), observability (LangSmith, Weights & Biases), latency optimization, monitoring retrieval quality
- [ ] **RAG Optimization** — chunk optimization (hierarchical, sliding window), query rewriting/expansion, HyDE (Hypothetical Document Embeddings), multi-hop retrieval, RAPTOR (tree-based summarization retrieval)
- [ ] Evaluation — retrieval precision/recall, generation faithfulness, answer relevance, hallucination detection

#### Agents & Tool-Use — `ai-integration/agents/`
- [ ] **Tool calling** — defining tools/functions, LLM tool selection, tool execution, result feedback
- [ ] **MCP (Model Context Protocol)** — Anthropic's standard for connecting LLMs to tools and data sources
- [ ] **AI Agents** — ReAct pattern (Reasoning + Acting), planning, self-reflection
- [ ] **Agent Orchestration** — multi-step agent workflows, sub-agent delegation, human-in-the-loop
- [ ] **Multi-Agent Workflows** — agent teams, supervisor agents, specialized agents (researcher, coder, reviewer)
- [ ] Agent evaluation — task completion rate, cost per task, robustness

#### Fine-Tuning — `ai-integration/fine-tuning/`
- [ ] Fine-tuning concepts — full fine-tuning vs. LoRA/QLoRA, PEFT, instruction tuning
- [ ] When to fine-tune vs. prompt engineer vs. RAG (decision framework)
- [ ] Data preparation for fine-tuning — prompt templates, formatting, quality filtering
- [ ] P2: RLHF, DPO (Direct Preference Optimization)

#### Evaluation & Safety — `ai-integration/evaluation/`
- [ ] **LLM Evaluation** — automated eval (prompt-based judges, BLEU/ROUGE, BERTScore), human eval
- [ ] **AI Evaluation** — task-specific metrics, end-to-end pipeline evals, regression testing
- [ ] **Evaluation Pipelines** — continuous eval (CI for AI), eval datasets, test splits
- [ ] **Safety** — prompt injection prevention, jailbreak detection, output filtering, PII redaction, content moderation
- [ ] **Guardrails** — guardrail frameworks (NeMo Guardrails, Guardrails AI), input/output validation, topic restrictions, policy enforcement

#### Cost Optimization — `ai-integration/cost/`
- [ ] Cost tracking — per-request cost, token accounting, usage dashboards
- [ ] Cost reduction — prompt compression, caching (semantic cache, KV cache), model routing (cheap model first, escalate), batching, quantization
- [ ] Budget controls — usage quotas, spending alerts, fallback models on rate limits

- **Resources:** Anthropic's docs and prompt engineering guide (docs.claude.com), OpenAI docs, LangChain/LlamaIndex docs, MCP specification (modelcontextprotocol.io), Pinecone/Weaviate docs, NeMo Guardrails docs

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

## Phase 7: Projects & Portfolio

> Build projects that simulate real FDE work — client-oriented, full-stack, deployed. Quality over quantity: 3–4 polished, deployed projects with architecture docs and demo videos beat 10 half-finished tutorials.

### 1. Enterprise RAG Chatbot — `projects/rag-chatbot/`
- [ ] **Authentication** — multi-tenant auth, JWT/session management, user-scoped access to documents
- [ ] **Chat history** — persistent conversation storage, context management across sessions
- [ ] **Document ingestion** — PDF/HTML/CSV parsing, chunking, embedding, vector storage
- [ ] Admin dashboard — document management, usage analytics, user management
- **Resources:** LangChain docs, OpenAI docs, pgvector docs

### 2. AI Support Agent — `projects/support-agent/`
- [ ] **Tool integration** — CRM (HubSpot/Salesforce), ticketing (Zendesk/Jira), knowledge base, Slack/Teams
- [ ] **Analytics dashboard** — ticket resolution rates, user satisfaction, common query patterns
- [ ] **Cloud deployment** — containerized (Docker), CI/CD pipeline, cloud hosting (AWS/GCP), domain + TLS
- **Resources:** OpenAI function calling docs, Slack API, Zapier/Retool for rapid prototyping

### 3. Operations Dashboard — `projects/ops-dashboard/`
- [ ] **Real-time metrics** — WebSocket-based live updates, Prometheus/Grafana integration
- [ ] **Alerts** — threshold-based alerting, PagerDuty/Slack notification integration
- [ ] Multi-service health monitoring — uptime tracking, latency monitoring, error rate dashboards
- **Resources:** Grafana docs, WebSocket basics, React/Streamlit for frontend

### 4. Multi-Tenant SaaS Platform — `projects/saas-platform/`
- [ ] **RBAC** — role-based access control across tenants, data isolation
- [ ] **Monitoring** — per-tenant metrics, tenant health dashboards, usage billing tracking
- [ ] Tiered plans — feature gating by subscription tier, usage quotas
- **Resources:** Auth0/Okta for multi-tenant auth, Terraform for infra, Stripe for billing

### 5. Project Polish (apply to all projects above)
- [ ] **Documentation** — README, setup guide, API docs (OpenAPI/Swagger), architecture overview
- [ ] **Architecture diagrams** — system context, container, component diagrams (C4 model, draw.io, Excalidraw)
- [ ] **Demo videos** — 3–5 min walkthrough showing the problem, solution, architecture, and demo
- [ ] **Deployment** — Docker Compose or Kubernetes, CI/CD pipeline, production-grade configuration

---

## Phase 8: Business / Customer Engineering

> FDEs are not pure engineers — you're a technical consultant embedded with the client. These skills differentiate a good engineer from an effective FDE.

### 1. Customer-Facing Skills (P0)
- [ ] **Requirement Gathering** — structured discovery sessions, asking the right questions, distinguishing needs from wants, documenting requirements back to the client for verification
- [ ] **Customer Communication** — technical translation (explaining complex tradeoffs to non-technical stakeholders), status updates, setting expectations, managing scope creep
- [ ] **Technical Discovery** — auditing existing client systems, understanding architecture without docs, identifying constraints (security, compliance, legacy integration points)
- [ ] **Product Thinking** — understanding the client's business goals, mapping technical solutions to business outcomes, prioritization by impact

### 2. Solution Architecture & Documentation (P0)
- [ ] **Solution Architecture** — designing end-to-end solutions that fit within client constraints, writing architecture decision records (ADRs), technology recommendation rationale
- [ ] **Documentation** — technical proposals, design docs, integration guides, runbooks — written clearly enough for a non-technical stakeholder to follow
- [ ] **Technical Proposals** — structured proposal writing: problem statement, proposed solution, architecture, timeline, risks/mitigations, alternatives considered

### 3. Stakeholder Management (P1)
- [ ] **Stakeholder Management** — identifying stakeholders, understanding their incentives, managing expectations across technical and business stakeholders
- [ ] **Executive Communication** — concise status updates, executive summaries, ROI framing, escalation handling
- [ ] **Product Roadmap Discussions** — translating engineering effort into business timelines, tradeoff communication (scope vs. quality vs. time)
- [ ] **Prioritization** — MoSCoW method, RICE scoring, impact vs. effort matrices, saying "no" gracefully

**Resources:** *The Mom Test* (Rob Fitzpatrick), *Never Split the Difference* (Chris Voss), *Articulating Design Decisions* (Tom Greever)

---

## Phase 9: Interview Preparation

> Interviewing is a separate skill from engineering. Dedicate 8–12 weeks of focused prep before the interview season. Start practicing mocks earlier (Month 6+).

### 1. Resume & Profile Optimization
- [ ] **Resume Optimization** — FDE-specific keywords, quantifiable impact metrics, projects section, one-page format
- [ ] **LinkedIn Optimization** — headline, summary, featured projects, recommendations, FDE-relevant keywords
- [ ] Portfolio curation — select 3–4 best projects with links, descriptions, and architecture highlights

### 2. Behavioral Preparation (P0)
- [ ] **STAR Stories** — craft 8–10 stories covering: technical challenge, conflict resolution, failure/learning, leadership, client impact, initiative, design decision, cross-team collaboration
- [ ] **Behavioral Questions** — practice "Why FDE?", "Why this company?", "Tell me about a time you dealt with ambiguity", "Tell me about a time you handled a difficult client"
- [ ] **Behavioral Interviews** — target 5+ mock behavioral interviews with peers or coaches

### 3. Coding Interview Prep
- [ ] **Coding Mocks** — timed coding mocks (LeetCode-style), target 10–15 mocks before real interviews
- [ ] Company-specific question patterns — research and practice target company's interview style
- [ ] Speed improvement — time-boxed solving: Easy 10 min, Medium 25 min, Hard 40 min
- [ ] **Revision tracking** — maintain a solved-problems log with pattern tags and revisit dates

### 4. System Design Interview Prep
- [ ] **System Design Mocks** — target 8–10 mock design interviews (Pramp, interviewing.io, peers)
- [ ] **Whiteboarding** — practice on a physical whiteboard or virtual whiteboard (Excalidraw, Miro), focus on structured approach
- [ ] **Architecture Interviews** — practice justifying tradeoffs, comparing alternatives, handling follow-up questions
- [ ] Company-specific design questions — research commonly asked design problems at target companies

### 5. Product & Case Studies
- [ ] **Product Case Studies** — practice product thinking: "Design a feature for X", "How would you improve Y?", metrics definition, experimentation design
- [ ] **Case Studies** — end-to-end problem solving: gather requirements, propose solution, discuss tradeoffs, outline implementation plan
- [ ] **Client Communication Practice** — mock client meetings, presenting technical solutions to non-technical stakeholders, handling pushback

### 6. Mock Interview Cycle (last 4–6 weeks)
- [ ] **Weekly Mock Interviews** — 1–2 per week rotating between: coding, system design, behavioral, product case
- [ ] **Mock Presentations** — present a past project architecture as if to a client/executive
- [ ] **Feedback Sessions** — record mocks, review with peers or mentors, track improvement areas
- [ ] Interview warmup — daily 15-min warmup (1 easy LC + 1 STAR story review) during the final month

**Resources:** *Cracking the PM Interview* (for product cases, useful for FDE client-facing questions), *System Design Interview* (Alex Xu), Pramp, interviewing.io, Exponent

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
