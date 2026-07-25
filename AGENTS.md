# AGENTS.md — opencode Instructions for FDE Learning Repository

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
