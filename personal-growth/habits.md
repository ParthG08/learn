# Habits — FDE Operating Principles

*Your edge as an FDE isn't just the technical toolkit — it's how your brain processes ambiguity, handles pressure, and bridges disconnected groups of people. These are the high-leverage intellectual and personal habits that compound over a career.*

---

## I. Information Diet & The Low-Noise Filter

**The problem:** Most AI discourse on social media is optimized for engagement, FOMO, and benchmark hype — not practical engineering or problem-solving.

---

## Why Fundamentals Beat Hype

Focusing on fundamentals and real projects is far more valuable for three reasons:

1. **Hype changes weekly; foundations don't.** The underlying concepts — data pipelines, evaluation metrics, prompt architecture, API integration, product design — stay constant regardless of which model leads the leaderboard this week.

2. **Benchmarks rarely reflect real-world utility.** A model that scores 2% higher on an academic benchmark might be slower, harder to steer, or negligible in actual production.

3. **Building builds intuition.** You learn more about model failure modes, latency constraints, and cost trade-offs by deploying one real project than by reading 100 benchmark threads.

---

## The Sustainable "Low-Noise" Filter

Instead of tracking daily announcements, use a simple rhythm:

1. **Pick a reliable default model** (a standard GPT-4o / Claude Sonnet-class workhorse) and build your project.

2. **Abstract your model layer** using simple wrappers or tools like LiteLLM so you can swap models with a single environment variable later.

3. **Check in once a month or quarter** via a curated digest or release notes — *only* when your current workflow hits a concrete wall (cost, speed, or quality).

---

## The Rule

> Don't chase the leaderboard. Chase the fundamentals. Build first, upgrade only when a concrete constraint forces it.

---

## II. The Six Compounding Habits

### 1. Dispassionate De-escalation (Intellectual Calm)

- **The Reality:** FDEs are dropped into high-stakes, broken environments where clients are frustrated and timelines are aggressive.
- **The Habit:** Separate *urgency of emotion* from *urgency of action*. When a client or internal lead panics, your baseline state becomes visibly calmer and more methodical.
- **Practice:** Before responding to an escalation, pause and write down the facts strictly as data points (what broke, when, impact) — removing all emotional adjectives.

### 2. High "Cognitive Code-Switching"

- **The Reality:** In a single day you might talk to a VP of Finance about ROI, an enterprise security officer about VPC peering, and a backend developer about concurrency bugs.
- **The Habit:** Actively practice translating complex ideas between different mental models.
- **Practice:** For any technical concept or business model you learn, explain it in two distinct ways:
  - **To an executive** — in terms of risk, speed, and cost.
  - **To a junior engineer** — in terms of inputs, state, and edge cases.

### 3. Radical Intellectual Humility (First-Principles Skepticism)

- **The Reality:** Client environments are filled with legacy assumptions ("We do it this way because it's the only secure way"). Take them at face value and you get stuck; act arrogant and they push back.
- **The Habit:** Cultivate genuine curiosity without judgment. Ask *"Help me understand what problem led to this design?"* instead of *"Why are you doing it this way?"*
- **Practice:** Default to assuming you don't have the full context until you've traced the problem back to the raw source code or data logs.

### 4. Writing for Extreme Cognitive Low-Load

- **The Reality:** Brilliant engineers fail as FDEs because their thought process is a tangled mess in emails and Slack.
- **The Habit:** Make your thinking effortless for others to parse.
- **Practice:** Structure every decision or proposal around: **Context → Core Decision → Options Considered → Tradeoffs → Recommended Next Step.** Eliminate fluff; respect the reader's cognitive bandwidth.

### 5. High Agency / Low Helplessness

- **The Reality:** In deployed environments, documentation is missing, APIs lack credentials, and access is blocked.
- **The Habit:** Eliminate the phrase *"I'm waiting on X"* from your vocabulary. Replace it with *"While blocked on X, I've mocked the interface and started on Y."*
- **Practice:** Treat every roadblock as a navigation puzzle, not a stopping point. Always create a provisional, temporary path forward on your own.

### 6. Relentless Systems Thinking (Second-Order Consequences)

- **The Reality:** Quick hacks in client deployments often create hidden technical debt or political friction.
- **The Habit:** Whenever you propose a fix, deliberately ask: *"And then what happens?"*
- **Practice:** Trace changes two steps ahead — if I deploy this patch, how does it affect their data governance next month? How does it affect our core platform's maintenance burden next quarter?

---

## III. Off-the-Job Reps (Daily & Weekly Drills)

*To build the intellect, instinct, and presence of an elite FDE outside of work, you need reps that train architectural judgment, clear verbal articulation, and systems empathy — daily and weekly, compounded over years.*

### 1. Reading: Trade Twitter for RFCs, Post-Mortems, and 10-Ks

- **Weekly Post-Mortem Dissections** — read real-world incident post-mortems (Cloudflare, AWS, Uber, GitHub).
  - *Why:* FDEs live in degraded environments. Post-mortems train your brain on how complex distributed systems *actually* fail, not how they work in textbooks.
- **Architecture Docs & RFCs over Tutorials** — read system whitepapers and open-source RFCs (Kafka design docs, SQLite architecture, Raft consensus paper).
  - *Why:* You learn the trade-offs authors made, which trains your judgment on *why* certain architectural constraints exist.
- **Occasional Business Literacy (10-Ks & S-1s)** — read the business overview and risk factors of enterprise SaaS companies' annual filings.
  - *Why:* An FDE must understand how enterprise clients make money, evaluate vendor risk, and justify budgets.

### 2. Communication: The "Verbal Synthesis" Drill

- **The 60-Second "Explain to a VP" Exercise** — pick one complex technical primitive each week (Raft consensus, vector indexing, OAuth2 authorization code grant, reverse proxies). Record a 60-second voice memo explaining:
  1. What business problem it solves.
  2. The primary failure mode/risk.
  3. The core trade-off (cost vs. speed vs. simplicity).
  - *Rule:* Zero jargon a non-technical executive wouldn't understand.
- **Join a Public Speaking Forum** (Toastmasters or Meetup Lightning Talks).
  - *Why:* FDEs frequently stand in front of skeptical client rooms with mixed technical backgrounds. Unscripted, high-stakes speaking removes stage fright and teaches you to read a room in real time.

### 3. System Design: "Reverse-Engineering" on Paper

- **Daily 15-Minute Architecture Sketching** — pick a real service you use (Stripe's webhook delivery, Figma's collaborative state engine, Uber's dynamic pricing) and sketch the end-to-end architecture on blank paper: **Ingestion → Storage → Caching → Failure Queues → Auth boundary.**
- **Ask the "Failure Question"** — on every sketch, circle two components and ask: *"If this service has a 500ms network timeout or returns malformed JSON, what fails silently, and what explodes?"*

### 4. Technical Literacy: "Source Code Archaeology"

- **Read Open-Source Repositories (Not Just Docs)** — pick a popular, battle-tested tool or library (requests, Redis core, FastAPI, LiteLLM, ClickHouse client) and trace a single request from entry point down to the socket or DB driver.
  - *Why:* On a client site with obscure errors and no documentation, being comfortable jumping straight into library source code makes you 10x faster than anyone relying on Google/StackOverflow.

### 5. Writing: The "One-Page Architecture Decision Record" (ADR)

- **Practice Synthetic Writing** — whenever you build a side project or solve a tricky personal tech problem, write a 1-page ADR in this exact format:
  1. **Context:** What is the actual problem constraint?
  2. **Options Considered:** 2–3 alternatives.
  3. **Trade-offs:** Latency vs. complexity vs. cost.
  4. **Decision:** What was chosen and why.
  5. **Consequences:** What technical debt are we consciously taking on?
  - *Why:* Writing cleanly forces you to clarify your thinking. If you can write an ADR in 20 minutes, you can lead technical alignment meetings effortlessly.

---

## IV. The Weekly Cadence

| Frequency | Habit | Target Muscle |
| :--- | :--- | :--- |
| **Daily (15 min)** | Paper system design sketches / Open-source code reading | Architectural intuition & low-level literacy |
| **Weekly (30 min)** | Read one real-world post-mortem | Failure-mode analysis & resilience |
| **Weekly (15 min)** | 60-second voice memo translation drill | High-stakes executive communication |
| **Monthly** | Give a technical talk or write a rigorous 1-page ADR | Synthesis, persuasion, and clarity |
