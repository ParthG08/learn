# Filesystem Navigation

## `pwd` — Print working directory

Shows the absolute path of the current directory.

## `ls` — List directory contents

### Ordering options

| Option | Effect |
|--------|--------|
| `ls -t` | Sort by modification time (newest first) |
| `ls -tr` | Sort by modification time (oldest first) |
| `ls -S` | Sort by file size (largest first) |
| `ls -Sr` | Sort by file size (smallest first) |
| `ls -X` | Sort by file extension |
| `ls -v` | Natural version sorting (e.g. `file1, file2, file10` not `file1, file10, file2`) |

### Other useful options

| Option | Effect |
|--------|--------|
| `ls -l` | Long format (permissions, owner, size, date) |
| `ls -a` | Show hidden files (`.` and `..`) |
| `ls -A` | Show hidden files (exclude `.` and `..`) |
| `ls -h` | Human-readable sizes (with `-l`) |
| `ls -R` | Recursive listing |
| `ls -d */` | List only directories |
| `ls -1` | One entry per line |

Common combos: `ls -ltr` (long, by time, reversed — see most recent at bottom), `ls -lah` (long, all, human-readable).

## `cd` — Change directory

| Command | Effect |
|---------|--------|
| `cd /path/to/dir` | Absolute path (starts from `/`) |
| `cd path/to/dir` | Relative path (from current directory) |
| `cd ..` | Up one level |
| `cd -` | Previous directory |
| `cd ~` or `cd` | Home directory |
| `cd ~user` | Home of `user` |
