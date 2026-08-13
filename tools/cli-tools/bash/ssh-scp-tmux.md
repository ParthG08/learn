# SSH, SCP/SFTP/rsync, tmux

> SSH is the single most-used tool for an FDE. Every server, every jump host, every on-prem box, every customer environment — you get there through SSH. This note focuses on the practical, daily-workshop usage: keys, config files, agent, tunnels, jump hosts, and the standard debugging flow.

---

## 1. How SSH Works (the 30-second version)

- **SSH = Secure Shell.** A protocol that authenticates a client to a server and gives you an encrypted shell.
- Runs on **port 22** by default.
- **Encryption (transport layer):** the whole session is encrypted end-to-end using key exchange (usually Curve25519 / ECDH).
- **Authentication:** two methods —
  1. **Password** (default, weakest, should be a last resort)
  2. **Public-key** (the standard for anything real)

### Key exchange basics

- `ssh-keygen` creates a **key pair**: a private key (secret, stays on YOUR machine) and a public key (safe to share).
- You place your **public key** in `~/.ssh/authorized_keys` on the server.
- The server proves you own the private key via a cryptographic challenge — your private key **never** leaves your machine.

---

## 2. First Connection

```bash
ssh user@server.example.com
ssh user@server.example.com -p 2222      # non-default port
ssh server.example.com                   # uses your current username
```

**First time you connect**, SSH asks to trust the server's host key fingerprint:

```
The authenticity of host 'server (10.0.0.5)' can't be established.
ECDSA key fingerprint is SHA256:...
Are you sure you want to continue connecting (yes/no)?
```

- Type `yes` → the fingerprint is stored in `~/.ssh/known_hosts`.
- **On every later connection** SSH verifies the server's key against `known_hosts`. If it changed, you get a warning (the server was reinstalled, or you're being MITM'd).

### `known_hosts` — remember trusted servers

```bash
cat ~/.ssh/known_hosts
ssh-keygen -R hostname     # remove a stale entry (e.g. after a reinstall)
```

If the server was rebuilt, the old key is invalid → use `ssh-keygen -R` to clear it and reconnect.

---

## 3. Passwordless Login — SSH Keys (the most important habit)

### Generate a key

```bash
ssh-keygen -t ed25519 -C "parth@laptop"
```

- `-t ed25519` — modern, fast, secure key type (prefer over RSA).
- `-C` — a comment (usually `user@host`), helps identify keys later.
- Creates `~/.ssh/id_ed25519` (**private**) and `~/.ssh/id_ed25519.pub` (**public**).
- Optional passphrase on the private key — if set, use `ssh-agent` (below) so you only type it once.

### Copy the public key to a server

```bash
ssh-copy-id user@server.example.com     # appends your key to server's authorized_keys
```

If `ssh-copy-id` isn't available (macOS older / some minimal systems), do it manually:

```bash
cat ~/.ssh/id_ed25519.pub | ssh user@server "mkdir -p ~/.ssh && chmod 700 ~/.ssh && cat >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys"
```

### Permission rules that MUST hold (or SSH refuses keys)

| File | Permissions |
|------|-------------|
| `~/.ssh` on client & server | `700` (drwx------) |
| `~/.ssh/authorized_keys` on server | `600` |
| private key `~/.ssh/id_ed25519` | `600` |
| `~/.ssh/config` | `600` or `644` |

SSH is strict: too-open permissions → "Permissions too open" error / key silently ignored.

```bash
chmod 700 ~/.ssh
chmod 600 ~/.ssh/id_ed25519
```

---

## 4. `~/.ssh/config` — the file that makes SSH fast to use

Instead of typing long command lines, define hosts once:

```bash
# ~/.ssh/config
Host prod-web1
    HostName 10.0.1.20
    User deploy
    Port 22
    IdentityFile ~/.ssh/id_ed25519

Host db-*                          # wildcards work
    HostName %h.internal.corp.com  # %h = the literal host you typed
    User root
    ProxyJump jump.example.com     # route through a jump host

Host *
    ServerAliveInterval 60         # keep-alive ping every 60s (keeps connections alive)
    ServerAliveCountMax 2
    ControlMaster auto
    ControlPath ~/.ssh/ctrl-%r@%h:%p
    ControlPersist 10m
```

Now:

```bash
ssh prod-web1         # resolves the whole lot
```

**Why an FDE should always use a config file:**
- No more remembering usernames, ports, and IPs per environment.
- `ProxyJump` per host makes bastion/jump-host networks trivial.
- Keep-alive options save you from mysteriously dropped sessions during long deploys.

---

## 5. `ssh-agent` — don't type your passphrase a hundred times

```bash
eval "$(ssh-agent -s)"       # start the agent (usually auto-starts on desktop Linux/macOS)
ssh-add ~/.ssh/id_ed25519     # load your key (type passphrase once)
ssh-add -l                    # list loaded keys
ssh-agent -k                  # stop the agent
```

Agent also matters for **agent forwarding**:

```bash
ssh -A user@server            # forward agent (your keys) through the server
```

Use `-A` when you SSH from server A to server B and don't want to copy your key onto A. **Security:** only use `-A` on trusted hosts — a compromised server can use your agent to impersonate you.

---

## 6. Running commands remotely (no shell)

SSH's most powerful habit: execute a command and get the output back.

```bash
ssh prod-web1 "uptime && free -h"
ssh prod-web1 "systemctl status nginx --no-pager"
ssh prod-web1 "tail -n 50 /var/log/nginx/error.log"
```

Loop over many servers:

```bash
for h in prod-web1 prod-web2 prod-web3; do
  echo "== $h =="
  ssh "$h" "uptime"
done
```

Pipe data **through** SSH (remote backup of a DB, etc.):

```bash
ssh prod-db "pg_dump mydb" > mydb.dump     # remote → local
cat local.sql | ssh prod-db "psql mydb"    # local → remote
```

---

## 7. Tunneling / Port Forwarding (the FDE superpower)

Tunnel = forward traffic on one machine's port through the encrypted SSH connection to another host's port.

### Local port forward (`-L`) — reach a remote service via your own port

```bash
ssh -L 8080:internal-host:80 user@bastion
```

Now `http://localhost:8080` on your machine reaches `internal-host:80` as seen from `bastion`.
**The classic use-case:** the customer's web app / DB is only reachable inside their network. You tunnel it to your laptop and point your browser/`psql`/API client at `localhost`.

Example — tunnel a PostgreSQL DB that only listens on the private network:

```bash
ssh -L 5433:10.0.2.5:5432 user@jump
psql -h localhost -p 5433 -U app dbname
```

### Remote port forward (`-R`) — expose YOUR machine's port to the remote side

```bash
ssh -R 8080:localhost:3000 user@server
```

`server:8080` now forwards to `localhost:3000` on your machine. Useful for demos: show a customer a local app running on your laptop through your company's public server.

### SOCKS proxy (`-D`) — tunnel ALL your traffic

```bash
ssh -D 1080 user@server
```

A local SOCKS5 proxy at `localhost:1080`. Point your browser at it and all traffic exits through the server — effectively "browse as if you were on that network."

### Multiple forwards in one command

```bash
ssh -L 8080:web:80 -L 5433:db:5432 user@jump
```

### `-N` — no command, just the tunnel

```bash
ssh -N -L 5433:10.0.2.5:5432 user@jump
```

Keeps the connection open purely for port forwarding (don't waste a shell). Combine with `ControlPersist` to leave tunnels running in the background.

---

## 8. Jump / Bastion Hosts

In enterprise and customer environments you rarely SSH straight to the target — you go through a **bastion (jump) host** that's the only box with access.

```bash
# old way: nested SSH
ssh -J jump.example.com target.internal

# same, but declared once in config (cleanest)
#   Host target
#       HostName target.internal
#       ProxyJump jump.example.com
```

Chain multiple jumps:

```bash
ssh -J jump1, jump2 target
```

Your **local** keys authenticate at each hop (no keys copied onto the jump boxes).

---

## 9. `scp`, `sftp`, and `rsync` — moving files

All three run **over SSH**, so they use the same keys, config, ports, and security as `ssh` — no new auth needed.

| Tool | When to use |
|------|-------------|
| `scp` | Quick one-off file copy (single file or small tree) |
| `sftp` | Interactive browse + transfer, or scripting uploads to a fixed dir |
| `rsync` | Anything large, repeated, or incremental — the default for real work |

### `scp` (simple, one-off copy)

```bash
scp file.txt user@server:/tmp/                 # local → remote
scp user@server:/tmp/file.txt ./               # remote → local
scp -r ./deploy user@server:/opt/app/          # copy a whole directory
scp -P 2222 file user@server:/tmp/             # note: -P (capital) for port
scp user@server1:/app/data.csv user@server2:/import/   # remote → remote (flows through your machine)
```

Real practical uses:
- Push a config file or a `.war`/`.jar`/binary to a single server.
- Pull a log file or a DB dump down to your laptop for analysis.
- Grab a customer's error log / screen-recorded repro file when debugging.

### `sftp` (interactive file manager over SSH)

If `scp` is "copy now," `sftp` is "browse, look around, then transfer." Gives you a filesystem shell with commands similar to `ls`/`cd`.

```bash
sftp user@server
```

Inside the sftp prompt:

| Command | Meaning |
|---------|---------|
| `ls`, `cd`, `pwd` | browse the **remote** filesystem |
| `lls`, `lcd`, `lpwd` | browse your **local** filesystem (`l` = local) |
| `get remote.txt` | download file to current local dir |
| `get -r remote_dir` | download a whole directory recursively |
| `put local.txt` | upload file to current remote dir |
| `put -r local_dir` | upload a whole directory |
| `mget *.csv` | download multiple files matching a pattern |
| `mput *.log` | upload multiple files |
| `rm remote.txt`, `mkdir x`, `rmdir x` | remote housekeeping |
| `rename old new` | rename a remote file |
| `bye` / `exit` / `quit` | disconnect |

Practical pattern — download a specific file without a shell:

```bash
sftp user@server:/var/log/app/error.log ./error.log
```

Real practical uses:
- **Enterprise file handoffs** — many legacy/customer systems (banking, gov, insurance) still do flat-file/SFTP exchanges. You'll `sftp`-browse a partner's drop folder to inspect which files arrived and pull them.
- Inspect remote file sizes/timestamps before deciding to pull (`ls -l`).
- Upload a handful of files to a specific dir when a single `scp` won't cut it.
- Batch `mget`/`mput` for small directory trees.

### `rsync` (preferred for anything large/repeated)

```bash
rsync -avz ./dist/ user@server:/var/www/html/     # sync local dir → remote
rsync -avz user@server:/var/log/app/ ./logs/       # remote → local
rsync -avz --delete ./dist/ user@server:/var/www/html/
```

Why `rsync` over `scp`:
- **Incremental** — only transfers what changed (restartable, huge time saver for big trees).
- `-a` archive (preserves perms, times, symlinks), `-v` verbose, `-z` compress.
- `--delete` removes remote files not present locally (careful — preview with `-n` first).
- Can go over SSH automatically (`rsync -avz ... user@host:...`).

Safe habit: `rsync -avzn` first (dry run), then the real run.

Real practical uses:
- Deploy a build artifact / web app to a server — push only the diff instead of the whole tree.
- Mirror customer data or logs to a local staging box for analysis.
- Restartable large transfers: if a multi-GB sync dies, re-run it and it picks up from where it stopped.

### When to use which — quick decision

- Single file, one-off, ad-hoc → `scp`
- Need to browse the remote filesystem / flat-file handoffs → `sftp`
- Directory sync, large files, repeated deploys, resumable → `rsync`

---

## 10. Keeping connections alive (and reattaching to them)

### Why sessions drop

Idle SSH connections get killed by NAT/firewalls/proxies. Fix with keep-alives:

```bash
# in ~/.ssh/config (global fix):
Host *
    ServerAliveInterval 60
    ServerAliveCountMax 2
```

(`ServerAliveInterval` pings the server every 60s. If 2 pings go unanswered, drop the session.)

### `ControlMaster` — reuse one SSH connection

With the config from §4, repeated `ssh`/`scp` to the same host reuse a single TCP connection — connecting becomes instant instead of re-handshaking each time. `ControlPersist 10m` keeps the master alive 10 minutes after the last session closes.

---

## 11. tmux — terminal multiplexer (survives SSH drops)

The one tool that makes long remote sessions painless: your session keeps running on the server even if your SSH connection drops.

### Core model: sessions → windows → panes

- **Session** — a named workspace (`tmux new -s deploy`).
- **Window** — like a browser tab (`Ctrl+b c`).
- **Pane** — split a window (`Ctrl+b %` vertical, `Ctrl+b "` horizontal).

### The workflow that matters

```bash
tmux new -s deploy          # start a session named "deploy"
tmux ls                     # list live sessions
tmux attach -t deploy       # re-attach (after connection drop or from another terminal)
tmux detach                 # Ctrl+b d — leave session running in background
tmux kill-session -t deploy # destroy it
```

### The essential keybindings

| Keys | Action |
|------|--------|
| `Ctrl+b c` | new window |
| `Ctrl+b n` / `p` | next / previous window |
| `Ctrl+b d` | detach (session keeps running) |
| `Ctrl+b %` | split vertically (left/right) |
| `Ctrl+b "` | split horizontally (top/bottom) |
| `Ctrl+b arrow` | move between panes |
| `Ctrl+b z` | zoom pane fullscreen (press again to un-zoom) |
| `Ctrl+b [` | scrollback / copy mode (Exit with `q`) |
| `Ctrl+b ?` | show all keybindings |

### Practical FDE pattern

1. `ssh prod-web1`
2. `tmux new -s deploy` (or `tmux attach` if it already exists)
3. Run your long deploy/log-tail inside tmux
4. Connection drops → `ssh prod-web1` → `tmux attach -s deploy` → your work is still there

**Also useful locally:** tmux + multiple panes for "watch logs in one pane, edit in another."

---

## 12. Debugging SSH problems

### The golden flags

```bash
ssh -v user@host       # verbose
ssh -vv user@host      # more
ssh -vvv user@host     # debug-level — full handshake trace
```

Read the output: look for which authentication method is offered/accepted, key exchange failures, and where it hangs.

### Common errors & fixes

| Symptom | Likely cause | Fix |
|---------|--------------|-----|
| `Permission denied (publickey)` | Key not in `authorized_keys`, wrong `IdentityFile`, bad perms | `ssh-copy-id`, check `~/.ssh` perms, `ssh -vv` |
| `REMOTE HOST IDENTIFICATION HAS CHANGED` | Server reinstalled → stale `known_hosts` | `ssh-keygen -R host` |
| Connection hangs / drops after idle | NAT timeout | `ServerAliveInterval 60` in config |
| `Connection refused` | SSH not running on target, blocked port, wrong port | `nc -vz host 22`, check firewall |
| `Permissions too open` | `~/.ssh` or key perms too loose | `chmod 700 ~/.ssh`, `chmod 600 ~/.ssh/id_*` |
| `Too many authentication failures` | Client trying many keys before the right one | specify `IdentityFile`, or `IdentitiesOnly yes` |

### Network-level checks

```bash
nc -vz server 22        # is port 22 reachable?
ssh-keyscan -t ed25519 server    # fetch a host key (for adding to known_hosts in scripts)
```

---

## 13. Security rules of thumb

- **Always use keys, never passwords** in any real environment.
- **Add a passphrase** to your private key + use `ssh-agent` (protects your key if the laptop is stolen).
- **`ssh -A` sparingly** — agent forwarding means any compromised intermediate host can use your keys.
- **Never copy your private key** (`id_ed25519`) to servers. Copy only public keys.
- **Rotate keys** if a machine is compromised; remove old keys from `authorized_keys`.
- For production: enforce on the server `PasswordAuthentication no` and `PermitRootLogin no` in `/etc/ssh/sshd_config`.

---

## Cheat sheet — the 20 commands you'll actually use

```bash
ssh user@host                          # connect
ssh -p 2222 user@host                  # custom port
ssh host "command"                     # run remote command
ssh -J jump host                       # via jump host
ssh -L 8080:target:80 user@jump        # local port forward
ssh -N -L 5433:db:5432 user@jump       # tunnel only, no shell
ssh -D 1080 user@host                  # SOCKS proxy
ssh -A user@host                       # forward agent
ssh -v user@host                       # debug

ssh-keygen -t ed25519                  # generate key
ssh-copy-id user@host                  # install public key
ssh-add ~/.ssh/id_ed25519              # load key into agent
ssh-add -l                             # list agent keys
ssh-keygen -R host                     # clear known_hosts entry

scp file user@host:/path/              # copy up
scp -r dir user@host:/path/            # copy dir up
sftp user@host                         # interactive browse + transfer
sftp user@host:/path/file.txt ./       # grab one file without a shell
rsync -avz ./src/ user@host:/dest/     # incremental sync

tmux new -s name                       # new session
tmux attach -t name                    # re-attach after drop
tmux ls                                # list sessions
```
