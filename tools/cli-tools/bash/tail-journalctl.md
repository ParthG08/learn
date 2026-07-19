# tail & journalctl — Live Log Reading

---

## `tail` — View the End of a File

### Syntax

```
tail [options] file
```

### Common Options

| Option | Effect |
|--------|--------|
| `-n N` | Print last N lines (default: 10) |
| `-f` | Follow — keep file open, print new lines as appended (kill with `Ctrl+C`) |
| `-F` | Follow with retry — same as `-f` but reopens file if it's rotated/deleted |
| `-n +N` | Print starting from line N (not last N) |

### Patterns

```bash
tail -n 50 /var/log/syslog        → last 50 lines
tail -f /var/log/nginx/access.log → live stream new requests
tail -f /var/log/app.log          → watch app output in real time
tail -f *.log                     → follow multiple files at once
tail -n +100 file.log | head -20  → lines 100-120
```

### Real-Life Use Cases

- **Debugging prod**: `tail -f /var/log/app.log` while reproducing a bug to see errors as they happen
- **Watching deployments**: `tail -f deployment.log` during a deploy to catch failures live
- **Monitoring access logs**: `tail -f access.log | grep ' 500 '` — stream live and filter for 500 errors
- **Quick check before grep**: `tail -n 100 app.log | grep ERROR` — search recent context only
- **Multi-file watch**: `tail -f /var/log/{app,db,nginx}/*.log` to correlate events across services

---

## `journalctl` — systemd Journal Viewer

### What is systemd?

**systemd** is the init system and service manager on virtually all modern Linux distros (Ubuntu 15.04+, Debian 8+, CentOS 7+, RHEL 7+, Fedora, Arch). It is PID 1 — the first process the kernel starts. Its jobs:

- **Boots the system**: starts services in the right order with parallelization and dependency resolution
- **Manages services**: starts, stops, restarts, and monitors daemons (nginx, sshd, docker, your app, etc.)
- **Collects logs**: every process it manages has its stdout/stderr captured by systemd's journal — the unified logging system called `journald`

Before systemd, Linux used SysV init or Upstart. Each service managed its own log files (usually under `/var/log/`), and there was no unified way to query logs across services or time ranges. systemd + journald solved that fragmentation.

### Why `journalctl` instead of just `tail -f /var/log/...`?

When systemd launches a service, the process's stdout and stderr are attached to the journal, **not** a traditional log file. There are three cases:

| Scenario | How logs are captured | Tool |
|----------|----------------------|------|
| **Process launched manually** (`./myapp`) | Output goes to your terminal | Just read the terminal |
| **Service that writes its own log file** (nginx, custom app with file logging) | Writes to `/var/log/nginx/access.log`, etc. | `tail -f /var/log/...` |
| **systemd-managed service writing to stdout/stderr** | Captured by journald | `journalctl -u <service>` |

Many modern apps (especially containerized/cloud-native ones following the [12-factor app](https://12factor.net/logs) methodology) log **only** to stdout/stderr and let the platform handle log routing. For these, `tail` on a file doesn't work — there is no file. You **must** use `journalctl`.

Even when log files exist, `journalctl` gives you superpowers that `tail` alone can't:

1. **Time-based queries** — `--since "10 min ago"` without calculating line offsets
2. **Cross-service correlation** — `journalctl -u nginx -u myapp` interleaves logs from both services in chronological order
3. **Post-crash forensics** — `-b -1` reads logs from the previous boot, even if the filesystem was corrupted
4. **Priority filtering** — `-p err` skips the noise, only errors
5. **Structured output** — `-o json-pretty` for scripting/automation

> **TL;DR**: If it's a systemd service, reach for `journalctl` first. It works regardless of whether the app writes to files or stdout, and the filtering capabilities save enormous time during incidents.

### Syntax

```
journalctl [options] [matches]
```

### Common Options

| Option | Effect |
|--------|--------|
| `-u <unit>` | Filter by systemd service (e.g., `-u nginx.service`) |
| `-f` | Follow — live tail like `tail -f` but for journal |
| `-n N` | Show last N lines |
| `-b` | Messages from current boot only |
| `-b -1` | Messages from previous boot (useful after a crash) |
| `--since "..."` | Time-based filter (e.g., `--since "10 min ago"`, `--since "2026-07-19 14:00"`) |
| `--until "..."` | Upper time bound |
| `-p` | Filter by priority: `emerg`, `alert`, `crit`, `err`, `warning`, `notice`, `info`, `debug` |
| `-k` | Kernel messages only (dmesg) |
| `-r` | Reverse order (newest first) |
| `--no-pager` | Don't pipe through `less` |
| `-o json-pretty` | JSON output (good for scripting/programmatic parsing) |

### Patterns

```bash
journalctl -u nginx.service                        → all logs for nginx
journalctl -u nginx.service -f                     → live stream nginx logs
journalctl -u nginx.service --since "2026-07-19"   → today's nginx logs
journalctl -u app.service -n 100 --no-pager        → last 100 entries, no pager
journalctl -u app.service -p err                   → only errors and above
journalctl -b -u docker.service -p err             → docker errors since last boot
journalctl --since "1 hour ago" -u sshd.service    → ssh connections in last hour
```

### Real-Life Use Cases

- **Service crashed?** → `journalctl -u myapp.service -b -1 -n 50` — see what the app logged right before it died during the previous boot
- **Is a service even running?** → `journalctl -u myapp.service --since "1 min ago" -f` — watch for activity
- **SSH break-in check** → `journalctl -u sshd.service --since "1 hour ago" | grep Failed` — spot brute-force attempts
- **Debugging a failed deploy** → `journalctl -u myapp.service -p err --since "10 min ago"` — only errors from the last 10 minutes
- **Post-mortem after server crash** → `journalctl -b -1 -p err` — all errors from the previous boot (why it died)
- **Cron jobs** → `journalctl -u cron.service --since today` — did that backup job actually run?
- **Disk I/O issues** → `journalctl -k -p err` — kernel-level errors that don't appear in app logs

---

## `tail` vs `journalctl` — When to Use Which

| Situation | Use |
|-----------|-----|
| Plain log file on disk, no systemd | `tail -f` |
| systemd-managed service | `journalctl -u <service> -f` |
| Post-crash analysis (previous boot) | `journalctl -b -1` |
| Quick peek at end of any file | `tail -n 50` |
| Time-range queries, rich filtering | `journalctl --since/--until -p` |
