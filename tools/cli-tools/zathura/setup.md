# Zathura — Setup

**Zathura is my default PDF viewer** — it's a lightweight, plugin-based document
viewer with **Vim keybindings**, so navigation feels like editing a file in Vim.

## Install

```bash
# Arch
sudo pacman -S zathura zathura-pdf-mupdf

# Debian/Ubuntu
sudo apt install zathura zathura-pdf-mupdf

# macOS
brew install zathura zathura-pdf-mupdf
```

The `zathura-pdf-mupdf` plugin adds PDF support (there are also `-poppler` and
`-djvulibre` variants).

## Vim keybindings (default)

| Key | Action |
|---|---|
| `j` / `k` | scroll down / up |
| `h` / `l` | scroll left / right |
| `gg` / `G` | jump to first / last page |
| `/` | search |
| `n` / `N` | next / previous search match |
| `d` / `u` | half-page down / up |
| `Ctrl+d` / `Ctrl+u` | half-page down / up |
| `f` | follow links / jump to page (with prompt) |
| `+` / `-` | zoom in / out |
| `0` | fit width |
| `a` | fit page |
| `p` | print |
| `r` | reload |
| `R` | rotate |
| `Tab` | toggle index/outline |

## Config location

- Config: `~/.config/zathura/zathurarc`
- Repo reference: `tools/cli-tools/zathura/`

## Verify

```bash
zathura some.pdf   # opens with vim-style keys: j/k scroll, gg/G page jumps
```
