# Branching & Merging Logic

- Branches are not folders. They are pointers (references) to a specific commit in Git.(Just like you could see in a commit tree visualization)
- A branch name simply tells Git which commit is the current tip for that branch.
- When you move a branch, you are moving the pointer to a new commit.
- visualize commit tree like a graph with nodes. Ref: https://git-scm.com/docs/commit-graph

## Fast-forward vs. 3-way merge

### Fast-forward merge
- Happens when the branch being merged into has no new commits since the branch was created.
- Git can simply move the target branch pointer forward to the latest commit of the source branch.
- No new merge commit is created.
- Example: `main` points to commit A, `feature` points to commit B, and B is a descendant of A.
- Result: `main` now points to B.

### 3-way merge
- Happens when both branches have new commits since they diverged.
- Git must combine changes from:
  1. the common ancestor commit,
  2. the source branch tip,
  3. the target branch tip.
- Git creates a new merge commit with two parents.
- This preserves the history of both branches and records the merge event.

### Why Git sometimes merges instantly and sometimes creates a merge commit
- If the current branch has not advanced beyond the branch you are merging, Git can fast-forward.
- If both branches have independent commits after they split, Git must perform a three-way merge.
- A merge commit is created when the histories have diverged.

## Merge Conflicts

- Conflicts occur when the same file region changed in different ways on both branches.
- Git marks conflicts inside the file with special markers:
  - `<<<<<<< HEAD`
  - `=======`
  - `>>>>>>> branch-name`

### How to resolve conflicts manually
1. Open the conflicted file.
2. Find the conflict markers.
3. Decide which code should remain:
   - keep the code from the current branch,
   - keep the code from the branch being merged,
   - or combine both changes.
4. Remove the markers and any unwanted code.
5. Save the file.
6. Mark the conflict as resolved: `git add <file>`.
7. Complete the merge: `git commit` (if Git did not auto-create the merge commit).

### Example conflict block
```text
- <<<<<<< HEAD 

current branch code
=======
merged branch code

- >>>>>>> feature-branch
```
- Everything between `<<<<<<< HEAD` and `=======` is from the current branch.
- Everything between `=======` and `>>>>>>> feature-branch` is from the branch being merged.
- Choose the correct result and delete the `<<<<<<<`, `=======`, `>>>>>>>` lines.

## Practical ideas

- Think of branches as lightweight pointers, not directories.
- A clean history often uses fast-forward merges when possible.
- Use merge commits when you want to keep explicit branch history.
- Be comfortable reading and editing conflict markers; that is the core of manual merge resolution.
