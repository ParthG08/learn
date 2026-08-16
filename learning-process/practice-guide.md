# Practice Guide — Interactive Playgrounds, Labs & Drills

Everything below is for **learning by doing** (skills that need hands-on practice, online courses, and reiteration — not memorization). For each topic in `LEARNING_PATH.md`, this is where you *train*, not just read. **Read the notes → drill here → repeat.**

## Cross-link map → LEARNING_PATH.md

| Practice section (this file) | Corresponding topic in `learning-process/LEARNING_PATH.md` |
|---|---|
| [Git](#git) | Phase 1 §1 Git — `tools/git/` |
| [Linux & Shell](#linux--shell), [Regex](#regex-used-daily-with-grepsedawk) | Phase 1 §2 Linux & Shell — `tools/cli-tools/bash/` |
| [SQL](#sql), [Database practice sandbox](#database-practice-sandbox) | Phase 1 §4 Databases — `cs-fundamentals/dbms/` |
| [Docker](#docker) | Phase 1 §5 Docker — `tools/cli-tools/docker/` |
| [API Design](#api-design) | Phase 1 §6 API Design — `api-design/` |
| [Testing](#testing) | Phase 1 §7 Testing — `tools/testing/` |
| [AuthN/AuthZ](#authnauthz) | Phase 2 §2 AuthN/AuthZ |
| [Caching / Background Jobs](#caching--background-jobs) | Phase 2 §3 Caching, §4 Background Jobs |
| [Kafka / Messaging](#kafka--messaging) | Phase 2 §5 Messaging & Kafka — `messaging/` |
| [Observability](#observability) | Phase 3 §1 Observability — `tools/observability/` |
| [CI/CD](#cicd) | Phase 3 §2 CI/CD — `tools/cicd/` |
| [Cloud (AWS)](#cloud-aws) | Phase 3 §3 Cloud — `infrastructure/cloud-fundamentals/` |
| [Kubernetes](#kubernetes) | Phase 3 §4 Kubernetes — `infrastructure/orchestration/kubernetes/` |
| [Terraform / IaC](#terraform--iac) | Phase 3 §5 IaC — `infrastructure/iac/terraform/` |
| [LLD / Design Patterns](#lld--design-patterns) | Phase 4 §1 Low-Level Design — `system-design/lld/` |
| [HLD / System Design](#hld--system-design) | Phase 4 §2 High-Level Design — `system-design/hld/` |
| [Distributed Systems](#distributed-systems) | Phase 4 §3 Distributed Systems — `system-design/distributed-systems/` |
| [DSA](#dsa) | Phase 5 §1 DSA — `dsa/` |
| [Operating Systems](#operating-systems) | Phase 5 §2 OS — `cs-fundamentals/os/` |
| [Computer Networks](#computer-networks) | Phase 5 §3 Networks — `cs-fundamentals/cn/` |
| [Data Engineering](#data-engineering-spark-airflow-dbt-warehouses) | Phase 6A Data Engineering — `data-engineering/` |
| [Multi-Cloud / On-Prem](#multi-cloud--on-prem) | Phase 6B Multi-Cloud — `infrastructure/multi-cloud/` |
| [Enterprise Integration & Identity](#enterprise-integration--identity) | Phase 6C Enterprise Integration — `integration/` |
| [AI / LLM](#ai--llm) | Phase 6D AI/LLM Integration — `ai-integration/` |
| [Japanese Language](#japanese-language) | Japanese Track — `japanese/` |
| [Language Tracks](#language-tracks) | Language-Specific Tracks — `languages/*` |
| [General drill sites](#general-drill-sites-mix-of-everything) | Cross-cutting (DSA, coding speed, shell) |

---

## Phase 1 — Daily Engineering Spine

### Git
| Resource | What to do |
|---|---|
| **Learn Git Branching** — learngitbranching.js.org | The definitive interactive git playground. Complete ALL levels (main, remote, and advanced) — commit trees, rebase, cherry-pick, interactive rebase, remotes. Repeat until you can solve each level without hints. |
| **GitHub Skills** — skills.github.com | Free interactive courses (GitHub Actions, PRs, first day on GitHub). Real repo, real PRs. |
| **git-school / visualizer** — git-school.github.io | Visualize what commands do to the commit graph. |
| **Reiteration:** redo "rebase & fixup" + "detaching HEAD" levels from memory weekly until instant. |

### Linux & Shell
| Resource | What to do |
|---|---|
| **OverTheWire: Bandit** — overthewire.org/wargames/bandit/ | The best shell game. SSH into a box each level, solve using shell commands (permissions, find, grep, awk, sort, netcat, base64...). 34 levels — do 3–4/week. |
| **CmdChallenge** — cmdchallenge.com | Quick daily shell drills (cd, pipes, redirects, grep). |
| **Webminal** — webminal.org | Free online Linux terminal for practice anywhere. |
| **Linux Journey** — linuxjourney.com | Short lessons + interactive terminal for each chapter. |
| **Reiteration:** after reading each `bash/*.md` note, reproduce the commands on your own terminal with your own test files. |

### Regex (used daily with grep/sed/awk)
| Resource | What to do |
|---|---|
| **RegexOne** — regexone.com | Step-by-step interactive regex drills. Complete all lessons. |
| **Regex101** — regex101.com | Live regex tester with explanation — verify every pattern you write. |

### SQL
| Resource | What to do |
|---|---|
| **SQLBolt** — sqlbolt.com | Interactive SQL course — do it start to finish in a day or two. |
| **SQLZoo** — sqlzoo.net | Interactive exercises (join, subqueries, aggregates, window functions). |
| **PostgreSQL Exercises** — pgexercises.com | The best practical drill set on a real-ish dataset (basic → joins → subqueries → aggregation → window functions). Aim for full completion. |
| **StrataScratch** — stratascratch.com | Real SQL interview questions from actual companies (join, window functions, CTEs, aggregation). Free tier — filter by "easy/medium" and write the queries yourself before checking solutions. |
| **SQL Murder Mystery** — mysteries.knightlab.com | Gamified SQL — solve a murder using joins/CTEs/window functions. Great consolidation. |
| **Mode Analytics SQL Tutorial** — mode.com/sql-tutorial | Excellent in-browser Postgres; especially the window function + advanced sections. |
| **Reiteration:** pick 3 window-function problems from pgexercises weekly + 1–2 StrataScratch interview questions until they're automatic. |

### Database practice sandbox
| Resource | What to do |
|---|---|
| **Run Postgres/Redis locally** (or via `docker compose`) | Create sample tables, insert 100k+ rows, and test indexes / isolation / locks yourself (the notes list concrete experiments). |
| **Use The Index, Luke** — use-the-index-luke.com | Interactive examples of why indexes do/don't fire. Read the "SQL Where does my query run" pages and trace the plans. |
| **Redis University** — redis.io/university | Free courses incl. "Redis for Developers" with live exercises. |
| **Try Redis** — try.redis.io | 15-min interactive command drill — do it to memorize the data structure commands. |

### Docker
| Resource | What to do |
|---|---|
| **Play with Docker** — labs.play-with-docker.com | Free 4-hour online Docker playground in your browser. |
| **Docker official "Get Started" tutorial** — docs.docker.com/get-started/ | Build + run + compose a real app. |
| **Reiteration:** recreate every `docker/*.md` note's example (build a multi-stage image, compose a stack, debug a broken container) locally. |

### API Design
| Resource | What to do |
|---|---|
| **Postman Learning Center** — learning.postman.com | Interactive API practice environment; build requests, collections, mocks. |
| **httpbin.org** | Free echo/status-code test endpoint — fire real requests and observe codes. |
| **Real APIs to drill against:** GitHub API, Stripe API (test mode), JSONPlaceholder. Read a request's status codes and error bodies. |
| **Reiteration:** after each `api-design/*.md` note, implement that one concept in a tiny local API (idempotency key, cursor pagination, rate limit, error shape). |

### Testing
| Resource | What to do |
|---|---|
| **Reiteration is the whole skill** — there is no playground. After each `tools/testing/*.md` note: write the tests yourself. Unit test a function (with mocks), add a Testcontainers integration test, and lay out a test pyramid for a small project. |

---

## Phase 2 — Building Services

### AuthN/AuthZ
| Resource | What to do |
|---|---|
| **OAuth 2.0 Playground** — oauth.tools | Step through the Authorization Code flow interactively — watch each request/response. |
| **JWT.io** | Decode/verify JWTs — inspect real tokens. |
| **Build a mini OAuth** flow against GitHub/Google as a provider (their free OAuth apps) to see tokens end-to-end. |

### Kafka / Messaging
| Resource | What to do |
|---|---|
| **Confluent Developer** — developer.confluent.io | Free "Kafka 101" + interactive tutorials (Python/Go/Java). |
| **Run Kafka locally** via docker-compose, publish/consume, and try the notes' examples (consumer groups, offsets, DLQ). |

### Caching / Background Jobs
| Resource | What to do |
|---|---|
| No dedicated playground — **build it.** Write a cache-aside with Redis and an idempotent job with retries/backoff (the notes give the patterns). |

---

## Phase 3 — Production Engineering

### Observability
| Resource | What to do |
|---|---|
| **Grafana Play** — play.grafana.org | Interactive live Grafana dashboards — drill on metrics, logs, alerts. |
| **Prometheus playground** | Run Prometheus + a demo exporter in docker-compose and write your own queries/rules. |

### CI/CD
| Resource | What to do |
|---|---|
| **GitHub Skills: Actions** — skills.github.com | Interactive course building real workflows. |
| **Reiteration:** every workflow you write, extend it (add caching, matrix, a deploy job). |

### Cloud (AWS)
| Resource | What to do |
|---|---|
| **AWS getting-started hands-on** — aws.amazon.com/getting-started/hands-on/ | Free step-by-step labs (EC2, S3, Lambda, VPC, IAM). |
| **AWS Workshop Studio** — catalog.workshops.aws | Community-run guided labs in your own account (free tier). |

### Kubernetes
| Resource | What to do |
|---|---|
| **Killercoda** — killercoda.com | Free interactive Kubernetes scenarios in-browser (kubectl, deployments, services, ingress, helm). The spiritual successor of Katacoda. |
| **Play with Kubernetes** — labs.play-with-k8s.com | Real cluster playground for an hour. |
| **Reiteration:** daily `kubectl` fluency — after reading the notes, create/destroy a namespace, deployment, service, HPA on a local k3d/k3s cluster. |

### Terraform / IaC
| Resource | What to do |
|---|---|
| **HashiCorp Developer tutorials** — developer.hashicorp.com/terraform/tutorials | Free guided labs (local provider to start, no cloud needed). |
| **Reiteration:** write a module, apply it, inspect state, destroy — repeatedly until plan/apply is muscle memory. |

---

## Phase 4 — Architecture & Design

### LLD / Design Patterns
| Resource | What to do |
|---|---|
| **Refactoring Guru** — refactoring.guru | Diagrams + code examples — read, then reimplement each pattern in your language. |
| **LLD practice problems** | parking lot, rate limiter, elevator — implement, then compare with a reference. |

### HLD / System Design
| Resource | What to do |
|---|---|
| **Excalidraw** — excalidraw.com | The go-to whiteboard for system design practice — fast freeform drawing, used by most interview prep. Draw every design you study here, not in your head. |
| **draw.io (diagrams.net)** — draw.io | For structured diagrams — C4 context/container/component, AWS/GCP/Azure shape libraries, sequence/ER/flow diagrams. Use for project architecture docs and polished designs. |
| **Miro** | Collaborative whiteboard — use when doing mocks with a peer (Pramp-style). |
| **LLD practice problems** | parking lot, rate limiter, elevator — draw class diagrams in Excalidraw, then implement. |
| **Pramp** — pramp.com (free peer mocks) | 8–10 system design mocks target — you draw live in their shared whiteboard. |
| **ByteByteGo / System Design Newsletter** | Read for breadth; always sketch the design yourself in Excalidraw before reading theirs. |
| **DDIA companion** | github.com/ept/ddia — exercises + discussions for the book. |
| **Reiteration:** for every design you read, redraw it from memory in Excalidraw until you can produce the C4 diagram without notes. |

### Distributed Systems
| Resource | What to do |
|---|---|
| **MIT 6.824** labs — pdos.csail.mit.edu/6.824 | Build a distributed key-value store + Raft. The best hands-on in the field (Go). |
| **Fly.io's Distributed Systems challenge** — fly.io/dist-sys | Distributed systems exercises with a real test harness. |

---

## Phase 5 — Foundations

### DSA
| Resource | What to do |
|---|---|
| **LeetCode** — leetcode.com (NeetCode 150 list, free) | The main trainer. Pattern-based solving, 3–4/week (see DSA notes). |
| **NeetCode** — neetcode.io | Free pattern roadmaps. |
| **Visualgo** — visualgo.net | Interactive algorithm visualizations — use BEFORE coding each pattern to build intuition. |
| **Codeforces / LeetCode contests** | Weekly timed contests for speed (later phase). |
| **Reiteration:** SRS-review solved problems (see `dsa/` notes for the revision log). |

### Operating Systems
| Resource | What to do |
|---|---|
| **OSTEP projects** — github.com/remzi-arpacidusseau/ostep-projects | Real kernel/process/concurrency projects that pair with the book. |
| **pythontutor.com** — visualize pointers/memory | Step through pointer/memory code visually. |

### Computer Networks
| Resource | What to do |
|---|---|
| **Wireshark** + local captures | Sniff your own traffic — see the TCP handshake, DNS, TLS live. |
| **Subnetting practice** | subnetpractice.com — drill CIDR/subnet math until instant. |
| **Cisco Packet Tracer** (free via Cisco NetAcad) | Simulate networks and watch packets traverse them. |
| **httpbin.org + your browser devtools** | Observe HTTP/HTTPS headers, status codes, and requests live. |

---

## Phase 6 — FDE Specialization

### Data Engineering (Spark, Airflow, dbt, warehouses)
| Resource | What to do |
|---|---|
| **dbt Learn** — learn.getdbt.com | Free interactive dbt courses (models, tests, lineage) with a working environment. |
| **Databricks Academy** — databricks.com/learn | Free Spark/PySpark courses with notebooks. |
| **Airflow Tutorials** — airflow.apache.org | Run Airflow in docker-compose and write DAGs (scheduling, retries, sensors). |
| **Kaggle** — kaggle.com | Real messy datasets for ETL practice. |

### Multi-Cloud / On-Prem
| Resource | What to do |
|---|---|
| **Killercoda / Play with K8s** | Reused for on-prem-ish K8s scenarios (kubeadm, OpenShift basics). |
| **Azure / GCP free tier** | Create the AWS-equivalent resources in each (VM, storage, IAM) to learn the mapping. |

### Enterprise Integration & Identity
| Resource | What to do |
|---|---|
| **Okta / Auth0 developer sandboxes** | Free tenant to practice SSO (OIDC/SAML) end-to-end — wire your own app as the SP. |
| **oauth.tools / samltool.com** | Step through OIDC/SAML flows interactively — inspect assertions/tokens. |
| **Build the integration** | Stand up a mock SFTP/SOAP service (or `nc`/a tiny server) and write a client that parses flat files defensively — see `integration/` notes. |

### AI / LLM
| Resource | What to do |
|---|---|
| **OpenAI Playground** — platform.openai.com/playground | Directly experiment with prompts, chat, function calling, structured outputs. |
| **Anthropic Console** — console.anthropic.com | Prompt engineering with tool use + eval tools. |
| **Google AI Studio** — aistudio.google.com | Free model playground (Gemini). |
| **LangSmith / LangGraph tutorials** | Build a real agent; iterate on it. |
| **Reiteration:** every `ai-integration/*.md` note has an experiment — run them all in the playgrounds. |

### Python
| Resource | What to do |
|---|---|
| **Python Tutor** — pythontutor.com | Visualize asyncio/threading/pointers step-by-step. |
| **Exercism Python track** — exercism.io | Mentored practice problems. |

---

## Language Tracks

| Language | Practice |
|---|---|
| **Java/Spring** | Spring Academy (spring.academy, free courses), Baeldung exercises, Exercism Java. |
| **Go** | Go by Example (gobyexample.com), A Tour of Go (go.dev/tour), Exercism Go, **Gophercises** (github.com/gophercises — mini-projects). |
| **Python** | Exercism Python, Codewars, real projects. |
| **TypeScript/Node** | Exercism TypeScript, Advent of Code. |

---

## Japanese Language
| Resource | What to do |
|---|---|
| **WaniKani** — wanikani.com | Kanji SRS (radicals → readings). |
| **Anki** — core 2k/6k decks | Daily vocab SRS. |
| **Bunpro** — bunpro.jp | Grammar SRS per JLPT level. |
| **NHK Easy News** — easyjapanese.net | Daily reading + listening. |
| **Nihongo con Teppei / Japanese with Shun** | Listening practice. |
| **Reiteration:** daily — this is pure spaced repetition. |

---

## General drill sites (mix of everything)
| Resource | What it's for |
|---|---|
| **Exercism** — exercism.io | Mentored coding practice across languages. |
| **Codewars** — codewars.com | Gamified kata per language. |
| **Advent of Code** — adventofcode.com | Seasonal daily problems — great for speed + pattern recognition. |
| **ExplainShell** — explainshell.com | Explains any shell command — use while practicing. |
| **ShellCheck** — shellcheck.net | Lint your bash scripts to learn correct practices. |

---

## How to use this guide
1. **After reading a notes file**, open the matching section here and do the drill within the same sitting.
2. **For repeated use**, keep a rotation: shell game + SQL exercises + 1 LeetCode are a solid daily combo.
3. **Reiteration wins** — these skills degrade fast. Revisit the top 3 per topic before exams/interviews.
