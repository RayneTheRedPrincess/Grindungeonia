#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "$0")/.." && pwd)"
: "${GRINDUNGEONIA_DEVKIT:?Set GRINDUNGEONIA_DEVKIT to the extracted GBA devkit directory}"
mkdir -p "$ROOT/captures"
python3 "$GRINDUNGEONIA_DEVKIT/emulator/capture.py" "$ROOT/Grindungeonia.gba" "$@"
