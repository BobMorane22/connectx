# Connect X v0.28 (Month DD, YYYY)

## New features

In this iteration:

1. The unit test fixture for the win and tie game resolution algorithms was simplified.


## A simplified fixture

The `GameResolutionStrategyTestFixture` unit test fixture has been revised to simplify
the unit testing of the win and tie resolution algorithms. Before this version, this
fixture had very limited features: creating a board, dropping a disc in it, and so on.
Writing a full test for one of these algorithms required many lines of code, most of
which were duplicated. Now, a new functionnality has been added to simplify the process.
With it, unit tests can now be written in next to no line of code.

A new method has been added to the fixture, which has this following signature:

```
[[nodiscard]] bool ValidateGame(const std::vector<cxmodel::Player>& p_playerList,
                                const size_t p_inARowValue,
                                const std::string& p_asciiGame);
```
It takes, as arguments, a list of players, an in-a-row value and an ASCII encoded game.
The ASCII encoded game represents the "story" of a game, in ASCII format. For example,
this is a valid ASCII encoded game, if paired with a valid two players list and a 4
in-a-row value:

```
|    |   |   |   |   |   |   |
|    |   |   |   |   |   |   |
| 7w |   |   |   |   |   |   |
| 5  | 6 |   |   |   |   |   |
| 3  | 4 |   |   |   |   |   |
| 1  | 2 |   |   |   |   |   |
```
This ASCII encoded game could be understood as this: on a 6 (height) by 7 (width) board,
the following sequence of moves occurred:

1. Player A played first at (0, 0)
2. Player B played second at (0, 1)
3. Player A played third at (1, 0)
4. Player B played fourth at (1, 1)
5. Player A played fifth at (2, 0)
6. Player B played sixth at (2, 1)
7. Player A played seventh at (3, 0) and won the game.

The `ValidateGame` method then analyses the game and validates that the scenario is indeed
right (e.g. by playing these moves, player A indeed wins at turn 7). Not that ties can
also be verified by using the `t` mark next to the turn number instead of `w` (win).

In addition, the `ValidateGame` method also checks that the ASCII encoded game makes
sense in the following ways:

- If a turn number is skipped, the validation fails.
- If a turn number exists twice, the validation fails.
- If there are no `w` nor `t` mark, the validation fails.
- If a game contains more than one `t` or `w` mark, the validation fails.
- If a the unique `t` or `w` mark is not located at the last move, the validation fails.

For all these scenarios, a specific message is logged into the unit test report to help
quickly diagnose the problem.

Finally, note that for an ASCCI encoded game, spaced are ignored. This means that the
following is equivalent to the above examples to the eyes of `ValidateGame`:
```
||||||||
||||||||
|7w|||||||
|5|6||||||
|3|4||||||
|1|2||||||
```
Spaces are used only to help readibility.


## Feature 2

Description for feature 2 here...
