# tmux — Setup

Setup notes for tmux (terminal multiplexer). Installed version on this
machine: **3.7b**. Replica: `tmux.conf` (+ helper script `tmux-window-fzf`)
in this directory.

## Install

```bash
sudo pacman -S tmux        # Arch
sudo apt install tmux      # Debian/Ubuntu
sudo dnf install tmux      # Fedora
brew install tmux          # macOS
```

## Wire-up

1. Copy the config:

```bash
mkdir -p ~/.config/tmux
cp tools/cli-tools/tmux/tmux.conf ~/.config/tmux/tmux.conf
```

2. Copy the fzf window-switcher helper (`prefix + f` depends on it):

```bash
mkdir -p ~/.local/bin
cp tools/cli-tools/tmux/tmux-window-fzf ~/.local/bin/tmux-window-fzf
chmod +x ~/.local/bin/tmux-window-fzf
```

Requires `fzf` on `PATH` (see `../bash/fzf/setup.md`) and `~/.local/bin` on
`PATH` (it is on this machine).

3. Reload in a running session: `tmux source-file ~/.config/tmux/tmux.conf`

## What `tmux.conf` does

| Setting | Effect |
|---|---|
| `set -g mouse on` | mouse support |
| `set -g history-limit 100000` | large scrollback |
| `setw -g mode-keys vi` | vi-style copy mode |
| `bind -n C-l ...` | `Ctrl+L` (no prefix) smart pane navigation — keeps a zoomed pane zoomed |
| `bind \| split-window -h -c "#{pane_current_path}"` | `prefix + \|` vertical split inheriting pane cwd |
| `bind _ split-window -v -c "#{pane_current_path}"` | `prefix + _` horizontal split inheriting pane cwd |
| `set -g renumber-windows on` | windows renumber when one closes |
| `bind-key f display-popup ... tmux-window-fzf` | `prefix + f` fuzzy window switcher (popup) |
| `bind-key -n C-q last-window` | `Ctrl+q` (no prefix) jump to last window |
| pane/window status styling | active pane cyan border, active window yellow highlight |

## Verify

```bash
tmux -V                    # 3.7b
tmux new-session -d -s t && tmux source-file ~/.config/tmux/tmux.conf && tmux kill-session -t t
# interactive: start tmux, try `prefix + |`, `prefix + f`, `Ctrl+L`
```

## Notes for This Machine

- Config lives at `~/.config/tmux/tmux.conf` (not `~/.tmux.conf`).
- `prefix + f` needs `tmux-window-fzf` at `~/.local/bin` and `fzf` installed.
- See `tmux-shortcuts.md` for the full shortcut cheat-sheet.
