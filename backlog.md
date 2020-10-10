# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

## (05-10-2020) Rename model notification contexts

Notification context should represent _completed_ actions. Hence, the items in it should
be renamed to reflect so:

 - CREATE_NEW_GAME : NEW_GAME_CREATED
 - UNDO: LAST_ACTION_UNDOED
 - ...


## (10-10-2020) Add convinience MACROs for if-ASSERT blocks.

The following pattern is often repeated in code, sometimes making the true production
code hard to find:

```
if(!ASSERT(condition)
{
    DoSomething();
}
```

It could be simplified to a call such as:

```
DO_IF_ASSERT_FAILS(condition, DoSomething());
```

The same is true for pre/post conditions.


## (10-10-2020) Simplify complex logging structures

In the `cxmodel`, information is often loggued. This information is more than often pretty complex
and requires some string formatting before the actual logging. This is most usually done with
`std::ostringstream`, which bloat the production code.

There should be some other way to log the information and hide all this useless formatting
information.

Example from `Model.cpp`:

```
const Player& activePlayer = GetActivePlayer();
if(!PRECONDITION(activePlayer.GetChip() == p_chip))
{
    const IChip& activePlayerChip = activePlayer.GetChip();
    std::ostringstream logStream;
    logStream << "Active player's color: (" << activePlayerChip.GetColor().R() << ", "
                                            << activePlayerChip.GetColor().G() << ", "
                                            << activePlayerChip.GetColor().B() << ")";
    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

    logStream.str("");
    logStream << "Dropped disc color: (" << p_chip.GetColor().R() << ", "
                                         << p_chip.GetColor().G() << ", "
                                         << p_chip.GetColor().B() << ")";
    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

    return;
}
```
Here, only the `return;` instruction is really usefull as far as production is concerned.


## (10-10-2020) Remove duplication for model related static constant values

In the code base, the following pieces of information are often duplicated across the code,
often as private constant values:

- No disc
- Invalid players
- etc.

Which is a problem because if the information is changed at one location, it is not changed
everywhere else and bugs may creep in. All these informations should be located in the model
itself and included in a `constant.h` file. All external modules should get these values
directly through the model.
