# Building the Errata

The errata itself is a database specified in `errata/*.yaml` which can be processed as needed.
However, this repository also contains the following autogenerated files:

- `vulkan-errata.h` and `vulkan-errata.c`: pair of header and source files usable by C applications.
- `vulkan-errata.hpp` and `vulkan-errata.cpp`: pair of header and source files usable by C++
  applications.

These files contain helper code that, given the Vulkan device and driver properties, produces a list
of bugs affecting the application.  Applications can use the resulting list to apply workarounds.

This repository does not build the above code as a library.  The application can include and build
these files as preferred.

## Building The Tests

The Vulkan Driver Errata repository comes with unit tests.  This is primarily useful for developers
of this repository.  This is done through a typical cmake build:

```
$ mkdir build && cd build
$ cmake ..
$ make -j
$ ./errata_tests
```
