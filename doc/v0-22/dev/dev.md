# Connect X v0.22 (December 20, 2020)

## Sprint objectives

In the current sprint:

1. convenience macros have been added for `if-ASSERT` blocks.


## new convenience macro

Prior to version 0.22, if a developper wanted to check critical conditions, with
an assertion, for example:

```
if(!ASSERT(condition))
{
    DoSomething();
}
```

such `if` statements were polluting the code base (especially for preconditions and
plain assertions). New macros have been added to make the reading easier for these
case, especially where they are numerous:

- `IF_CONDITION_NOT_MET_DO` (assertion case, like show above)
- `IF_PRECONDITION_NOT_MET_DO` (precondition case)

So the above code could simply be rewritten as:

```
IF_CONDITION_NOT_MET_DO(condition, DoSomething());
```
