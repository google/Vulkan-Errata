# The `incorrect_dynamic_stencil_write_mask_state` Bug

## Description

When the stencil write mask state is dynamic (`VK_DYNAMIC_STATE_STENCIL_WRITE_MASK`), the static
state provided when creating the pipeline must be ignored.

On some implementations, when the static state is 0, the pipeline is created such that it is unable
to avoid writing to stencil when a pixel is discarded.

## Bug Side Effect

The side effect of this bug is that when a shader discards a fragment, or when alpha-to-coverage is
used, the stencil value is still written to the fragments that were expected to be discarded.

## Known Workarounds

This bug can be worked around by placing any non-zero value in `VkStencilOpState::writeMask` when
creating a pipeline with `VK_DYNAMIC_STATE_STENCIL_WRITE_MASK` (even though that value was supposed
to be ignored).
