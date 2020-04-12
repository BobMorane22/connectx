# Connect X v0.11 (April 19, 2020)

## Sprint objectives

In the current sprint:

1. Game view mock added; 
2. Connect X icon added to all windows;
3. test code and header files excluded from the coverage report;
4. The `cxgui::MainWindow` now uses the `cxgui::Window<T>` for its implementation.


## Game view analysis

Here is the mock for the Game view: 

![Game view mock](./game.png)

Players can move the disc using the left/right arrows. The down arrow is used to place a disc in the current column. For now, this vew will be kept simple. Reinitializing the game will be available from the menu only.


## Connect X icon 

This feature is fully described [here](../user/user.md).


## Coverage report updated

It used to be that the coverage report for a library `cxfoo` included in its analysis code in the `cxfoo/include` and `cxfoo/test` directories. The coverage of these directories is almost never useful and only dillutes the interesting coverage. Fot this reason, they have been removed from analysis. Because of this, the coverage has taken a serious hit and is now down below 90%. To have all code covered, a new `cxexec` library has been introduced. It includes everything that was previously in the `cxmain` directory, except for `main.cpp` which now resides in the `connectx` directory, where the executable is built.


## Main window implementation upgrade

The main window now uses the `cxgui::Window<T>` class for its implementation. To acheive this, the realize signal is not used anymore and `cxgui::Window<T>::Init` now needs to be called by hand.


## Next sprint

In the next sprint, the objectives will be:

1. increase the `cxlog` library code coverage;
2. implement the New Game dialog.
