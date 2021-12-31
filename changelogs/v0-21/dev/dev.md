# Connect X v0.21 (December 6, 2020)

## Sprint objectives

In the current sprint:

1. convenience MACROs have been added to check pointers;
2. a new class to carry operation's completion status and error messages has been added.


## Checking pointers

Prior to v0.21, checking for pointers (especially smart pointers) for `nullptr` was very verbose. For example:

```
std::unique_ptr<MyType> pointer = std::make_unique<MyType>();
if(!ASSERT(pointer != nullptr))
{
    // Handle nullptr case...
}
```

Now, overloads of `cxinv::handleAssert` for `std::unique_ptr<T>` and `std::shared_ptr<T>` have been added, making
the following code legal:

```
std::unique_ptr<MyType> pointer = std::make_unique<MyType>();
if(!ASSERT(pointer))
{
    // Handle nullptr case...
}
```

This is available for `PRECONDITION`, `POSTCONDITION`, `INVARIANT` and of course, `ASSERT` variants.


## Checking the completion status of an operation

A recurring problem in the code is to management of error messages when operations fail. For example, if you have
an operation which may fail in a presenter, it will look something like this (prior to this):

```
class IPresenter
{
public:

    virtual std::string GetSomeOperationErrorMessage() const = 0;
    virtual bool SomeOperation() = 0;
}
```

The `bool` returned value can be checked for failure/success. If 

```
if(!presenter.SomeOperation())
{
    const std::string errorMessage = presenter.GetSomeOperationErrorMessage();
    
    // Do something with the error message...
}
else
{
    // No error, all is good.
}
```

This means that for every operation that may fail, there should be at least one other method in the presenter to get
the specific error message associated with the operation. The clutters the presenter's interface, as well as the unit
tests associated with the presenter. To solve this, a new `Status` class has been added to the `cxmodel` library. A
status is, in essence, an operation return value (a `bool`) and, possibly, an error message. The class can be used
through two convenience functions:

```
cxmodel::Status MakeSuccess();
cxmodel::Status MakeError(const std::string& p_errorMessage);
```

With these, the presenter's interface becomes:

```
class IPresenter
{
public:

    virtual cxmodel::Status SomeOperation() = 0;
}
```

and usage:

```
const cxmodel::Status status = presenter.SomeOperation();
if(!status.IsSuccess())
{
    const std::string errorMessage = status.GetMessage();
    
    // Do something with the error message...
}
else
{
    // No error, all is good.
}
```

Which is way cleaner.
