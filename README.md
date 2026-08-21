# Pinnacle-HAL

## Project Summary

Pinnacle-HAL is the C++17 hardware abstraction and validation library for Pinnacle boards built around NXP i.MX 8M/9 application processors and an optional Cortex-M co-processor.

The `src` tree contains a library and CMake target per hardware domain:

- CPU, GPU, deep-learning, and vision accelerators.
- Memory, storage, networking, USB, and PCIe.
- Cameras, displays, audio/video, GPIO, IMU, and GNSS.
- Power, thermal, watchdog, security, reliability, functional safety, MCU, and system integration.

`src/platform_pinnacle.h` and `lib_base.*` establish the A-core to M-core RPMsg/OpenAMP boundary.

The public test-class contract is retained while probes use Linux sysfs, device nodes, network interfaces, media, and storage. Functional-safety sources include watchdog keepalive, safe-state requests, and error-reporting hooks.

`protos/registry/modules.yaml` describes module identifiers used by Client and SDK. CMake/CPack installs the headers and library as `pinnacle-hal`; the Makefile provides native, Docker, and cross-build routes.

The `tests` tree has per-module CMake targets and executable runners, and the top-level Makefile invokes CTest.

This is a substantial implementation surface, but test executables do not prove every probe returns valid data on a specific board.

Checks depend on kernel interfaces, attached peripherals, firmware, RPMsg endpoints, and safety hardware. The packaged `.deb` does not establish installation or runtime ABI compatibility.

Use `make build`, `make run`, and CTest in a configured target. Then validate connected modules and safety paths on hardware.

## Feature Status

| # | Name / Description | Implemented? | Test Coverage? | Manual Test |
|---:|---|---|---|---|
| 1 | Per-module C++ HAL libraries and public test contract | Yes | Per-module CMake test targets exist across `tests` | [ ] Manual verification required |
| 2 | Linux A-core hardware probes | Yes | Module test executables exist; device results are not fully evidenced | [ ] Manual verification required |
| 3 | RPMsg/OpenAMP A-core to M-core transport | Partial | Platform and transport code exist; live co-processor communication is unproven | [ ] Manual verification required |
| 4 | Functional-safety, watchdog, and safe-state hooks | Partial | Dedicated source and test targets exist; safety needs hardware validation | [ ] Manual verification required |
| 5 | Module registry and test discovery metadata | Yes | Registry YAML and test runners provide coverage scaffolding | [ ] Manual verification required |
| 6 | CMake, CPack, native, Docker, and cross builds | Yes | Build/test commands are wired; package validation is limited | [ ] Manual verification required |

## Tests and Commands

```bash
make build
make run
ctest --test-dir build --output-on-failure
```

## Limitations

- Hardware, kernel configuration, firmware, permissions, and peripherals control the meaningful result.
- A green build or CTest run is not board-level IV&V.
