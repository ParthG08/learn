# OpenCode Aliases — New Machine Setup

Aliases to set up when installing opencode on a new laptop.

## Aliases

| Alias | Command |
|-------|---------|
| `oc` | `opencode` |
| `occ` | `opencode --continue` |

## How to Set Up

**Option 1 — run the repo setup script (recommended):**

```bash
bash scripts/setup.sh
```

It appends both aliases to `~/.zshrc` only if they aren't already present (idempotent).

**Option 2 — manual:**

Add to `~/.zshrc`:

```sh
alias oc="opencode"
alias occ="opencode --continue"
```

Then reload: `source ~/.zshrc`.

## Verify

```bash
which oc occ
```

## Why

- `oc` → quick way to start opencode.
- `occ` → continue the last session (equivalent to `opencode -c`), which is the most common daily action.
