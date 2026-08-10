# yazi — File Manager Setup

Setup notes for yazi (terminal file manager). Companion usage guide: `yazi.md`.

## Config Location

Config lives at `~/.config/yazi/`:

| File | Purpose |
|---|---|
| `~/.config/yazi/yazi.toml` | Main config — openers (`[opener]`) and open rules (`[open]`) |
| `~/.config/yazi/keymap.toml` | Custom keybindings (Ctrl+f fuzzy-find, `!` shell, `;` interactive command) |

## Installed Tools & Openers

Yazi itself is installed via `pacman` (`/usr/bin/yazi`). Custom openers:

| Tool | Location | Used for |
|---|---|---|
| zathura | system | PDFs (`application/pdf`) |
| **glow** | `~/.local/bin/glow` | Markdown (`text/markdown`) |

### glow — markdown renderer

Installed from the official GitHub release to `~/.local/bin` (no sudo needed):

```bash
curl -sL https://github.com/charmbracelet/glow/releases/download/v2.1.2/glow_2.1.2_Linux_x86_64.tar.gz -o /tmp/glow.tar.gz
tar -xzf /tmp/glow.tar.gz -C /tmp && cp /tmp/glow_2.1.2_Linux_x86_64/glow ~/.local/bin/
chmod +x ~/.local/bin/glow
```

Requires `~/.local/bin` to be on `PATH` (it is).

## Openers in `yazi.toml`

```toml
[opener]
zathura = [
    { run = "zathura %s1", orphan = true, for = "unix" }
]
glow = [
    { run = "glow -p %s1", block = true, stay = true, desc = "Render markdown with glow in pager mode", for = "unix" }
]

[open]
prepend_rules = [
    { mime = "application/pdf", use = "zathura" },
    { url = "*.md", use = "glow" }
]
```

### Why `url = "*.md"` instead of `mime = "text/markdown"`

`file` reports `.md` files as `text/plain` (there's no system markdown mime mapping), so a mime-based rule never matches and yazi falls back to a broken default opener (exit 127). Matching on the filename glob `*.md` is reliable. Note the rule field is `url` — a `name` field doesn't exist and causes a TOML validation error.

### Why `-p` pager mode + `stay = true` on glow

`glow -p` renders the markdown through the built-in pager (`less` by default) — scrollable, and it stays on screen until you press `q`/`Esc` to quit manually. The `stay = true` flag keeps the terminal alive (doesn't flash back to yazi) after glow exits.

## Verify

```bash
glow --version        # e.g. 2.1.2
yazi                  # open, press Enter on a .md file → renders via glow
```

## Notes for This Machine

- glow is at `~/.local/bin/glow` (user install, survives without root).
- To also install via pacman: `sudo pacman -S glow`.
- If a markdown file doesn't open in glow, check the mime with `file <file>` — it must report as `text/markdown`.
