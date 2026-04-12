# Recovery (The Safety Net)

## 1. The Reflog

- `git reflog` records the history of your local `HEAD` movements.
- As long as you committed or moved `HEAD`, `reflog` can usually recover it.
- It is your map to find work that appears deleted, including lost commits and branches.
- Example: `git reflog` then `git checkout <reflog-hash>` to restore a discarded state.

## 2. Reset Levels

- `git reset --soft <commit>` moves `HEAD` to `<commit>` but keeps changes staged.
- `git reset --mixed <commit>` (the default) moves `HEAD` to `<commit>` and keeps changes unstaged in the working tree.
- `git reset --hard <commit>` moves `HEAD` to `<commit>` and discards all working-tree and staging-area changes.
- Use `--soft` when you want to edit commit history without losing the index, `--mixed` when you want to unstage changes, and `--hard` only when you are sure you want to throw changes away.
