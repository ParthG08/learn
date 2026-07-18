# Process Management

## `ps` — Process Snapshot

Lists currently running processes at the moment the command runs.

### `ps` (no options)

Shows only processes associated with the current terminal session.

```
$ ps
  PID TTY          TIME CMD
 1234 pts/0    00:00:00 bash
 5678 pts/0    00:00:00 ps
```

### `ps x` — All processes owned by the user

Shows **all** processes owned by you, not just those attached to the current terminal.

```
$ ps x
  PID TTY      STAT   TIME COMMAND
 1234 pts/0    Ss     0:00 bash
 5678 ?        S      0:00 sshd
 ...
```

Output is usually large — pipe through `less`:

```
ps x | less
```

### `ps aux` — All processes (every user, BSD style)

Shows **every** process on the system, owned by any user. Combines:

- `a` — processes from all users (not just your own)
- `u` — user-oriented format (shows CPU/memory usage, etc.)
- `x` — processes without a controlling terminal (daemons)

```
$ ps aux
USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root         1  0.0  0.3 167936 13444 ?        Ss   Jul17   0:05 /sbin/init
parth     1234  0.0  0.2  23456  9876 pts/0    Ss   10:00   0:00 bash
```

### BSD-style vs UNIX/Linux-style options

- **BSD-style** (no dash before options): `ps aux`, `ps x`
- **UNIX/Linux-style** (dash before options): `ps -ef`, `ps -aux` (note: `ps aux` and `ps -aux` are **not** the same)

## Column Meanings

| Column | Meaning |
|--------|---------|
| `PID` | Process ID — unique numeric identifier for each running process |
| `TTY` | Terminal associated with the process. `?` means no terminal (daemon/background process) |
| `STAT` | Current state of the process (see below) |
| `TIME` | Total CPU time consumed by the process so far (not wall-clock time) |
| `COMMAND` | The command that started the process (may be truncated; use `ps auxww` to see full command) |

## STAT Column Values

| Code | Meaning |
|------|---------|
| `R` | **Running** or runnable (in the run queue) |
| `S` | **Sleeping** — waiting for an event to complete (interruptible sleep) |
| `D` | **Uninterruptible sleep** — waiting for I/O (usually disk), cannot be killed easily |
| `T` | **Stopped** — suspended, e.g. by `Ctrl+Z` or `SIGSTOP` |
| `Z` | **Zombie** — process terminated but not yet reaped by parent |
| `<` | High-priority (not nice to others) |
| `N` | Low-priority (nice to others) |
| `s` | Session leader (contains multiple child processes) |
| `l` | Multi-threaded (CLONE_THREAD) |
| `+` | In the foreground process group |

Multiple characters can appear together (e.g. `Ss` = sleeping + session leader, `S<` = sleeping + high priority).

## `top` — Dynamic process viewer

Refreshes the process list in real time. Shows processes sorted by CPU usage by default.

```
$ top
top - 10:15:30 up 2 days,  3:45,  2 users,  load average: 0.08, 0.03, 0.01
Tasks: 187 total,   1 running, 186 sleeping,   0 stopped,   0 zombie
%Cpu(s):  2.3 us,  1.0 sy,  0.0 ni, 96.4 id,  0.3 wa,  0.0 hi,  0.0 si,  0.0 st
MiB Mem :   7956.2 total,   2345.6 free,   3120.4 used,   2490.2 buff/cache
MiB Swap:   2048.0 total,   2048.0 free,      0.0 used.   4241.9 avail Mem

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND
 1234 parth     20   0  234568  12345   8765 S   0.3   0.2   0:01.23 bash
 5678 root      20   0  167936  13444   9876 S   0.0   0.2   0:05.67 systemd
```

### Top Columns

| Column | Meaning |
|--------|---------|
| `PID` | Process ID |
| `USER` | Owner of the process |
| `PR` | Priority — kernel scheduling priority (lower number = higher priority) |
| `NI` | Nice value — user-controllable priority adjustment (`-20` to `19`; negative = higher priority) |
| `VIRT` | Total virtual memory used (includes shared libraries, swapped pages, etc.) |
| `RES` | Resident memory — physical RAM currently used (in KiB) |
| `SHR` | Shared memory size |
| `S` | Process state (same as `STAT` in `ps`) |
| `%CPU` | Percentage of CPU used |
| `%MEM` | Percentage of physical RAM used |
| `TIME+` | Total CPU time consumed (with hundredths of a second) |
| `COMMAND` | Command name |

### Useful `top` keyboard commands

| Key | Action |
|-----|--------|
| `q` | Quit `top` |
| `h` | Help / show available commands |
| `k` | Kill a process (prompts for PID and signal) |
| `r` | Renice a process (change priority) |
| `u` | Show only processes for a specific user |
| `M` | Sort by memory usage (%MEM) |
| `P` | Sort by CPU usage (%CPU) — default |
| `1` | Toggle per-CPU/core view |
| `c` | Toggle between command name and full command line |
| `H` | Toggle thread view / process view |
| `space` | Refresh immediately |
| `R` | Reverse sort order |
| `W` | Write current configuration to `~/.toprc` |
| `x` | Highlight sort column |

## Job Control

### Starting a background process with `&`

Append `&` to a command to run it in the background, freeing the terminal.

```
$ xlogo &
[1] 12345
```

The output `[1] 12345` means:
- `[1]` — job number (in this session)
- `12345` — PID of the backgrounded process

This is part of the shell's **job control** feature — the ability to manage multiple processes from a single terminal.

### `jobs` — List background jobs

Shows the jobs that were started from the **current terminal session** (not across all sessions).

```
$ jobs
[1]+  Running                 xlogo &
```

`+` indicates the most recent job; `-` indicates the second most recent.

### `fg` — Bring a job to the foreground

```
$ fg %1
```

Brings job `[1]` to the foreground. If only one job exists, `fg` alone works.

### `bg` — Resume a stopped job in the background

If you suspended a foreground job with `Ctrl+Z`, you can resume it in the background:

```
$ sleep 100
^Z
[2]+  Stopped                 sleep 100

$ bg %2
[2]+ sleep 100 &
```

### `Ctrl+Z` — Suspend a foreground process

Sends `SIGTSTP`, pausing the process (STAT becomes `T`). The process can later be resumed with `fg` or `bg`.

### `Ctrl+C` — Terminate a foreground process

Sends `SIGINT`, interrupting and killing the process.

### Summary of job control keys

| Command | Action |
|---------|--------|
| `command &` | Start `command` in the background |
| `Ctrl+Z` | Suspend the current foreground process |
| `Ctrl+C` | Kill the current foreground process |
| `jobs` | List background jobs in the current terminal session |
| `fg %n` | Bring job `n` to the foreground |
| `bg %n` | Resume job `n` in the background |

---

## `kill` — Send signals to processes

Sends a signal to a process by PID. If no signal is specified, `SIGTERM` (15) is sent by default.

```
kill [-signal] PID
```

### Common signals

| Signal | Number | Meaning |
|--------|--------|---------|
| `HUP` | 1 | **Hangup** — Originally meant the terminal hung up (modem disconnect). Today, many daemons reload their configuration on `HUP` (e.g. `systemctl reload nginx`). |
| `INT` | 2 | **Interrupt** — Requests a process to stop. Sent by `Ctrl+C`. Most programs clean up and exit. |
| `KILL` | 9 | **Kill** — Forces immediate termination. The process cannot catch, block, or ignore this signal. The kernel terminates it directly. Last resort. |
| `TERM` | 15 | **Terminate** — Default signal. Asks the process to exit gracefully, allowing cleanup of resources. |
| `STOP` | 19 | **Stop** — Pauses the process (like `Ctrl+Z`). Cannot be caught or ignored. |
| `CONT` | 18 | **Continue** — Resumes a stopped process. |

### Examples

```
kill 1234                  # send SIGTERM (default)
kill -TERM 1234            # same as above
kill -9 1234               # send SIGKILL (force kill)
kill -HUP 1234             # send SIGHUP (often reloads config)
kill -INT 1234             # send SIGINT (like Ctrl+C)
kill -l                    # list all available signals
```

---

## `killall` — Kill processes by name

Kills all processes matching a given command name.

```
killall [-signal] name
```

### Examples

```
killall firefox            # send SIGTERM to all firefox processes
killall -9 chrome          # force kill all chrome processes
killall -HUP nginx         # reload nginx config
killall -u parth firefox   # only kill firefox processes owned by user parth
killall -I firefox         # case-insensitive match
```

Useful when you don't know the PID or when multiple instances are running.

---

## Shutdown, Reboot, and System Control

### `shutdown` — Power off or reboot the system

Requires root privileges.

```
shutdown -h +5 "System will shut down in 5 minutes"    # halt in 5 min with message
shutdown -h now                                          # halt immediately
shutdown -r +5                                           # reboot in 5 min
shutdown -r now                                          # reboot immediately
shutdown -c                                              # cancel a pending shutdown
```

| Option | Meaning |
|--------|---------|
| `-h` | Halt (power off) |
| `-r` | Reboot |
| `-c` | Cancel pending shutdown |

### `reboot` — Reboot the system

```
reboot                     # reboot immediately
```

### `poweroff` — Power off the system

```
poweroff                   # power off immediately
```

### `halt` — Halt the system

```
halt                       # halt the system (may not power off)
halt -p                    # halt and power off (like poweroff)
```

### `systemctl` — Modern system control (systemd systems)

```
systemctl reboot           # reboot
systemctl poweroff         # power off
systemctl halt             # halt
systemctl suspend          # suspend to RAM (sleep)
systemctl hibernate        # hibernate to disk
systemctl hybrid-sleep     # suspend + hibernate
```

---

## Process Monitoring Commands

### `pstree` — Processes as a tree

Displays running processes in a tree structure, showing parent-child relationships.

```
$ pstree
systemd─┬─ModemManager───2*[{ModemManager}]
        ├─NetworkManager───2*[{NetworkManager}]
        ├─sshd───sshd───bash───pstree
```

```
pstree -p                  # show PIDs alongside process names
pstree -u                  # show uid transitions
pstree 1234                # show only the subtree of PID 1234
```

### `vmstat` — Virtual memory stats

Reports system memory, processes, paging, block I/O, traps, and CPU activity.

```
# snapshot every 2 seconds, 5 times
$ vmstat 2 5
procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd   free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0      0 234567 12345 678901    0    0    12    34  567  890  2  1 97  0  0
```

Key columns:
- `r` — number of processes waiting for CPU (run queue)
- `b` — number of processes in uninterruptible sleep
- `swpd` — amount of swap used
- `free` — free memory
- `si`/`so` — swap in/out (non-zero means memory pressure)
- `us`/`sy`/`id`/`wa` — user CPU / system CPU / idle / I/O wait

### `xload` — Graphical load average

A simple X11 tool that pops up a window showing a graph of system load average over time. Useful when you want a quick visual at a glance.

```
xload                      # open graphical load graph
xload -display :0          # specify display
```

### `tload` — Terminal load average graph

Similar to `xload` but draws a text-based load graph in the terminal.

```
tload                      # show load graph in terminal
tload -s 2                 # update every 2 seconds
tload -d 3                 # scale with a delay of 3
```
