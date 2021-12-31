# Connect X v0.16 (September 27, 2020)

## Sprint objectives

In the current sprint:

1. remove `cxmodel::IModel::GetGameInformation()` from the model;
2. offer the possibility to register _n_ players when creating a new game.


## Model interface update

While doing this (should have been simple) refactoring, the `cxmodel::IModel` interface was split into smaller interfaces (one per responsibility). Here is a list of all the interfaces the `cxmodel::Model` class now implements, with a description of their responsibilities:

 - `cxlog::Logger` : logging (e.g. the `--verbose` switch). This interface was already implemented.
 - `cxmodel::Subject` : Subject/Observer notifications. This interface was already implemented.
 - `cxmodel::IVersioning` : Keep track of the model's versioning information.
 - `cxmodel::IUndoRedo` : Global undo/redo (i.e user makes an undo).
 - `cxmodel::IConnectXLimits` : Access model limits (e.g. The maximum number of allowed players). Read only.
 - `cxmodel::IConnectXGameInformation` : Access information about the current state of the game (e.g. is the game, in its current state, a tie?).
 - `cxmodel::IConnectXGameActions` : Make actions on the model (e.g. create a new game).

The splitting of the model into many smaller interfaces make mocking much easier.


## Registering _n_ players

This feature is fully documented [here](../user/user.md).
