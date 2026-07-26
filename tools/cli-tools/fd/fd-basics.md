# `fd` — A Smarter `find`

`fd` is a fast, user-friendly alternative to `find`. Sane defaults (ignores `.gitignore`, hidden files, respects `.git`), colored output, regex by default.

## Core Usage

```bash
fd PATTERN              # Search by filename (regex)
fd PATTERN /path        # Search in specific directory
fd -e py PATTERN        # Filter by extension
fd -H PATTERN           # Include hidden files
fd -t d PATTERN         # Only directories
fd -t f PATTERN         # Only files
fd -x CMD               # Execute command on each result (like find -exec)
fd ... | xargs CMD      # Pipe-friendly
fd --changed-within 24h # Files changed in last 24 hours
```

## fd + xargs (execution)

```bash
fd -e md | xargs wc -l           # Line count on all .md files
fd -e py -x black                # Format all Python files (parallel safe)
fd 'TODO' -e js -x sed -i 's/TODO/FIXME/g'  # Replace across files
```

## Why Learn Standalone When Yazi Has It Built In?

Yazi uses `fd` as its **search backend** — you type in the file browser, and Yazi calls `fd` under the hood. That gives you `fd` inside Yazi without learning it.

But standalone `fd` has uses Yazi can't cover:

| Context | Yazi | Standalone `fd` |
|---|---|---|
| Scripting / automation | No | Yes — `fd ... | xargs`, `fd -x` |
| CI/CD pipelines | No | Yes |
| Any non-interactive terminal session | No | Yes |
| Combining with other tools (`rg`, `sed`, pipes) | No | Yes |

**Verdict:** Not critical. Learn it when `find` starts feeling slow or verbose. Cost = one afternoon. The composability with `xargs` and pipes is where it earns its keep — and Yazi can't help you in a script. Low priority, but useful eventually.
