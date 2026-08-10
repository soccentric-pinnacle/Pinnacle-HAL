# Pinnacle Retarget Inventory (Pre-Change Baseline) This inventory was prepared before code changes and covers all module implementations under `src/*` and all test launchers under `tests/*`. ## Module Mapping | Module | Current backend shape | Pinnacle mapping |
|---|---|---|
| audio_interfaces | ALSA + platform sysfs constants | i.MX SAI/ALSA on A-core Linux |
| camera_interfaces_lib | V4L2/video nodes + platform identifiers | i.MX CSI/V4L2 on A-core Linux |
| camera_module3_lib | camera module specific checks | i.MX camera stack via V4L2; board-specific sensors |
| clock_and_timing_lib | POSIX clocks + platform comments/constants | i.MX timers/RTC via Linux clock + RTC subsystems |
| communication_interface_lib | UART/SPI/I2C/CAN probes | i.MX native UART/SPI/I2C/FlexCAN devices |
| cpu_lib | cpufreq/sysfs + affinity assumptions | i.MX 8M/9 A-core CPU checks + M-core heartbeat |
| debug_and_development_interfaces | UART/JTAG/openocd checks | i.MX debug UART + JTAG/OpenOCD |
| deep_learning_accelerator_lib | external accelerator checks + NXP i.MX 93 strings | i.MX NPU on A-core, optional RPMsg offload to M-core |
| display_interfaces | DRM/KMS checks | i.MX DRM/KMS |
| environmental_lib | thermal/hwmon/iio checks | i.MX thermal/hwmon/iio |
| ethernet_lib | net/ethtool checks | i.MX Ethernet MAC/PHY via Linux net stack |
| ethernet_switch_lib | switch topology checks | i.MX switch topology where available |
| external_connector_lib | connector continuity/peripheral checks | Pinnacle connector map and Linux devices |
| functional_safety_lib | watchdog/proxy safety checks | FuSa hooks: watchdog/safe-state/lockstep/error-reporting |
| gnss_lib | serial GNSS checks | i.MX serial GNSS on A-core |
| gpio_lib | gpio checks and constants | i.MX gpiochip + optional M-core mediated GPIO |
| gpu_lib | platform GPU checks with NXP i.MX 93-specific text | i.MX GPU/NPU stack checks |
| imu_lib | I2C sensor checks | i.MX I2C/IIO sensor checks |
| mcu_interface_lib | SPI/UART/I2C MCU checks (NXP i.MX 93-focused text) | i.MX RT/Cortex-M coprocessor over RPMsg/OpenAMP |
| pcie_lib | sysfs PCIe checks | i.MX PCIe link and endpoint checks |
| poe_hat_lib | PoE and voltage checks with NXP i.MX 93 assumptions | Pinnacle power domain checks, board-specific PoE option |
| power_management_lib | power_supply + firmware tool checks | i.MX PMIC rails + RPMsg safety telemetry |
| reliability_lib | stress/thermal checks | i.MX endurance, thermal, watchdog interaction |
| security_features_lib | secure boot/crypto checks | i.MX secure boot + CAAM/crypto checks |
| sense_hat_lib | accessory sensor checks | optional accessory support on Pinnacle |
| serializer_deserializer_lib | media pipeline checks | i.MX CSI/SerDes media checks |
| software_interface_lib | kernel/module/tools checks with NXP i.MX 93 strings | Yocto i.MX software stack checks |
| storage_lib | block device checks | i.MX eMMC/NVMe/SD checks |
| system_integration_lib | aggregate subsystem exercise | i.MX full-system integration checks |
| system_memory_lib | meminfo/DMA checks | i.MX memory + DMA + EDAC checks |
| thermal_management_lib | thermal zone checks | i.MX thermal zones + RPMsg thermal telemetry |
| usb_lib | USB host/device checks | i.MX USB controller checks |
| video_encode_decode_lib | V4L2 codec checks | i.MX codec path |
| vision_accelerator_lib | accelerator checks | i.MX vision/NPU + M-core assist |
| watchdog_and_reset_lib | Linux watchdog checks | i.MX watchdog + cross-core watchdog handshake | ## Test Inventory All test targets under `tests/*` currently compile a launcher `main.cpp` that invokes `runTestApp<ModuleTesting>(...)`. The executable coverage set is preserved and retargeted by changing module internals, plus additional RPMsg/FuSa test methods in: - `mcu_interface_lib`
- `watchdog_and_reset_lib`
- `functional_safety_lib` ## Required Contract Injection Points - `src/platform_pinnacle.h`: platform constants + A-core <-> M-core RPMsg message IDs
- `src/lib_base.h` / `src/lib_base.cpp`: RPMsg transport helpers usable by all modules
- `src/test_runner.h`: platform-agnostic monitor set + RPMsg link status monitor ## FuSa Hook Targets - `watchdog_and_reset_lib`: watchdog channel + cross-domain keepalive behavior
- `functional_safety_lib`: safe-state entry, lockstep health reporting, fault reporting path
- `mcu_interface_lib`: RPMsg channel bring-up and handshake tests
