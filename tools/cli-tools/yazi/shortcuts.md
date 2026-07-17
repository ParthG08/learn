# Yazi — Shortcuts Reference

## Navigation

| Shortcut | Action |
|---|---|
| `h` / `j` / `k` / `l` | Move left / down / up / right (or arrows) |
| `g` → `g` | Go to top of list |
| `G` | Go to bottom of list |
| `Ctrl+d` / `Ctrl+u` | Half page down / up |
| `[` / `]` | Parent / child directory (bracket nav) |
| `-` | Go to parent directory |
| `~` | Go to home directory |
| `@` | Go to root directory |
| `gp` | Jump to previously visited directory |

## File Management

| Shortcut | Action |
|---|---|
| `y` | Yank (copy) selected files |
| `x` | Cut selected files |
| `p` | Paste files |
| `P` | Paste files (overwrite) |
| `d` | Delete selected files |
| `D` | Permanently delete (no trash) |
| `r` | Rename file |
| `a` | Create new file or directory (`/` suffix = dir) |
| `.` | Toggle hidden files |
| `Space` | Toggle selection on current file |
| `V` | Enter visual mode (line-wise) |
| `v` | Enter visual mode (character-wise) |
| `Ctrl+a` | Select all |
| `Ctrl+r` | Inverse selection |
| `Esc` | Clear selection / exit search mode |

## Filtering & Searching

| Shortcut | Action |
|---|---|
| `f` | **Filter** current directory — type a **regex** (e.g. `\.png$`, `^main`) to show only matching files. Re-press `f` or `Esc` to clear. |
| `/` | **Find** — type characters to fuzzy-filter. `Enter` jumps to the highlighted candidate. |
| `n` / `N` | Next / previous **match** (after `/` or `Z`). |
| `Z` | **Recursive search** — spawns an `fd`/`ripgrep`-powered overlay pane. Type a pattern, results update live across all subfolders. `n`/`N` to cycle matches, `Enter` to open. |
| `?` | Toggle help (lists all keybindings) |

## Opening & Preview

| Shortcut | Action |
|---|---|
| `Enter` | Open file / enter directory |
| `o` / `O` | Open file with default / system opener |
| `t` | Open file in new tab |
| `K` / `J` | Scroll preview pane up / down |
| `Ctrl+d` / `Ctrl+u` | Half-page scroll in preview pane |
| `gf` | Reveal file location in OS file manager |

## Tabs

| Shortcut | Action |
|---|---|
| `Tab` | Next tab |
| `Shift+Tab` | Previous tab |
| `Ctrl+q` | Close current tab |
| `1`–`9` | Jump to tab by number |

## Sorting

| Shortcut | Action |
|---|---|
| `za` | Sort alphabetically |
| `zm` | Sort by modified time |
| `zl` | Sort by file size |
| `ze` | Sort by extension |

## Command Mode

| Shortcut | Action |
|---|---|
| `:` | Enter command mode (e.g. `:q`, `:bd`, `:help`) |
| `q` | Quit current tab (or quit if last tab) |
| `Q` | Force quit |
### Common commands

| Command | Action |
|---|---|
| `:bd` | Close current tab |
| `:q` | Quit |
| `:help` | Open help overlay |
| `:yazi` | Reload the current instance |
