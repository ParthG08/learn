# Yazi — Setup

## Install

```bash
# Arch
sudo pacman -S yazi

# Debian/Ubuntu
sudo apt install yazi

# macOS
brew install yazi
```

## Shell Function (`y`)

`y` opens yazi **and** cds into the directory you ended in when you quit.

**Why a function, not an alias:** a plain `alias y='yazi'` can't run code *after*
yazi exits, so it would never cd. A function can.

Add to `~/.config/zsh/.zsh_aliases` (or `~/.bash_aliases` for bash):

```sh
function y() {
	local tmp="$(mktemp -t "yazi-cwd.XXXXXX")" cwd
	yazi "$@" --cwd-file="$tmp"
	if cwd="$(command cat -- "$tmp")" && [ -n "$cwd" ] && [ "$cwd" != "$PWD" ]; then
		builtin cd -- "$cwd"
	fi
	rm -f -- "$tmp"
}
```

Reload: `source ~/.config/zsh/.zsh_aliases`

**How it works:**
1. `--cwd-file="$tmp"` — yazi writes its final directory to a temp file on quit
2. After yazi exits, the function reads that path
3. If it differs from `$PWD`, `cd` into it (skips if same dir — no pointless cd)
4. `builtin cd` bypasses any `cd` aliases/overrides (e.g. zoxide) to keep it a real cd
5. Temp file is cleaned up

## Config location

- Config: `~/.config/yazi/` (e.g. `keymap.toml`, `yazi.toml`)
- Repo reference: `tools/cli-tools/yazi/` (see `shortcuts.md`, `config.md`)

## Open PDFs with zathura (default viewer)

Zathura is the default PDF viewer (vim-keybindings — see
`tools/cli-tools/zathura/setup.md`). In `~/.config/yazi/yazi.toml`, register it
as an opener and prepend a rule so PDFs always open with zathura:

```toml
[opener]
zathura = [
    { run = "zathura %s1", orphan = true, for = "unix" }
]

[open]
prepend_rules = [
    { mime = "application/pdf", use = "zathura" }
]
```

- `orphan = true` — detaches zathura from yazi so it keeps running when yazi closes
- `prepend_rules` — checked before the default rules, so PDFs go straight to zathura

## Markdown preview with glow (critical: needs `less`)

Opening `.md` files in yazi renders them via `glow` in pager mode:

```toml
# ~/.config/yazi/yazi.toml
[opener]
glow = [
  { run = 'glow -p "$1"', block = true, for = "unix" }
]

[open]
prepend_rules = [
  { url = "*.md", use = "glow" },
]
```

**Requirement — `less` must be installed and be the pager:**
- Install: `sudo pacman -S less` (Arch). Without it, `glow -p` falls back to
  `$PAGER`, and if that is `more`, the colored output renders garbled with big
  gaps and truncated lines (`--More--` prompt is the tell-tale sign).
- Ensure `export PAGER=less` in your shell aliases (`tools/cli-tools/bash/bash_aliases`).
- `export LESS="-R"` so less passes glow's ANSI color codes through (raw
  control chars) instead of printing them literally.
- Keep the `-p` flag: without it glow prints to stdout and exits immediately,
  so the preview flashes open and closes.
- Other tools (man pages, `git diff`, etc.) also prefer `less` — same exports fix them.

## Verify

```bash
type y     # y is a shell function
y          # open yazi, navigate somewhere, quit → you're now in that dir
```

## Other tool notes

- `gcb` (git checkout branch) and `z`/`zi` (zoxide) also rely on `fzf` — see `fzf/setup.md`.
