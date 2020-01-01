# Connect X v0.4 (January 12, 2020)

## Sprint objectives

In this sprint, there are two main objectives:

1. add minimal user interaction with the application;
2. add automatic testing to the build process.

## Minimal user interaction

This part is described in details [here](../user/user.md). One change was made to the architecture described in [v0.2](../../v0-2/dev/dev.md): The _Presenter_ does not know about anyone (not the _Model_, not the _View_ nor the _Controller_). This is an improvement over what was described earlier since the _Presenter_ classes are more decoupled.


## Automatic testing

Up until now, unit test executables had to be run by hand, for each library (and for the Connect X application). This made it hard to make sure all tests run all the time and that nothing was broken. In this iteration, running the unit tests has been included in the building process. For example, calling

```
> make
```

will not only build all of the libraries and the Connect X executable, but also run all of their associated unit tests executables and display the results to the user. For example, we have the following output for the `cxinv` library:

```
Compiling cxinv/test/DisableStdStreamsRAII.cpp...
g++ -std=c++17 -g -o0 -Wall -Wextra -Wshadow -Wpedantic -pedantic-errors -Werror -Icxinv/test/../include -Icxinv/test -o cxinv/test/DisableStdStreamsRAII.o -c cxinv/test/DisableStdStreamsRAII.cpp
Compiling cxinv/test/HandleAssertTestFixture.cpp...
g++ -std=c++17 -g -o0 -Wall -Wextra -Wshadow -Wpedantic -pedantic-errors -Werror -Icxinv/test/../include -Icxinv/test -o cxinv/test/HandleAssertTestFixture.o -c cxinv/test/HandleAssertTestFixture.cpp
Compiling cxinv/test/handleAssertTests.cpp...
g++ -std=c++17 -g -o0 -Wall -Wextra -Wshadow -Wpedantic -pedantic-errors -Werror -Icxinv/test/../include -Icxinv/test -o cxinv/test/handleAssertTests.o -c cxinv/test/handleAssertTests.cpp
Compiling cxinv/src/assertion.cpp...
g++ -std=c++17 -g -o0 -Wall -Wextra -Wshadow -Wpedantic -pedantic-errors -Werror -Icxinv/include -o cxinv/src/assertion.o -c cxinv/src/assertion.cpp
~~~ Generating the libcxinv.a static library ~~~
ar rc cxinv/libcxinv.a cxinv/src/assertion.o
~~~ Generating the cxinv unit tests executable ~~~
g++   -o cxinv/test/cxinvtests cxinv/test/DisableStdStreamsRAII.o cxinv/test/HandleAssertTestFixture.o cxinv/test/handleAssertTests.o cxinv/libcxinv.a cxinv/libcxinv.a -lgtest -lgtest_main -lpthread 
/bin/sh -c cxinv/test/cxinvtests
Running main() from gtest_main.cc
[==========] Running 11 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 11 tests from HandleAssertTestFixture
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessageAssertion_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessageAssertion_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessagePrecondition_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessagePrecondition_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessagePostcondition_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessagePostcondition_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessageInvariant_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsNoMessageInvariant_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessageAssertion_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessageAssertion_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessagePrecondition_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessagePrecondition_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessagePostcondition_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessagePostcondition_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessageInvariant_ValidMessages
[       OK ] HandleAssertTestFixture.HandleAssert_AllValidInputsWithMessageInvariant_ValidMessages (0 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_invalidConditionExpression_ExecutionAborted
[       OK ] HandleAssertTestFixture.HandleAssert_invalidConditionExpression_ExecutionAborted (95 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_invalidFileName_ExecutionAborted
[       OK ] HandleAssertTestFixture.HandleAssert_invalidFileName_ExecutionAborted (94 ms)
[ RUN      ] HandleAssertTestFixture.HandleAssert_invalidFunctionName_ExecutionAborted
[       OK ] HandleAssertTestFixture.HandleAssert_invalidFunctionName_ExecutionAborted (94 ms)
[----------] 11 tests from HandleAssertTestFixture (283 ms total)

[----------] Global test environment tear-down
[==========] 11 tests from 1 test case ran. (283 ms total)
[  PASSED  ] 11 tests.

```

If any of the tests fail, the whole building process is stopped (make exits). Note that building only a specific library does not include running its associated unit tests. For example, calling

```
> make cxinv/libcxinv.a
```

will not run the `cxinvtests` executable.


## Next sprint

In the next iteration, we will:

1. add undo/redo support to the application;
2. review the Connect X model design (development of the real business rules should start soon).

