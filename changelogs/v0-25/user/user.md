# Connect X v0.25 (January 31, 2021)

## New features

In this iteration:

1. The possibility to undo a disc drop was added.


## Undo the last disc drop

### Undoing a disc drop

When the following conditions are met:

1. a game has been started;
2. one (or more) discs have been dropped,

undoing is unlocked. At this point, a user can go in the `Game->Undo`
menu to undo his last disc drop:

![Undoing in the menu bar](./menu.png)

Alternatively, the user can hit `Ctrl + z` to undo his last disc drop.


### Limitation

For now, undoing can be dangerous, especially if many undoes are necessary.
This is because, for now, redoing a disc drop is not supported. In addition,
at this point, disc drops is the only "undoable" operation.
