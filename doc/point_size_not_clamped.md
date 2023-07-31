# The `point_size_not_clamped` Bug

## Description

The Vulkan specification [says][spec]:

> The point size is taken from the (potentially clipped) shader built-in `PointSize` written by:
>
> * the geometry shader, if active;
> * the tessellation evaluation shader, if active and no geometry shader is active;
> * the vertex shader, otherwise
>
> and clamped to the implementation-dependent point size range
> `[pointSizeRange[0],pointSizeRange[1]]`.

In the above quote, `pointSizeRange` references `VkPhysicalDeviceLimits::pointSizeRange`.

On some implementations, the above clamping is not done.

[spec]: https://registry.khronos.org/vulkan/specs/1.3-extensions/html/chap28.html#primsrast-points

## Bug Side Effect

The side effect of this bug is that if a shader outputs to the `PointSize` shader built-in with a
value that is outside the range reported in `VkPhysicalDeviceLimits::pointSizeRange`, incorrect
rendering is done for that point only.

## Known Workarounds

This bug can be worked around by making sure that the shader clamps the value written to `PointSize`
with the values retrieved from `VkPhysicalDeviceLimits::pointSizeRange`.
