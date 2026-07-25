# fzf — Fuzzy Finder

## Overview
fzf is a general-purpose command-line fuzzy finder. It pipes input from stdin, shows an interactive fuzzy search interface, and outputs the selected match to stdout.

## Installation
```bash
# Linux (apt)
sudo apt install fzf

# Homebrew (macOS/Linux)
brew install fzf

# From source
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf && ~/.fzf/install
```

## Key Bindings (after `fzf/install`)
| Binding | Action |
|---|---|
| `Ctrl-T` | Paste selected files/dirs into command line |
| `Ctrl-R` | Search through shell history |
| `Alt-C` | cd into selected directory |

## Common Use Cases

### 1. Interactive File Search
```bash
# Find files recursively, fuzzy-search interactively
find . -type f | fzf

# Much faster with fd
fd --type f | fzf
```

### 2. Open Selected File in Editor
```bash
# Open the fuzzy-selected file in $EDITOR
vim "$(fzf)"

# With preview window
fzf --preview 'bat --color=always {}'
```

### 3. Search and Kill Processes
```bash
# Interactive kill
kill -9 "$(ps aux | fzf | awk '{print $2}')"

# Or use fzf's built-in
fzf --bind 'enter:become(kill -9 {1})' < <(ps aux)
```

### 4. Directory Navigation
```bash
# cd into a subdirectory
cd "$(find . -type d | fzf)"

# Jump to a deeply nested directory
cd "$(fd --type d | fzf)"
```

### 5. Search Git Branches
```bash
# Checkout a branch
git checkout "$(git branch -a | fzf | tr -d ' *')"

# Interactive git log
git log --oneline | fzf --preview 'git show {+1}'
```

### 6. Command History Search (Ctrl-R replacement)
```bash
# Search through history with preview
history | fzf --tac --preview 'echo {2..}' | awk '{$1=""; print $0}' | source /dev/stdin
```

## FZF-Based Tools

### fzf-tmux
```bash
# Launch fzf in a tmux pane
fzf-tmux -d 40%

# Right-side pane
fzf-tmux -r 60%
```

### fzf integration with autojump/zoxide
```bash
# Use fzf to fuzzy-search zoxide results
zoxide query -l | fzf --prompt="zoxide> " | xargs cd
```

## Yazi Integration

Yazi uses fzf (or fd/fzf combo) internally for its file filtering. You can also configure custom fzf-based commands in yazi via `~/.config/yazi/yazi.toml`:

```toml
# In yazi, open fzf to fuzzy-find files in the current directory
[plugin]
prefetch = "fzf --preview 'bat --color=always {}'"

[open]
rules = [
  # Use fzf for directory jumping within yazi
  { name = "*", run = "fzf --preview 'bat --color=always {}'", block = true }
]
```

### Practical yazi + fzf workflow
- Press `f` in yazi to enter filter mode (uses fzf if `fzf` is installed)
- Type fuzzy pattern → yazi filters files in real time
- In yazi's `:` command mode: `shell fzf | xargs -o nvim` — selects file via fzf and opens in neovim

### Custom yazi plugin for fzf search
Create `~/.config/yazi/plugins/fzf.yazi/init.lua`:
```lua
-- Simple fzf file finder for yazi
--- @sync entry
return {
  entry = function()
    local output = ya.sync(function()
      return io.popen("fd --type f --hidden --no-ignore-vcs | fzf --preview 'bat --color=always {}'"):read("*a")
    end)()
    if output and #output > 0 then
      ya.manager_emit("open", { ya.quote(output:gsub("\n$", "")) })
    end
  end,
}
```

## Tips & Tricks

### Preview with bat (syntax-highlighted)
```bash
fzf --preview 'bat --color=always --style=numbers --line-range=:500 {}'
```

### Multi-select
```bash
# Tab to select multiple, Enter to confirm
fzf --multi --bind 'ctrl-a:select-all,ctrl-d:deselect-all'
```

### Custom prompt and layout
```bash
fzf --prompt="🔍 " --height=60% --border --layout=reverse
```

### Key bindings customization
```bash
# Create custom bindings via FZF_DEFAULT_OPTS
export FZF_DEFAULT_OPTS='--bind "ctrl-e:preview-up,ctrl-y:preview-down"'
```

## Resources
- [GitHub: junegunn/fzf](https://github.com/junegunn/fzf)
- [fzf wiki](https://github.com/junegunn/fzf/wiki)
