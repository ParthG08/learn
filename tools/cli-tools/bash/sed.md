# sed — Stream Editor

## Syntax

```
sed [options] 'command' file
```

## Core Commands

| Command | Meaning |
|---------|---------|
| `s/pattern/replacement/` | Substitute first match per line |
| `s/pattern/replacement/g` | Substitute all matches per line (global) |
| `/pattern/d` | Delete matching lines |
| `/pattern/p` | Print matching lines |
| `5,10p` | Print lines 5 through 10 |

## Common Options

| Option | Effect |
|--------|--------|
| `-i` | Edit file in-place (use `-i.bak` for backup) |
| `-n` | Suppress automatic printing (use with `/p`) |
| `-E` | Extended regex (like `grep -E`) |
| `-e` | Multiple commands |

## Common Patterns

```bash
sed -i 's/foo/bar/g' file.txt              → replace all foo with bar in-place
sed 's/[[:space:]]*$//' file.txt            → strip trailing whitespace
sed -i '/^$/d' file.txt                     → delete blank lines in-place
sed -n '10,20p' file.txt                    → print lines 10-20 only
sed 's/^#//' config.conf                    → uncomment lines (remove leading #)
sed -i.bak 's/localhost:3306/prod-db:3306/' → replace host, keep backup
```

## Real-Life Use Cases

- **Config file updates**: change DB hosts, ports, or env vars across config files before deployment
- **Log cleanup**: strip timestamps, redact PII (e.g., mask emails with `sed -E 's/[a-zA-Z0-9._%+-]+@/REDACTED@/g'`), extract specific fields
- **CI/CD scripting**: modify YAML/JSON values in pipeline scripts
- **Data munging**: strip whitespace, remove comment lines, normalize line endings
- **Bulk refactoring**: rename variables/constants across many files
