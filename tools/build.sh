#!/usr/bin/env bash
set -euo pipefail
ROOT="$(cd -- "$(dirname -- "$0")/.." && pwd)"
: "${GRINDUNGEONIA_DEVKIT:?Set GRINDUNGEONIA_DEVKIT to the extracted GBA devkit directory}"
source "$GRINDUNGEONIA_DEVKIT/env.sh"
export BUTANO_ROOT="$GRINDUNGEONIA_DEVKIT/butano/butano-21.9.0/butano"
make -C "$ROOT" -j"${JOBS:-4}" PYTHON=python3
