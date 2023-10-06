# The Vulkan Driver Errata Database

The `*.yaml` files in this directory together contain a database of known issues in Vulkan drivers
and platforms.  Each issue is given a name, a short description, conditions under
which they occur, as well as:

 * Category: A tag that categorizes bugs by how they manifest:
   * `rendering`: The bug results in rendering artifacts.
   * `crash`: The bug results in a crash.
   * `performance`: The bug results in degraded performance.

 * Severity: How severe the effects of the bug are:
   * `low`: the bug is rarely triggered or the effects are small.
   * `high`: the side effects of the bug are too severe to ignore.

The format of each entry is:

```
name:
  description: >
    Brief description of what the issue is. Limit to one or two sentences.
  category: rendering|crash|performance
  severity: high|low
  affected:
    - driver: VK_DRIVER_ID_...
    - device: device
    - platform: Android|ChromeOS|Fuchsia|IOS|Linux|Mac|Windows
    - version_start: N (or A.B, A.B.C, A.B.C.D)
    - version_fixed: N (or A.B, A.B.C, A.B.C.D)
  cts_enforced: A.B.C
```

In the above:

 * `driver` is optional; some bugs affect a platform regardless of driver
 * `device` is optional; some bugs only affect certain devices.  This is a
   list of substrings of VkPhysicalDeviceProperties::deviceName.  If this field
   is present, the `driver` field should also be present
 * `platform` is optional; some bugs affect a driver regardless of platform
 * `version_start` and `version_fixed` are optional, but if present `driver`
   must also be present.  The version values are driver dependent.
 * `cts_enforced` is optional; if present, a bug is assumed fixed (regardless
   of platform, version range etc) if the driver advertises that it passes the
   CTS with the given version
