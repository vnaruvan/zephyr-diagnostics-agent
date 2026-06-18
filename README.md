# Zephyr Diagnostics Agent

A small Zephyr RTOS diagnostics-style application built for `native_sim`.

This project was created as a hands-on ramp-up exercise for Zephyr application development, C module structure, build/debug workflow, logging, timers, workqueues, and Bash automation.

## What This Demonstrates

- Standalone Zephyr application structure
- `west` build workflow
- `CMakeLists.txt` source registration
- `prj.conf` feature configuration
- C module separation with `health.h` and `health.c`
- Timer-driven execution using `k_timer`
- Deferred processing using `k_work`
- Structured logging with Zephyr logging macros
- Basic Bash automation for build/run checks

## Project Structure

```text
zephyr-diagnostics-agent/
├── CMakeLists.txt
├── prj.conf
├── README.md
├── scripts/
│   ├── build_native.sh
│   ├── check.sh
│   └── run.sh
└── src/
    ├── health.c
    ├── health.h
    └── main.c
