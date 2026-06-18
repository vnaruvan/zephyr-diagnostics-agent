#!/usr/bin/env bash
set -euo pipefail

west build -p always -b native_sim .
timeout 8s west build -t run || true
