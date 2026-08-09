# Daily Tmux Shortcuts

> `prefix` = `Ctrl+b` — trigger for all tmux commands.

| Shortcut | Action | Source |
|---|---|---|
| `prefix + f` | FZF window switcher (popup) | `~/.tmux.conf` / `tmux.conf` |
| `prefix + 0-9` | Jump to window by number | Default tmux |
| `prefix + w` | List / switch windows | Default tmux (unbound in local config, overridden by fzf) |
| `prefix + \|` | Vertical split (inherits pane cwd) | `tmux.conf` — `bind \| split-window -h` |
| `prefix + _` | Horizontal split (inherits pane cwd) | `tmux.conf` — `bind _ split-window -v` |
| `prefix + z` | Zoom pane fullscreen / toggle back | Default tmux |
| `Ctrl + q` | Quick pane jump (no prefix needed) | `tmux.conf` — `bind -n C-q select-pane` |
