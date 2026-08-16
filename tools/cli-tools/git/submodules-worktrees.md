# Submodules & Worktrees (P2)

## Git Submodules

A submodule is a git repo nested inside another git repo. The parent repo records a **commit SHA** of the submodule, not the submodule's contents.

### Adding
```bash
git submodule add https://github.com/org/lib.git  vendor/lib
git commit -m "add vendor/lib submodule"
```
- Creates `vendor/lib/` (clone of the repo) + a `.gitmodules` file.
- The parent repo stores: `.gitmodules` (URL + path) and a gitlink (commit SHA) at `vendor/lib`.

### Cloning a repo with submodules
```bash
git clone --recurse-submodules <url>    # clone + init + update
# or after a plain clone:
git submodule update --init --recursive
```

### Updating / pulling
```bash
git submodule update --remote        # update each submodule to its remote default branch tip
git submodule update --init --recursive   # sync to recorded SHAs
git submodule foreach git pull      # run a command in every submodule
```

### Key mental model
- The submodule is **checked out at a specific commit**, pinned by the parent.
- If someone changes the submodule repo, you must `git submodule update` to get the new SHA.
- `git status` shows `dirty` when the submodule's working dir differs from the recorded SHA.

### When to use / avoid
| Use submodules | Avoid submodules |
|---|---|
| Pinning a dependency that needs its own history | Simple vendoring you rarely update |
| Multiple repos sharing a library | Anything with complicated build coupling |
| Exact reproducibility of a dependency version | If a monorepo or package manager solves it better (often it does) |

### Common pain points
- Forgetting `--recurse-submodules` → empty directory with no content.
- Swapping branches in the parent doesn't auto-update submodules.
- Merging branches that moved the submodule can leave it "on a detached HEAD" or dirty.
- Prefer package managers (npm/pip/go modules) over submodules whenever possible.

---

## Git Worktrees

A worktree is **multiple working directories from the same repo**, all sharing one `.git` directory. Lets you check out two branches simultaneously.

```bash
git worktree add ../project-hotfix feature/x    # new dir checked out to branch feature/x
git worktree add -b fix/typo ../typo-fix main   # create branch + worktree
git worktree list                                # show all worktrees
git worktree remove ../project-hotfix            # remove (must be clean/not checked out)
```

### Why use worktrees
- Work on a hotfix without stashing or losing your current uncommitted work.
- Run tests / review a PR branch while keeping your main worktree open.
- Clean separation: each directory has its own files — no context switching cost.
- Great for running two versions of a service simultaneously (dev + test).

### Rules / gotchas
- You cannot check out the **same branch in two worktrees**.
- Each worktree still shares branch refs, config, and objects — commit in one, it's visible in the other's log (different working dirs, same repo).
- Files that are **untracked** in one worktree don't block the other (tracked changes are protected).
- `.git/worktrees/<name>` holds per-worktree state (index, HEAD).

### Comparison
| Submodules | Worktrees |
|---|---|
| Multiple repos nested | One repo, multiple checkouts |
| Independent histories | Shared history / refs / objects |
| For vendoring pinned deps | For parallel development on branches |
| Adds complexity | Removes the "can't switch branches" problem |

---

## Quick reference
- **Submodule** = git repo pinned at a commit inside your repo → `.gitmodules` + gitlink SHA.
- Clone with `--recurse-submodules`; update with `git submodule update --init`.
- **Worktree** = second working directory for another branch of the same repo → `git worktree add <dir> <branch>`.
- Use worktrees for parallel dev; use submodules only when a package manager can't do the job.
