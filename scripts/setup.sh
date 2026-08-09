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

echo "Done. Run 'source $ZSHRC' to apply."
