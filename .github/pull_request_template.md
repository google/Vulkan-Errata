## Add <entry name>

Please include a short description of the new entry.
Please read the [contribution guidelines](https://github.com/google/Vulkan-Errata/tree/master/CONTRIBUTING.md)

## Reporter Checklist:

Please ensure the following points are checked:

- [ ] I have reviewed the [license](https://github.com/google/Vulkan-Errata/tree/master/LICENSE)
- [ ] I have reported this bug to the IHV(s) and they have confirmed the bug
  - [ ] Link to bug report: TODO
  - [ ] This bug has been hit by an application (i.e. not only tests)
- [ ] I have created an entry under `errata/<name>.yaml` with as much information as available to me
- [ ] I have added documentation on the bug under `doc/<name>.md`, including issue workaround
- [ ] I have added tests in `tests/tests.cpp` to make sure the bug is detected appropriately

## Reviewer Checklist

Please leave the following items for the reviewer(s) to check:

- [ ] The new `.yaml` files are appropriately licensed
- [ ] The IHV(s) confirm this bug
- [ ] The tests cover both positive and negative cases
- [ ] A CTS issue is added for coverage: TODO link
