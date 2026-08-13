# File Structure

This is how the file structure looks like (LazyVim starter):

```bash
~/.config/nvim % ls
init.lua  lazy-lock.json  LICENSE  README.md  stylua.toml  lua
```

```
lua/
├── config/
│   ├── lazy.lua      # bootstraps lazy.nvim + LazyVim
│   ├── options.lua   # editor options
│   ├── keymaps.lua   # keymaps
│   └── autocmds.lua  # autocommands
└── plugins/
    └── example.lua   # template for adding your own plugins
```

everything is inside of the `.config/nvim`. This repo mirrors it in `.config/`.

See `setup.md` for how to install/reinstall this config.
