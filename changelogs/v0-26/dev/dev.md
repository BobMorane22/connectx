# Connect X v0.26 (February 14, 2021)

## Sprint objectives

In the current sprint:

1. Add a way to enable/disable output stream per tests via a fixture.


## Unit testing

### Enabling/disabling stream output on a test-by-test basis

This has been ported to all existing unit tests.

### `DisableStdStreamsRAII` code duplication

Duplication of the `DisableStdStreamsRAII` class has been removed from all
test executables. All of them now use the `cxunit` equivalent or some
variant of the `cxunit::StdStreamsRedirector` fixture.