# Connect X v0.28 (April 25, 2021)

## New features

In this iteration:

1. Restrictions added when creating new games to avoid _unwinable_ games.


## Unwinable games

Up to now, only the most basic checks were performed when the creation of
a new game was requested. For example, negative values (or even worst,
textual values) were rejected for in-a-row value and such. Validation
against the system's limits were also performed.

However, there exist situations in which all these basic conditions are
met, but for which the creation of a new game does not make sense. For
example, if creating a game with an in-a-row value which is bigger than
both board dimensions, the game cannot be won, and hence makes no sense.
Creating a game with so much players (and an in-a-row value big enough)
so that the minumum amount of moves for the first player to win is
bigger that the number of possible moves on the board is also a nonsense.

Both these conditions are now validated and an appropriate error message
is displayed when they are violated.
