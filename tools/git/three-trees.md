## Three Trees

# Working Directory

The working directory is the actual files on disk where you are actively making changes.
When files are modified here, Git marks them as changed and you can see the diff in VS Code or with `git diff`.
From the working directory, you can:

- edit files
- create new files
- delete files
- inspect uncommitted changes

If you want to undo changes in the working directory, use `git restore <file>` or `git checkout -- <file>`.

# Staging Area (Index)

The staging area is the waiting room for your next commit.
You explicitly add changes to this area using commands like:

```bash
git add .
# or git add <file>
```

When changes are staged, they are prepared for commit but not yet part of history.
This is useful when you want to group only some changes into a commit or review exactly what will be recorded.
Use `git status` to see what is in the working directory and what is staged.

# HEAD (Commit History)

HEAD points to the latest commit in your current branch — the snapshot of the project that Git thinks is current.
When you commit staged changes, they move from the staging area into HEAD:

```bash
git commit -m "Your message"
```

After commit, the changes are stored in history and no longer appear as modified in the working directory unless new edits are made.

# Important notes

- Working Directory -> Staging Area: `git add` moves changes into the index.
- Staging Area -> HEAD: `git commit` writes staged changes into commit history.
- If you modify a file after staging it, the working directory and staging area can differ for that file.
- Common errors happen when users think `git add` already commits changes, or when they forget which state their files are in.
- Use `git status` frequently to understand where each file lives.

# Common confusion

- A file can be modified in the working directory but not staged.
- A file can be staged but not committed.
- HEAD is the last committed snapshot, not the current editable file contents.
- If you want to remove a change from staging but keep it in the working directory, use `git restore --staged <file>`.
- If you want to discard unstaged changes completely, use `git restore <file>`.
