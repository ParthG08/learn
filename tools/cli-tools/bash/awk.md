# awk — Pattern Scanning & Processing Language

## Syntax

```
awk 'pattern { action }' file
```

If no pattern, action runs on every line. If no action, matching lines are printed.

## Core Concepts

- awk splits each line into fields (columns) by whitespace by default
- `$0` = whole line, `$1` = first field, `$2` = second field, `$NF` = last field
- `NR` = current line number, `NF` = number of fields

## Common Patterns

```bash
awk '{print $1}' access.log              → print first column
awk '{print $1, $NF}' access.log         → print first and last columns
awk -F',' '{print $2}' data.csv          → comma delimiter (CSV)
awk '/ERROR/' app.log                    → print lines containing ERROR
awk '$3 > 500' metrics.log               → print lines where 3rd field > 500
awk '{sum+=$2} END {print sum}' data     → sum of second column
awk '{count[$1]++} END {for (k in count) print k, count[k]}' log → group-by count
```

## Built-in Variables

| Variable | Meaning |
|----------|---------|
| `$0` | Entire line |
| `$1, $2, ...` | Fields |
| `NF` | Number of fields |
| `NR` | Record (line) number |
| `FS` | Input field separator (default: whitespace) |
| `OFS` | Output field separator |

## Options

| Option | Effect |
|--------|--------|
| `-F:` | Set field separator (e.g., `:` for `/etc/passwd`) |
| `-v var=value` | Define variable (e.g., `-v threshold=500`) |

## Real-Life Use Cases

- **Log analysis**: extract response times, count HTTP status codes by group (`awk '{print $9}' access.log | sort | uniq -c`), find slowest requests
- **CSV/TSV processing**: sum columns, filter rows by value, compute averages
- **Ad-hoc reporting**: summarize data from command output without needing Python or a DB
- **Parsing structured text**: `/etc/passwd`, `ps aux`, `df -h`, `netstat` output
- **Server metrics**: aggregate CPU/memory usage across processes, calculate totals from `ps aux`
