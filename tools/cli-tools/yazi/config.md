# Config for yazi.


You need to put the keymap.toml in the /Users/parth.gupta/.config/yazi directory so as to apply the config.

## yazi.toml — open .md files with glow

`yazi.toml` defines an opener that renders markdown files with `glow` when you press Enter.

```toml
[opener]
glow = [
  { run = 'glow -p "$1"', block = true, for = "unix" }
]

[open]
prepend_rules = [
  { url = "*.md", use = "glow" },
]
```

> **Important:** keep the `-p` (pager) flag. Without it, `glow` renders the file to stdout and exits immediately, so the preview flashes open and closes instantly. With `-p`, the view stays on screen until you quit the pager (e.g. `q`).

Copy `yazi.toml` into `~/.config/yazi/` to apply it.
