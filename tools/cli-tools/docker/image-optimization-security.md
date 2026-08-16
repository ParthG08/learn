# Image Size Optimization & Security Scanning (P2)

## Why size matters
Smaller images = faster pulls (CI/CD + cold starts), less disk, smaller attack surface, cheaper registries/eGPU transfers. A good multi-stage build is the #1 lever (see images-containers-dockerfile.md).

---

## Image size optimization

### 1. Base image selection
| Base | Approx. size | Notes |
|---|---|---|
| `node:20` (debian) | ~1GB | Full toolchain, comfortable |
| `node:20-slim` | ~200MB | Debian, trimmed — good default |
| `node:20-alpine` | ~130MB | musl libc; small but beware native deps |
| `distroless` | ~10-50MB | No shell, no package manager — runtime only, most secure |
| `scratch` | ~0MB | Empty; you copy a static binary (Go) — smallest possible |

- **Alpine gotchas:** musl vs glibc can break native modules (e.g. some node/python wheels, `bcrypt`, sharp); debug inside a distroless container is hard (no shell). Test your app on the chosen base before committing to it.

### 2. Multi-stage builds (the big win)
- Stage 1 installs build tools + compiles; final stage `COPY --from=build` only the artifact.

```dockerfile
FROM golang:1.22 AS build
WORKDIR /src
COPY go.mod go.sum ./
RUN go mod download
COPY . .
RUN CGO_ENABLED=0 GOOS=linux go build -ldflags="-s -w" -o /out/app .

FROM scratch
COPY --from=build /out/app /app
ENTRYPOINT ["/app"]
```
- `-ldflags="-s -w"` strips debug symbols (Go) — shrinks binaries.
- Python: build wheels in stage 1, then `pip install --no-cache-dir` the wheels into the runtime image.
- Node: `npm ci --omit=dev` in prod stage; use `pruned` build for larger apps.

### 3. Layer hygiene
- Chain and clean in the same `RUN`:
```dockerfile
RUN apt-get update && apt-get install -y --no-install-recommends curl \
    && rm -rf /var/lib/apt/lists/*
```
- Order deps before source (cache-friendly, see dockerfile best practices).
- Use `.dockerignore` so junk (node_modules, .git, logs) never enters the build context.

### 4. Copy only what's needed
- `COPY . .` vs `COPY dist/ /app/dist/` + `COPY server.js /app/`.
- Avoid copying a full monorepo when one package is enough.

### 5. Measure
```bash
docker images                    # sizes
docker history <image>           # per-layer sizes
docker system df                 # reclaimable space
docker buildx imagetools inspect <image> --format '{{json .Manifest}}'  # per-arch sizes
```

---

## Security scanning

### 1. `docker scan` / `docker scout`
- Docker's built-in scanner (Snyk-powered) — checks images for **CVEs** in packages:
```bash
docker scan <image>              # scan for vulnerabilities (classic, Snyk)
docker scout cves <image>        # newer Docker Scout CLI
docker scout recommendations <image>
```
- Fixes: rebuild with patched base; report shows `patchedVersion`.

### 2. Trivy (open-source, popular, fast)
```bash
trivy image <image>              # vuln scan of image
trivy image --severity HIGH,CRITICAL <image>
trivy fs .                       # scan the filesystem/working dir
trivy config .                   # scan IaC (Dockerfile, compose, k8s)
trivy repo <url>                 # scan a git repo
```
- Also scans IaC and secrets — good for CI gates.

### 3. Grype (Anchore)
```bash
grype <image>                    # fast, precise; outputs SBOM-friendly report
syft <image>                     # generate SBOM first, then grype against it
```

### 4. Best practices beyond scanners
- **Pin base image digests** (`FROM node:20-alpine@sha256:...`) for reproducible + tamper-evident builds.
- **Non-root user** in the image (see dockerfile best practices).
- **Don't bake secrets**: use build args only for non-secret values; runtime secrets via env/secrets managers. (`ARG` is visible in history; build-time secrets via `--secret` / BuildKit `RUN --mount=type=secret`.)
- **Sign images** (Docker Content Trust / cosign) if the pipeline supports it.
- **Scan on every build in CI** — fail on critical/high CVEs; don't rely on ad-hoc scans.
- **Regularly rebuild** against a current base image — fixes known CVEs automatically (this is often more effective than chasing individual CVEs).
- Minimize attack surface: distroless/scratch (no shell), drop unnecessary packages, `cap_drop: all` at runtime where possible.

---

## CI gate example (Trivy)
```yaml
- name: Scan image
  run: trivy image --exit-code 1 --severity CRITICAL myapp:${{ github.sha }}
```

---

## Practice ideas
- Build the same app with `node:20`, `node:20-slim`, `node:20-alpine`, and multi-stage — compare sizes with `docker images`.
- Run `docker scout cves` / `trivy image` on an old, un-updated base image vs a fresh one — compare the CVE lists.
- Write a `.dockerignore` for a real repo and time the build-context transfer before/after.
- Add a non-root `USER` step and confirm the container runs (many apps need writable dirs — adjust permissions).
