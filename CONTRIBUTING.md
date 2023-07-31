# Contributing to the Vulkan Driver Errata

**Disclaimer:** The Vulkan Driver Errata repository is _not_ meant for reporting driver bugs.  If
you have found a driver bug, please report it directly to the affected vendor(s) for triage.  This
repository is intended to be populated by the hardware vendors themselves and associated partners.

## Contributing Fixes

If you have ideas for or fixes to the scripts or the generated output, please open an issue or a
pull request.  Anyone is welcome to contribute in this area.

## Contributing to the Errata

If you are contributing to the errata on behalf of an IHV or as a partner, please open a pull
request having done the following:

- One or more entries added to `errata/`
- Run `scripts/generate.py` to update the files under `src/`
- Add tests under `tests/` to make sure the bug is correctly identified as active or not with
  different driver versions.  In most cases, it is sufficient to augment existing tests written for
  bugs affecting the same driver.
- Add a documentation file under `doc/` for each new entry in the errata, using the entry's name as
  file name.  Use `doc/TEMPLATE.md`.
