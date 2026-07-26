# zoxide — Smarter cd Command

## Overview
zoxide is a blazing-fast replacement for `cd`. It learns your directory habits and lets you jump anywhere with just a few keystrokes. It's inspired by z and autojump, but much faster.

## Installation
```bash
# apt (may be outdated)
sudo apt install zoxide

# Homebrew
brew install zoxide

# From source (recommended — latest version)
curl -sS https://raw.githubusercontent.com/ajeetdsouza/zoxide/main/install.sh | bash

# Cargo
cargo install zoxide
```

## Shell Setup
Add to `~/.bashrc` or `~/.zshrc`:
```bash
eval "$(zoxide init bash)"   # for bash
eval "$(zoxide init zsh)"    # for zsh
eval "$(zoxide init fish)"   # for fish
```

## Common Use Cases

### 1. Basic Directory Jump
```bash
# Jump to a directory by name (partial match OK)
z projects
z doc
z down

# Jump to a subdirectory of a matching directory
z projects/learn

# Jump to a directory that matches multiple keywords
z go project       # jumps to project/go or go/project
```

### 2. Interactive Mode
```bash
# Fuzzy search through all known directories
zi               # starts fzf on your zoxide database

# With custom fzf options
zi --bind 'ctrl-space:toggle-preview' --preview 'ls -la {}'
```

### 3. Add Directories Manually
```bash
# Add current dir to database
zoxide add .

# Add a specific path
zoxide add /home/user/projects/my-project
```

### 4. Remove Directories
```bash
# Remove from database
zoxide remove /old/project

# Remove all matches of "temp"
zoxide remove temp
```

### 5. Query Without Changing Directory
```bash
# Print the best match
zoxide query my-project

# List all matches
zoxide query -l my-project

# List all known directories
zoxide query -l
```

### 6. List All Directories
```bash
# All directories in database
zoxide query -l

# Piped to fzf for interactive selection
zoxide query -l | fzf --prompt="jump> "
```

### 7. Exclude Directories
```bash
# Remove a directory from history
zoxide remove /path/to/exclude
```

## Key Differences from cd

| Feature | `cd` | `zoxide` |
|---|---|---|
| Navigation | Full path required | Fuzzy match on any part of path |
| Learning | None | Learns from your `z` usage |
| Speed | Instant | ~1ms lookup (DB is tiny) |
| Frecent | No | Yes (frequency + recency) |

## Advanced Usage

### Use with fzf for visual directory picker
```bash
# Interactive jump with preview
zoxide query -l | fzf --preview 'exa -la {}' --prompt="zoxide> "

# Or use built-in zi
zi --preview 'ls --color=always {}'
```

### Use with cd for fallback
```bash
# Try zoxide first, fall back to cd
function c() {
  z "$@" || cd "$@"
}
```

### Use with z for compatibility
```bash
# Import z/autojump database
zoxide import /path/to/z/database
```

### Export/Backup Your Database
```bash
# Export to text file
zoxide query -l > ~/.zoxide_backup.txt

# Import back
cat ~/.zoxide_backup.txt | zoxide add
```

## Yazi Integration

### Direct use in yazi
- Yazi does not use zoxide internally (it's a file manager, not a shell)
- But you can trigger zoxide-powered navigation from within yazi via the command line

### From yazi's command mode
Press `:` and type:
```bash
# Open terminal with zoxide to jump
:shell zoxide query project-a
```

### Open terminal at a zoxide destination
```bash
# Spawn a new terminal in a zoxide-targeted directory
:terminal zoxide query project-a && exec $SHELL
```

### Custom yazi plugin for zoxide navigation
Create `~/.config/yazi/plugins/zoxide.yazi/init.lua`:
```lua
--- @sync entry
return {
  entry = function()
    local target = ya.input({ title = "zoxide: Jump to" })
    if not target then return end

    local dir = io.popen("zoxide query " .. target  .. " 2>/dev/null"):read("*a"):gsub("\n$", "")
    if dir and #dir > 0 then
      ya.manager_emit("cd", { dir })
    end
  end,
}
```

### Open yazi at a zoxide-jumped location from terminal
```bash
# Use zoxide to jump and immediately open yazi there
yazi "$(zoxide query project)"
```

## Practical Workflow

### Daily use
```bash
# After a few days of cd-ing around:
cd ~/projects/my-app          # type once
z my-app                      # next time: 8 keystrokes
z my                          # after a few times: 3 keystrokes
```

### Combining zoxide with other tools
```bash
# Find and jump
cd "$(fd --type d -d 3 | fzf)"   # manual
z my-project                      # zoxide (faster once learned)

# Open file in project using zoxide + fzf + nvim
nvim "$(zoxide query my-project)"/src/main.go

# Git operations in a known project
cd "$(zoxide query my-app)" && git status
```

## Integration with Other Tools

### zoxide + fzf (zi - built-in)
```bash
# zi is the interactive wrapper that comes with zoxide
zi
zi --preview 'tree -C {} | head -50'
```

### zoxide + tmux
```bash
# Open a new tmux window at a zoxide target
tmux new-window -c "$(zoxide query my-project)"
```

### zoxide + lf/ranger
```bash
# Open lf at a zoxide-jumped location
lf "$(zoxide query my-project)"
```

## Tips & Tricks

### Prevent a directory from being tracked
```bash
# Set environment variable
export _ZO_EXCLUDE_DIRS="/tmp/*:/var/tmp/*:/proc/*"
```

### Change database location
```bash
export _ZO_DATA_DIR="$HOME/.local/share/zoxide"
```

### Set max database entries
```bash
export _ZO_MAX_ENTRIES=5000
```

### Use with hooks to avoid learning from non-interactive cd
```bash
# Only add directories from interactive shell usage
eval "$(zoxide init bash --no-aliases)"
```

## Resources
- [GitHub: ajeetdsouza/zoxide](https://github.com/ajeetdsouza/zoxide)
- [zoxide manual](https://github.com/ajeetdsouza/zoxide/wiki)
