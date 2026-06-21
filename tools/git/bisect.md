# Bisect (Regression Hunting)

`git bisect` is a built-in binary search tool that helps you find the exact commit that introduced a bug or broke something. Instead of manually checking out commits one by one, Git does the math and narrows down the culprit in O(log n) steps.

## The Core Idea

You tell Git two things:

1. A **bad** commit — where the bug exists (usually `HEAD`).
2. A **good** commit — a point in history where everything worked fine.

Git then checks out the midpoint between those two commits and asks you: is this good or bad? Based on your answer, it eliminates half the remaining range and picks the next midpoint. Repeat until it pins down the exact offending commit.

	## Basic Workflow

```bash
git bisect start
git bisect bad                  # mark current HEAD as broken
git bisect good <commit-hash>   # mark a known-good commit
```

Git checks out a commit in the middle. You test it (run the app, run a test, whatever tells you if the bug is present), then report:

```bash
git bisect good   # this commit is fine, bug isn't here yet
# or
git bisect bad    # bug is present here too, narrow further
```

Keep going until Git prints something like:

```
abc1234 is the first bad commit
```

When done, always clean up:

```bash
git bisect reset   # returns HEAD back to where you started
```

## Automating It

If you have a script or test command that exits `0` for good and non-zero for bad, you can hand the entire process off to Git:

```bash
git bisect start
git bisect bad HEAD
git bisect good v1.4.0
git bisect run npm test         # or any script that returns 0/non-zero
```

Git will run the command at each midpoint automatically and find the bad commit without any manual input. This is the real power — you can walk away and come back to the answer.

## Skipping a Commit

Sometimes a commit in the middle can't be tested (broken build, missing dependency, etc.):

```bash
git bisect skip
```

Git will pick a nearby commit to test instead and keep narrowing.

## Practical Tips

- **You don't need to know the exact good commit.** A tag like `v1.0` or even `HEAD~100` is fine as a starting point.
- **The fewer commits in the range, the faster it converges.** `git log --oneline good..bad | wc -l` tells you how many commits are in the range, and bisect will take roughly `log2(n)` steps.
- **Write a reproducer first.** Bisect is only as useful as your ability to reliably tell good from bad. A flaky manual check will give you a wrong answer. A deterministic script is ideal.
- **Bisect works on any change** — not just bugs. You can bisect for when a performance regression appeared, when a test started failing, when a file changed, anything with a clear binary signal.

## Why This Matters

In a repo with hundreds of commits, manually narrowing down a regression can take hours. Bisect turns it into ~7-10 steps regardless of range size. It is one of those commands that feels like overkill until the first time you actually need it, and then it saves you completely.
