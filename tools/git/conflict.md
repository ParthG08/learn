# Git Conflict Resolution Notes

## Understanding Git Conflicts

A conflict occurs when Git can't automatically merge changes from two different branches because they modified the same part of the same file.

### When Conflicts Happen
- Two branches modify the same line in a file
- One branch deletes a file while another modifies it
- Merge/rebase operations with overlapping changes

## Conflict Resolution Steps

### 1. Identify Conflicted Files
```bash
git status
```

