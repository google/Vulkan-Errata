# Vulkan Driver Errata

The Vulkan graphics API empowers software to perform a great variety of operations, and developer
ingenuity always finds new ways the API can be used that were not originally foreseen.  While the
[Vulkan Conformance Test Suite][CTS] strives to extensively test Vulkan drivers for correctness, the
shear number of possibilities the API can be used leads to test gaps and unfortunate driver bugs.

This repository documents known driver or platform issues, how they are triggered and how they can
be worked around.  This database of bugs is machine readable and found in the `errata/` directory.
Baked in this directory is also generated C header and source files (under the `src/` directory)
that provide an easy way for applications to know which bugs need to be worked around on the running
device.

Each bug in the errata and its workaround is documented in a separate file under the `doc/`
directory.  The `doc/README.md` file categorizes the bugs to help identify those that are relevant
to a developer's target platforms.

This is not an officially supported Google product.

[CTS]: https://github.com/KhronosGroup/VK-GL-CTS

## Contributing

**Disclaimer:** The Vulkan Driver Errata repository is _not_ meant for reporting driver bugs.  If
you have found a driver bug, please report it directly to the affected vendor(s) for triage.  This
repository is intended to be populated by the hardware vendors themselves and associated partners.

See [CONTRIBUTING.md] for further details.

Use the following links to report bugs to hardware vendors (based on `VkDriverId`):

- `VK_DRIVER_ID_AMD_PROPRIETARY`: https://www.amd.com/en/support/kb/faq/amdbrt
- `VK_DRIVER_ID_AMD_OPEN_SOURCE`: https://amdgpu-install.readthedocs.io/en/latest/install-bugrep.html
- `VK_DRIVER_ID_ARM_PROPRIETARY`: https://community.arm.com/support-forums/f/graphics-gaming-and-vr-forum and https://discord.com/invite/armsoftwaredev
- `VK_DRIVER_ID_BROADCOM_PROPRIETARY`: Use internal partner channels
- `VK_DRIVER_ID_COREAVI_PROPRIETARY`: https://coreavi.com/technical-support/
- `VK_DRIVER_ID_GGP_PROPRIETARY`: Use internal partner channels
- `VK_DRIVER_ID_GOOGLE_SWIFTSHADER`: https://issuetracker.google.com/issues?q=componentid:408190
- `VK_DRIVER_ID_IMAGINATION_PROPRIETARY`: Use internal partner channels
- `VK_DRIVER_ID_INTEL_PROPRIETARY_WINDOWS`: https://www.intel.com/content/www/us/en/support/articles/000005848/graphics.html
- `VK_DRIVER_ID_JUICE_PROPRIETARY`: Use internal partner channels
- `VK_DRIVER_ID_MOLTENVK`: https://github.com/KhronosGroup/MoltenVK/issues
- `VK_DRIVER_ID_NVIDIA_PROPRIETARY`: https://www.nvidia.com/en-us/geforce/forums/support/
- `VK_DRIVER_ID_QUALCOMM_PROPRIETARY`: Use internal partner channels
- `VK_DRIVER_ID_SAMSUNG_PROPRIETARY`: https://developer.samsung.com/issues-and-bugs
- `VK_DRIVER_ID_VERISILICON_PROPRIETARY`: Use internal partner channels
- `VK_DRIVER_ID_*MESA*` (all Mesa drivers): https://gitlab.freedesktop.org/mesa/mesa/-/issues
