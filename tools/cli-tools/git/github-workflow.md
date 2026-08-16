# GitHub Workflow

## Forking vs. Branching

| Approach | When used | Model |
|---|---|---|
| **Branch + PR** | You have write access to the repo | Single shared repo, feature branches |
| **Fork + PR** | External contributor / no write access | Your own copy of the repo → PR back to upstream |

### Fork flow
1. Click "Fork" on GitHub → creates your copy `you/repo`.
2. `git clone https://github.com/you/repo.git`
3. Add upstream: `git remote add upstream https://github.com/original/repo.git`
4. Keep in sync:
   - `git fetch upstream`
   - `git checkout main && git merge upstream/main` (or `rebase`)
5. Create a branch, commit, push to `origin`, open a PR from `you/branch` → `original/branch`.

---

## Pull Requests

### Anatomy of a good PR
- **Title:** imperative, summary of change (matches commit style: "Add retry logic to sync worker").
- **Description:** what / why / how. Template usually covers:
  - Problem being solved
  - Approach + tradeoffs
  - Screenshots / before-after
  - Test plan
  - Breaking changes / migration notes
  - Issue link (`Closes #123`)
- **Size:** keep small — one logical change per PR. Large PRs get shallow review.
- **Linked issue:** auto-close by writing `Fixes #42` in the body.

### PR lifecycle
```
open → draft (WIP) → ready for review → requested changes → approved → merge
```

### Reviewing (the reviewer's job)
- Review the *diff intent*, not just the code — "why does this exist?"
- Ask questions before demanding changes; mark nits vs. blockers.
- Use GitHub review comments: inline comments, or comment + `suggest` (suggested change can be committed in one click).
- Approve only when you'd accept it merged as-is.

### Author workflow
- Respond to every review comment (reply or resolve).
- Push follow-up commits; prefer fixups if the branch will be rebase-merged.
- Re-request review after addressing feedback.

---

## Code Review Best Practices

1. **Automate the mechanical stuff** — lint, format, typecheck, tests in CI so humans review logic, not style.
2. **Review in small batches** — review at most ~400 LOC at a time; beyond that quality drops.
3. **Read tests as documentation** — if tests are clear, the behavior is clear.
4. **Check for the silent bugs:**
   - Race conditions / thread safety
   - Error handling paths (what happens on failure?)
   - Resource leaks (connections, file handles)
   - Security (input validation, authz on every endpoint, secrets in logs)
   - Backward compatibility (schema changes, API contract)
5. **Don't nitpick** — prefer a handful of substantive comments over dozens of style ones.
6. **Use the "why" test** — if a comment asks a question, the author may need to explain in code/docs instead.

### PR review checklist (quick)
```
[ ] Solves the stated problem
[ ] No scope creep
[ ] Edge cases handled
[ ] Tests cover the change
[ ] Docs/CHANGELOG updated if needed
[ ] No secrets or debugging leftovers
[ ] Performance reasonable
[ ] Naming clear
```

---

## Protected Branches

Branch protection rules (repo Settings → Branches) enforce quality gates on key branches (usually `main`):

| Rule | Effect |
|---|---|
| **Require PR before merging** | No direct pushes to the branch |
| **Require approvals** | e.g. at least 1–2 approving reviews |
| **Dismiss stale reviews** | New commits invalidate old approvals |
| **Require status checks** | CI must pass before merge (lint/test/build) |
| **Require up-to-date branch** | Branch must be rebased on latest `main` |
| **Linear history** | Only squash/rebase merges allowed (no merge commits) |
| **No force-pushes** | Prevents history rewrite on protected branch |
| **Code owners review** | Files owned by specific teams need their review |
| **Include administrators** | Even admins must follow the rules |

---

## Merge Strategies

| Strategy | History | When to use |
|---|---|---|
| **Create a merge commit** | Preserves branch topology, has merge commits | Feature branches you want to keep visible |
| **Squash and merge** | Single clean commit, linear history | Default for most repos; PR = 1 commit on main |
| **Rebase and merge** | Linear, every PR commit preserved | When individual commits matter |

- **Squash** loses the granular commits — good for cleanup, bad if you want bisect granularity.
- Choose one default per repo and stay consistent.

---

## CI Integration

GitHub Actions workflow basics (`.github/workflows/ci.yml`):

```yaml
name: CI
on:
  pull_request:
  push:
    branches: [main]
jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v4
      - uses: actions/setup-node@v4
        with:
          node-version: 20
      - run: npm ci
      - run: npm run lint
      - run: npm test
```

### Common CI jobs for a backend repo
- **lint / format** — style only, fails fast
- **unit tests** — fast, no external deps
- **integration tests** — spin up DB/cache (Testcontainers) 
- **build / typecheck** — compiles and catches type errors
- **coverage report** — guard against regressions (optional threshold)
- **deploy** — only on `main` after tests pass (or via CD)

### CI patterns
- **Required status checks:** the PR can't merge until these jobs pass.
- **Secrets:** use GitHub Secrets / Environments — never commit `.env`.
- **Matrix builds:** test multiple OS/node versions.
- **Caching:** cache `node_modules`/`~/.npm` etc. to speed up runs.
- **Path filters:** run job only when relevant files change (`paths:`).

---

## GitHub CLI (`gh`)

```bash
gh pr create --title "..." --body "..."         # create PR from current branch
gh pr checkout 123                              # checkout PR #123 locally
gh pr review 123 --approve                      # approve
gh pr diff 123                                  # view diff
gh pr status                                    # your open PRs
gh repo fork <owner/repo>                       # fork + clone
gh workflow run ci.yml                          # trigger workflow
gh run list                                     # recent runs
gh run watch                                    # watch a run live
```

---

## Quick reference
- Fork = your remote copy; branch = your local copy in the same repo.
- PR merges should require: CI green + ≥1 approval + branch up to date.
- Squash-and-merge keeps `main` linear and reviewable.
- `gh` CLI makes PR creation/review scriptable from the terminal.
