# zoxide — New Machine Setup

Setup notes for zoxide (smarter `cd`). Companion usage guide: `zoxide.md`.

## Install

**Arch (no root):** official install script → `~/.local/bin/zoxide`

```bash
curl -sS https://raw.githubusercontent.com/ajeetdsouza/zoxide/main/install.sh | bash
```

Alternatives:
```bash
sudo apt install zoxide     # Debian/Ubuntu (may be outdated)
brew install zoxide         # macOS/Linux
pacman -S zoxide            # Arch (needs sudo)
```

## Shell Init

Add to `$ZDOTDIR/.zshrc` (this machine: `~/.config/zsh/.zshrc`):

```sh
eval "$(zoxide init zsh)"
```

Reload: `source ~/.config/zsh/.zshrc`

## Verify

```bash
zoxide --version   # e.g. 0.10.0
type z             # "z is a shell function from .../.zshrc"
z <dir-name>       # actually jumps
```

## Notes for This Machine

- Shell is zsh with **ZDOTDIR = `~/.config/zsh`** — edit **that** `.zshrc`, not `~/.zshrc`.
- Installed via official script to `~/.local/bin` (no sudo needed); ensure that dir is on `PATH`.
- `zi` (interactive fuzzy jump) requires `fzf` to be installed too.
