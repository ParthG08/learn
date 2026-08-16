# Qutebrowser — Setup

**Qutebrowser is my keyboard-driven web browser** — it's a Vim-style browser
with a minimal, unobtrusive UI. Config lives in Python, so setup is
declarative and version-controllable.

## Install

```bash
# Arch
sudo pacman -S qutebrowser

# Debian/Ubuntu
sudo apt install qutebrowser

# macOS
brew install --cask qutebrowser
```

## Config location

- Live config: `~/.config/qutebrowser/config.py` (this repo's replica is the
  source of truth)
- Autoconfig (settings toggled via `:set`, auto-generated): `~/.config/qutebrowser/autoconfig.yml`
- Repo reference: `tools/cli-tools/qutebrowser/`

## Fuzzy tab search (tab-select)

The built-in `tab-select` command opens a completion prompt where you type the
tab title/URL (fuzzy match) and hit `Enter` to jump straight to that tab.

| Key | Action |
|---|---|
| `<Ctrl+P>` | fuzzy search tabs (VS Code / Ctrl+P style) |
| `gb` | fuzzy search tabs (Vim-style) |
| `<Ctrl+Shift+a>` | fuzzy search tabs (set via autoconfig) |
| `<Ctrl+Shift+f>` | fuzzy search tabs (set via autoconfig) |

### Why `tab-select` and not a custom script?

`tab-select` is built in, supports fuzzy matching out of the box, and requires
no external dependencies (no `fzf`, no userscript). A hand-rolled script is
only worth it if you need extra filtering (e.g. by URL domain or pinned tabs).

### Wiring it up

The bindings live in `config.py`:

```python
config.load_autoconfig()

config.bind('<Ctrl+Shift+a>', 'set-cmd-text -s :tab-select')
config.bind('<Ctrl+Shift+f>', 'set-cmd-text -s :tab-select')
config.bind('<Ctrl+P>', 'set-cmd-text -s :tab-select')
config.bind('gb', 'set-cmd-text -s :tab-select')
```

The `-s` flag puts the `:tab-select` text into the command prompt with the
cursor ready, so you can type straight away.

## Applying config changes

No restart needed:

```
:config-source
```

## Verify

1. Open two or more tabs.
2. Press `Ctrl+P` (or `gb`).
3. Type part of a tab title → completion should fuzzy-match.
4. `Enter` → switches to that tab.
