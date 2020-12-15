# BACKLOG

List of all tasks which should eventually be documented in the project management tool.


## (28-10-2020) Add a way to enable/disable output stream disabling per tests via a fixture

There is no way to enable or disable, for some fixture, the ouput streams. For example, for
a base fixture:

```
class Fixture { /* ... */ };
```
it would be helpful to have a related

```
class QuietFixture : public Fixture
{
    /* Ouptput streams captured. */
    std::string GetStdOutContents() const;
    std::string GetStdErrContents() const;
};
```
Both fixtures could be used exchangably for unit testing, except for the one that require
quieting (or interraction) with the output streams, where `QuietFixture` would be needed.
This would allow not capturing streams for all unit tests when only some require this
special treatment. Capturing all streams is dangerous since it may hide assertions from
showing in the unit test executable report.


## (12-11-2020) Encapsulate the creation of all the cxgui::MainWindow-related windows

The MainWindow now has two child windows:

1. The 'About' window
2. The 'GameResolution' window

all of which are instanciated via `std::make_unique` in the code. Since both these
windows are used solely through their `cxgui::IWindow` interface after creation,
some factory could be used for their creation, which would make them total
abtractions to the MainWindow.

Note that a possible problem with the factory approach is that both windows take
different presenters/controllers as constructor parameters, which might be a
problem.


## (18-11-2020) Centralize duplicated logic in the cxgui::Board class 

In the `cxgui::Board` class, which is a widget, a lot of logic exist. A lot of this
logic are (almost) duplicated loops to change disc colors (which sometimes do not
even come from the presenter, especially in the transparent cases...). All of this
logic becomes confusing to read and errors creep in.

All these loops should be centralized.


## (19-11-2020) After a game resolution with a big grid, the New Game view is oversized

When a game is resolved and that the Game view was bigger than the New Game view, comming
back to the New Game view make the window look oversized.

Steps to reproduce:

1. Create a new game with a 20x20 board
2. Win the game
3. Start a new game

And you will see the oversized window. This is due to the Main Window not being resized
when views are switched from Game to New Game (resize happens from New Game to Game).


## (24-11-2020) Hightlight the current column as players drop chips

For big boards, it can become very hard (almost impossible without touching the screen
for players to see the discs in the column in which they are about to drop their chip.
This is especially true if the game has just started and they are not a lot of dripped
chips. To make it easier for users to know where their chip would land, the column on
which their about to be dropped chip stands should be highlighted.


## (12-12-2020) Centralize mocks

As the application grows, the number of unit tests requiring mocks is growing as well.
More often than not, mocks are simply duplicated (we often don't really care about
their implementations). Whenever a method is added to a model interface, all mocks
depending on this interface have to be updated, which is a pain. It would be nice to
have a common mock class that could be overriden whenever necessary, and that would
serve as a single point to handle when such a scenario arises.



## (XX-XX-XXXX) Title

Description...
