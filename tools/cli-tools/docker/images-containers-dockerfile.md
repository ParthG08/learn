# Images vs. Containers & Dockerfile Best Practices

## Images vs. Containers

| | **Image** | **Container** |
|---|---|---|
| What | Immutable template / blueprint | A running instance of an image |
| State | Static, read-only layers | Has a writable layer + running process |
| Analogy | A class / an ISO file | An object / a running VM from that ISO |
| Created by | `docker build` | `docker run` |
| Count | Many images, many instances | Each `run` = one container |
| Lifecycle | Persistent until removed | Starts/stops, can be removed |

### Layers
- An image is built from **read-only layers**, one per instruction in the Dockerfile.
- `docker build` caches layers — unchanged instructions reuse cached layers (this is why layer order matters).
- When you `docker run`, Docker adds a thin **writable container layer** on top. Changes to the filesystem inside the container live there and are lost when the container is removed (unless you use volumes).
- **Union filesystem** overlays the layers; reads go down the stack, writes go to the top writable layer (copy-on-write).

```bash
docker pull postgres:16        # pull image
docker run --name db -e POSTGRES_PASSWORD=secret -d postgres:16   # create+start container
docker ps                      # running containers
docker images                  # local images
docker rmi postgres:16         # remove image (not while in use)
docker rm -f db                # remove container
```

---

## Anatomy of a Dockerfile

```dockerfile
# 1. Base image — start from something trustworthy and specific
FROM node:20-alpine

# 2. Set metadata / working dir
LABEL maintainer="you@example.com"
WORKDIR /app

# 3. Install dependencies FIRST (cheap layer, cached unless deps change)
COPY package*.json ./
RUN npm ci --only=production

# 4. Copy source AFTER deps (so code changes don't invalidate the dep layer)
COPY . .

# 5. Non-root user for security
RUN addgroup -S app && adduser -S app -G app
USER app

# 6. Expose port (informational — actual mapping is -p)
EXPOSE 3000

# 7. Healthcheck (optional but good)
HEALTHCHECK CMD curl -f http://localhost:3000/health || exit 1

# 8. Runtime command
CMD ["node", "server.js"]
```

---

## Dockerfile best practices

### 1. Order layers from least to most frequently changing
- Dependencies (`COPY package.json` + `RUN npm ci`) before source (`COPY . .`).
- A change to your code then **reuses the cached dependency layer** → fast rebuilds.

### 2. Use multi-stage builds (key pattern)
Separate the build environment from the runtime, so the final image only carries what it needs.

```dockerfile
# Stage 1: build
FROM golang:1.22 AS build
WORKDIR /src
COPY go.mod go.sum ./
RUN go mod download
COPY . .
RUN CGO_ENABLED=0 go build -o /app .

# Stage 2: tiny runtime
FROM scratch                    # or alpine / distroless
COPY --from=build /app /app
ENTRYPOINT ["/app"]
```
- Build tools (compilers, dev deps) stay out of the final image.
- Result: image goes from ~1GB to tens of MB.

### 3. Use a `.dockerignore`
Like `.gitignore` — keeps `node_modules`, `.git`, build artifacts out of the build context (faster sends, no accidental secrets).

```
node_modules
.git
*.log
.env
```

### 4. Prefer specific base images
- `alpine` (small), `distroless` (minimal, no shell), or official `-slim` variants.
- Pin a version (`node:20-alpine` not `node:latest`).

### 5. Minimize layers but don't obsess
- `RUN` commands that produce intermediate junk should be chained with `&&` and cleaned in the same layer.

```dockerfile
RUN apt-get update \
    && apt-get install -y --no-install-recommends curl \
    && rm -rf /var/lib/apt/lists/*
```

### 6. Run as non-root
- Default is root inside the container — huge risk if the container is compromised. Add a `USER` step.

### 7. Don't use `ADD` when `COPY` suffices
- `COPY` is predictable (only copies files); `ADD` also auto-extracts tarballs and fetches URLs — surprising behavior.

### 8. Metadata
- `LABEL`, `ENV`, `EXPOSE` are cheap and document intent.

### 9. Make the image ephemeral
- Containers should be disposable: all state goes in volumes, config via env vars, never "ssh into a container and fix it" (the fix belongs in the image).

---

## Common commands cheat-sheet
```bash
docker build -t myapp:1.0 .          # build image from ./Dockerfile
docker run -d -p 8080:3000 myapp:1.0 # run detached, map host:container port
docker run --rm -it myapp sh         # run interactively, remove on exit
docker exec -it <container> sh       # shell into a running container
docker logs -f <container>           # follow logs
docker inspect <container>           # low-level details (env, mounts, network)
docker ps -a                         # all containers (incl. stopped)
docker system prune -a               # clean unused images/containers/networks
```

---

## Practice ideas
- `docker run hello-world` then `docker inspect` it to see the layers + writable layer.
- Build a Dockerfile for a small Node/Python app with multi-stage build; compare `docker images` sizes before/after.
- `docker history <image>` to see every layer and how big each is.
- Deliberately order `COPY` deps before source and observe rebuild caching (`CACHED` in build output).
