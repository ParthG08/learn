#!/usr/bin/env bash
set -euo pipefail

ALIASES=(
  'alias oc="opencode"'
  'alias occ="opencode --continue"'
)

ZSHRC="$HOME/.zshrc"

touch "$ZSHRC"

for alias_def in "${ALIASES[@]}"; do
  if grep -qF "$alias_def" "$ZSHRC"; then
    echo "Already present: $alias_def"
  else
    echo "$alias_def" >> "$ZSHRC"
    echo "Added: $alias_def"
  fi
done

REPO_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
TUI_SRC="$REPO_DIR/tools/cli-tools/opencode/tui.json"
TUI_DEST="$HOME/.config/opencode/tui.json"

if [ -f "$TUI_SRC" ]; then
  mkdir -p "$(dirname "$TUI_DEST")"
  if [ -f "$TUI_DEST" ] && cmp -s "$TUI_SRC" "$TUI_DEST"; then
    echo "Already in sync: $TUI_DEST"
  else
    cp "$TUI_SRC" "$TUI_DEST"
    echo "Copied: $TUI_SRC -> $TUI_DEST"
  fi
else
  echo "Skipping opencode tui.json: replica not found at $TUI_SRC"
fi

echo "Done. Run 'source $ZSHRC' to apply (and restart opencode for tui.json)."
