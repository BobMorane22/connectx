# Connect X v0.6 (February 10, 2020)

## Sprint objectives

In this sprint, there are two objectives:

1. make user actions loggable;
2. add all possible warning options to the build process.


## Make user actions loggable

This new feature is fully documented [here](../user/user.md).


## Warning options

After analysis, I have decided not to add any more warnings. The flags `Wall` and `Wextra` are already enabled and add most wanted warnings. I believe that all other warnings should be added when the need occurs because most of them are very precise.


## Next sprint

In the next sprint, the objectives will be:

1. add a verbose option to the application;
2. create DEBUG and RELEASE build configurations.