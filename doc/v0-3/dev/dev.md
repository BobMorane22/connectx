# Connect X v0.3 (December 29, 2019)

## Sprint objectives

In this sprint, there are three main objectives:

1. Import the `cxinv` library from the last project.
2. Add a minimal GUI.
3. Implement the Observer design pattern.


## The `cxinv` library

Three new macros are available to facilitate programming by contract:

* `PRECONDITION(p_predicate)`: method/function precondition.
* `POSTCONDITION(p_predicate)`: method/function post-condition.
* `INVARIANT(p_predicate)`: class invariant.

Furthermore, custom assertions macros are also available:

* `ASSERT(p_predicate)`: assert that `p_predicate` is `true`.
* `ASSERT_MSG(p_predicate, p_message)`: assert that `p_predicate` is `true` and feed a custom error message (`p_message`).
* `ASSERT_ERROR()`: assert that the current state of execution is an error (unconditional errors).
* `ASSERT_ERROR_MSG(p_message)`: assert that the current state of execution is an error (unconditional errors) and feed a custom error message (`p_message`).

All of these macros, when fed a `false` predicate, print an error message to `stdout` by default. If the `ABORT_ON_ERROR` environment variable is `define`d, the program will terminate instead. Furthermore, these macros are all disabled when the `NDEBUG` environment variable is defined (release builds).


## A minimal GUI

See the user documentation [here](../user/user.md).


## The Observer design pattern

Two classes are now available:

* `Subject`: an abstract class to inherit from to define an entity that you can subscribe to for notifications. Note that the abstractness of the class comes from is pure virtual constructor only. We do not want people using `Subject` instances.
* `IObserver`: an interface to inherit from to define entities that can subscribe to a `Subject` instance. These entities can update their state following a notification from the subject.

For more information, see _Design Patterns: Elements of Reusable Object-Oriented Software_ from Erich Gamma & al.


## Next sprint

In the next iteration, we will:

1. add the MVP architecture to the project through a minimal interactivity window;
2. automate the process of running the unit test from the build. Every time a build will be performed, the related unit tests are going to be automatically run. If any one test fail, the build will fail.