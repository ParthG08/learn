# ripgrep (rg) — Fast Grep Alternative

## Overview
ripgrep (rg) is a line-oriented search tool that recursively searches your current directory for a regex pattern. It's built on top of Rust's regex engine and is significantly faster than grep, ag, or ack.

## Installation
```bash
# apt
sudo apt install ripgrep

# Homebrew
brew install ripgrep

# From source
cargo install ripgrep
```

## Common Use Cases

### 1. Basic Search
```bash
# Search for pattern (recursive, respects .gitignore)
rg "pattern"

# Case-insensitive
rg -i "pattern"

# Invert match (lines NOT matching)
rg -v "pattern"

# Whole word match
rg -w "pattern"
```

### 2. Search by File Type
```bash
# Specific language
rg --type rust "unsafe"
rg --type go "goroutine"
rg -t py "def "          # -t is shorthand for --type

# List available file types
rg --type-list

# Exclude file types
rg --type-not html "pattern"

# Only .rs and .go files
rg --type rust --type go "pattern"
```

### 3. Search with File Globs
```bash
# Include only matching files
rg -g "*.py" "pattern"
rg -g "!*.py" "pattern"   # exclude .py

# Multiple globs
rg -g "*.{py,js,ts}" "pattern"

# Full path glob
rg -g "src/**/*.rs" "pattern"
```

### 4. Show Context
```bash
# Lines before/after match
rg -C 3 "pattern"         # 3 lines before AND after
rg -B 2 "pattern"         # 2 lines before
rg -A 5 "pattern"         # 5 lines after
```

### 5. Show Match Details
```bash
# Show line numbers
rg -n "pattern"

# Show column numbers
rg --column "pattern"

# Only show matching filenames (like grep -l)
rg -l "pattern"

# Only count matches
rg -c "pattern"
```

### 6. Search and Replace
```bash
# Preview replacements
rg "old_text" --replace "new_text"

# Actually replace (needs sed or perl)
rg -l "old_text" | xargs sed -i 's/old_text/new_text/g'

# With backup
rg -l "old_text" | xargs sed -i.bak 's/old_text/new_text/g'
```

### 7. Search Hidden Files and Ignored
```bash
rg --hidden "pattern"         # also search hidden files
rg --no-ignore "pattern"      # ignore .gitignore
rg -uuu "pattern"             # ultra-ultra-ultra: hidden + no-ignore + binary
rg --no-ignore-vcs "pattern"  # respect .ignore but not .gitignore
```

### 8. Search in Specific Directories
```bash
rg "pattern" src/
rg "pattern" src/ tests/ docs/
rg "pattern" --max-depth 3
```

### 9. Smart Case
```bash
# Smart case: case-sensitive only if pattern has uppercase
rg -S "Pattern"     # sensitive
rg -S "pattern"     # insensitive
```

### 10. Binary and Encodings
```bash
# Search binary files (treat as text)
rg --binary "pattern"

# Specific encoding
rg --encoding utf-16 "pattern"
```

## Advanced Use Cases

### Search for Multi-Line Patterns
```bash
# Use -U (multiline) with -z (search through compressed too)
rg -U "fn\s+\w+\(.*\)\s*{" --type rust
```

### JSON Output (for scripting)
```bash
rg --json "pattern" | jq 'select(.type == "match") | .data.path.text'
```

### Search and Pipe to fzf
```bash
# Interactive search results
rg --line-number "pattern" | fzf --delimiter=: --preview 'bat --color=always --line-range={2}:{2} {1}'
```

### Search Through Compressed Files
```bash
rg -z "pattern" *.gz
rg -z "pattern" *.log.gz
```

### Follow Symlinks
```bash
rg -L "pattern"
```

## Performance Benchmarks
```
Searching 10GB of source code:

  grep -r "pattern"    → ~12 min
  ag "pattern"         → ~4 min
  rg "pattern"         → ~30 sec  (~24x faster than grep)
```

## Yazi Integration

Yazi uses ripgrep for content search. If `rg` is installed, yazi's built-in content search (`Ctrl-F` or `:search`) uses it automatically.

### Default yazi behavior with rg
- **Filter by content:** Press `/` then type a pattern — yazi shows files whose *names* match (uses fd). For *content* search, press `Ctrl-F` or type `:search` in yazi
- Yazi's content search command: `:search <pattern>` — uses rg behind the scenes if available

### Content searching inside yazi
1. Press `:` → type `search "TODO"` → yazi shows all files containing "TODO"
2. Press `Ctrl-S` (if bound) to toggle content search mode

### Custom rg commands from yazi
- Press `:` → enter command mode
```bash
# Search for pattern in all files under current dir, show results in yazi
:shell rg --no-heading --line-number "pattern" | fzf

# Open all files containing a pattern in neovim
:shell rg -l "pattern" | xargs nvim
```

### Yazi config for custom rg search plugin
Create `~/.config/yazi/plugins/ripgrep.yazi/init.lua`:
```lua
--- @sync entry
return {
  entry = function()
    local pattern = ya.input({ title = "Ripgrep: Enter pattern" })
    if not pattern then return end

    local output = io.popen("rg -l --no-ignore-vcs \"" .. pattern .. "\" 2>/dev/null"):read("*a")
    if output and #output > 0 then
      ya.manager_emit("open", { ya.quote(output:gsub("\n$", "")) })
    end
  end,
}
```

### Practical yazi + rg workflow
1. Navigate to a project directory
2. Press `:` → type `search "fn main"` — finds all files containing `fn main`
3. Browse the filtered results; press Enter to open any file
4. Press `Esc` to clear the search filter

## Integration with Other Tools

### rg + bat (colored output)
```bash
rg -n "pattern" --color always | bat
```

### rg + fzf (interactive file search by content)
```bash
rg --line-number "pattern" | fzf --delimiter=: --preview 'bat --color=always --line-range={2}:{2} {1}' --preview-window=+{2}-/2
```

### rg + fd (search only certain file types)
```bash
# Search only Rust files for "unsafe"
fd -e rs -X rg "unsafe" {}
```

### rg + sed (replace across files)
```bash
# Replace in all .js files
rg -l "old_api" --type js | xargs sed -i 's/old_api/new_api/g'
```

## Tips & Tricks

### Pretty output
```bash
# With colors and line numbers
rg --color always -n "pattern" | less -R

# Show file path with line number
rg --with-filename -n "pattern"
```

### Sort results by file
```bash
rg --sort path "pattern"
rg --sort modified "pattern"   # most recently modified first
```

### Use no config
```bash
# Skip all config files (~/.ripgreprc, .ripgreprc)
rg --no-config "pattern"
```

### Search for Todo/Fixme
```bash
rg -i "TODO|FIXME|HACK|XXX" -g "!*.min.*" -g "!vendor/" -g "!node_modules/"
```

### Regex examples
```bash
# Start/end of line
rg "^import "         # lines starting with "import "
rg "go$"              # lines ending with "go"

# Character classes
rg "[A-Z]{2,}"        # 2+ uppercase letters in a row
rg "\d{3}-\d{4}"     # phone-number-like patterns

# Alternation
rg "async|await" --type js
```

## Resources
- [GitHub: BurntSushi/ripgrep](https://github.com/BurntSushi/ripgrep)
- [ripgrep user guide](https://github.com/BurntSushi/ripgrep/blob/master/GUIDE.md)
