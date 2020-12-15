# Connect X v0.24 (January 17, 2021)

## Sprint objectives

In the current sprint:

1. A complete (early) tie algorithm has been added to the model.


## Early tie

### Difference with a basic tie

An early tie is different that a basic tie in that the tie is detected
_before_ the board has been completely filled, keeping the players from
having to drop disc even though no win is possible.

The bigger the board, the more interesting this becomes.


### Limitation

The original plan was to deliver this algorithm in v0.24, but the existing
unit tests were judged too fragile and incomplete to qualify the algorithm
as reliable. There is no reason for now to believe it is not, but more
testing is needed (and a better way to write tests for these cases).

For now, the algorithm and its tests have been ported to the model, but the
algorithm does not run (except in testing).
