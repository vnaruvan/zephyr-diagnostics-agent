#!/usr/bin/env bash
set -euo pipefail

gcc -Wall -Wextra -Werror -Isrc tests/plain/test_health.c src/health.c -o tests/plain/test_health
./tests/plain/test_health

echo "plain C health tests passed"
