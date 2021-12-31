# Connect X v0.7 (February 23, 2020)

## Sprint objectives

In this sprint, there are two objectives:

1. make user actions loggable to the console;
2. make DEBUG and RELEASE builds possible.


## Make user actions loggable to the console

This new feature is fully documented [here](../user/user.md).


## DEBUG and RELEASE builds

We can now activate the two configurations through the `NDEBUG` flag. To build in debug mode:

```
make
```

To build in release mode:
```
make NDEBUG=1
```

When building in release, all possible optimizations are enabled and coverage is deactivated. Note that both release and debug builds will result in the same executable name: `connectx`.


## Next sprint

In the next sprint, the objectives will be:

1. analyze the Connect X application workflow;
2. import the GUID generator script from the previous project;
3. add a status bar to the application.