#!/usr/bin/env python3
"""Keep dsa/lc-solutions/*.cpp and their Obsidian .md mirrors in sync.

The .cpp files are the source of truth. Each gets a matching .md file
(a header line + the full C++ source in a ```cpp fenced block) so the
solutions render nicely in Obsidian.

Usage:
  python scripts/lc_sync.py            # .cpp -> .md  (default: regenerate mirrors)
  python scripts/lc_sync.py md2cpp     # .md -> .cpp  (propagate an edited code block back)
  python scripts/lc_sync.py check      # report any mirror that is out of date

Only the ```cpp fenced block in a .md is synced; the file is otherwise
fully regenerated from the .cpp, so do not hand-edit the .md.
"""

import sys
from pathlib import Path

LC_DIR = Path(__file__).resolve().parent.parent / "dsa" / "lc-solutions"
CPP_SUFFIX = ".cpp"
MD_SUFFIX = ".cpp.md"
FENCE = "```"
SKIP = {"test.cpp"}


def cpp_files():
    return sorted(
        p for p in LC_DIR.glob(f"*{CPP_SUFFIX}")
        if p.name not in SKIP
    )


def md_path(cpp_path: Path) -> Path:
    return cpp_path.with_suffix(MD_SUFFIX)


def build_md(cpp_path: Path) -> str:
    body = cpp_path.read_text().rstrip("\n")
    return f"# {cpp_path.stem}\n\n{FENCE}cpp\n{body}\n{FENCE}\n"


def extract_cpp(md_path: Path) -> str | None:
    lines = md_path.read_text().splitlines()
    out, in_block = [], False
    for line in lines:
        if line.strip().startswith(FENCE):
            if not in_block:
                in_block = True
            else:
                return "\n".join(out) + "\n"
            continue
        if in_block:
            out.append(line)
    return None


def cmd_regenerate() -> int:
    n = 0
    for cpp in cpp_files():
        md = md_path(cpp)
        content = build_md(cpp)
        if md.exists() and md.read_text() == content:
            continue
        md.write_text(content)
        print(f"updated {md.relative_to(LC_DIR)}")
        n += 1
    print(f"regenerated {n} mirror(s)" if n else "all mirrors up to date")
    return 0


def cmd_md2cpp() -> int:
    n = 0
    for cpp in cpp_files():
        md = md_path(cpp)
        if not md.exists():
            continue
        code = extract_cpp(md)
        if code is None:
            print(f"no cpp fence in {md.relative_to(LC_DIR)}, skipping")
            continue
        if cpp.exists() and cpp.read_text() == code:
            continue
        cpp.write_text(code)
        print(f"updated {cpp.relative_to(LC_DIR)}")
        n += 1
    print(f"propagated {n} file(s)" if n else "nothing to propagate")
    return 0


def cmd_check() -> int:
    dirty = []
    for cpp in cpp_files():
        md = md_path(cpp)
        if not md.exists():
            dirty.append(f"{cpp.relative_to(LC_DIR)}: no mirror (run lc_sync.py)")
        elif md.read_text() != build_md(cpp):
            dirty.append(f"{md.relative_to(LC_DIR)}: out of date (run lc_sync.py)")
    for md in sorted(LC_DIR.glob(f"*{MD_SUFFIX}")):
        cpp = md.with_suffix("")
        if not cpp.exists():
            dirty.append(f"{md.relative_to(LC_DIR)}: no matching .cpp (orphan)")
    if dirty:
        for d in dirty:
            print(d)
        return 1
    print("all mirrors in sync")
    return 0


def main() -> int:
    cmd = sys.argv[1] if len(sys.argv) > 1 else "regenerate"
    return {"regenerate": cmd_regenerate,
            "md2cpp": cmd_md2cpp,
            "check": cmd_check}.get(cmd, cmd_regenerate)()


if __name__ == "__main__":
    sys.exit(main())
