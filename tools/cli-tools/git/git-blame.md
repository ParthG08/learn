# Git Blame & Code Archaeology

`git blame` annotates each line of a file with the commit that last changed it — who, when, and which commit. Paired with `git log -p` and `git log --follow`, it forms the core toolkit for tracing the origins and evolution of any piece of code.

## `git blame` — Line-Level Annotation

```bash
git blame <file>
```

Output per line:

```
abc1234 (Alice  2025-03-15 10:22:01 +0900  42)   return x * 2;
```

Columns: commit hash, author, timestamp, timezone, line number, then the line content.

### Key Options

```bash
git blame -L 10,50 <file>          # only lines 10–50
git blame -L '/func main/',/^}/ <file>  # from "func main" to the closing brace
git blame -w                        # ignore whitespace-only changes
git blame -C                        # detect lines moved/copied from other files
git blame -CCC                      # deeper copy detection (across any commit)
git blame -M                        # detect lines moved within the same file
git blame --date=short              # YYYY-MM-DD format instead of full timestamp
```

### Ignoring Bulk Reformatting

If a large reformat commit pollutes your blame output (every line shows the same refactor commit), tell blame to ignore it:

```bash
git blame --ignore-revs-file .git-blame-ignore-revs <file>
```

Where `.git-blame-ignore-revs` contains commit hashes to skip, one per line. You can also set it globally:

```bash
git config blame.ignoreRevsFile .git-blame-ignore-revs
```

### Show the Actual Commit

Blame shows the hash — to see the full commit message:

```bash
git show abc1234
```

Or combine blame + show in one flow: find the line, get the hash, inspect the commit to understand *why* the change was made.

## `git log -p` — Patches in Logs

Shows the full diff/patch for each commit inline with the log, so you see the actual code changes as you walk through history.

```bash
git log -p                              # all commits with diffs
git log -p -3                           # last 3 commits with diffs
git log -p -- <file>                    # history of a specific file with diffs
git log -p -S "someFunction"            # show diffs for commits that added/removed "someFunction"
git log -p -G "regexPattern"           # show diffs for commits whose diff matches the regex
```

Useful when you know a function or string appeared/disappeared but not when. `-S` (pickaxe) finds commits where the count of that string changed.

## `git log --follow` — Track Across Renames

`git log <file>` normally stops at the point the file was renamed. `--follow` continues the history through renames.

```bash
git log --follow -p -- <file>          # full diff history, even if renamed
git log --follow --oneline -- <file>   # compact one-line history across renames
```

Git detects renames by similarity (default 50%). Lower the threshold for more aggressive detection:

```bash
git log --follow --find-renames=30% -- <file>
```

## Code Archaeology Workflow

When you encounter a line of code and need to understand its full story:

```bash
# 1. Who wrote this line and when?
git blame -L <line>,<line> <file>

# 2. What was the full commit that introduced it?
git show <hash>

# 3. What was the discussion/context around that commit?
git log --oneline <hash>~3..<hash>    # commits right before it

# 4. Has this line been touched by later commits?
git log -L <line>,<line>:<file>       # trace the evolution of specific lines
```

### `git log -L` — Line History

Unlike blame (which shows the *last* change), `-L` shows *every* commit that touched a given range of lines:

```bash
git log -L 42,42:<file>                # every commit that changed line 42
git log -L '/func main/',/^}/:<file>   # every commit that touched func main
```

This is the most powerful archaeology tool. It follows the lines even as they move due to additions/deletions above them.

## Practical Patterns

**Find out when a bug was introduced:**

```bash
git log -p -S "buggyFunction" -- path/to/file.go
```

**Trace a file's entire life across renames:**

```bash
git log --follow --oneline --name-status -- path/to/current-name.go
```

**See who to ask about a section of code:**

```bash
git blame -L '/func Handler/',/^}/ -w -C handler.go
```

**Find deleted code (find the commit that removed something):**

```bash
git log -p -S "removedVariable"        # shows the commit where it was deleted
```

## Git Blame in VSCode

### Built-in (No Extensions)

**Inline blame annotation (status bar):**

Open any file, then install and enable the built-in GitLens-free blame via the setting:

```json
"git.blame.statusBarItem": true
```

This shows the blame for the currently selected line in the VSCode status bar (author + commit message).

**Open the blame view from the command palette:**

- `Ctrl+Shift+P` → **"Git: Toggle File Blame"** — opens a read-only blame editor showing every line annotated with author, commit hash, and relative timestamp.
- `Ctrl+Shift+P` → **"Git: Toggle File Blame Annotations"** — adds gutter annotations directly in the current editor (less disruptive than the full blame editor).

**GitLens is not required for basic blame** — VSCode ships with a lightweight `@builtin git` blame feature that covers most daily needs.

### GitLens Extension

Install: `eamodio.gitlens` from the VSCode marketplace.

**What GitLens adds on top of built-in blame:**

- **Inline blame annotations** (always visible, no toggle needed) — each line gets a faded author + relative timestamp at the end.
- **File history view** (`Ctrl+Shift+P` → "GitLens: Show File History") — full commit log for the current file, grouped by contributor.
- **Line history view** (`Ctrl+Shift+P` → "GitLens: Show Line History") — equivalent to `git log -L` but in a GUI. Select a line or range and see every commit that touched it.
- **Commit details hover** — hover any blame annotation to see the full commit message, diff, and related pull request.
- **Revision navigation** — `Alt+]` / `Alt+[` to jump through the history of a selected line, seeing how it changed commit-by-commit.
- **Interactive rebase editor** — visual squash/reorder/drop for rebasing.

**Key GitLens settings to configure:**

```json
{
  "gitlens.currentLine.enabled": true,           // blame on current line
  "gitlens.currentLine.pullRequests.enabled": true, // link blame to PR
  "gitlens.blame.highlight.enabled": true,        // heatmap coloring by age
  "gitlens.blame.heatmap.enabled": true,          // hotter color = more recent
  "gitlens.blame.format": "${author|15} ${agoOrDate|14-}", // compact format
  "gitlens.codeLens.enabled": true                // inline buttons on functions/classes
}
```

**Workflow with GitLens:**

1. Open a file → see inline blame on every line (author + when).
2. Hover a blame annotation → full commit message, files changed, linked PR.
3. Right-click a line → **"Show Line History"** → every commit that touched that line.
4. Right-click a line → **"Show File History"** → full commit log filtered to this file.
5. Heatmap colors tell you at a glance which sections are stable (cold/blue) vs recently churning (hot/red).

**Comparison: Built-in vs GitLens**

| Feature | VSCode Built-in | GitLens |
|---|---|---|
| Per-line blame | Toggle on/off | Always visible |
| Commit hover details | No | Yes (full diff + PR) |
| Line history (`git log -L`) | No | Yes |
| Heatmap (age coloring) | No | Yes |
| File history | `Git: View File History` (basic) | Rich UI grouped by author |
| Interactive rebase | No | Yes |
| Performance | Faster | Slightly heavier |

## Why This Matters

Production incidents often start with a single line of code that looks suspicious. `git blame` tells you who wrote it and when. `git log -p` shows the diff context. `git log --follow` traces its full history. Together, they let you reconstruct the intent behind any change without asking anyone — a critical skill for debugging unfamiliar codebases at speed.
