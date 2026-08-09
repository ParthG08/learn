# Git Setup

## Aliases

### `git cb` — current branch name

I use the `git cb` alias (made with git itself) to refer to the current branch I'm on.

```sh
git config --global alias.cb "rev-parse --abbrev-ref HEAD"
```

Usage: `git cb` prints only the current branch name (e.g. `main`).
