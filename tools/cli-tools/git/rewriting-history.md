# Rewriting History (The "Clean-Up")

This separates amateurs from pros. You need to know how to keep a project history readable.

## Rebase: Moving a sequence of commits to a new base commit (keeps history linear).

Rebase replays commits from one branch onto another, creating a linear history without merge commits.

### Basic Rebase
```bash
# Rebase current branch onto main
git checkout feature-branch
git rebase main
```

### Interactive Rebase (-i): Essential for "squashing" 10 tiny "fix typo" commits into one professional "Feature X implementation" commit.

Interactive rebase allows you to edit, squash, reorder, or drop commits.

```bash
# Start interactive rebase for the last 5 commits
git rebase -i HEAD~5

# In the editor, change 'pick' to 'squash' for commits to combine
# Example:
# pick abc123 Initial commit
# squash def456 Fix typo
# squash ghi789 Add feature
```

Common commands in interactive rebase:
- `pick`: Keep the commit as is
- `squash`: Combine with previous commit
- `edit`: Stop to edit the commit
- `drop`: Remove the commit
- `reword`: Change commit message

## Amending: Using git commit --amend to add a forgotten file to your last commit without creating a new one.

Amend modifies the last commit instead of creating a new one.

### Amend last commit with new changes
```bash
# Stage the forgotten file
git add forgotten-file.txt

# Amend the last commit
git commit --amend
```

### Amend with new message
```bash
git commit --amend -m "New commit message"
```

### Amend without changing message
```bash
git commit --amend --no-edit
```

## Amend for editing the last commit
- To change the commit message: Just run git commit --amend. Your editor will open, allowing you to rewrite the text.
- To add or change code:
    1. Edit your files or add the forgotten file.
    2. Stage them: 
        ```bash
            git add <file>.
        ```
    3. Run: 
        ```bash
            git commit --amend --no-edit
        ```
        (The --no-edit flag keeps the existing message so you don't have to re-type it).

## Warning
Never amend a commit that you have already pushed to a shared branch. It changes the SHA, which will break the history for your teammates

## Practical Tips

- Use rebase on local branches before pushing to keep remote history clean
- Interactive rebase is powerful but rewrites history - avoid on shared branches
- Amend is safe for local commits, but dangerous after pushing
- Always backup with a branch before complex rebases
