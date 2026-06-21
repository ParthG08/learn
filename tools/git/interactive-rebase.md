# Git Interactive Rebase (`git rebase -i`)

An **interactive rebase** is a powerful Git tool used to modify, clean up, and reorganize commit history before merging or pushing code. Unlike a standard rebase, it provides an interactive menu allowing you to alter individual commits.

## Overview of Operation
Running `git rebase -i HEAD~N` opens a temporary text file listing the last `N` commits in **chronological order** (oldest to newest). History is manipulated by replacing the default `pick` command with specific action keywords or by changing the line order.

## Key Commands

| Command | Shortcut | Description |
| :--- | :---: | :--- |
| **`pick`** | `p` | Keep the commit as-is. |
| **`reword`** | `r` | Keep the commit, but modify the commit message. |
| **`edit`** | `e` | Pause the rebase at this commit to amend files or contents. |
| **`squash`** | `s` | Meld the commit into the previous one, combining their log messages. |
| **`fixup`** | `f` | Meld the commit into the previous one, discarding this commit's log message. |
| **`drop`** | `d` | Completely remove the commit from history. |

## Common Workflows
* **Cleaning Up History:** Reordering commits or using `fixup`/`squash` to hide "WIP" (Work In Progress) steps before code review.
* **Fixing Typos:** Using `reword` to correct structural errors or spelling mistakes in older commit logs.

## The Golden Rule
> ⚠️ **Never interactively rebase commits that have already been pushed to a public/shared repository.**
> 
> Because rebasing rewrites history (generating completely new commit hashes), altering shared history forces teammates into split-history states and disrupts collaboration. Restrict interactive rebasing to local, unpushed feature branches.
