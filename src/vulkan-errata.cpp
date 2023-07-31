// GENERATED FILE - DO NOT EDIT.
// Generated by scripts/generate.py using data from errata/*.yaml
//
// Copyright 2023 Google LLC
//
// SPDX-License-Identifier: Apache-2.0

#include "vulkan-errata.hpp"

namespace vulkan_errata {

#define VENDOR_AMD 0x1002
#define VENDOR_ARM 0x13B5
#define VENDOR_Broadcom 0x14E4
#define VENDOR_GOOGLE 0x1AE0
#define VENDOR_ImgTec 0x1010
#define VENDOR_Intel 0x8086
#define VENDOR_NVIDIA 0x10DE
#define VENDOR_Qualcomm 0x5143
#define VENDOR_Samsung 0x144D
#define VENDOR_VMWare 0x15ad
#define VENDOR_Apple 0x106B
#define VENDOR_Microsoft 0x1414
#define VENDOR_VirtIO 0x1AF4
#define VENDOR_Vivante 0x10001
#define VENDOR_VeriSilicon 0x10002
#define VENDOR_Kazan 0x10003
#define VENDOR_CodePlay 0x10004
#define VENDOR_Mesa 0x10005
#define VENDOR_PoCL 0x10006

static uint32_t NvidiaProprietaryVersion(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch)
{
    return major << 22 | minor << 14 | subminor << 6 | patch;
}

static uint32_t QualcommProprietaryVersion(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch)
{
    // TODO: find out the correct formula; currently major holds the entire version
    return major;
}

static uint32_t SamsungProprietaryVersion(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch)
{
    // TODO: find out the correct formula; currently major holds the entire version
    return major;
}

static uint32_t ArmProprietaryVersion(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch)
{
    return major << 22 | minor << 12 | patch;
}

static uint32_t IntelOpenSourceMesaVersion(uint32_t major, uint32_t minor, uint32_t subminor, uint32_t patch)
{
    return major << 22 | minor << 12 | subminor;
}

static bool IsDriver(const VkPhysicalDeviceProperties *device,
    const VkPhysicalDeviceDriverProperties *driver,
    VkDriverId driverID,
    uint32_t vendorID)
{
    if (driver != NULL)
    {
        return driver->driverID == driverID;
    }
    return device->vendorID == vendorID;
}

// Given the conformance version that the driver advertises it has passed and the version in which
// the scenario triggering the bug is known to be tested, decide if the driver is affected by the
// bug.  If the driver has passed at least that conformance version, it's assumed that the bug is
// fixed.
static bool CTSVerified(VkConformanceVersion driverVersion, VkConformanceVersion fixedVersion)
{
    if (driverVersion.major > fixedVersion.major) return true;
    if (driverVersion.major < fixedVersion.major) return false;

    if (driverVersion.minor > fixedVersion.minor) return true;
    if (driverVersion.minor < fixedVersion.minor) return false;

    if (driverVersion.subminor > fixedVersion.subminor) return true;
    if (driverVersion.subminor < fixedVersion.subminor) return false;

    return driverVersion.patch >= fixedVersion.patch;
}

VkResult GetKnownIssues(
    Platform platform,
    const VkPhysicalDeviceProperties *device,
    const VkPhysicalDeviceDriverProperties *driver,
    KnownIssues *issues)
{
    if (device == NULL || issues == NULL)
        return VK_ERROR_INITIALIZATION_FAILED;

    // Short names for platform
    const bool isAndroid = platform == vulkan_errata::Platform::Android;
    const bool isChromeOS = platform == vulkan_errata::Platform::ChromeOS;
    const bool isFuchsia = platform == vulkan_errata::Platform::Fuchsia;
    const bool isIOS = platform == vulkan_errata::Platform::IOS;
    const bool isLinux = platform == vulkan_errata::Platform::Linux;
    const bool isMac = platform == vulkan_errata::Platform::Mac;
    const bool isWindows = platform == vulkan_errata::Platform::Windows;
    if (!isAndroid && !isChromeOS && !isFuchsia && !isIOS && !isLinux && !isMac && !isWindows)
        return VK_ERROR_INCOMPATIBLE_DRIVER;

    // Short names for driver
    const bool isNvidiaProprietary = IsDriver(device, driver, VK_DRIVER_ID_NVIDIA_PROPRIETARY, VENDOR_NVIDIA);
    const bool isQualcommProprietary = IsDriver(device, driver, VK_DRIVER_ID_QUALCOMM_PROPRIETARY, VENDOR_Qualcomm);
    const bool isArmProprietary = IsDriver(device, driver, VK_DRIVER_ID_ARM_PROPRIETARY, VENDOR_ARM);
    const bool isIntelOpenSourceMesa = IsDriver(device, driver, VK_DRIVER_ID_INTEL_OPEN_SOURCE_MESA, VENDOR_Intel);
    const bool isSamsungProprietary = IsDriver(device, driver, VK_DRIVER_ID_SAMSUNG_PROPRIETARY, VENDOR_Samsung);
    if (!isNvidiaProprietary && !isQualcommProprietary && !isArmProprietary && !isIntelOpenSourceMesa && !isSamsungProprietary)
        return VK_ERROR_INCOMPATIBLE_DRIVER;


    return VK_SUCCESS;
}

}  // namespace vulkan_errata