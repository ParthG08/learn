# Bash Scripting

## When is bash scripting useful?

- **Automation**: daily reports, log rotation, backup scripts, clean-up cron jobs
- **CI/CD**: build pipelines, test runners, deployment glue scripts
- **Dev environment setup**: one-command bootstrap scripts (`setup.sh`)
- **Log parsing & monitoring**: combined with `grep`/`sed`/`awk` for quick incident response
- **Docker entrypoints**: many containers use bash entrypoint scripts
- **System administration**: user provisioning, disk checks, service health checks

Rule of thumb: if the task is under ~200 lines and mostly shells out to other CLI tools, bash is fine. Beyond that, switch to Python/Go.

---

## Variables

```bash
NAME="parth"               # no spaces around =
AGE=25
CURRENT_DIR=$(pwd)         # command substitution
FILES=$(ls *.txt)          # capture command output (use cautiously)

echo "Hello, $NAME"        # $VAR for value
echo "Path: ${CURRENT_DIR}"  # ${} for clarity or concat
echo 'Literal $NAME'       # single quotes = no expansion
```

Variables are untyped (everything is a string). Special variables:

| Var | Meaning |
|-----|---------|
| `$0` | Script name |
| `$1, $2...` | Positional arguments |
| `$#` | Number of arguments |
| `$@` | All arguments (as separate words) |
| `$*` | All arguments (as single string) |
| `$?` | Exit code of last command |
| `$$` | PID of the script |

## Conditionals

### `if` / `elif` / `else`

```bash
if [ "$NAME" = "parth" ]; then
    echo "It's you"
elif [ "$AGE" -gt 20 ]; then
    echo "Old enough"
else
    echo "Nope"
fi
```

### `[ ]` vs `[[ ]]` — prefer `[[]]` in bash

```bash
# [[ ]] supports regex, pattern matching, &&, ||, and no quoting needed for vars
if [[ $NAME == parth ]]; then echo "match"; fi
```

### Common test operators

| String | Integer | File |
|--------|---------|------|
| `=` / `==` | `-eq` equal | `-f` exists and is file |
| `!=` | `-ne` not equal | `-d` is directory |
| `-z` empty | `-gt` greater than | `-x` executable |
| `-n` not empty | `-lt` less than | `-e` exists |
| | `-ge`, `-le` | `-s` non-empty |

### `&&` and `||` as inline conditionals

```bash
[ -d /tmp ] && echo "tmp exists"
[ -f /etc/passwd ] || echo "no passwd file!"
mkdir logs 2>/dev/null || { echo "Cannot create logs dir"; exit 1; }
```

### `case`

```bash
case "$1" in
    start)  echo "Starting...";;
    stop)   echo "Stopping...";;
    *)      echo "Usage: $0 {start|stop}"; exit 1;;
esac
```

## Loops

### `for`

```bash
for i in 1 2 3; do echo "$i"; done
for file in *.txt; do echo "Processing $file"; done
for ((i=0; i<5; i++)); do echo "$i"; done  # C-style
```

### `while`

```bash
count=0
while [[ $count -lt 5 ]]; do
    echo "$count"
    ((count++))
done

# read file line by line
while IFS= read -r line; do
    echo "$line"
done < file.txt
```

### `until`

```bash
until ping -c1 google.com &>/dev/null; do
    echo "Waiting for network..."
    sleep 1
done
```

## Functions

```bash
greet() {
    local name="$1"
    echo "Hello, $name"
}

greet "parth"

# return codes (0 = success, 1-255 = failure)
is_running() {
    pgrep -x "$1" > /dev/null
    return $?
}
```

- `local` prevents variable leaking to outer scope.
- Use `return`, not `exit` ( `exit` terminates the whole script).
- Arguments accessed as `$1`, `$2`, etc. within the function.

## Script template

```bash
#!/bin/bash
set -euo pipefail   # exit on error, undefined var, pipe failure

# set -e  = exit on any command failure
# set -u  = error on undefined variables
# set -o pipefail = pipeline fails if any command in it fails

usage() {
    echo "Usage: $0 <name>"
    exit 1
}

main() {
    local name="${1:-}"
    [[ -z "$name" ]] && usage
    echo "Hello, $name"
}

main "$@"
```
