# Pinnacle-HAL Build and Deployment

## Purpose and scope

Pinnacle-HAL is the C++ hardware-abstraction and gRPC contract layer. CMake generates/builds protobuf and gRPC sources, native tests, and installable DEB/RPM/IPK packages. The root Makefile also provides ARM64 Docker builds, package targets, SSH deployment, static analysis, and Doxygen generation.

## 1. Prerequisites

- Linux with GNU Make, CMake, Ninja, a C++ compiler, `nproc`, and the development libraries required by the root `CMakeLists.txt`.
- For native tests and packaging: CTest, CPack, and package tools appropriate to the selected generator.
- For quality/docs: `clang-format`, `cmake-format`, `cppcheck`, `doxygen`, and `graphviz` as required by the checked targets.
- For Docker: Docker with ARM64/QEMU support; `make docker-install` may use `sudo apt`.
- For cross deployment: `sshpass`, SSH/SCP access, and Raspberry Pi 5 target addresses. The Makefile defaults to `IP_A=192.168.1.3`, `IP_B=192.168.1.13`, and user `root` with no password (key-based SSH); override with `HAL_SSH_USER`/`HAL_SSH_PASS` and never commit credentials.

## 2. Setup

```bash
make help
make configure
```

Native output is `build/native`; Docker cross output is `build/cross`. Override native parallelism with `make JOBS=N`. Credentials can be supplied as `HAL_SSH_USER` and `HAL_SSH_PASS` or Make variables for deployment.

## 3. Build and compile

Native CMake/Ninja build:

```bash
make configure
make build
```

The native configure step uses CMake/Ninja and then `make build` runs Ninja. ARM64 Docker build:

```bash
make docker-install       # conditional; may require sudo
make docker-image
make docker-configure
make docker-build
```

The Docker path uses `--platform linux/arm64` and a persistent ccache volume. `make docker-shell` opens the image for interactive development.

## 4. Test and lint

```bash
make test                 # native build followed by CTest
make docker-test          # ARM64/QEMU CTest
make format               # modifies C++ and CMake files
make cppcheck
make doc
```

`cppcheck` and `doc` check for their required tools before invoking Ninja. The Docker test path is emulated and does not validate every physical peripheral.

## 5. Packaging and artifacts

Native packages:

```bash
make package-deb
make package-rpm
make package-ipk
make package
```

These invoke CPack or the `package_ipk` build target after `make build`; outputs are expected in `build/native/` with `pinnacle-hal_*` package names. Cross packages:

```bash
make docker-package-deb
make docker-package-rpm
make docker-package-ipk
make docker-package
```

Cross outputs are under `build/cross/`. RPM packaging is conditional on `rpmbuild` in the Docker image/host. Review package names and install metadata before distributing.

## 6. Deployment, install, and run

Copy cross-built `lib/` and `bin/` directories to one or both targets:

```bash
make deploy-a IP_A=192.168.1.3 HAL_SSH_USER=pi HAL_SSH_PASS='<password>'
make deploy-b IP_B=192.168.1.13 HAL_SSH_USER=pi HAL_SSH_PASS='<password>'
make deploy
```

The target clears `/tmp/acu-test` remotely and copies `build/cross/lib` and `build/cross/bin`. Run all applications or a named application:

```bash
make run-a
make run-a APP_NAME arg1 arg2
make run-b APP_NAME arg1 arg2
```

Run native binaries with `LD_LIBRARY_PATH`:

```bash
make run
make run APP_NAME arg1 arg2
make list
```

The root Makefile has no package installation target. Installing a DEB/IPK/RPM, registering libraries, configuring permissions, and enabling any service are target-image operations and must be documented by the image owner.

## 7. Cleanup

```bash
make clean
make docker-clean
```

`clean` removes `build/`; `docker-clean` removes the cross build in the container-mounted path and requires the Docker image.

## 8. Hardware, cloud, and manual verification caveats

- HAL behavior depends on the board kernel, device nodes, permissions, firmware, and attached peripherals.
- `deploy-*` requires reachable devices and credentials; SSH host-key checking is disabled by the Makefile, which is a production security risk to assess before use.
- Validate package installation, ABI/library loading, gRPC compatibility with Client/Server, and representative physical modules manually on the supported target.
- No cloud deployment is implemented by this Makefile. Any remote fleet rollout, credentials, OTA integration, or monitoring is external and requires environment-specific verification.
