# Connect X v0.7 (February 23, 2020)

## New features

In this release, a new verbose mode has been introduced.

## Verbose mode

A new `--verbose` switch has been added to make all user actions loggable to the console (standard ouptut to be more precise). You can now start Connect X with this switch and get visual feedback on the user actions:

```
> connectx@doc: ~/connectx$ ./connectx --verbose
2020-02-15T14:04:28.101, DEBUG, cxmodel/src/Model.cpp, Increment, 64, Incremented value.
2020-02-15T14:04:28.803, DEBUG, cxmodel/src/Model.cpp, Increment, 64, Incremented value.
2020-02-15T14:04:29.411, DEBUG, cxmodel/src/Model.cpp, Increment, 64, Incremented value.
2020-02-15T14:04:30.755, DEBUG, cxmodel/src/Model.cpp, Reinitialize, 79, Reinitialized value.
2020-02-15T14:04:31.495, DEBUG, cxmodel/src/Model.cpp, Undo, 91, Last action undoed.
2020-02-15T14:04:32.261, DEBUG, cxmodel/src/Model.cpp, Increment, 64, Incremented value.
2020-02-15T14:04:32.755, DEBUG, cxmodel/src/Model.cpp, Increment, 64, Incremented value.
2020-02-15T14:04:34.700, DEBUG, cxmodel/src/Model.cpp, Reinitialize, 79, Reinitialized value.
2020-02-15T14:04:35.527, DEBUG, cxmodel/src/Model.cpp, Redo, 103, Last action redoed.
2020-02-15T14:04:39.554, DEBUG, cxmodel/src/Model.cpp, Redo, 103, Last action redoed.

```

Notes that if you use this switch in conjunction with either the `--help` or `--version` switch, it will be ignored and the first of the `--help` or `--version` switch will be used instead. For example, the following calls:

```
> connectx@doc: ~/connectx$ ./connectx --verbose --help
> connectx@doc: ~/connectx$ ./connectx --verbose --help --version
> connectx@doc: ~/connectx$ ./connectx --help --verbose --version
> connectx@doc: ~/connectx$ ./connectx --help --version --verbose
```

are equivalent to:

```
> connectx@doc: ~/connectx$ ./connectx --help
```