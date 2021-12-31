# Connect X v0.19 (November 8, 2020)

## Sprint objectives

In the current sprint:

1. add the win algorithm to the model;
2. silence an assertion when a dialog is created.


## Win algorithm

The old Connect X win algorithm has been ported (as well as all its unit tests) to this code base. The algorithm is the same as before but from an architectural standpoint, it has been made into a `GameResolution` strategy. The idea is to re-use the same abstraction for the tie algorithm that will soon be ported as well.


## Assertion

This feature is documented [here](../user/user.md).
