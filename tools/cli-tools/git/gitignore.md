# `.gitignore` — Telling Git What to Ignore

## What It Is

A `.gitignore` file tells Git which **untracked** files/directories to exclude from `git status` and `git add`. It only affects files not yet tracked — once a file is tracked, `.gitignore` has no effect on it.

## Basic Syntax

| Rule | Example | Meaning |
|------|---------|---------|
| Comment | `# build artifacts` | Anything after `#` is ignored |
| Blank line | | For readability (ignored) |
| Directory | `node_modules/` | Matches the directory and everything inside it |
| File | `*.log` | Matches any file ending in `.log` |
| Negation | `!important.log` | Re-includes a previously ignored file |
| Anchored | `/build` | Matches only at the repo root, not in subdirectories |
| Multi-level | `logs/**/debug.log` | `**` matches across directories |

### Common glob patterns

- `*` — any characters except `/`
- `?` — a single character
- `[abc]` — one of the listed characters
- `**` — any number of directories (e.g. `a/**/b`)

## Key Rules to Remember

1. **Order matters** — later patterns override earlier ones. Put `!` negations after the pattern they override.
2. A pattern ending in `/` only matches directories; one without `/` matches files and directories.
3. **You can't ignore already-tracked files.** If a file is already committed, `.gitignore` won't hide it. Untrack it first:
   ```
   git rm --cached file.log     # removes from index, keeps it on disk
   ```
4. `.gitignore` files can exist in any subdirectory and apply to that subtree.

## Global Ignore (personal, not per-repo)

```
git config --global core.excludesFile ~/.gitignore_global
```

Put machine-specific patterns here (editor swap files, OS junk) so they don't get committed to shared repos.

## Checking What Will Be Ignored

```
git status --ignored        # shows ignored files too
git check-ignore -v path    # which rule matched this file
git check-ignore -v .env    # -> .env:12:.env  (file:line:pattern)
```

## Common Repo Examples

```
node_modules/
dist/
build/
*.log
.env
.env.*
!.env.example
.DS_Store
target/
__pycache__/
```
