# Debugging Running Containers

## The mental model
- A container is a process (or process tree) with an isolated filesystem/network — **you can debug it like a remote box** with `exec`, `logs`, `inspect`, and `cp`.
- Containers should be disposable — prefer fixing the image over fixing a running container — but you still must diagnose live ones (especially in prod).

## 1. `docker logs` — what the app printed
```bash
docker logs <container>           # stdout/stderr of PID 1
docker logs -f <container>        # follow (tail -f)
docker logs --tail 200 <container>
docker logs --since 10m <container>
```
- If nothing appears, the app may log to a file, not stdout — exec in and check, or it may not have started.

## 2. `docker exec` — run commands inside
```bash
docker exec -it <container> sh            # interactive shell (or bash, or ash for alpine)
docker exec <container> env               # check env vars
docker exec <container> ps aux            # what's running inside
docker exec <container> cat /etc/os-release
docker exec -it <container> psql -U postgres   # app-specific tooling
```
- `-i` keep stdin open, `-t` allocate a TTY (for interactive shells).
- Alpine images ship `ash` not `bash` — and often lack curl/wget; `apk add` if needed.

## 3. `docker inspect` — metadata & state
```bash
docker inspect <container>            # full JSON
docker inspect -f '{{.State.Status}}' <container>
docker inspect -f '{{.Config.Env}}' <container>
docker inspect -f '{{range .Mounts}}{{.Source}} -> {{.Destination}}{{end}}' <container>
docker inspect -f '{{.HostConfig.Binds}}' <container>
docker inspect -f '{{json .NetworkSettings.Networks}}' <container>
```
- Exit code of the process: `{{.State.ExitCode}}`.
- `docker events --filter container=<name>` — live stream of start/stop/die events.

## 4. `docker cp` — copy files in/out
```bash
docker cp <container>:/app/logs/app.log ./app.log   # pull a file out
docker cp ./fix.sh <container>:/tmp/                # push a file in
```

## 5. `docker top` & resource stats
```bash
docker top <container>          # host view of the container's processes
docker stats                    # live CPU/mem/network of all containers
docker stats --no-stream <container>
```

## 6. Common failure modes & how to check

| Symptom | Check |
|---|---|
| Container exits immediately | `docker logs` last lines; `docker inspect .State.ExitCode`; entrypoint CMD wrong |
| Port not reachable | `docker port <c>`; is `-p` right order (host:container)? is the app bound to 0.0.0.0 inside? |
| `CrashLoopBackOff`-style restarting | `docker ps -a` + `docker inspect .State.RestartCount`; read logs |
| Can't resolve other service | network: are they on the same user-defined network? name correct? |
| DB connection refused | `docker exec` the app and `ping`/telnet the db host; env `DATABASE_URL` correct? |
| No logs | app writing to file not stdout; or process not starting |
| Disk full | `docker system df`; `docker system prune` |

## 7. The debugging flow (systematic)
1. `docker ps -a` — is it running? exited? restarting?
2. `docker logs <c>` — what did it print? (missing env, panic, port busy?)
3. `docker inspect <c>` — exit code, env, mounts, network.
4. `docker exec -it <c> sh` — poke around: processes, files, config, connectivity.
5. Fix the image, rebuild, re-run — don't hand-patch a running container.

## 8. Running diagnostics tools inside
- `docker exec -it <c> sh -c 'netstat -tlnp'` or `ss -tlnp` — listening ports.
- `docker exec <c> sh -c 'wget -qO- http://localhost:3000/health'` — hit a local endpoint.
- Compare container config to a known-good one with `docker inspect`.

## 9. Cleanup
```bash
docker ps -a                    # find strays
docker rm -f <container>        # force remove
docker system prune             # remove stopped containers, unused networks, dangling images
docker system prune -a --volumes   # aggressive full cleanup (DANGER: volumes)
```

---

## Practice ideas
- Run an app that exits immediately (bad CMD) and diagnose via logs + exit code.
- Start a container with a wrong port mapping and find the real port via `docker port`/`inspect`.
- Deliberately put the app and DB on different networks, observe the DNS failure, fix by joining networks.
- Use `docker stats` while generating load to spot CPU/memory issues.
