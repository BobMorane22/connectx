# Connect X v1.1 (March 9, 2023)

## New features

In this iteration:

1. A new `RETURN_IF` macro to simplify validation logic has been added.


## Simplified validation logic

Consider the following functions, both returning early if `SomeCondition()` is
not `true`:

```c++
void Foo()
{
    if(!SomeCondition())
    {
        return;
    }

    // Logic continues...
}

bool Bar()
{
    if(!SomeCondition())
    {
        return false;
    }

    // Logic continues...

    return true;
}
```

The new `RETURN_IF` macro makes this code much simpler by encapsulating the `if`
structure:

```c++
#include <cxstd/helpers.h>

void Foo()
{
    RETURN_IF(!SomeCondition());

    // Logic continues...
}

bool Bar()
{
    RETURN_IF(!SomeCondition(), false);

    // Logic continues...

    return true;
}
```
Note that `RETURN_IF` should be used in valid cases, where an early return does
not cause an assertion to be raised. For these cases, refer to the `IF_CONDITION_NOT_MET`
macro.
