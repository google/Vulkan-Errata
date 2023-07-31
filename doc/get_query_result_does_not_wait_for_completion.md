# The `get_query_result_does_not_wait_for_completion` Bug

## Description

When a submission is made that writes to a query, the `vkGetQueryPoolResults` command can be used
with `VK_QUERY_RESULT_WAIT_BIT` to wait for the query results to be available.

When this call is made before the device is finished processing the commands, on some
implementations this function instead returns `VK_NOT_READY`.  On some other implementations, it
returns incorrect results.

## Bug Side Effect

The side effect of this bug is that the query results are not obtained correctly.  The application's
following calculations that depend on these values would be incorrect.

## Known Workarounds

This bug can be worked around by ensuring that the submission writing to the query is finished
first.  This can be done by waiting on the submissions corresponding fence.
