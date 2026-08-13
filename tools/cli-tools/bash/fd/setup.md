# fd — New Machine Setup

Setup notes for fd (fast `find` alternative). Companion usage guide: `fd.md`.

## Install

**Arch (no root):** official GitHub release binary → `~/.local/bin/fd`

```bash
VER=$(curl -s https://api.github.com/repos/sharkdp/fd/releases/latest | grep -oP 'v\d+\.\d+\.\d+' | head -1)
curl -sL -o /tmp/fd.tar.gz "https://github.com/sharkdp/fd/releases/download/$VER/fd-$VER-x86_64-unknown-linux-gnu.tar.gz"
tar -xzf /tmp/fd.tar.gz -C /tmp
cp "/tmp/fd-${VER#v}-x86_64-unknown-linux-gnu/fd" ~/.local/bin/fd
chmod +x ~/.local/bin/fd
```

Alternatives:
```bash
sudo pacman -S fd        # Arch (root)
sudo apt install fd-find # Debian/Ubuntu (binary is `fdfind`)
brew install fd          # macOS
```

## Shell Completion (zsh)

Install the completion file into `$ZDOTDIR/completions` (this machine: `~/.config/zsh/completions`):

```bash
cp <release>/autocomplete/_fd ~/.config/zsh/completions/_fd
```

It's picked up automatically if `fpath` includes `$ZDOTDIR/completions` and `compinit` runs.

## Verify

```bash
fd --version             # e.g. fd 10.4.2
fd pattern ~/            # search example
type _fd                 # completion loaded (autoload shell function)
```

## Notes for This Machine

- Installed fd **10.4.2** to `~/.local/bin` (no sudo needed).
- Shell is zsh with **ZDOTDIR = `~/.config/zsh`** — completions go in `~/.config/zsh/completions/`.
- Debian/Ubuntu call the binary `fdfind` — add `alias fd='fdfind'` there if you use that distro.
