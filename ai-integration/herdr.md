# Herdr — Agent-Aware Terminal Multiplexer (Backlog)

> **Status:** deferred. Not a current focus. Revisit after Phase 1 core topics (GitHub Workflow, SQL, Docker, API design) are done.

## What it is
A Rust terminal multiplexer for AI coding agents — like tmux, but **agent-aware**. Run multiple agents side by side in panes with live status (working / idle / blocked), persistent sessions that survive closing the laptop, reattach from any terminal or over SSH, plus a socket API for automation.

- Repo: https://github.com/herdrdev/herdr
- Docs: https://herdr.dev/docs/
- Tagline: "the runtime your coding agents live on"

## Why I want to learn it (later)
- Enables running multiple agents on the **same terminal** in parallel panes — work faster with agents.
- Agent state awareness (idle vs. working vs. blocked) is a genuine upgrade over tmux.
- Remote attach / SSH sessions fit FDE work (client boxes, remote environments).

## Why it's deferred
- Current setup: Cursor + single DeepSeek model, personal laptop, small repos — no fleet-of-agents workload yet.
- Underlying multiplexing skill already covered (`ssh-scp-tmux.md` in `tools/cli-tools/bash/`).
- Priority is the unchecked P0 topics on the LEARNING_PATH, not tool-of-the-week chasing.

## When to revisit
- When a project actually needs 2–3 agents running in parallel, or
- Phase 6D (AI/LLM Integration → Agents & Tool-Use) study, or
- If it stabilizes into a clear tmux replacement for daily work.

## Related
- **DeepSeek Harness (`dsh`)** — another deferred agent-tooling item (agent harness, everything-is-a-plugin, MIT). Both belong to the same "agent tooling to evaluate later" bucket, keep them together when you study.
