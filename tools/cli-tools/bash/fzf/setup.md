# fzf — New Machine Setup

Setup notes for fzf (fuzzy finder). Companion usage guide: `fzf.md`.

## Install

```bash
sudo apt install fzf        # Debian/Ubuntu
brew install fzf            # macOS/Linux
pacman -S fzf               # Arch
```

Installed version on this machine: **0.74.2** (`/usr/bin/fzf`).

## Shell Init (keybindings + completion)

The binary alone gives you `fzf`; the **keybindings** (`Ctrl-T`, `Ctrl-R`, `Alt-C`)
and `**` completion come from the shell init. For fzf ≥ 0.48, add to
`$ZDOTDIR/.zshrc` (this machine: `~/.config/zsh/.zshrc`):

```sh
eval "$(fzf --zsh)"
```

(Older fzf: run `~/.fzf/install` instead.)

Reload: `source ~/.config/zsh/.zshrc`

## Verify

```bash
fzf --version                    # e.g. 0.74.2 (3337be9d)
bindkey | grep fzf               # Ctrl-R / Ctrl-T / Alt-C widgets bound
echo hi | fzf --height=5         # interactive picker opens
```

## Notes for This Machine

- Shell is zsh with **ZDOTDIR = `~/.config/zsh`** — edit **that** `.zshrc`, not `~/.zshrc`.
- Keybindings only load with the init line — a bare `pacman -S fzf` does **not** give you `Ctrl-R` history search.
- Pairs well with `zoxide` (its `zi` command needs fzf).
