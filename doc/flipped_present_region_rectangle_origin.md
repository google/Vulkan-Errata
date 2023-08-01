# The `flipped_present_region_rectangle_origin` Bug

## Description

The `VK_KHR_incremental_present` extension is the Vulkan equivalent of
`EGL_KHR_swap_buffers_with_damage`.  In EGL, the coordinates follow OpenGL's bottom-left origin
convention.  In Vulkan however, the coordinates follow Vulkan's top-left origin convention.

[Issue #2][spec] in the extension specification clarifies this:

> 2) Where is the origin of the VkRectLayerKHR?
>
> RESOLVED: The upper left corner of the presentable image(s) of the swapchain, per the definition of framebuffer coordinates.

On some implementations, the Vulkan implementation uses the EGL convention.

[spec]: https://registry.khronos.org/vulkan/specs/1.3-extensions/html/chap54.html#VK_KHR_incremental_present

## Bug Side Effect

The side effect of this bug is that damage rectangles are flipped in the Y axis, resulting in
incorrect areas of the swapchain being identified as modified.  The actually modified region may not
be updated on the screen as a result.

## Known Workarounds

This bug can be worked around by using `swapchain_height - (offset.y + extent.height)` as `offset.y`
in `VkRectLayerKHR`.
