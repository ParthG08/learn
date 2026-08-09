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

## Verify

```bash
type y     # y is a shell function
y          # open yazi, navigate somewhere, quit → you're now in that dir
```

## Other tool notes

- `gcb` (git checkout branch) and `z`/`zi` (zoxide) also rely on `fzf` — see `fzf/setup.md`.
