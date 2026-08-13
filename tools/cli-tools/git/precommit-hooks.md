# Pre-commit Hooks

## What Are Git Hooks?

Git hooks are scripts Git runs automatically before or after certain events (commit, push, merge, etc.). They live in `.git/hooks/` — **not versioned**, they stay on your machine.

| Hook | When It Runs |
|------|-------------|
| `pre-commit` | Before the commit is created. Exit code non-zero **aborts** the commit. |
| `commit-msg` | After the message is written, before commit. Good for message linting. |
| `pre-push` | Before `git push`. Good for running tests before pushing. |
| `post-commit` | After commit. Good for notifications. |

## Anatomy of a pre-commit Hook

```bash
#!/bin/sh
# .git/hooks/pre-commit
if [ -f .eslintrc.json ]; then
  npx eslint . || { echo "Lint failed"; exit 1; }
fi
```

The script must be **executable** to run:

```
chmod +x .git/hooks/pre-commit
```

Any non-zero exit code blocks the commit.

## Bypassing Hooks

```
git commit --no-verify    # skip hooks for this commit
git push --no-verify
```

Use sparingly — usually reserved for emergencies (CI is running the checks anyway).

## Sharing Hooks with the Team

`.git/hooks/` isn't versioned, so teammates don't get your hooks automatically. Options:

1. **`core.hooksPath`** — point Git at a versioned hooks directory:
   ```
   git config core.hooksPath .githooks
   ```
2. **pre-commit framework** (pre-commit.com) — `.pre-commit-config.yaml` in the repo, hooks installed once with `pre-commit install`. Handles versioning of hook tools.
3. **Husky** — the npm-ecosystem equivalent, driven by `package.json` + `.husky/` directory.

## Common pre-commit Checks

- Linting / formatting (eslint, ruff, gofmt, prettier)
- Secrets scanning (gitleaks, trufflehog — catches accidentally committed API keys)
- Large-file or merge-conflict-marker detection
- License header checks
- Running a fast subset of tests

## Mental Model

The pre-commit hook is a **cheap local guardrail** — it catches mistakes at the last moment before they enter history, but it's not a substitute for CI (which runs the full checks on the shared branch).
