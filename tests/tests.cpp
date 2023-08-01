// Copyright 2023 Google LLC
//
// SPDX-License-Identifier: Apache-2.0
//
// This file tests the C interface of the Vulkan Driver Errata.  It's a C++ file nevertheless due to
// the use of gtest.

#include <assert.h>
#include <gtest/gtest.h>
#include <string.h>

#include "../src/vulkan-errata.h"

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

#define DEVICE_unspecified 0
#define DEVICE_Swiftshader 0xC0DE

static uint32_t ArmProprietaryVersion(uint32_t major, uint32_t minor)
{
    return major << 22 | minor << 12;
}

static uint32_t IntelOpenSourceMesaVersion(uint32_t major, uint32_t minor)
{
    return major << 22 | minor << 12;
}

static uint32_t NvidiaProprietaryVersion(uint32_t major, uint32_t minor)
{
    return major << 22 | minor << 14;
}

static uint32_t QualcommProprietaryVersion(uint32_t major, uint32_t minor)
{
    // TODO: find the right formula
    return major;
}

static uint32_t SamsungProprietaryVersion(uint32_t major, uint32_t minor)
{
    // TODO: find the right formula
    return major;
}

static VkPhysicalDeviceProperties MakeDevice(
    uint32_t driverVersion,
    uint32_t vendorID,
    uint32_t deviceID)
{
    return VkPhysicalDeviceProperties{
        .driverVersion = driverVersion,
        .vendorID = vendorID,
        .deviceID = deviceID,
    };
}

static VkPhysicalDeviceDriverProperties MakeDriver(
    VkDriverId driverID,
    const char *driverName,
    const char *driverInfo,
    VkConformanceVersion conformanceVersion)
{
    VkPhysicalDeviceDriverProperties properties = {
        .driverID = driverID,
        .conformanceVersion = conformanceVersion,
    };

    assert(strlen(driverName) < VK_MAX_DRIVER_NAME_SIZE);
    assert(strlen(driverInfo) < VK_MAX_DRIVER_INFO_SIZE);

    strcpy(properties.driverName, driverName);
    strcpy(properties.driverInfo, driverInfo);

    return properties;
}

TEST(Errata, NegativeAPI)
{
    // Device properties must always be provided
    VulkanErrataKnownIssues issues = {};
    VkResult result = vulkanErrataGetKnownIssues(VulkanErrataPlatformLinux, nullptr, nullptr, &issues);
    EXPECT_EQ(result, VK_ERROR_INITIALIZATION_FAILED);

    // The output struct must always be provided
    VkPhysicalDeviceProperties device = MakeDevice(NvidiaProprietaryVersion(400, 0), VENDOR_NVIDIA, DEVICE_unspecified);
    result = vulkanErrataGetKnownIssues(VulkanErrataPlatformLinux, &device, nullptr, nullptr);
    EXPECT_EQ(result, VK_ERROR_INITIALIZATION_FAILED);

    // Bogus platform values should cause a failure
    result = vulkanErrataGetKnownIssues((VulkanErrataPlatform)0x6151, &device, nullptr, &issues);
    EXPECT_EQ(result, VK_ERROR_INCOMPATIBLE_DRIVER);

    // Bogus vendorID values should cause a failure
    device = MakeDevice(NvidiaProprietaryVersion(400, 0), 0x123456, DEVICE_unspecified);
    result = vulkanErrataGetKnownIssues(VulkanErrataPlatformLinux, &device, nullptr, &issues);
    EXPECT_EQ(result, VK_ERROR_INCOMPATIBLE_DRIVER);

    // Bogus driverID values should cause a failure
    device = MakeDevice(NvidiaProprietaryVersion(400, 0), VENDOR_NVIDIA, DEVICE_unspecified);
    VkPhysicalDeviceDriverProperties driver = MakeDriver((VkDriverId)0x99999999, "NVIDIA", "NVIDIA",
            VkConformanceVersion{1, 3, 0, 0});
    result = vulkanErrataGetKnownIssues(VulkanErrataPlatformLinux, &device, &driver, &issues);
    EXPECT_EQ(result, VK_ERROR_INCOMPATIBLE_DRIVER);
}

TEST(Errata, NvidiaProprietary_400)
{
    VkPhysicalDeviceProperties device = MakeDevice(NvidiaProprietaryVersion(400, 0), VENDOR_NVIDIA, DEVICE_unspecified);
    VkPhysicalDeviceDriverProperties driver = MakeDriver(VK_DRIVER_ID_NVIDIA_PROPRIETARY, "NVIDIA", "NVIDIA",
            VkConformanceVersion{1, 3, 0, 0});

    VulkanErrataKnownIssues issues;
    VkResult result = vulkanErrataGetKnownIssues(VulkanErrataPlatformLinux, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_TRUE(issues.get_query_result_does_not_wait_for_completion.affected);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.name, "get_query_result_does_not_wait_for_completion"), 0);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.camelCaseName, "getQueryResultDoesNotWaitForCompletion"), 0);
    EXPECT_NE(strcmp(issues.get_query_result_does_not_wait_for_completion.description, ""), 0);
    EXPECT_NE(strstr(issues.get_query_result_does_not_wait_for_completion.condition, "Nvidia"), nullptr);

    result = vulkanErrataGetKnownIssues(VulkanErrataPlatformWindows, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_TRUE(issues.get_query_result_does_not_wait_for_completion.affected);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.name, "get_query_result_does_not_wait_for_completion"), 0);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.camelCaseName, "getQueryResultDoesNotWaitForCompletion"), 0);
    EXPECT_NE(strcmp(issues.get_query_result_does_not_wait_for_completion.description, ""), 0);
    EXPECT_NE(strstr(issues.get_query_result_does_not_wait_for_completion.condition, "Nvidia"), nullptr);
}

TEST(Errata, NvidiaProprietary_500)
{
    VkPhysicalDeviceProperties device = MakeDevice(NvidiaProprietaryVersion(500, 0), VENDOR_NVIDIA, DEVICE_unspecified);
    VkPhysicalDeviceDriverProperties driver = MakeDriver(VK_DRIVER_ID_NVIDIA_PROPRIETARY, "NVIDIA", "NVIDIA",
            VkConformanceVersion{1, 3, 0, 0});

    VulkanErrataKnownIssues issues;
    VkResult result = vulkanErrataGetKnownIssues(VulkanErrataPlatformLinux, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_FALSE(issues.get_query_result_does_not_wait_for_completion.affected);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.name, "get_query_result_does_not_wait_for_completion"), 0);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.camelCaseName, "getQueryResultDoesNotWaitForCompletion"), 0);
    EXPECT_NE(strcmp(issues.get_query_result_does_not_wait_for_completion.description, ""), 0);
    EXPECT_NE(strstr(issues.get_query_result_does_not_wait_for_completion.condition, "Nvidia"), nullptr);

    result = vulkanErrataGetKnownIssues(VulkanErrataPlatformWindows, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_FALSE(issues.get_query_result_does_not_wait_for_completion.affected);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.name, "get_query_result_does_not_wait_for_completion"), 0);
    EXPECT_EQ(strcmp(issues.get_query_result_does_not_wait_for_completion.camelCaseName, "getQueryResultDoesNotWaitForCompletion"), 0);
    EXPECT_NE(strcmp(issues.get_query_result_does_not_wait_for_completion.description, ""), 0);
    EXPECT_NE(strstr(issues.get_query_result_does_not_wait_for_completion.condition, "Nvidia"), nullptr);
}

TEST(Errata, ArmProprietary_38)
{
    VkPhysicalDeviceProperties device = MakeDevice(ArmProprietaryVersion(38, 0), VENDOR_ARM, DEVICE_unspecified);
    VkPhysicalDeviceDriverProperties driver = MakeDriver(VK_DRIVER_ID_ARM_PROPRIETARY, "ARM", "ARM",
            VkConformanceVersion{1, 3, 6, 0});

    VulkanErrataKnownIssues issues;
    VkResult result = vulkanErrataGetKnownIssues(VulkanErrataPlatformAndroid, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_TRUE(issues.get_query_result_does_not_wait_for_completion.affected);
}

TEST(Errata, ArmProprietary_42)
{
    VkPhysicalDeviceProperties device = MakeDevice(ArmProprietaryVersion(42, 0), VENDOR_ARM, DEVICE_unspecified);
    VkPhysicalDeviceDriverProperties driver = MakeDriver(VK_DRIVER_ID_ARM_PROPRIETARY, "ARM", "ARM",
            VkConformanceVersion{1, 3, 6, 0});

    VulkanErrataKnownIssues issues;
    VkResult result = vulkanErrataGetKnownIssues(VulkanErrataPlatformAndroid, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_TRUE(issues.get_query_result_does_not_wait_for_completion.affected);
}

TEST(Errata, ArmProprietary_43)
{
    VkPhysicalDeviceProperties device = MakeDevice(ArmProprietaryVersion(43, 0), VENDOR_ARM, DEVICE_unspecified);
    VkPhysicalDeviceDriverProperties driver = MakeDriver(VK_DRIVER_ID_ARM_PROPRIETARY, "ARM", "ARM",
            VkConformanceVersion{1, 3, 6, 0});

    VulkanErrataKnownIssues issues;
    VkResult result = vulkanErrataGetKnownIssues(VulkanErrataPlatformAndroid, &device, &driver, &issues);

    ASSERT_EQ(result, VK_SUCCESS);
    EXPECT_TRUE(issues.get_query_result_does_not_wait_for_completion.affected);
}
