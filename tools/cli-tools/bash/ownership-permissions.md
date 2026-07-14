# Linux File Ownership & Permissions (`ls -al`)

## The `ls -al` Output

```
-rw-r--r--  1 parth dev  1024 Jul 13 10:00 file.txt
drwxr-x---  2 root root  4096 Jul 13 09:00 secret/
```

## Permission String Breakdown

String: `-rw-r--r--`

| Position | Meaning |
|---|---|
| `-` | File type (`-`=file, `d`=directory, `l`=symlink) |
| `rw-` | **Owner** permissions (read + write) |
| `r--` | **Group** permissions (read only) |
| `r--` | **World/Others** permissions (read only) |

Sequence is always: **Owner → Group → World (Others)**

## Permission Characters

| Char | File | Directory |
|---|---|---|
| `r` | Read content | List entries |
| `w` | Modify content | Create/delete files inside |
| `x` | Execute as program | Enter (`cd` into it) |
| `-` | No permission | No permission |

### Detailed: `r` (Read)

| Entity | Effect | Common Error |
|---|---|---|
| **File** | View file contents (`cat`, `less`, `head`, `tail`, `vim` to open) | `Permission denied` on open |
| **Directory** | List directory contents (`ls` without `-l` works, but **without `x` you can't `cd` in** and can't see metadata like inode numbers) | `ls: .: Permission denied` |

Without `r` on a file, you cannot read it even if you own it. Without `r` on a directory, `ls` fails — but `ls -l` also needs `x` to stat each entry's metadata.

### Detailed: `w` (Write)

| Entity | Effect | Common Error |
|---|---|---|
| **File** | Modify/truncate file content (`vim`, `echo >`, `>>`, `sed -i`). Does **not** let you delete the file itself (that's directory permission). | `Permission denied` on write |
| **Directory** | Create, rename, or delete **any file inside** the directory (regardless of who owns the file!). This is why `/tmp` has the **sticky bit** (`chmod +t`). | ` touch: cannot touch 'file': Permission denied` |

**Key nuance:** `w` on a directory is extremely powerful — you can delete files you don't own inside it. The sticky bit (`t` on `/tmp/`) restricts this so only file owners can delete their own files.

### Detailed: `x` (Execute)

| Entity | Effect | Common Error |
|---|---|---|
| **File** | Run the file as a program/script. For scripts, the shebang (`#!/bin/bash`) must be readable too. Binary executables just need `x`. | `Permission denied` (or `command not found` if trying to run `./script`) |
| **Directory** | **Traverse** the directory — `cd` into it, access files inside by name, stat metadata (`ls -l`). Without `x`, you can't reach any files inside, even if those files have permissive permissions. | `cd: directory: Permission denied` |

**Key nuance:** `x` on a directory is often needed alongside `r`:
- `r` only → `ls` lists names but fails on metadata; `cd` fails
- `x` only → can `cd` in and access files by name, but `ls` fails (can't list)
- `r` + `x` → full browse capability (`ls -l`, `cd`, access files)

### Common Combinations for Directories

| Perms | Meaning |
|---|---|
| `---` | Locked — nobody can see or enter |
| `r--` | Can see names with `ls` but can't `cd` in or access files |
| `--x` | Can `cd` in and access files **by known name** but can't list contents |
| `r-x` | **Standard for public directories** — can list, enter, read files |
| `rwx` | Full access — can list, enter, create, delete |

## Ownership Columns

From `ls -al`:

```
-rw-r--r--  1  owner  group  size  date  name
             ^^^^^   ^^^^^
```

- **Owner** — user who owns the file (usually the creator)
- **Group** — group that owns the file (all group members get group permissions)

## Numeric (Octal) Permissions

| Octal | Binary | Perms |
|---|---|---|
| 7 | 111 | rwx |
| 6 | 110 | rw- |
| 5 | 101 | r-x |
| 4 | 100 | r-- |
| 0 | 000 | --- |

Each digit = owner/group/world. Example: `chmod 755 file` = `rwxr-xr-x`

## Common Commands

```bash
# Change owner
chown parth file.txt

# Change owner + group
chown parth:dev file.txt

# Change group only
chgrp dev file.txt

# Set permissions (symbolic)
chmod u+x script.sh     # add execute for owner
chmod g-w file.txt      # remove write for group
chmod o+r file.txt      # add read for world
chmod a+x script.sh     # add execute for all

# Set permissions (octal)
chmod 755 script.sh     # rwxr-xr-x
chmod 644 file.txt      # rw-r--r--
chmod 700 private/      # rwx------

# Directory recursive
chmod -R 755 directory/
chown -R parth:dev directory/
```

## Special Bits

| Bit | Symbol | Effect |
|---|---|---|
| SUID | `s` in owner-x (`rws`) | Run as file owner, not executor |
| SGID | `s` in group-x (`rws`) | New files inherit directory's group |
| Sticky | `t` in world-x (`rwt`) | Only owner can delete own files (`/tmp`) |

```bash
chmod u+s binary      # set SUID
chmod g+s directory/   # set SGID
chmod +t /shared/      # sticky bit
```

## Quick Reference

```
-rwxr-xr--
└└└└└└└└└
 │││││││││
 ││││││││└─ world: read
 │││││││└── world: no write
 ││││││└─── world: no execute
 │││││└──── group: read
 ││││└───── group: execute
 │││└────── group: no write
 ││└─────── owner: read
 │└──────── owner: write
 └───────── owner: execute
type: file (-)
```
