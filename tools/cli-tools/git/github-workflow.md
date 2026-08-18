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

## GitHub Flow vs. Git Flow

Two common branch models. Pick one per repo and standardize.

### GitHub Flow (default for most modern repos)

- `main` is **always deployable**.
- Everything else lives on short-lived feature branches.
- Loop: branch → commit → PR → review → squash-merge → deploy.

```
main (always green) ── merge ── merge ── merge
                      ▲        ▲        ▲
feature/a  ───────────┘        │        │
feature/b  ────────────────────┘        │
feature/c  ─────────────────────────────┘
```

- Best for: continuous deployment, SaaS, small–medium teams.
- Why it wins: no long-lived branches, `main` never diverges, PRs are the single review gate.

### Git Flow (release-driven, legacy but still common)

- `main` = production releases **only** (every commit tagged with a version).
- `develop` = integration branch where features accumulate.
- `feature/*` branches off `develop` → merge back into `develop`.
- `release/*` branches off `develop` for stabilization → merge into `main` + back to `develop`.
- `hotfix/*` branches off `main` → merge into `main` + `develop`.

```
main     ──●──────────────────────● (v1.0) ────────● (v1.0.1)
           \                    /                  /
develop  ────●──●──●──●────────●──●────────────●───
              \  \     \      /
feature/*      ●   ●     ●    ●
```

- Best for: versioned releases (libraries, installed software), scheduled releases, strict change-control environments.
- Downsides: ceremony, `develop` and `main` can diverge, merge commits everywhere, harder to CD.

### Which to use

| | GitHub Flow | Git Flow |
|---|---|---|
| `main` meaning | deployable at all times | release-only |
| Branch lifetime | days | weeks (`develop` + `release`) |
| Merge model | squash, linear | merge commits, preserved topology |
| Releases | deploy on merge | tagged release branches |
| When | most projects, CD | versioned releases, compliance |

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
open (draft) → mark ready → requested review → approved / changes requested → merge / close
```

### Draft PRs
- **Draft** = "not ready yet" — no review is requested, cannot be merged.
- Use it for work-in-progress, testing CI on your branch, or sharing early design.
- Convert to **ready for review** (`gh pr ready 123`) when done — only then is it mergeable.

### Requesting & re-requesting review
- **Request review** explicitly assigns reviewers; without an explicit request, "require approvals" can't be satisfied.
- Pushing new commits **dismisses stale approvals** (if the rule is on) and moves the PR back to needing review.
- After addressing feedback, **re-request review** (`gh pr edit 123 --add-reviewer`) instead of hoping the reviewer notices.
- PR states are the source of truth: `OPEN`, `DRAFT`, `APPROVED`, `CHANGES_REQUESTED`, `MERGED`, `CLOSED` (`gh pr view 123`).

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

### CODEOWNERS — automatic review assignment by path
- A `.github/CODEOWNERS` file assigns code owners to paths; anyone opening a PR that touches those paths **automatically gets the owner team requested for review**.
- Syntax (paths follow `.gitignore` matching):
  ```gitignore
  *                      @org/core-platform
  apps/api/**            @org/backend-eng
  apps/web/**            @org/frontend-eng
  *.md                   @docs-owners
  /infra/terraform/**    @platform-eng
  ```
- Combine with the **"Require review from code owners"** branch rule: changes to an owned path can't merge without that owner's approval.
- Unmatched paths fall through to the previous matching rule (or the repo default if none match).

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
- **Reusable workflows:** `uses: owner/repo/.github/workflows/build.yml@main` to share a pipeline across many repos instead of copy-pasting.
- **Workflow triggers:** `pull_request`, `push`, `workflow_dispatch` (manual), `schedule` (cron), `merge_group` (merge queue).

### Protecting deployments (Environments)
- **Environments** (Settings → Environments) gate *deployments*, not just merges.
- Rule examples: `production` requires an approving review + a wait timer, and only deploys from `main`; `staging` is automatic.
- Deployment jobs reference the environment via `environment: production` and read its secrets — production secrets are never available to PR jobs.

### Action security hygiene
- **Pin actions to a full commit SHA** (not `@main`) for supply-chain safety; update deliberately.
- Give each job the **least-privilege `permissions:`** block instead of the repo-wide default.
- Never log secrets; pass `${{ secrets.X }}` only via `env`/`with` and mask anything sensitive.

---

## GitHub CLI (`gh`)

```bash
gh pr create --title "..." --body "..."         # create PR from current branch
gh pr create --draft                            # create as draft
gh pr ready 123                                 # mark draft → ready for review
gh pr checkout 123                              # checkout PR #123 locally
gh pr review 123 --approve                      # approve
gh pr review 123 --request-changes --body "..." # request changes
gh pr view 123                                  # state, reviewers, checks
gh pr edit 123 --add-reviewer @org/backend-eng  # (re-)request review
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
- CODEOWNERS auto-requests review by path; pair it with branch protection.
- `gh` CLI makes PR creation/review scriptable from the terminal.
