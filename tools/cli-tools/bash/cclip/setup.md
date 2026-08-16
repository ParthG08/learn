# cclip — copy a command's output to the clipboard

Setup notes for `cclip`, a small shell function that runs a command (or reads
stdin) and copies the result to the clipboard. It is defined in
`.zsh_aliases` / `bash_aliases` (see `../setup.md`), so there is nothing to
install beyond the clipboard backend.

## What it does

```sh
cclip pwd              # copy the current directory
cclip git branch       # copy the output of `git branch`
cclip "some text"      # copy literal text (first arg is not a command)
echo hi | cclip        # copy stdin
```

How it decides:
- **No args** → copy stdin (clipboard tool reads from the pipe).
- **First arg is a command** → run it and copy its output.
- **Otherwise** → treat the args as literal text and copy them.

That last rule is what makes `cclip $(git branch)` work: the shell expands
`$(git branch)` to a string, `git branch` is not the first arg, so cclip just
copies the text.

## Trailing newline stripping

Every path pipes the content through `perl -0777 -pe 's/\n+\z//'` before it
reaches the clipboard tool, so a trailing `\n` (or several) never lands on your
clipboard. Without this, `cclip echo hi` / `echo hi | cclip` copies `hi\n`, and
pasting adds a blank line — annoying when you `cclip git branch` and paste into
a chat or PR.

`wl-copy`, `xclip`, and `pbcopy` all copy stdin **verbatim** — none of them
strip newlines — so the strip must happen in cclip itself. This applies on
Linux/X11 too: `xclip` happily copies `hello\n` and pastes it back with the
newline. `perl` (required here) ships by default on macOS and essentially
every Linux distro.

## Prerequisites (one clipboard backend per platform)

cclip auto-detects in this order: `wl-copy` → `xclip` → `pbcopy`.

**Linux — Wayland** (this machine uses Hyprland):

```bash
sudo pacman -S wl-clipboard        # Arch: wl-copy / wl-paste
sudo apt install wl-clipboard      # Debian/Ubuntu
sudo dnf install wl-clipboard      # Fedora
```

**Linux — X11**:

```bash
sudo pacman -S xclip               # Arch
sudo apt install xclip             # Debian/Ubuntu
sudo dnf install xclip             # Fedora
```

**macOS**: `pbcopy` / `pbpaste` are built in — nothing to install.

Check: `command -v wl-copy` → `/usr/bin/wl-copy` (or whichever backend).

## Where it lives

| File | Purpose |
|---|---|
| `~/.config/zsh/.zsh_aliases` | Live definition (zsh, sourced from `$ZDOTDIR/.zshrc`) |
| `~/.zshrc` | Live definition on macOS (this machine — cclip lives in `.zshrc`) |
| `~/.bash_aliases` | Live definition (bash, sourced from `~/.bashrc`) |
| `tools/cli-tools/bash/.zsh_aliases` | Repo replica / reference copy (source of truth) |
| `tools/cli-tools/bash/bash_aliases` | Repo replica / reference copy (bash flavor) |

The function body is identical in all five files — keep them in sync.

## Verify

```bash
source ~/.config/zsh/.zsh_aliases   # or: source ~/.bash_aliases
cclip pwd              # then paste (Ctrl+V / Ctrl+Shift+V): should show $PWD
cclip "hello cclip"    # paste: should show "hello cclip"
cclip git branch       # paste: should show your branches
type cclip             # "cclip is a shell function"
```
