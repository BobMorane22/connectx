# Connect X v0.23 (January 3, 2021)

## Sprint objectives

In the current sprint:

1. Remove duplication in the file `ModelTests.cpp`.


## Duplication removed

The unit tests for the model often rely on the fact that a valid game has been created
and that chips have been dropped. Before v0.23, this boiler plate code was duplicated
for all tests needing it, making the file big and difficult to follow.

With v0.23, a new `ModelTestFixture` class has been added. Its main goal it to automatically
create a valid model for each test and make services available to make repetitive code
go away in the tests. For now, two major services are offered:

 - creation of a new game as a one liner;
 - dropping multiple chips as a one liner.

It is important to use this fixture in the future to avoid polluting the model unit test
file.
