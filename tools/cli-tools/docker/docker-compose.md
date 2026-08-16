# Docker Compose

## What it is
- Declarative multi-container orchestration for **local dev** (and small single-host deploys).
- One `docker-compose.yml` defines all services, their networks, volumes, env, and dependencies — `docker compose up` starts everything.
- (Note: `docker-compose` v1 vs `docker compose` v2 plugin — use the v2 syntax.)

## Minimal example
```yaml
# docker-compose.yml
version: "3.9"          # optional; newer compose doesn't require it

services:
  web:
    build: .
    ports:
      - "8080:3000"
    environment:
      - DATABASE_URL=postgres://app:pass@db:5432/app
    depends_on:
      - db
    volumes:
      - .:/app          # mount source for hot reload in dev

  db:
    image: postgres:16
    environment:
      POSTGRES_USER: app
      POSTGRES_PASSWORD: pass
      POSTGRES_DB: app
    volumes:
      - pgdata:/var/lib/postgresql/data
    ports:
      - "5432:5432"

volumes:
  pgdata:
```

## Core concepts

### `services`
Each service = one container (or a scaled set). Define `image` **or** `build`.

### `ports` vs `expose`
- `ports: "8080:3000"` — publish to the host; accessible outside the compose network.
- `expose: "3000"` — only reachable by other containers inside the compose network.

### `volumes`
- **Named volumes** (`pgdata:`) — Docker-managed, persist across restarts, survive `down`.
- **Bind mounts** (`.:/app`) — map host dir into container; used for live code reload or mounting config.
- State that must survive `docker compose down` goes in named volumes.

### `environment` vs `env_file`
- `environment:` inline key-values.
- `env_file:` load from a `.env` file (good for secrets kept out of the yml).

### `networks`
- Compose creates a default network; services reach each other by **service name** (so `db` is resolvable as hostname `db`).
- Custom networks allow grouping/isolating services.

### `depends_on`
- Ordering only (starts db before web). It does **not** wait until db is ready to accept connections — apps should retry/healthcheck.

### `command` / `entrypoint`
- Override the image's CMD/ENTRYPOINT, e.g. run a migration before serving.

## Useful commands
```bash
docker compose up -d           # build + start detached
docker compose up --build      # rebuild images before starting
docker compose down            # stop + remove containers/networks (keeps named volumes)
docker compose down -v         # ALSO delete named volumes (destructive)
docker compose logs -f web     # follow one service's logs
docker compose ps              # status
docker compose exec web sh     # shell into a running service
docker compose run web npm test  # one-off command
docker compose config          # validate + show resolved config
docker compose scale worker=4  # run N replicas of a service (swarm mode)
```

## Compose for a typical dev stack
```yaml
services:
  api: { build: ., ports: ["8080:3000"], depends_on: [db, redis] }
  db: { image: postgres:16, volumes: [pgdata:/var/lib/postgresql/data] }
  redis: { image: redis:7-alpine }
  queue:
    build: .
    command: node worker.js
    depends_on: [redis]
```

## Compose in FDE/dev workflow
- **Reproducible dev env**: one command spins up API + DB + cache + queue + message broker — no "works on my machine".
- **Local testing of integrations** without touching a shared environment.
- **Portable demo environment** for showing a client a working stack.

## Gotchas
- Named volumes vs bind mounts: don't bind-mount `node_modules` (overwrites container's) unless handled.
- Env vars with special chars need quotes.
- Secret files: prefer env_file + gitignore rather than committing.
- `depends_on` is not readiness — add healthchecks or retry logic.

## Practice ideas
- Compose a Postgres + Redis + a small API service; verify they resolve each other by service name.
- Use bind mount for source code and confirm hot reload; then switch to a named volume for the DB and confirm data survives `down`/`up`.
- Add a healthcheck to the db service and watch ordering improve.
