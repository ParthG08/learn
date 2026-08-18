# OpenCode — New Machine Setup

Setup notes for opencode. Replica: `tui.json` in this directory → live
`~/.config/opencode/tui.json`. Installed via the standard installer (see
<https://opencode.ai/docs/installation/>).

## TUI keybindings (tui.json)

opencode's TUI keybinds are configured in `~/.config/opencode/tui.json`.
Replica: `tui.json` in this directory.

What it remaps (opencode merges with defaults, only changed binds are listed):

| Key | Action |
|-----|--------|
| `Ctrl+U` | scroll messages half page up |
| `Ctrl+D` | scroll messages half page down (Vim-style) |
| `Ctrl+C` | exit opencode (instead of the default `Ctrl+D`) |

`Ctrl+D` no longer exits opencode.

### Wire-up

```bash
mkdir -p ~/.config/opencode
cp tools/cli-tools/opencode/tui.json ~/.config/opencode/tui.json
```

### Verify

```bash
cat ~/.config/opencode/tui.json
# restart opencode, then: Ctrl+U / Ctrl+D scroll half pages, Ctrl+C exits
```

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

It appends both aliases to `~/.zshrc` only if they aren't already present (idempotent), and copies the `tui.json` replica to `~/.config/opencode/tui.json` if it isn't already in sync.

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
