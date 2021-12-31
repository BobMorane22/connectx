# Connect X v0.8 (March 8, 2020)

## Sprint objectives

In this sprint, there are three objectives:

1. add a status bar to the application;
2. migrate the header guard generator script to the current project;
3. analyze the application user workflow.


## Status bar

This new feature is fully documented [here](../user/user.md).


## Header guard script

The script has been moved to the `tools/script` location. It can be invoked as follow (from root of the project), for a class named "MyClass":

```
./tools/script/gen_guid.sh MyClass
```

which results in:

```
#ifndef MYCLASS_H_2DF26874_85E2_45DE_BE10_C7AB9F694192
#define MYCLASS_H_2DF26874_85E2_45DE_BE10_C7AB9F694192
#endif // MYCLASS_H_2DF26874_85E2_45DE_BE10_C7AB9F694192
```

#  Application user workflow

Moved to another sprint due to lack of time.


## Next sprint

In the next sprint, the objectives will be:

1. analyze the Connect X application workflow;
2. add a menu to the application.
