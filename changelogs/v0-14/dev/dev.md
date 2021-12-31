# Connect X v0.14 (May 31, 2020)

## Sprint objectives

In the current sprint:

1. have `make` always builds the necessary without having to `make clean` first;
2. have the `cxinv::handleAssert` returns a boolean;
3. the status bar does not stick to the bottom of the main window when a view changes.

## Makefiles update

When some piece of code is changed, running `make` now rebuilds the necessary code. This means that from now, when making a change anywhere in the code (even in header files), `Connect X` will be rebuild accordingly.


## `cxinv::HandleAssert` returns a boolean

Now, all of these macros return:

1. `ASSERT`;
2. `PRECONDITION`;
3. `POSTCONDITION`;
4. `INVARIANT`.

For cases 2-3, there is no evidence that returning a boolean is needed. For now, it will be accepted but might be deprecated in the future, unless explicitly needed somewhere.


## Status bar issue

This feature is documented [here](../user/user.md).


## Next sprint

In the next sprint, the objectives will be:

1. add code coverage for the `cxmodel::NewGameInformation` class;
2. add color picking for discs when registering a new user;
3. bug: crash when launching the application outside the source directory.