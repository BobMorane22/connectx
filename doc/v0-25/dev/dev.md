# Connect X v0.25 (January 31, 2021)

## Sprint objectives

In the current sprint:

1. Create a unit test utilities library.
2. Add a way to enable/disable output stream per tests via a fixture.
3. Automatically build the project and prepare binaries (for all configurations).


## Unit testing

### Unit testing library

A new unit testing library, `cxunit`, has been created. The goal of this library
is to gather all the _Connect X independent_ unit testing tools. For example, the
`DisableStreamRAII` class is a good candidate for this library (in fact, a copy
of it has been added there). However, the particular test fixtures that depend
on any other Connect X related library, such as `cxinv`, `cxmodel` or any other
are _not_ good candidates.


### Enabling/disabling stream output on a test-by-test basis

Up to now, whenever a particular test fixture was added with an instance of the
`DisableStreamRAII` as a member, all output, for any test using the fixture,
was by default redirected. This meant that if a test that did not intend to
redirect its output asserted, there was no sign of it in the terminal. All
tests that did not wish to see their output redirected needed to have special
treatment (duplicated code to re-enable streams).

With this iteration, a new class template has been added (in `cxunit`) to
automate this process: `StdStreamRedirector`. When this file (`StdStreamRedirector.h`)
is included, a macro becomes available which can be used to create a special
fixture for any redirection schemes. For example, let's say you have a test suite
that is composed as follow:

- Ten tests that do not wish to redirect their outputs.
- One test that only wishes to redirect its `STDOUT` output.
- One test that only wishes to redirect its `STDERR` output.
- One test that wishes to redirect all outputs.

Let's assume as well that all these tests use the `MyFixture` test fixture.
Instead of adding a `DisableStreamRAII` member to `MyFixture` (and hence
silencing all the tests), one can now use the `ADD_STREAM_REDIRECTORS` as
follow:

```
class MyFixture : public ::testing:Test
{
};

ADD_STREAM_REDIRECTORS(MyFixture);
```

This will declare four new types:

- `MyFixtureNoStreamRedirector`    : Same as `MyFixture`. I recommend using
                                     `MyFixture` instead. This type was only
                                     added for completeness.
- `MyFixtureStdOutStreamRedirector`: Same as `MyFixture`, but with `STDOUT`
                                     redirected (only).
- `MyFixtureStdErrStreamRedirector`: Same as `MyFixture`, but with `STDERR`
                                     redirected (only).
- `MyFixtureBothStreamsRedirector` : Same as `MyFixture`, bith with both
                                     `STDOUT` and `STDERR` redirected.

These new types can then be used as fixtures in the unit tests to better document
was is redirected and remove duplication (or worst, unwanted redirection).


## Tools

Two new tools have been added: one to automatically prepare the project's binaries
and another to facilitate project wise find and replace.

### Automatically preparing the project's binaries

The `tools/script/distribute.sh` script can be used to automatically generate the
project's binaries (both in debug and release configurations) in an archive. It
can be used as follow:

```
./tools/script/distribute.sh vX.Y
```

where `vX.Y` is the current Connect X release version. When calling this script, the
following will happen (assuming everything builds fine and your system is configured
appropriately):

For both debug and release configurations:

1. Connect X is built (unit tests are run as well)
2. The executable is archived in `connectx_debug.tar.gz` (or alternatively
   `connectx_release.tar.gz`).
3. The archive is moved to a directory called `vX.Y` at the project's root level.

At the end of the process, you should have the following at the project's root level:

```
connectx/
├─vX.Y/
│ ├─ connectx_debug.tar.gz
│ └─ connectx_release.tar.gz
└─...

```


### Project find and replace

Unless using an IDE, finding and replacing at the project level may not be a built in
functionality in your tool. It is my case in Vim, in which I have found no easy way to
globally finding and replacing at the project scope. To facilitate the process, a
script has been written: `tools/script/findReplace.sh`. Assuming you want to replace
every occurrence of `OLD` by `NEW` in the project, you can use the following:

```
./tool/script/findReplace.sh OLD NEW
```

the tool will search all files with the following extensions: `.h`, `.hpp`, `.cpp`, `.cc`,
`.ipp` and perform the substitution.