# Remote Workflows

## 1. Upstream vs Origin

- `origin` is usually the remote that points to your personal fork of a repository.
- `upstream` is usually the remote that points to the original source repository you forked from.
- Use `git remote -v` to inspect configured remotes and confirm which one is which.
- When collaborating on a forked project, fetch or pull from `upstream` to keep your fork current, then push your feature branches to `origin`.

## 2. Fetching vs Pulling

- `git fetch` downloads commits, branches, and tags from a remote without changing your current working tree.
- `git pull` is shorthand for `git fetch` followed by `git merge` (or `git rebase`, depending on config).
- Fetching first is safer because it lets you review incoming changes before integrating them.
- Example safe workflow:
  - `git fetch upstream`
  - `git log HEAD..upstream/main` or `git diff HEAD..upstream/main`
  - `git merge upstream/main`
- Mostly the remote of the fetcha nd teh push are the same like when you write
  - `git remove -v` 
    The result shows
        origin  git@github.com:ParthG08/learn.git (fetch)
        origin  git@github.com:ParthG08/learn.git (push)
    This shows that the fetch remote and the push remote are essentially the same.
    (You can ponder more over when they are acutally different).

## 3. Force Pushing

- `git push --force` overwrites the remote branch history and can discard others' commits if they are present.
- This is dangerous on shared branches because it rewrites commit history and can break collaborators' work.
- `git push --force-with-lease` is safer because it verifies the remote branch has not changed since you last fetched.
- Use `--force-with-lease` when you need to rewrite the branch history for a personal feature branch, but avoid force pushing to shared branches like `main` or `master`.
