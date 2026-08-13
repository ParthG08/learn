# AGENTS.md — opencode Instructions for FDE Learning Repository

## Outside-the-Repo Changes Policy

- **Never make changes outside the learn repo** (e.g., `~/.zshrc`, `~/.zsh_aliases`, `~/.bash_aliases`, home-dir configs).
- If a task truly requires touching a file outside the repo, **ask the user once first** before doing it.
- Shell config files live in the repo under `dotfiles/` (e.g., `dotfiles/zsh_aliases`, `dotfiles/bash_aliases`). These are the source of truth — edit them here, not the home-dir copies.

## Web Search/Scraping Tools Policy (Exa + Firecrawl)

- **Only use Exa tools (`exa_web_search_exa`, `exa_web_fetch_exa`, `exa_web_search_advanced_exa`) and Firecrawl CLI tools (`firecrawl scrape`, `firecrawl search`, etc.) when the user explicitly says the phrase: "deep research with exa and firecrawl".** Otherwise, do not touch them.
- Each time Exa or Firecrawl is used, hit the respective usage/status API and report credits remaining:
  - Firecrawl: `npx -y firecrawl-cli@latest --status`
  - Exa: TBD (check Exa dashboard or API for credit usage endpoint)

## Context

This repository tracks my journey to become a **Forward Deployed Engineer (FDE) in Japan** within 2–3 years. The `learning-process/LEARNING_PATH.md` defines the full skills roadmap. I create notes as Markdown files for everything I study. opencode's job is to:

---

## Current Topic

**Phase 1.2 — Linux & Shell: Process management** (sub-topic of first checkbox)
- Status: **in progress**
- Notes created: `ownership-permissions.md`, `user-groups-permissions.md`, `find/find-exec.md`
- Waiting on: `process-management/process-management.md` (commands: `ps`, `killall`, `top`, `bg`, `jobs`, `fg`, `kill`, `shutdown`)
- Next after this: `filesystem-navigation.md`, then grep/sed/awk for log parsing

---

---

## Responsibilities

### 1. Cross-Validate the Learning Path Against FDE Requirements

The learning path at `learning-process/LEARNING_PATH.md` is the canonical roadmap. Periodically, or when asked, verify it covers every skill an FDE needs — especially for **Japan** (Japanese language, Japanese enterprise tech stacks, Japan-specific compliance, business culture). Flag gaps explicitly.

### 2. Track Progress From Notes Files

- Every topic in `LEARNING_PATH.md` maps to a directory in this repo (e.g., `tools/git/`, `languages/java/`, `cs-fundamentals/os/`).
- **Progress is determined by the existence and quality of notes files in those directories**, not by manually toggling checkboxes.
- When I ask for a progress update, scan the relevant directories, check which topics have notes, and report:
  - What's done (has substantive notes)
  - What's in progress (has some files but incomplete)
  - What's untouched (empty directory or directory doesn't exist)
- Update the `[ ]` → `[x]` checkboxes in `LEARNING_PATH.md` based on actual notes found in the repo.

### 3. Daily Study Recommendations

When I ask "what should I study today?", "what is next?", "what's next?", "what do I study now?" (or similar):
- Look at `learning-process/LEARNING_PATH.md` and follow the **exact sequence** (Phase 1 → 9, within each phase top-to-bottom, P0 → P1 → P2).
- Identify the **first unchecked ( `[ ]` ) topic** in the sequence — that's what I study next.
- Tell me:
  - **What** to study (specific topic and sub-topics)
  - **Where** to create the notes file (exact directory path)
  - **Sources** from the resources listed in the learning path
- Factor in the parallel tracks (DSA problems 3–4/week, Japanese study daily).

### 4. Marking Topics as Done

After I finish studying a topic and create/update the notes file:
- **Review the latest notes file** to verify it covers all the sub-topics listed in that checkbox item comprehensively.
- If the notes are complete and cover everything useful for that topic:
  - Change `[ ]` → `[x]` in `LEARNING_PATH.md`.
  - **Append the notes filename** beside the checkbox using the format `— \`filename.md\`` (or multiple files if applicable).
  - Strike through the notes file link so it reads like: `— ~~\`filename.md\`~~` (if there was a placeholder).
- If the notes are incomplete or only cover part of the topic, leave it unchecked until the rest is covered.
- **Do not** mark topics as done based on directory existence alone — only when the actual notes content is complete and useful.

---

## Spaced Repetition System (SRS)

Every `.md` note in this repo is a review card. The SRS engine is `scripts/srs.py`
(SM-2 algorithm, standard-library only, no deps). Performance lives in `.srs/state.json`
(never the quiz content — quizzes are generated fresh each session).

**Engine commands:**
- `python scripts/srs.py today` — list due cards, grouped by topic (optionally `--topic DIR`)
- `python scripts/srs.py update <path> <rating>` — record `again|hard|good|easy`, recompute schedule
- `python scripts/srs.py schedule` — upcoming reviews per topic
- `python scripts/srs.py stats` — deck summary

**The review session loop** (when I say "review", "revise", "quiz me", or "SRS"):
1. Run `python scripts/srs.py today` → get the due cards.
2. For each due card, **read the `.md` file** and drive a free-recall session:
   - Present the key points from the notes
   - Ask one open-ended question at a time (no MCQs), let me answer from memory
   - Grade honestly: `again` = forgot, `hard` = struggled, `good` = recalled, `easy` = trivial
3. After my answer, run `python scripts/srs.py update <path> <rating>` for that card.
4. Report the new interval for each card, then summarize the remaining list.
- Stop when the `today` list is empty or I call it.

---

## LeetCode Solutions Sync (.cpp ↔ .md)

`dsa/lc-solutions/` keeps every solution as a pair of files that must stay in sync:

- `NAME.cpp` — the code (source of truth, you compile/test this)
- `NAME.cpp.md` — an Obsidian-friendly mirror (header + the code in a ` ```cpp ` fence)

**Consistency rule:** when you create or change a solution, always keep both files
consistent — the two are meant to display the same code.

**The canonical, reliable way is the sync script `scripts/lc_sync.py`** (do not hand-edit
the `.md` code block):
- `python scripts/lc_sync.py` — regenerate every `.cpp.md` mirror from its `.cpp`
- `python scripts/lc_sync.py md2cpp` — push an edited `.md` code block back into `.cpp`
- `python scripts/lc_sync.py check` — report any pair that has drifted

**Workflow to follow:**
1. Edit the `.cpp` normally (or edit the code block in the `.md` in Obsidian).
2. Run the appropriate sync command above to update the mirror.
3. Run `python scripts/lc_sync.py check` to confirm the pair is in sync before finishing.

Do not let the `.cpp` and its `.cpp.md` diverge — if a pair is out of sync, run the script
to reconcile, and note which file was the intended source.

---

## Notes File Conventions

- Notes are Markdown (`.md`) files inside the topic's directory.
- Directory structure mirrors `LEARNING_PATH.md` sections:
  - `tools/git/` → Phase 1.1 (Git)
  - `tools/cli-tools/bash/` → Phase 1.2 (Linux & Shell)
  - `tools/docker/` → Phase 1.5 (Docker) — **note: existing notes are in `tools/cli-tools/docker/`, consider moving**
  - `languages/java/` → Language-Specific Track (Java/Spring)
  - `languages/golang/` → Language-Specific Track (Go)
  - `languages/python/` → Language-Specific Track (Python)
  - `languages/typescript/` → Language-Specific Track (TypeScript)
  - `cs-fundamentals/dbms/` → Phase 1.4 (Databases)
  - `cs-fundamentals/os/` → Phase 5.2 (Operating Systems)
  - `cs-fundamentals/cn/` → Phase 5.3 (Computer Networks)
  - `api-design/` → Phase 1.6 (API Design)
  - `messaging/` → Phase 2.5 (Messaging & Kafka)
  - `tools/observability/` → Phase 3.1 (Observability)
  - `tools/cicd/` → Phase 3.2 (CI/CD)
  - `infrastructure/cloud-fundamentals/` → Phase 3.3 (Cloud)
  - `infrastructure/orchestration/kubernetes/` → Phase 3.4 (Kubernetes)
  - `infrastructure/iac/terraform/` → Phase 3.5 (IaC)
  - `infrastructure/multi-cloud/` → Phase 6B (Multi-Cloud)
  - `system-design/lld/` → Phase 4.1 (Low-Level Design)
  - `system-design/hld/` → Phase 4.2 (High-Level Design)
  - `system-design/distributed-systems/` → Phase 4.3 (Distributed Systems)
  - `dsa/` → Phase 5.1 (DSA)
  - `data-engineering/` → Phase 6A (Data Engineering)
  - `ai-integration/` → Phase 6D (AI/LLM Integration)
  - `integration/` → Phase 6C (Enterprise Integration)
  - `projects/` → Phase 7 (Projects & Portfolio)
  - `business/` → Phase 8 (Business / Customer Engineering)
  - `interview-prep/` → Phase 9 (Interview Preparation)
  - `personal-growth/japan/` → Japanese language study (not in LEARNING_PATH.md but critical for Japan FDE)
  - `personal-growth/escape/` → Extra-curriculars & life outside work
  - `personal-growth/savings/` → Personal finance & tax strategy

---

## Missing Directories to Create

When starting new topics, create these directories if they don't exist:
- `api-design/`
- `data-engineering/`
- `ai-integration/`
- `integration/`
- `messaging/`
- `infrastructure/multi-cloud/`
- `system-design/distributed-systems/`
- `personal-growth/japan/`
- `languages/python/`
- `languages/typescript/`
- `projects/`
- `business/`
- `interview-prep/`
