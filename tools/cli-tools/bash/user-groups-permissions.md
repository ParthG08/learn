# User & Group Management, sudo, setuid/setgid

## User-Specific Files & System Directories

### Home Directories (`/home/`)

Each user gets their own home directory (`/home/<username>/`). User-specific config files live here:

- `~/.bashrc` — bash shell config (aliases, env vars, prompt)
- `~/.profile` / `~/.bash_profile` — login shell config
- `~/.config/` — modern XDG-compliant app configs
- `~/.ssh/` — SSH keys and config

**Why this matters for shared privileges:** even if two users share the same group, their `.bashrc`, `profile`, and personal configs are isolated by home directory. One user cannot accidentally (or intentionally) modify another user's dotfiles unless they have `root` or specific `sudo` access.

### System-Wide Settings (`/etc/`)

System-wide config files live in `/etc/` and apply to all users:

- `/etc/passwd` — user accounts list
- `/etc/shadow` — encrypted passwords (root-only readable)
- `/etc/group` — group definitions
- `/etc/sudoers` — sudo permissions (edit with `visudo`, never manually)
- `/etc/ssh/sshd_config` — SSH server config
- `/etc/hostname`, `/etc/hosts` — network naming
- `/etc/systemd/` — systemd service definitions

### User Runtime & Cache Data

- `/run/user/<uid>/` — per-user runtime files (pulseaudio, gnome-keyring, etc.) — cleared on reboot
- `/var/` — variable data: logs (`/var/log/`), caches (`/var/cache/`), spools (`/var/spool/`)
- `/tmp/` — temporary files, world-writable with sticky bit (users can only delete their own files)

---

## User Groups

### Creating & Managing Groups

```bash
# Create a group
sudo groupadd devs

# Create a group with a specific GID
sudo groupadd -g 2000 devs

# Delete a group
sudo groupdel devs

# List all groups on the system
getent group
# or
cat /etc/group
```

### Adding Users to Groups

```bash
# Add user to a supplementary group
sudo usermod -aG devs parth

# Remove user from a group (no usermod flag — edit /etc/group manually or use gpasswd)
sudo gpasswd -d parth devs

# Set primary group for a user
sudo usermod -g devs parth
```

**`-aG` vs `-G`:** always use `-aG` (append) unless you intend to remove the user from all other groups. `-G` alone **replaces** all supplementary groups.

### Listing Group Membership

```bash
# Check which groups a user belongs to
groups parth

# See user's uid, gid, and groups from /etc/passwd and /etc/group
id parth
```

### Common Group Patterns

- `sudo` / `wheel` — users who can run `sudo`
- `docker` — users who can run Docker commands (equivalent to root access — be careful)
- `www-data` — web server group
- `devs` — project-specific group for shared file access

**Why groups matter:** instead of giving everyone sudo, create a `devs` group, set shared directory ownership to `devs`, and grant group-write access. This gives collaborative access without elevating privileges.

---

## sudo — Running Commands as Another User

### Basic Usage

```bash
# Run command as root
sudo apt update

# Run command as a specific user
sudo -u parth whoami

# Open a shell as another user
sudo -u postgres -s

# Run with root's environment
sudo -i
```

### Key Flags

| Flag | Meaning |
|------|---------|
| `-u <user>` | Run as specified user (default: root) |
| `-s` | Open a shell (`$SHELL`) as the target user |
| `-i` | Login shell (loads target user's `.profile`, env) |
| `-E` | Preserve current environment variables |
| `-l` | List allowed commands for current user |

### sudoers Configuration (`/etc/sudoers`)

Always edit with `visudo` — it validates syntax and prevents lockouts:

```bash
sudo visudo
```

Common patterns:

```
# User can run any command as any user
parth   ALL=(ALL:ALL) ALL

# User can only run specific commands as root
parth   ALL=(root) /usr/bin/systemctl, /usr/bin/journalctl

# Group sudo access (members of `devs` can run any command)
%devs   ALL=(ALL:ALL) ALL

# No password required
parth   ALL=(ALL) NOPASSWD: ALL
```

### sudo vs su

| Command | Effect |
|---------|--------|
| `sudo command` | Run one command as root (logged, auditable) |
| `sudo -u user command` | Run one command as another user |
| `su - parth` | Switch to `parth`'s login shell (need parth's password) |
| `sudo su -` | Switch to root shell via sudo (your password, not root's) |

**Prefer `sudo` over `su`** — it's auditable, granular, and doesn't require sharing passwords.

---

## setuid, setgid & Sticky Bit

### setuid (SUID — `u+s`)

When set on an **executable file**, the process runs with the **file owner's privileges**, not the user who executed it.

```bash
# Give any user the ability to check their own password
-rwsr-xr-x  1 root root  68216  /usr/bin/passwd
```

Without SUID, `/usr/bin/passwd` would need everyone to be root to update `/etc/shadow`. With SUID, it temporarily runs as `root` just for that operation.

**Use cases:**
- `passwd` — users need to change their own password (writing to `/etc/shadow`)
- `ping` — needs raw socket access
- `su` — needs to switch user identity

**Security risk:** a SUID root binary with a vulnerability = privilege escalation. Minimize SUID binaries on the system.

```bash
# Set SUID
chmod u+s binary

# Find all SUID binaries on the system
find / -perm -4000 -type f
```

### setgid (SGID — `g+s`)

Two behaviors depending on target:

**On an executable file:** runs with the **group** of the file, not the user's group.

```bash
-rwxr-sr-x  1 root mlocate  42456  /usr/bin/locate
```

**On a directory:** new files created inside inherit the **directory's group**, not the creator's group. This is the most common practical use.

```bash
# Shared project directory — all teammates create files under 'devs' group
sudo chgrp devs /shared/project/
sudo chmod g+s /shared/project/

# Now any file created in /shared/project/ belongs to group 'devs'
touch /shared/project/test.txt
ls -al /shared/project/test.txt
# -rw-r--r-- 1 parth devs 0 Jul 15 10:00 test.txt
```

**Why this matters for teams:** without SGID on a shared directory, user A creates a file with group `A`, and user B can't write to it even if they share the same group folder. SGID ensures all new files automatically get the right group.

```bash
# Set SGID on directory
chmod g+s /shared/project/

# Unset SGID
chmod g-s /shared/project/
```

### Sticky Bit (`+t`)

On a **directory**, only the **file owner** (or root) can delete or rename files inside — even if the directory is world-writable.

```bash
drwxrwxrwt  10 root root  4096  /tmp
```

Without the sticky bit on `/tmp` (world-writable), any user could delete any other user's temp files.

```bash
# Set sticky bit
chmod +t /shared/

# List directories with sticky bit (t in world-execute position)
ls -ld /tmp
```

### Quick Reference

| Bit | Symbol | File Effect | Directory Effect |
|-----|--------|-------------|------------------|
| SUID | `s` in owner-x | Runs as file owner | (none) |
| SGID | `s` in group-x | Runs as file group | New files inherit directory's group |
| Sticky | `t` in world-x | (none) | Only owner can delete their files |
