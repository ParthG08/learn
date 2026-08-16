# Shell Setup — zsh aliases & config

Setup notes for the zsh shell environment. Companion guides: `zoxide/setup.md`, `fzf/setup.md`, `cclip/setup.md`.

## Config Location (IMPORTANT)

This machine uses **zsh** with **`ZDOTDIR = ~/.config/zsh`**. All real config lives there:

| File | Purpose |
|---|---|
| `~/.config/zsh/.zshrc` | Main config — sources the aliases file, initializes zoxide/fzf |
| `~/.config/zsh/.zsh_aliases` | **All user aliases** live here |
| `~/.config/zsh/.zshenv` | Sources everything in `conf.d/*.zsh` (HyDE) |

> **Gotcha:** `~/.zshrc` (in `$HOME`) is **NOT loaded** — editing it does nothing. Edit the files under `~/.config/zsh/`.

## Aliases File

All aliases are in `~/.config/zsh/.zsh_aliases`, sourced from `.zshrc` via:

```sh
[ -f "$ZDOTDIR/.zsh_aliases" ] && source "$ZDOTDIR/.zsh_aliases"
```

| Alias | Command | Purpose |
|---|---|---|
| `oc` | `opencode` | start opencode |
| `occ` | `opencode --continue` | continue last opencode session |
| `batt` | `function batt()` | battery health & status summary via sysfs — status, current %, health % (capacity vs design), cycle count, voltage — Linux only |
| `gcb` | `git checkout $(git branch \| fzf)` | fuzzy-pick a branch to check out |
| `y` | `yazi` | open yazi, stay in the current directory on quit (plain alias) |
| `yy` | `function yy()` | open yazi, then `cd` to the last directory on quit (function — an alias can't run code after the program exits) |

### Adding a new alias

1. Edit `~/.config/zsh/.zsh_aliases`
2. Use **single quotes** if the command contains `$(...)` so it expands at *use* time, not definition time
3. Reload: `source ~/.config/zsh/.zsh_aliases`

## Verify

```bash
type gcb          # "gcb is an alias for git checkout $(git branch | fzf)"
```

## Why gcb

`git branch | fzf` gives an interactive list of branches to pick from, then checks it out — no need to type or remember branch names. Requires `fzf` (see `fzf/setup.md`).

## Why y vs yy

- `y` is a plain alias for `yazi` — good when you just want to browse without changing the shell's directory.
- `yy` is a function: it writes the last browsed directory to a temp file via `--cwd-file`, then `cd`s into it on quit. A plain alias can't do this (the `cd` must run *after* yazi exits), so it needs a function. Works only when yazi is quit with `q`, not `<C-c>`. See the full function in `.zsh_aliases`.
