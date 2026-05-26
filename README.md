# Pinnacle HAL

## Overview

Pinnacle HAL is a C++17 hardware abstraction and validation suite retargeted to the Pinnacle platform:

- NXP i.MX 8M/9 application core on Yocto Linux
- On/off-chip Cortex-M (i.MX RT class) real-time co-processor
- A-core <-> M-core communication via RPMsg/OpenAMP

The public HAL test-class contract remains intact, while backend implementation and platform bindings are retargeted from legacy board assumptions to Pinnacle i.MX.

## Architecture

- A-core domain: Linux-facing probes (sysfs, /dev nodes, net, media, storage)
- M-core domain: deterministic real-time/safety responsibilities
- Contract layer: RPMsg/OpenAMP message contract in `src/platform_pinnacle.h`
- Shared transport helpers: `hal::rt::*` in `src/lib_base.h` and `src/lib_base.cpp`

## Functional-Safety Hooks

The FuSa path includes:

- Watchdog keepalive path to Cortex-M
- Safe-state request path
- Lockstep/error-reporting path
- Expanded FuSa-oriented tests in:
  - `src/functional_safety_lib/functional_safety_lib.cpp`
  - `src/watchdog_and_reset_lib/watchdog_and_reset_lib.cpp`
  - `src/mcu_interface_lib/mcu_interface_lib.cpp`

## Build

```bash
make build
```

## Run

```bash
make run
```

## Test

```bash
ctest --test-dir build
```

## Packaging

CMake/CPack metadata is retargeted to `pinnacle-hal` and installs headers under `pinnacle_hal`.
