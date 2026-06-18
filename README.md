# Zephyr Diagnostics Agent

A small Zephyr RTOS diagnostics-style application built for `native_sim`.

This project was created as a hands-on ramp-up exercise for Zephyr application development, modular C design, build/debug workflow, runtime diagnostics, logging, timers, workqueues, shell commands, plain C testing, and Bash automation.

## What This Demonstrates

* Standalone Zephyr application structure
* `west` build workflow
* `CMakeLists.txt` source registration
* `prj.conf` feature configuration
* Modular C separation with `health.h`, `health.c`, `diagnostics.h`, and `diagnostics.c`
* Timer-driven execution using `k_timer`
* Deferred processing using `k_work`
* Runtime diagnostics through Zephyr shell commands
* Structured logging with Zephyr logging macros
* `printk()` console output for visible runtime status
* Plain C tests for core health logic
* Bash automation for build, run, and test checks

## Project Structure

```text
zephyr-diagnostics-agent/
├── CMakeLists.txt
├── prj.conf
├── README.md
├── scripts/
│   ├── build_native.sh
│   ├── check.sh
│   ├── run.sh
│   └── test_plain.sh
├── src/
│   ├── diagnostics.c
│   ├── diagnostics.h
│   ├── health.c
│   ├── health.h
│   ├── main.c
│   └── shell_cmds.c
└── tests/
    └── plain/
        └── test_health.c
```

## Build

```bash
source ~/zephyrproject/.venv/bin/activate
export ZEPHYR_BASE=~/zephyrproject/zephyr
./scripts/build_native.sh
```

## Run

```bash
./scripts/run.sh
```

The app periodically updates a simulated sensor value and reports health status.

Example output:

```text
starting Zephyr diagnostics agent
health monitor initialized with threshold=75
health=OK sensor=65 threshold=75 updates=1 errors=0
health=OK sensor=70 threshold=75 updates=2 errors=0
health=OK sensor=75 threshold=75 updates=3 errors=0
health=WARN sensor=80 threshold=75 updates=4 errors=1
```

## Run Plain C Tests

```bash
./scripts/test_plain.sh
```

Expected output:

```text
plain C health tests passed
```

## Runtime Behavior

The application simulates a sensor value and compares it against a configured threshold.

* If the sensor value is below or equal to the threshold, the health status is `OK`.
* If the sensor value exceeds the threshold, the health status becomes `WARN`.
* Each warning increments the error counter.
* A Zephyr timer fires every second.
* The timer callback submits work to a workqueue.
* The work handler updates diagnostics state and emits console/log output.

## Shell Commands

The project includes Zephyr shell commands for runtime inspection and control:

```text
health status
health reset
health inject_error
health threshold <value>
```

These commands allow the diagnostics state to be inspected, reset, modified, and tested at runtime.

## Design Notes

The core health logic is separated from Zephyr-specific runtime code.

* `health.c` contains testable health-state logic.
* `diagnostics.c` manages application-level diagnostics state.
* `main.c` handles Zephyr timer/workqueue execution.
* `shell_cmds.c` exposes runtime diagnostics commands.

This separation allows the core health logic to be tested using a plain C test without requiring Zephyr runtime execution.


