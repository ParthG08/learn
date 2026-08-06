# System Integration

## `.bashrc` Configuration

Add the following two lines to `~/.bashrc` to integrate fzf into the shell:

```bash
# fzf: fuzzy reverse search (Ctrl+R) and fuzzy completion (Ctrl+T)
source /usr/share/doc/fzf/examples/key-bindings.bash
source /usr/share/doc/fzf/examples/completion.bash
```

### What they do

- **`key-bindings.bash`**: Enables **Ctrl+R** for fuzzy reverse history search. Instead of the default bash reverse-search, you get an interactive fzf interface to search through your command history with fuzzy matching. It also enables **Ctrl+T** to fuzzy-search for files/directories from the current cursor position.

- **`completion.bash`**: Enables fzf-powered tab completion. When you press Tab after certain commands (like `kill`, `ssh`, `export`, `unset`), fzf provides an interactive fuzzy completion interface (e.g., `kill <Tab>` opens an fzf list of processes).

## Useful aliases using fzf

Add to `~/.bashrc` or `~/.zshrc`:

```bash
# git checkout <branch> with fuzzy branch picker
alias gcb='git checkout $(git branch | fzf)'
```

- **`gcb`**: Lists all local branches in an interactive fzf picker. Selecting one runs `git checkout <branch>`.
- Note: `git branch` shows the current branch prefixed with `* `; for a cleaner list use `git branch --format='%(refname:short)'` or `git for-each-ref --format='%(refname:short)' refs/heads`.
