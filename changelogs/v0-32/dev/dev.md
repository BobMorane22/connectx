# Connect X v0.32 (December 5, 2021)

## New features

In this iteration:

1. New math library added.
2. Strong type mechanism added.


## Math library

A new library named `cxmath` has been added. Its goal is to hold all mathematical constants,
functions and classes. All of what is included in `cxmath` should have no knowledge of Connect X
itself: it should stay a pure math library (that could be reused elswhere with no modifications).
Its only allowed dependency is the `cxassert` library.


## Strong types

A new class template for creating strong types, `cxstd::StrongType`, has been added to the 
`cxmodel` library. It can be used like this:

```
using StrongInteger = cxstd::StrongType<int, struct StrongIntegerTag>;

// ... later in the code, to retreive the underlying value:

const StrongInteger sInt{0};
const int value = sInt.Get();
```

For types that need specific capacities, the `cxstd::StrongType` can be extended. For example,
if one needs a strong type that defines `==` and `!=` operators, here is how to do it:

```
using StrongInteger = cxstd::StrongType<int, struct StrongIntegerTag, EqualityComparable>;

// ... later in the code, to compare:

const StrongInteger sInt1{0};
const StringInteger sInt2{1};

if(sInt1 == sInt2)
{
    // ...
}
```
