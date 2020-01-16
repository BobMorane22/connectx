# Connect X v0.5 (January 26, 2020)

## New features

Some user actions can now be undoed and redoed.


## Undo/Redo

Some user actions can now be undoed and redoed through undo and redo buttons on the UI.

![Undo and redo buttons](./undoredo.png)

For example, if a user incremented the value one too many times, he or she can click _Undo_ and the value will come back to its last value. Visually, it will look as if if were decremented by one.

![Undo and redo buttons](./undo.png)

Similarly, the user can then click _Redo_ to put the value back at the same state it was before _Undo_ was clicked.

![Undo and redo buttons](./redo.png)

Note that some actions cannot be undoed or redoed. For example, scaling the window is one such action.