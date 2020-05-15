# Connect X v0.13 (May 15, 2020)

## Sprint objectives

In the current sprint:

1. Beautify the _New game_ view.
2. Increase the `cxinv` library coverage.
3. Increase the `cxlog` library coverage.


## _New game_ view beautified

This feature is documented [here](../user/user.md).


## `cxinv` coverage

The `cxinv` coverage in the LCOV report is now at 100%. In theory, it was below 90%, but in reality, it always was 100%. Why wasn't that reported by LCOV? Because `cxinv` makes use of `ASSERT_DEATH` macros in its unit tests, to test cases where bad arguments are given to `cxinv::handleAssert`. In these cases, `std::abort` is called unconditionally, and this is correct (if there is a problem there, there is no point in going further). All cases are covered, but these tests are not reported by LCOV because another executable is created when these death assertion macros are used.

To get 100% coverage in the report, the following flags were added (as comments) to the source code that is not analyzed by LCOV:

* `LCOV_EXCL_LINE` : Lines containing this marker will be excluded.
* `LCOV_EXCL_START`: Marks the beginning of an excluded section. The current line is part of this section.
* `LCOV_EXCL_STOP` : Marks the end of an excluded section. The current line not part of this section.

As indicated, they can disable analysis for marked lines.


## `cxlog` coverage

The code coverage for the `cxlog` library is now 94.5%. Some tests were added, and unreachable code was removed from analysis with the same strategy that was previously described for `cxinv`.



## Next sprint

In the next sprint, the objectives will be:

1. have `make` always builds the necessary without having to `make clean` first;
2. have the `cxinv::handleAssert` returns a boolean;
3. the status bar does not stick to the bottom of the main window when a view changes.