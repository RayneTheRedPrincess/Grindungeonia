#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "$0")/.." && pwd)"
: "${GRINDUNGEONIA_DEVKIT:?Set GRINDUNGEONIA_DEVKIT to extracted devkit root}"
source "$GRINDUNGEONIA_DEVKIT/env.sh"
export BUTANO_ROOT="$GRINDUNGEONIA_DEVKIT/butano/butano-21.9.0/butano"
python3 "$ROOT/tools/generate_art.py"
python3 "$ROOT/tools/generate_hero_v3.py"
make -C "$ROOT" -j"${JOBS:-4}" PYTHON=python3
