# Volumes & Basic Networking

## Volumes — where container state lives

### Why volumes
The container's writable layer is **ephemeral** — removed with the container. Volumes persist data outside the container lifecycle.

### Three ways to persist data

| Type | What | Use case |
|---|---|---|
| **Named volume** | `docker volume create mydata` or referenced in `-v mydata:/data` | DB data, app state that must survive container restarts/removal |
| **Bind mount** | `-v /host/path:/container/path` | Live code reload, mounting configs, sharing host files |
| **tmpfs mount** | `--tmpfs /data` (memory-backed) | Sensitive scratch data, never persisted |

### Commands
```bash
docker volume create pgdata
docker volume ls
docker volume inspect pgdata
docker run -v pgdata:/var/lib/postgresql/data postgres:16
docker run -v "$(pwd)":/app -w /app node:20 node app.js   # bind mount cwd
docker volume rm pgdata
docker run --rm -v pgdata:/data alpine sh -c "cat /data/file"  # inspect volume contents
```

### Named volume details
- Managed by Docker, stored in `/var/lib/docker/volumes/`.
- **Only write to the volume path, not the mount point** — the image's files at that path are hidden while mounted (copy-on-run copies them on first use for empty volumes).
- This is the right home for a database (survives `docker compose down`).

### Bind mount details
- Direct host↔container mapping. Changes on either side are visible on the other.
- Great for dev hot-reload, but mounting a host dir can expose host file access to the container — be careful with broad mounts.

---

## Basic networking

### Default bridge network
- Containers on the default bridge can reach the internet but **cannot resolve each other by name** reliably; port publishing is needed to reach them from the host.
- For multi-container apps, create a **user-defined bridge network** — containers then resolve each other by **container name / service name**.

### Networks
```bash
docker network ls
docker network create mynet
docker run --network mynet --name api myapp
docker run --network mynet --name db postgres:16
# api can now reach "db" by hostname
docker network inspect mynet
```

### Published ports
```bash
docker run -p 8080:3000 myapp       # host:8080 → container:3000
docker run -p 127.0.0.1:8080:3000   # bind only on localhost
docker run -p 3000                  # random host port
```
- Without `-p`, the container is isolated from the host network (except outbound).

### Container-to-container by name
- User-defined bridge provides **built-in DNS** — use the service/container name as hostname.
- In compose this happens automatically (`db` from the example in docker-compose.md).

### Network types
| Driver | Behavior |
|---|---|
| `bridge` (default) | Private network per host, NAT'd outbound |
| `host` | Container shares the host's network stack (no port isolation) |
| `none` | No networking |
| `overlay` | Multi-host (swarm/k8s-like) |

### Useful debugging
```bash
docker exec -it api sh            # inside container
docker exec api ping db           # test container-name resolution
docker inspect api | grep -A20 NetworkSettings
docker port api                   # show published ports
```

---

## Practice ideas
- Run Postgres with a named volume, write rows, `docker compose down -v` vs without `-v` — observe persistence difference.
- Create a bridge network, run two containers, `ping` each other by name from inside one.
- Bind-mount a file from your home dir into a container and modify it both ways.
- Inspect `NetworkSettings.IPAddress` and ports with `docker inspect`.
