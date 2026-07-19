# grep — Global Regular Expression Print

## Syntax

```
grep [options] regex [file...]
```

If no file is given, `grep` reads from stdin. Filenames support shell globs:

```bash
grep bzip dirlist*.txt
```

---

## Common Options

| Option | Effect |
|--------|--------|
| `grep -i` | Case-insensitive match |
| `grep -v` | Invert match (lines that do **not** match) |
| `grep -c` | Count matching lines |
| `grep -l` | List only filenames with a match |
| `grep -L` | List only filenames with **no** match |
| `grep -n` | Show line numbers |
| `grep -h` | Suppress filename prefix (multi-file) |
| `grep -w` | Match whole words only |
| `grep -o` | Print only the matched part, not whole line |
| `grep -r` | Recursive search in directory |
| `grep -E` | Extended regex (`+`, `?`, `|`, `()`) |
| `grep -F` | Fixed strings (no regex, literal match) |
| `grep -A N` | Show N lines **after** match |
| `grep -B N` | Show N lines **before** match |
| `grep -C N` | Show N lines **context** (before + after) |

Common combo: `grep -rni "pattern" .` (recursive, line numbers, case-insensitive in current dir).

---

## File Globbing in Editors

### VSCode

Use **Search Across Files** (`Ctrl+Shift+F`). The **files to include** field supports glob patterns:

```
src/**/*.ts          — all .ts files under src/
**/*.{js,ts}         — all .js and .ts files
test/**/*.test.*     — test files
```

### nvim

With **telescope.nvim** (`live_grep`):

```
Live grep in: dirlist*.txt
```

With `:vimgrep`:

```vim
:vimgrep /pattern/ dirlist*.txt
:vimgrep /pattern/ **/*.py
```

---

# Regex Metacharacters

## 1. `.` — Any Character (dot)

Matches any single character except newline.

```bash
grep 'c.t' file      → cat, cot, cAt, c9t, c t
grep 'r..d' file     → read, road, r3id
```

## 2. `^` and `$` — Anchors

| Anchor | Meaning |
|--------|---------|
| `^` | Start of line |
| `$` | End of line |

```bash
grep '^Hello' file   → lines starting with Hello
grep 'world$' file   → lines ending with world
grep '^$' file       → empty lines
grep '^#.*$' file    → lines that are comments (start with #)
```

## 3. `[]` — Bracket Expressions

Matches **any one** character from the set inside brackets.

```bash
grep '[aeiou]' file          → any lowercase vowel
grep 'gr[ae]y' file          → gray or grey
```

### The `-` Range Operator

A hyphen between two characters defines a character range (by ASCII/Unicode collation order):

```bash
grep '[0-9]' file            → any digit (0 through 9)
grep '[a-z]' file            → any lowercase letter
grep '[A-Z]' file            → any uppercase letter
grep '[a-zA-Z]' file         → any letter (both cases)
grep '[0-9a-fA-F]' file      → any hex digit
```

`-` is only a range operator when placed **between** two characters. At the start or end of `[]`, it is literal:

```
[-abc]   → literal '-' or a or b or c
[a-c-]   → a through c, or literal '-'
```

### `^` inside `[]` — Negation

When `^` is the **first character** inside `[]`, it **negates** the set — it is **NOT** an anchor here:

```
[0-9]    → matches any digit
[^0-9]   → matches anything that is NOT a digit

^Hello   → anchor: line starts with Hello
[^H]     → negated set: any character except H
```

| Position of `^` inside `[]` | Meaning |
|------------------------------|---------|
| First character: `[^abc]` | Negation — NOT a, b, or c |
| Not first: `[a^bc]` | Literal `^` character |

Only `^`, `]`, and `-` have special meaning inside `[]`.

### POSIX Character Classes

These are **named** character classes usable inside bracket expressions. Note the **double brackets** — outer `[]` for the bracket expression, inner `[:class:]` for the class.

| Class | Equivalent | Matches |
|-------|-----------|---------|
| `[:alnum:]` | `[a-zA-Z0-9]` | Alphanumeric |
| `[:alpha:]` | `[a-zA-Z]` | Alphabetic |
| `[:blank:]` | `[ \t]` | Space and tab |
| `[:cntrl:]` | | Control characters |
| `[:digit:]` | `[0-9]` | Digits |
| `[:graph:]` | | Visible characters (excl. space) |
| `[:lower:]` | `[a-z]` | Lowercase |
| `[:print:]` | | Printable characters (incl. space) |
| `[:punct:]` | | Punctuation characters |
| `[:space:]` | `[ \t\n\r\f\v]` | Whitespace |
| `[:upper:]` | `[A-Z]` | Uppercase |
| `[:xdigit:]` | `[0-9a-fA-F]` | Hex digits |

Usage in regex:

```bash
grep '[[:digit:]]' file         → lines containing a digit
grep '[[:upper:]]' file         → lines containing an uppercase letter
grep '^[[:space:]]' file        → lines starting with whitespace
```

---

## Pathname Expansion (Shell Globbing) — **NOT Regex**

Shell globbing uses wildcards to match **filenames**. The syntax looks similar to regex but **is not regex**.

| Globbing | Regex | Meaning |
|----------|-------|---------|
| `*` | `.*` | Any string (0+ chars) |
| `?` | `.` | Any single character |
| `[abc]` | `[abc]` | One char from the set |
| `[A-Z]` | `[A-Z]` | One char in range |
| `[!abc]` | `[^abc]` | Negation (NOT a, b, or c) |

### Examples of Pathname Expansion

```bash
ls /usr/bin/[A-Z]*
# Output:
# /usr/bin/ModemManager
# /usr/bin/NetworkManager
```

`[A-Z]*` means: filenames starting with an uppercase letter (`[A-Z]`) followed by anything (`*`).

### POSIX Character Classes in Globbing

The same `[:class:]` syntax works in shell globbing:

```bash
ls /usr/sbin/[[:upper:]]*
# Output:
# /usr/sbin/MAKEFLOPPIES
# /usr/sbin/NetworkManagerDispatcher
```

```bash
ls /usr/bin/[[:digit:]]*        → files starting with a digit
ls /etc/[[:lower:]][[:lower:]]* → files starting with two lowercase letters
```

> **Key point**: Shell globbing expands filenames on the command line. `grep` uses regex. They look similar but serve different purposes.

### Globbing also works with grep's filename argument

```bash
grep error /var/log/[a-z]*.log
# Searches for "error" in log files starting with a lowercase letter
```

---

## BRE vs ERE (Basic vs Extended Regular Expressions)

There are **two kinds** of regex implementations. The difference is only a matter of **metacharacters**.

### BRE (Basic Regular Expression)

This is what plain `grep` uses. The recognized metacharacters are:

```
^ $ . [ ] * \
```

All other special characters (`( ) { } ? + |`) are treated as **literal** in BRE.

To use them as metacharacters in BRE, you must **escape them with a backslash**:

| BRE escaped | Meaning |
|-------------|---------|
| `\(...\)` | Grouping |
| `\{n,m\}` | Repetition (n to m times) |
| `\?` | Zero or one (optional) |
| `\+` | One or more |
| `\|` | Alternation (OR) |

```bash
# BRE examples (no -E flag)
grep 'foo\|bar' file            → foo OR bar
grep 'colou\?r' file            → color or colour
grep 'a\{3,5\}' file            → aaa, aaaa, aaaaa
grep '\(foo\|bar\)baz' file     → foobaz or barbaz
```

### ERE (Extended Regular Expression)

Use with `grep -E` (or `egrep`). The following metacharacters are added **without** needing backslashes:

```
( ) { } ? + |
```

| Meta | Meaning |
|------|---------|
| `( )` | Grouping |
| `{n,m}` | Quantifier (n to m) |
| `?` | Zero or one (optional) |
| `+` | One or more |
| `\|` | Alternation (OR) |

```bash
# ERE examples (with -E flag)
grep -E 'foo|bar' file           → foo OR bar
grep -E 'colou?r' file           → color or colour
grep -E 'a{3,5}' file            → aaa, aaaa, aaaaa
grep -E '(foo|bar)baz' file      → foobaz or barbaz
```

### BRE vs ERE Quick Reference

| Feature | BRE | ERE (`grep -E`) |
|---------|-----|-----------------|
| Grouping | `\( ... \)` | `( ... )` |
| OR | `\|` | `|` |
| 0 or 1 | `\?` | `?` |
| 1 or more | `\+` | `+` |
| Range quantifier | `\{n,m\}` | `{n,m}` |
| Literal `(` | `(` | `\(` |

---

## Alternation (`|`)

Matches **either** the expression on the left **or** the right.

```bash
grep -E 'error|warning|critical' app.log
# Matches lines containing error, warning, or critical

grep -E 'GET|POST|PUT|DELETE' access.log
# Matches any of these HTTP methods

grep -E '\.jpg$|\.png$|\.gif$' filelist.txt
# Lines ending with .jpg, .png, or .gif
```

Parentheses scope the alternation:

```bash
grep -E '(foo|bar)baz' file    → foobaz or barbaz
grep -E 'foo(bar|baz)' file    → foobar or foobaz
```

```bash
grep -E '^(error|warn)' file   → lines starting with "error" or "warn"
grep -E '(start|end)$' file    → lines ending with "start" or "end"
```

---

## Quantifiers — `?`, `*`, `+`, `{}`

Quantifiers control how many times the preceding character or group is allowed to repeat.

| Quantifier | Meaning | BRE | ERE |
|------------|---------|-----|-----|
| `*` | Zero or more | `*` | `*` |
| `?` | Zero or one (optional) | `\?` | `?` |
| `+` | One or more | `\+` | `+` |
| `{n}` | Exactly n times | `\{n\}` | `{n}` |
| `{n,}` | n or more times | `\{n,\}` | `{n,}` |
| `{n,m}` | Between n and m times | `\{n,m\}` | `{n,m}` |

### `*` — Zero or More

```bash
grep 'ab*c' file      → ac, abc, abbc, abbbc
grep '.*' file        → matches everything
grep 'go*gle' file    → ggle, gogle, google, gooogle
```

### `?` — Zero or One (Optional)

```bash
grep -E 'colou?r' file        → color or colour
grep -E 'https?' file         → http or https
grep -E '\.html?' file        → .htm or .html
grep -E 'files?' file         → file or files
grep -E '^(Mr|Ms|Mrs)\.' file → Mr., Ms., or Mrs.
```

### `+` — One or More

```bash
grep -E 'ab+c' file      → abc, abbc, abbbc (NOT ac)
grep -E '[0-9]+' file    → one or more consecutive digits
grep -E ' +' file        → one or more spaces
grep -E 'go+gle' file    → gogle, google, gooogle (NOT ggle)
```

### `{}` — Exact / Range Repetition

```bash
grep -E 'a{3}' file      → exactly aaa
grep -E '[0-9]{4}' file  → exactly four digits (e.g. years like 2024)
grep -E 'a{2,}' file     → two or more a's: aa, aaa, aaaa...
grep -E 'a{2,4}' file    → between 2 and 4: aa, aaa, aaaa
grep -E '.{8,}' file     → lines with 8+ characters
grep -E '^.{8,16}$' file → lines between 8 and 16 characters
```

---

## Common grep Patterns Recap

| Pattern | What it matches |
|---------|-----------------|
| `^$` | Empty lines |
| `^[^#]` | Lines NOT starting with `#` (non-comments) |
| `\.html$` | Lines ending with `.html` |
| `[[:space:]]$` | Lines with trailing whitespace |
| `\bword\b` | Whole word "word" (word boundary) |
| `^.{8}$` | Lines exactly 8 characters long |
| `^[A-Z]` | Lines starting with uppercase letter |

---

## `locate` — Find Files by Name (with Regex)

`locate` searches a pre-built file index (much faster than `find`). The database is usually updated daily by `updatedb`.

### Basic Usage

```bash
locate grep.md                  → find any file named grep.md
locate -i grep.md               → case-insensitive
locate -c grep.md               → count matches
locate -l 5 grep.md             → limit to 5 results
locate -e grep.md               → only existing files (db may be stale)
```

### Regex Search

| Option | Regex type | Example |
|--------|-----------|---------|
| `--regexp` | BRE (basic) | `locate --regexp 'grep\.md$'` |
| `--regex` | ERE (extended) | `locate --regex 'grep\.md$'` |

> Memory aid: `--regexp` has a **p** in its name, so it uses basic (BRE) like plain `grep` without `-E`.
> `--regex` (without the p) uses extended (ERE) like `grep -E`.

### Examples

```bash
# BRE (--regexp) — escaped metacharacters
locate --regexp '\.md$'                       → files ending with .md
locate --regexp 'bin/\(ls\|cp\|mv\)$'         → ls, cp, or mv in /bin
locate --regexp '/var/log/[a-z]\{3,\}\.log$'  → log files with 3+ char names

# ERE (--regex) — no escaping needed
locate --regex '\.(jpg|png|gif)$'             → image files
locate --regex 'bin/(ls|cp|mv)$'              → same: ls, cp, or mv in /bin
locate --regex '^/usr/bin/[A-Z].+'            → /usr/bin files starting with uppercase
locate --regex 'backup-[0-9]{4}-[0-9]{2}'     → backup-YYYY-MM pattern
locate --regex '^/etc/[^/]+\.conf$'           → .conf files directly in /etc
```

---

## Practice Questions

1. **Match all lines containing "error" (case-insensitive) in `app.log`.**
   <details><summary>Answer</summary>

   ```bash
   grep -i 'error' app.log
   ```
   </details>

2. **Count the number of blank lines in a file.**
   <details><summary>Answer</summary>

   ```bash
   grep -c '^$' file
   ```
   </details>

3. **Find all lines starting with a digit in `data.txt`.**
   <details><summary>Answer</summary>

   ```bash
   grep '^[0-9]' data.txt
   # or
   grep '^[[:digit:]]' data.txt
   ```
   </details>

4. **List filenames containing "TODO" recursively (case-insensitive), show only filenames.**
   <details><summary>Answer</summary>

   ```bash
   grep -ril 'TODO' .
   ```
   </details>

5. **Match lines that are exactly 10 characters long.**
   <details><summary>Answer</summary>

   ```bash
   grep '^..........$' file
   # or
   grep -E '^.{10}$' file
   ```
   </details>

6. **Find lines that contain either "GET" or "POST" in `access.log`.**
   <details><summary>Answer</summary>

   ```bash
   grep -E 'GET|POST' access.log
   ```
   </details>

7. **Match all lines NOT starting with a `#` (non-comment lines) in a config file, excluding blank lines.**
   <details><summary>Answer</summary>

   ```bash
   grep -E '^[^#]' nginx.conf | grep -v '^$'
   # or
   grep '^[^#]' nginx.conf | grep '.'
   ```
   </details>

8. **Find lines containing IP addresses (simple: exactly 4 octets).**
   <details><summary>Answer</summary>

   ```bash
   grep -E '[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}' file
   ```
   </details>

9. **Match words that start with "un" (whole words only).**
   <details><summary>Answer</summary>

   ```bash
   grep -w 'un[a-z]*' file
   # or
   grep -E '\bun[a-z]*' file
   ```
   </details>

10. **Find all `.conf` files in `/etc` whose names are exactly 5 characters long.**
    <details><summary>Answer</summary>

    ```bash
    locate --regex '^/etc/[^/]{5}\.conf$'
    # glob version:
    ls -d /etc/?????.conf
    ```
    </details>

11. **Search for "password" in all `.env` files recursively, showing 3 lines of context.**
    <details><summary>Answer</summary>

    ```bash
    grep -rni -C 3 'password' --include='*.env' .
    ```
    </details>

12. **Build a regex to match a valid email address (basic).**
    <details><summary>Answer</summary>

    ```bash
    grep -E '[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}' file
    ```
    </details>

13. **Find lines where a digit repeats 3 or more times consecutively.**
    <details><summary>Answer</summary>

    ```bash
    grep -E '[0-9]{3,}' file
    ```
    </details>

14. **Match lines ending with either `.jpg` or `.png` (case-insensitive).**
    <details><summary>Answer</summary>

    ```bash
    grep -iE '\.(jpg|png)$' file
    ```
    </details>

15. **Use `locate` to find all log files modified in January (filenames like `*-2026-01-*.log`).**
    <details><summary>Answer</summary>

    ```bash
    locate --regex '2026-01-[0-9]{2}\.log$'
    ```
    </details>

---
