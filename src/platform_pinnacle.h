/**
 * @file platform_pinnacle.h
 * @brief Pinnacle platform constants for NXP i.MX application core and RT co-processor.
 */

#pragma once

// ---------------------------------------------------------------------------
// CPU - NXP i.MX 8M/9 application core variants
// ---------------------------------------------------------------------------
static constexpr int    PINNACLE_CPU_CORES          = 4;
static constexpr double PINNACLE_CPU_MAX_FREQ_MHZ   = 2200.0;
static constexpr double PINNACLE_CPU_MIN_FREQ_MHZ   = 400.0;
static constexpr double PINNACLE_CPU_TEMP_MAX_C     = 105.0;

// ---------------------------------------------------------------------------
// GPU / NPU
// ---------------------------------------------------------------------------
static constexpr int    PINNACLE_GPU_SHADER_CORES   = 1;
static constexpr double PINNACLE_GPU_MAX_FREQ_MHZ   = 1000.0;
static constexpr double PINNACLE_GPU_MIN_FREQ_MHZ   = 200.0;
static constexpr double PINNACLE_GPU_TEMP_MAX_C     = 105.0;
static constexpr const char* PINNACLE_GPU_DEVFREQ_PATH =
    "/sys/class/devfreq";
static constexpr const char* PINNACLE_GPU_DEVICE_PATH  =
    "/sys/devices/platform";
static constexpr const char* PINNACLE_V3D_DEV_PATH     = "/dev/dri/card0";
static constexpr const char* PINNACLE_V3D_RENDER_PATH  = "/dev/dri/renderD128";

// ---------------------------------------------------------------------------
// Memory
// ---------------------------------------------------------------------------
static constexpr long long PINNACLE_MEM_8GB_BYTES   = 8LL * 1024 * 1024 * 1024;
static constexpr long long PINNACLE_MEM_4GB_BYTES   = 4LL * 1024 * 1024 * 1024;
static constexpr double    PINNACLE_MEM_SPEED_MHZ   = 6400.0;
static constexpr double    PINNACLE_MEM_BW_GBS      = 25.0;
static constexpr int       PINNACLE_MEM_BUS_BITS    = 32;

// ---------------------------------------------------------------------------
// PCIe / USB / Ethernet
// ---------------------------------------------------------------------------
static constexpr int    PINNACLE_PCIE_GEN           = 3;
static constexpr int    PINNACLE_PCIE_LANES         = 1;
static constexpr double PINNACLE_PCIE_BW_GBS        = 1.0;
static constexpr const char* PINNACLE_PCIE_RC_PATH  = "/sys/bus/pci/devices/0000:00:00.0";

static constexpr const char* PINNACLE_XHCI_DRIVER_PATH =
    "/sys/bus/platform/drivers/xhci-hcd";
static constexpr int PINNACLE_USB3_PORT_COUNT       = 2;
static constexpr int PINNACLE_USB2_PORT_COUNT       = 2;

static constexpr const char* PINNACLE_ETH_IFACE      = "eth0";
static constexpr int         PINNACLE_ETH_SPEED_MBPS = 1000;

// ---------------------------------------------------------------------------
// Camera / Display / Audio
// ---------------------------------------------------------------------------
static constexpr const char* PINNACLE_CSI_DEVICE0   = "/dev/video0";
static constexpr const char* PINNACLE_CSI_DEVICE1   = "/dev/video1";
static constexpr const char* PINNACLE_MEDIA_CTL0    = "/dev/media0";
static constexpr const char* PINNACLE_UNICAM_PATH   =
    "/sys/bus/platform/devices/32e20000.csi";

static constexpr const char* PINNACLE_DRM_CARD0     = "/dev/dri/card0";
static constexpr const char* PINNACLE_DRM_CARD1     = "/dev/dri/card1";

static constexpr const char* PINNACLE_I2S_DEVICE    =
    "/sys/bus/platform/devices/30030000.sai";
static constexpr const char* PINNACLE_ALSA_CARDS    = "/proc/asound/cards";

// ---------------------------------------------------------------------------
// Serial / Thermal / GPIO / Storage / Power
// ---------------------------------------------------------------------------
static constexpr const char* PINNACLE_DEBUG_UART    = "/dev/ttyLP0";
static constexpr const char* PINNACLE_UART1         = "/dev/ttyLP1";

static constexpr const char* PINNACLE_THERMAL_CPU_ZONE   = "/sys/class/thermal/thermal_zone0";
static constexpr const char* PINNACLE_THERMAL_SB_ZONE    = "/sys/class/thermal/thermal_zone1";
static constexpr double      PINNACLE_THERMAL_THROTTLE_C = 95.0;
static constexpr double      PINNACLE_THERMAL_SHUTDOWN_C = 105.0;

static constexpr const char* PINNACLE_GPIOCHIP_PATH = "/dev/gpiochip0";
static constexpr int         PINNACLE_GPIO_PIN_COUNT = 32;

static constexpr const char* PINNACLE_MMCBLK_PATH   = "/dev/mmcblk0";
static constexpr const char* PINNACLE_NVME_PATH     = "/dev/nvme0n1";

static constexpr const char* PINNACLE_POWER_SUPPLY_PATH = "/sys/class/power_supply";

// ---------------------------------------------------------------------------
// Optional external accelerators
// ---------------------------------------------------------------------------
static constexpr const char* PINNACLE_HAILO8_PCIE_VENDOR = "1e60";
static constexpr const char* PINNACLE_CORAL_USB_VENDOR   = "18d1";

// ---------------------------------------------------------------------------
// Platform identification
// ---------------------------------------------------------------------------
static constexpr const char* PLATFORM_NAME      = "Pinnacle i.MX";
static constexpr const char* PLATFORM_SOC       = "NXP i.MX 8M/9";
static constexpr const char* PLATFORM_IOBRIDGE  = "NXP i.MX RT / Cortex-M";
static constexpr const char* PINNACLE_DT_MODEL_PATH = "/proc/device-tree/model";

// ---------------------------------------------------------------------------
// RPMsg/OpenAMP message contract for A-core <-> M-core communication
// ---------------------------------------------------------------------------
enum class PinnacleRtMessageId : uint16_t {
    MSG_HEARTBEAT = 0x0001,
    MSG_CPU_STATUS = 0x0010,
    MSG_THERMAL_QUERY = 0x0020,
    MSG_WATCHDOG_KICK = 0x0030,
    MSG_WATCHDOG_CONFIG = 0x0031,
    MSG_SAFE_STATE_REQUEST = 0x0040,
    MSG_SAFE_STATE_ACK = 0x0041,
    MSG_LOCKSTEP_STATUS = 0x0050,
    MSG_ERROR_REPORT = 0x0060,
};

struct PinnacleRtMessageHeader {
    uint16_t message_id;
    uint16_t payload_size;
    uint32_t sequence;
};

static constexpr const char* PINNACLE_RPMSG_PRIMARY_DEV = "/dev/rpmsg0";
static constexpr const char* PINNACLE_RPMSG_CTRL_DEV    = "/dev/rpmsg_ctrl0";
static constexpr const char* PINNACLE_OPENAMP_ENDPOINT  = "pinnacle-hal-rt";
