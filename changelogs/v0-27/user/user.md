# Connect X v0.27 (February 28, 2021)

## New features

In this iteration:

1. the current column is not hilighted;
2. a window resizing bug has been fixed.


## Hilighted column

Whenever playing on a larger board, it was difficlult to see exactly
where, for a specific top position, a disc would drop. This often
resulted in innacurate drops. Even if the user can undo his bad drop,
this situation is very frustrating.

For this reason, the active column (the one in which the disc would
drop if the user pressed the _down_ arrow) is now hilighted:

![Column highlighting](./highlight.png)


## Window resizing

When playing a game and coming back to the _New Game_ view (e.g with
the `Game -> New` menu item), the _New Game_ view retained the size
of the _Game_ view. For small boards, this was not such a problem, but
for games with large boards, the _New Game_ view became completely
oversized.

This bug has now been fixed.
