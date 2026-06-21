# Debuggers: The Overview

## What a Debugger Actually Does (Under the Hood)

When you "attach a debugger" to a process, the debugger is asking the OS to let it observe and control another process. On Linux, this is done through a syscall called `ptrace`. It lets one process (the debugger) pause, inspect memory, read registers, and single-step through instructions of another process (your program).

This is why:
- Attaching a debugger requires either the same user or root — it's a privileged OS operation.
- Debuggers can set breakpoints: they literally overwrite the target instruction at that address with a special interrupt instruction (`int3` on x86). When the CPU hits it, the OS pauses the process and hands control to the debugger.
- On macOS, the equivalent is the Mach exception handling API. On Windows, it's the Win32 Debug API. Different surface, same idea.

So a debugger is fundamentally an OS-assisted process controller, not a language feature.

## The DAP Protocol (Why This Doesn't Explode into Chaos)

Before ~2016, every editor had to implement its own debugger integration for every language. VS Code introduced the **Debug Adapter Protocol (DAP)** — the same idea as LSP (Language Server Protocol) for autocomplete, but for debugging.

The model:
```
Your Editor (DAP Client)  <-->  Debug Adapter  <-->  Actual Debugger (GDB, Delve, etc.)
```

The debug adapter is a thin translation layer that speaks DAP on one side and the actual debugger's protocol on the other. This means:
- VS Code, nvim, Emacs, Zed — any editor that implements a DAP client can use any language's debugger.
- Language teams ship a debug adapter, not a full editor plugin.
- You get breakpoints, variable inspection, call stacks, watches — all through one standardized protocol.

DAP is now the de facto standard. If you're setting up debugging in any editor, you're almost certainly using a DAP client + adapter combo.

## The Standalone Debuggers (The Actual Engines)

These are the tools doing the real work. Everything else is a frontend.

### GDB (GNU Debugger)
- The closest thing to a "DBeaver for debuggers" — old (1986), CLI-first, works everywhere, most people use it through a GUI but it's the underlying engine.
- Supports C, C++, Go, Rust, Ada, Fortran, and more.
- Default debugger on Linux. If something is debuggable on Linux, GDB can probably do it.
- Commands: `break main`, `run`, `next`, `step`, `print var`, `backtrace`, `watch expr`.
- Its MI (Machine Interface) mode is what GUIs and DAP adapters talk to under the hood.

### LLDB
- Apple's answer to GDB — same concept, cleaner internals, default on macOS.
- Used by Xcode and VS Code's C/C++ extension on Mac.
- Commands are similar to GDB but not identical (`process launch`, `thread step-over`, etc.)
- For most purposes, if you know GDB you can use LLDB.

### Delve (`dlv`)
- Go-specific debugger. GDB technically works for Go but Delve understands Go's runtime (goroutines, channels, etc.) natively.
- `dlv debug`, `dlv attach <pid>`, `dlv test` — you use it directly or through a DAP adapter.

### `rr` (Mozilla's Record and Replay Debugger)
- A different category entirely: instead of pausing a live process, `rr record` captures an entire execution, and `rr replay` lets you step through it forwards *and backwards*.
- Huge for non-deterministic bugs (race conditions, flaky crashes) where you need to go back in time.
- Works as a GDB extension — the replay session is controlled through GDB commands.

### Language-specific mentions
- **Python**: `pdb` (built-in), `ipdb` (nicer version), `debugpy` (the DAP adapter VS Code uses)
- **Java**: JDWP (Java Debug Wire Protocol) — Java has its own debug protocol baked into the JVM. `jdb` is the CLI tool. Every Java IDE talks JDWP.
- **Node.js / JavaScript**: V8 Inspector Protocol, exposed via `--inspect` flag. Chrome DevTools and VS Code both connect to this.
- **Ruby**: `ruby-debug`, `byebug`, `debug` (stdlib in Ruby 3+)

## How nvim Users Debug

nvim doesn't ship with a debugger. You install a DAP client plugin and point it at debug adapters.

The standard plugin is **`nvim-dap`** (by mfussenegger). It's a DAP client — same protocol VS Code uses. You configure it per language:

```lua
-- example: telling nvim-dap where the Go debug adapter is
require('dap').adapters.go = {
  type = 'server',
  port = 38697,
  executable = { command = 'dlv', args = { 'dap', '-l', '127.0.0.1:38697' } }
}
```

Common companion plugins:
- `nvim-dap-ui` — gives you the watch/variables/call stack panels (reproduces the VS Code sidebar)
- `nvim-dap-virtual-text` — shows variable values inline next to the code as you step

The workflow in nvim:
1. Set breakpoints with a keybind (`<leader>db` or whatever you map).
2. Launch or attach via `:DapContinue`.
3. Step through with `<F10>` / `<F11>` (or your mappings).
4. Inspect variables in the DAP UI panel or hover with `nvim-dap`'s `require('dap.ui.widgets').hover()`.

It's more setup than VS Code but once configured it's the same experience.

## Attaching to a Running Process

This is the "attach" workflow as opposed to "launch." You use it when:
- Your process is already running (a server, a container, etc.)
- You can't easily restart it with the debugger in front.
- You're debugging in production-like conditions.

```bash
# GDB attach
gdb -p <pid>

# Delve attach
dlv attach <pid>

# Python (debugpy)
python -m debugpy --listen 5678 --wait-for-client your_script.py
# then attach from VS Code / nvim-dap at localhost:5678
```

For remote debugging (process is on a different machine or inside a container):
- You run the debug adapter/server on the remote side.
- Your editor connects to it over TCP.
- VS Code's `launch.json` has `"request": "attach"` + `"host"` + `"port"` for this.
- In Docker: you expose the debug port and map it (`-p 5678:5678`), then attach locally as if it's localhost.

## GUI Frontends (The Lens/DBeaver Equivalents)

There isn't one dominant standalone GUI debugger the way DBeaver owns database GUIs or Lens owns Kubernetes. The space is more fragmented:

| Tool | What it is |
|------|------------|
| **VS Code** | The de facto standard GUI debugging experience for most people, via DAP |
| **gdbgui** | Web-based GUI frontend for GDB specifically, runs in browser |
| **DDD** (Data Display Debugger) | Old-school GTK GUI for GDB/LLDB, from the 90s, still works |
| **CLion / IntelliJ** | JetBrains IDEs have excellent built-in debuggers (LLDB/GDB under the hood for C++, JDWP for Java) |
| **Xcode** | macOS/iOS, wraps LLDB |
| **Qt Creator** | C++/Qt projects, wraps GDB or LLDB |

The honest answer: for most people who aren't in C/C++, the debugger is just baked into their editor (VS Code, IntelliJ, etc.) and they never interact with GDB/LLDB directly. The standalone GUI tools mostly exist for C/C++ developers who want something between raw GDB CLI and a full IDE.

## The Mental Model

```
OS (ptrace / Mach exceptions / Win32 Debug API)
        |
Actual Debugger Engine (GDB, LLDB, Delve, debugpy...)
        |
DAP Adapter (translates DAP <-> debugger's own protocol)
        |
DAP Client in your editor (VS Code, nvim-dap, etc.)
        |
You, setting breakpoints and inspecting variables
```

The further down this stack you go, the more universal and lower-level it gets. The further up, the more editor-specific and user-friendly.
