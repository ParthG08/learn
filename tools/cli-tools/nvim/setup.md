# Neovim — LazyVim Setup

Setup for Neovim using the [LazyVim](https://www.lazyvim.org/) distro. Nvim version: v0.12.4.

## Prerequisites

- Neovim ≥ 0.9 (0.12.4 on this machine)
- Git
- A Nerd Font (for icons)

## Install (new machine / fresh)

```bash
# 1. Install LazyVim starter as your config (replaces existing ~/.config/nvim)
git clone --depth 1 https://github.com/LazyVim/starter ~/.config/nvim

# 2. Remove the .git so it's not a nested repo (keeps YOUR config under version control)
rm -rf ~/.config/nvim/.git
```

## First Run

Open nvim — lazy.nvim auto-installs all plugins on first launch:

```bash
nvim
```

Or install headlessly:

```bash
nvim --headless "+Lazy! sync" +qa
```

## Updating Plugins

```bash
nvim --headless "+Lazy! sync" +qa   # install/sync
# or inside nvim: <leader> + L + S  (Lazy → Sync)
```

## Adding Your Own Config

- **Options/keymaps/autocmds:** `lua/config/{options,keymaps,autocmds}.lua`
- **Extra plugins:** create a file in `lua/plugins/` (see `example.lua` for the template)
- After adding, run `<leader> + L + S` or `:Lazy sync`

## Mirror in This Repo

This repo keeps the config at `tools/cli-tools/nvim/.config/` (copied from
`~/.config/nvim`). To restore on a new machine:

```bash
cp -r tools/cli-tools/nvim/.config/* ~/.config/nvim/
```

## Verify

```bash
nvim --version | head -1     # Neovim
nvim --headless "+Lazy! sync" +qa  # plugins install cleanly
```

## Notes for This Machine

- Installed fresh (replaced previous custom lazy.nvim config — telescope, gitsigns, harpoon, jdtls were removed).
- Repo config under `tools/cli-tools/nvim/.config/` is a mirror; keep it in sync after config edits.
