# Commit Hash: Finding and Using It

## Where to Find the Commit Hash

The hash is the "fingerprint" of your work. Use these commands:

| Command | Output |
|---------|--------|
| `git log` | Shows the full 40-character SHA, author, date, and message. |
| `git log --oneline` | Shows only the short hash (first 7 characters) and the message. |
| `git reflog` | Shows hashes for every move HEAD has made (includes deleted commits). |
| `git rev-parse HEAD` | Outputs only the full hash of your current commit (great for scripts). |

## Use Cases for the Hash

You use the hash whenever you need to point Git at a specific moment in time:

- `git checkout [hash]`: "Time travel" to see what the code looked like at that exact moment.
- `git cherry-pick [hash]`: Copy a specific fix from a different branch into your current one.
- `git reset --hard [hash]`: Wipe away all work and revert the entire project back to that specific state.
- `git show [hash]`: See exactly what lines of code were changed in that specific commit.
- `git diff [hash1] [hash2]`: Compare the differences between two specific points in history.

## Pro Tip

In almost every Git command, you can use the short 7-character hash instead of the long 40-character one. Git is smart enough to find the right one.

## Finding the Pull Request from a Commit Hash

Yes, it is definitely possible to track a commit hash back to its originating Pull Request (PR). Depending on where your code is hosted, there are several useful approaches.

### 1. Using the Web Interface

- On GitHub, GitLab, or Bitbucket, paste the full commit hash into the repository search bar.
- On GitHub, you can often open the commit page directly with:
  `https://github.com/[owner]/[repo]/commit/221378aa7263663834a99deb6bfbc18beddaf481`
- If that commit was part of a PR, the commit page usually shows a link to the PR beneath the commit message title.
- If the commit was squash-merged, the exact hash may differ on the target branch, so search by commit message instead.

### 2. Using GitHub CLI (`gh`)

- If you have GitHub CLI installed, search merged PRs by the commit hash:
  `gh pr list --search "221378aa7263663834a99deb6bfbc18beddaf481" --state merged`

### 3. Using `git log` in the terminal

- If the PR was merged with a merge commit, you can search for the merge commit that introduced the hash:
  `git log --merges --ancestry-path 221378aa7263663834a99deb6bfbc18beddaf481..master`
- Look for messages like `Merge pull request #XX from ...` which identify the PR number.

### 4. Using the API

- GitHub offers an endpoint to list PRs associated with a commit:
  `curl -H "Authorization: token YOUR_TOKEN" https://api.github.com/repos/[OWNER]/[REPO]/commits/221378aa7263663834a99deb6bfbc18beddaf6bfbc18beddaf481/pulls`

### Note on Squash and Merge

- With `Squash and merge`, the commit hash on the final branch is usually different from the original feature branch commit.
- In that case, searching by the commit message in the PR search bar is often the most reliable way to find the source PR.

