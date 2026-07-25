# fd — Fast Find Alternative

## Overview
fd is a fast, user-friendly alternative to `find`. It searches files and directories by name, with sensible defaults (respects `.gitignore`, ignores hidden files by default).

## Installation
```bash
# apt
sudo apt install fd-find

# Homebrew (note: command is `fdfind` on Debian, `fd` on brew)
brew install fd

# From source
cargo install fd-find
```

> **Debian/Ubuntu note:** The binary is `fdfind`. Add `alias fd='fdfind'` to your shell config.

## Common Use Cases

### 1. Basic File Search
```bash
# Find files matching a pattern
fd "pattern"

# Case-insensitive
fd -i "pattern"

# Exact match
fd -g "*.rs"       # glob pattern
fd -e rs           # extension shortcut
```

### 2. Control Search Depth
```bash
# Max depth
fd --max-depth 3 "pattern"

# Min depth (skip top-level)
fd --min-depth 2 "pattern"
```

### 3. Filter by Type
```bash
fd --type f "pattern"     # files only
fd --type d "pattern"     # directories only
fd --type l "pattern"     # symlinks only
fd --type x "pattern"     # executable only
fd --type e "pattern"     # empty files/dirs
```

### 4. Hidden Files and Git Ignored
```bash
fd --hidden "pattern"         # include hidden files
fd --no-ignore "pattern"      # ignore .gitignore
fd --no-ignore-vcs "pattern"  # ignore .gitignore but respect other ignore files
fd -HI "pattern"              # hidden + no ignore (full search)
```

### 5. Execute Commands on Results
```bash
# Delete all .log files
fd -e log --exec rm {}

# Count lines in all Python files
fd -e py --exec wc -l {}

# Batch chmod
fd -e sh --exec chmod +x {}
```

### 6. Search and Open in Neovim
```bash
nvim "$(fd --type f -e md | fzf)"
nvim $(fd --type f -e go)
```

### 7. Integration with fzf (faster than `find | fzf`)
```bash
fd --type f | fzf --preview 'bat --color=always {}'

# Limit search to current git repo
fd --type f --hidden --no-ignore-vcs | fzf
```

### 8. List Files with Details
```bash
fd --type f -l        # long listing
fd --type f -X ls -l  # batch ls -l (like find -exec +)
```

### 9. Find by Modification Time
```bash
fd --changed-within 1hour    # modified within last hour
fd --changed-before 7days    # modified more than 7 days ago
fd --changed-within 10min --type f
```

### 10. Follow Symlinks
```bash
fd -L "pattern"
fd --follow "pattern"
```

## Performance Comparison
```
Benchmark: searching ~200K files in a large repo

                find . -name "*.rs"  →  ~2.4s
  fd -e rs                          →  ~0.3s  (~8x faster)
```

## Integration with Other Tools

### With ripgrep (search file contents in specific files)
```bash
# Find all Rust files, then search for "unsafe" in them
fd -e rs -X rg "unsafe" {}

# Same but with colored output
fd -e rs -X rg -n "unsafe" {} | less -R
```

### With sed (bulk rename/replace)
```bash
# Rename all .txt to .md
fd -e txt -x mv {} {.}.md
```

### With bat (preview in fzf)
```bash
fd --type f | fzf --preview 'bat --color=always {}'
```

## Yazi Integration

Yazi uses fd internally for file searching. It detects fd and uses it automatically for faster directory traversal. You can also trigger custom fd searches from within yazi:

### Default yazi behavior with fd
- Yazi prefers `fd` over `find` when available — it's used for file filtering and search
- No configuration needed; if `fd` is installed, yazi uses it

### Custom search from yazi command line
- Press `:` to enter command mode
- Type: `shell fd --type f --pattern "keyword" | xargs -o nvim`

### Use fd to find files and open them in yazi
```bash
# From terminal: find a file with fd, open its parent in yazi
fd --type f "pattern" --exec yazi "$(dirname {})" \;
```

### Yazi config to integrate fd with fzf for deep search
In `~/.config/yazi/yazi.toml`:
```toml
[plugin]
prefetch = "fd --type f --hidden --no-ignore | fzf --preview 'bat --color=always {}'"
```

### Practical yazi + fd workflow
1. Press `/` in yazi → type a pattern → yazi filters files in real time (uses fd under the hood)
2. Press `:shell fd --changed-within 1hour` → shows files modified in the last hour
3. Navigate to a filtered result and press Enter to open

## Tips & Tricks

### Search with exclusion
```bash
fd -e js -E node_modules
fd --type f -E "*.generated.*" -E ".git/"
```

### Search for files containing a string
```bash
# Find Python files that import something
fd -e py -X rg "import requests" {}
```

### Colorize output
```bash
fd --color always "pattern"
```

### Print absolute paths
```bash
fd --absolute-path "pattern"
```

### Null-separated output (for xargs -0)
```bash
fd --type f -0 | xargs -0 wc -l
```

## Resources
- [GitHub: sharkdp/fd](https://github.com/sharkdp/fd)
