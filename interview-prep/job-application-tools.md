# Job Application Workflow — $0/mo

One pipeline, 4 tools, applied repeatedly per application. Everything runs through a single flow: **Source → Tailor → Apply → Track → Prep**.

- **resume-as-code** — master resume, built once
- **LuJie CareerKit** — the hub (tracker + JD match + export)
- **DeepSeek** — the engine (tailoring + scoring + prep)
- **Simplify** — the hands (auto-fill forms)

---

## The One-Time Setup

### 1. Build the master resume (once)

**resume-as-code** — `github.com/zhiweio/resume-as-code`

Catalog your entire career in one YAML file: every role, project, skill, cert. This is the single source of truth — you never write a bullet twice, you only add to it.

- Point the LLM config at `api.deepseek.com` (free tier or ~$0.27/M tokens)
- From here on, every resume you produce is generated from this file — nothing is hand-typed per application

### 2. Wire up the hub

**LuJie CareerKit** — `github.com/Chozzc/Lujie-Careerkit`

Local app, SQLite, runs in your browser. This is your command center — it replaces Jobscan, JobTrackfy, Teal, and every other SaaS tracker in one install.

- Set `VITE_AI_API_URL=https://api.deepseek.com/v1` + your DeepSeek key
- Create kanban columns: **Research → Applied → Screening → Interview → Offer**
- Use it for: JD match score, resume editing, tracking, and AI mock interviews

### 3. Install the hands

**Simplify** — `simplify.jobs` (Chrome extension)

Auto-fills Greenhouse, Lever, Workday, and 50+ ATS forms. Install once; it also auto-tracks applications, so your Apply history is captured without manual entry.

---

## The Per-Application Loop

For every target role, run this loop — it takes ~20 minutes:

### Step A — Source the role

Pick a target from the FDE board, then go straight to the company's ATS:

- **Board:** `fde.directory/jobs` (curated, global, Tokyo included)
- **ATS:** `boards.greenhouse.io/anthropic`, `jobs.lever.co/palantir`, etc.
- **Japan boards:** `japan-dev.com`, `tokyodev.com`, `japanjobscan.com` (scrapes 1,000+ ATS pages), `gaijinjobs.com`
- **Search alternate titles too:** Solutions Engineer, Deployment Strategist, Applied AI Engineer, Professional Services Engineer, Partner Engineer, Customer Engineer, Field Engineer

### Step B — Match check (LuJie CareerKit)

Paste the JD into CareerKit. It shows keyword overlap % and your missing skills instantly. If match is <60%, skip or deprioritize — your time is better spent elsewhere.

### Step C — Tailor bullets (DeepSeek)

Feed your master resume + the JD. Two passes:

**Per-bullet rewrite:**
```
Here is a resume bullet:
"[paste bullet]"

Here is a JD excerpt:
"[paste JD section]"

Rewrite to surface relevant keywords without inventing anything.
Under 25 words. Active verbs. Quantify where truthful.
```

**Full pass:**
```
My master resume:
[paste from resume-as-code]

Job description:
[paste]

Identify top 10 keywords in the JD. Suggest rewritten bullets for the 3 most
relevant experiences. Keep all metrics factual — do not fabricate numbers.
```

### Step D — Score it (DeepSeek acts as ATS)

```
Act as an ATS screener. Compare this resume to the JD.
Score 0–100 on keyword overlap, skill alignment, role fit.
List top 5 missing keywords. Flag any formatting risks.

Resume: [paste]
JD: [paste]
```

If the score is weak, go back to Step C and fix the missing keywords. If strong, continue.

### Step E — Export & apply (CareerKit → Simplify)

1. Export the tailored PDF from LuJie CareerKit
2. Open the company ATS page → click Apply
3. Simplify auto-fills the form; the application is auto-tracked in both Simplify and CareerKit
4. Move the card to **Applied**

### Step F — Prep for the interview

Before the phone screen, ask DeepSeek:

```
"What would a Forward Deployed Engineer interview at [Company] look like?
Generate 10 likely questions from this JD: [paste]"
```

Then run the AI Mock Interview in CareerKit on the top 3–5 hardest ones. Move the card to **Interview**.

---

## The Rhythm

Repeat the loop per role. Once a week, sweep CareerKit: advance cards, drop dead leads, re-tailor the best-fit ones. Your master resume in resume-as-code only ever grows — tailoring is generated, never rewritten from scratch.

---

## Japan-Specific Notes

- **Rirekisho (履歴書) / Shokumu Keirekisho (職務経歴書):** maintain these manually — none of the tools above support Japanese formats
- For FDE roles at international companies in Japan, English resumes are usually sufficient
- N2+ Japanese expands your options 10x — `wantedly.com`, `green-japan.com`, `findy-code.io`, `lapras.com` open up
- **Known FDE orgs in Japan (2026):** Palantir (bilingual EN/JP), Stripe, Databricks, Snowflake, Cognition (Devin) — Tokyo/Singapore seats
