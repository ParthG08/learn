# OpenCode Shortcuts

Leader key: `ctrl+x` (default)

## Slash Commands

| Command | Aliases | Action | Keybind |
|---------|---------|--------|---------|
| `/new` | `/clear` | Start a new session | `<leader>n` |
| `/undo` | - | Undo last message + file changes | `<leader>u` |
| `/redo` | - | Redo previously undone message | `<leader>r` |
| `/compact` | `/summarize` | Compact current session | `<leader>c` |
| `/sessions` | `/resume`, `/continue` | List and switch sessions | `<leader>l` |
| `/models` | - | List available models | `<leader>m` |
| `/themes` | - | List available themes | `<leader>t` |
| `/editor` | - | Open external editor for composing | `<leader>e` |
| `/export` | - | Export conversation to Markdown | `<leader>x` |
| `/exit` | `/quit`, `/q` | Exit OpenCode | `<leader>q` |
| `/help` | - | Show help dialog | - |
| `/init` | - | Initialize/update AGENTS.md | - |
| `/connect` | - | Add a provider | - |
| `/share` | - | Share current session | - |
| `/unshare` | - | Unshare current session | - |
| `/details` | - | Toggle tool execution details | - |
| `/thinking` | - | Toggle thinking block visibility | - |

## Session Navigation

| Keybind | Action |
|---------|--------|
| `<leader>g` | Session timeline |
| `<leader>s` | View status |
| `up` | Go to parent session |
| `right` | Cycle to child session |
| `left` | Cycle to previous child session |
| `<leader>down` | Go to first child session |
| `escape` | Interrupt session |

## Session Management

| Keybind | Action |
|---------|--------|
| `ctrl+r` | Rename session |
| `ctrl+d` | Delete session |
| `<leader>x` | Export session |

## Agent & Model

| Keybind | Action |
|---------|--------|
| `tab` | Cycle agents (Act/Plan mode toggle) |
| `shift+tab` | Cycle agents reverse |
| `ctrl+t` | Cycle model variants (thinking effort) |
| `ctrl+a` | List providers |
| `ctrl+f` | Toggle favorite model |
| `f2` | Cycle recent models |
| `shift+f2` | Cycle recent models reverse |

## Input Editing

| Keybind | Action |
|---------|--------|
| `return` | Submit prompt |
| `shift+return` / `ctrl+return` / `alt+return` / `ctrl+j` | New line |
| `ctrl+c` | Clear input |
| `ctrl+v` | Paste |
| `ctrl+a` | Move to start of line |
| `ctrl+e` | Move to end of line |
| `ctrl+b` / `left` | Move cursor back |
| `ctrl+f` / `right` | Move cursor forward |
| `alt+b` / `alt+left` / `ctrl+left` | Move back one word |
| `alt+f` / `alt+right` / `ctrl+right` | Move forward one word |
| `ctrl+d` / `delete` | Delete character under cursor |
| `ctrl+k` | Delete to end of line |
| `ctrl+u` | Delete to start of line |
| `ctrl+w` / `ctrl+backspace` / `alt+backspace` | Delete previous word |
| `alt+d` / `alt+delete` / `ctrl+delete` | Delete next word |
| `ctrl+-` / `super+z` | Undo input |
| `ctrl+.` / `super+shift+z` | Redo input |
| `home` | Go to buffer start |
| `end` | Go to buffer end |

## Message Navigation

| Keybind | Action |
|---------|--------|
| `pageup` / `ctrl+alt+b` | Page up |
| `pagedown` / `ctrl+alt+f` | Page down |
| `ctrl+alt+y` | Line up |
| `ctrl+alt+e` | Line down |
| `ctrl+alt+u` | Half page up |
| `ctrl+alt+d` | Half page down |
| `ctrl+g` / `home` | Go to first message |
| `ctrl+alt+g` / `end` | Go to last message |
| `<leader>y` | Copy message |
| `<leader>h` | Toggle conceal (hide/show content) |

## Dialog / Palette

| Keybind | Action |
|---------|--------|
| `ctrl+p` | Open command palette |
| `ctrl+alt+k` | Show which-key |
| `escape` | Close dialog / hide autocomplete |

## File Referencing

- Type `@` to fuzzy-search and reference files in your prompt
- Type `@alias/` to browse files inside a configured reference
- Start message with `!` to run a shell command

## Desktop Prompt Shortcuts (built-in)

| Shortcut | Action |
|----------|--------|
| `ctrl+a` | Move to start of current line |
| `ctrl+e` | Move to end of current line |
| `ctrl+b` | Move cursor back one character |
| `ctrl+f` | Move cursor forward one character |
| `alt+b` | Move cursor back one word |
| `alt+f` | Move cursor forward one word |
| `ctrl+d` | Delete character under cursor |
| `ctrl+k` | Kill to end of line |
| `ctrl+u` | Kill to start of line |
| `ctrl+w` | Kill previous word |
| `alt+d` | Kill next word |
| `ctrl+t` | Transpose characters |
| `ctrl+g` | Cancel popovers / abort running response |

## CLI Commands

| Command | Description |
|---------|-------------|
| `opencode` | Start TUI |
| `opencode [project]` | Start TUI with project |
| `opencode -c` | Continue last session |
| `opencode run "prompt"` | Non-interactive mode |
| `opencode serve` | Start headless server |
| `opencode web` | Start server with web UI |
| `opencode attach <url>` | Attach TUI to running server |
| `opencode models` | List available models |
| `opencode auth login` | Configure provider API keys |
| `opencode session list` | List sessions |
| `opencode session delete <id>` | Delete a session |
| `opencode export <id>` | Export session as JSON |
| `opencode import <file\|url>` | Import session |
| `opencode stats` | Show token usage & cost |
| `opencode upgrade` | Update opencode |
| `opencode uninstall` | Uninstall opencode |
| `opencode agent create` | Create a new agent |
| `opencode agent list` | List agents |
| `opencode mcp add` | Add MCP server |
| `opencode mcp list` | List MCP servers |
| `opencode plugin <module>` | Install a plugin |
| `opencode pr <number>` | Fetch & checkout a PR, then run |

## Environment Variables

| Variable | Description |
|----------|-------------|
| `OPENCODE_CONFIG` | Path to config file |
| `OPENCODE_TUI_CONFIG` | Path to TUI config file |
| `OPENCODE_SERVER_PASSWORD` | Enable basic auth for serve/web |
| `OPENCODE_DISABLE_AUTOUPDATE` | Disable auto-update checks |
| `OPENCODE_PERMISSION` | Inline permissions config |
| `OPENCODE_AUTO_SHARE` | Auto-share sessions |
