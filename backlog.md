# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

---------------------------------------------------------------------------------------------------
## (30-11-2021) BUG - Crash when creating a new game after undo.

### Description
Steps to reproduce:
 - Start a two player game.
 - Make one chip drop.
 - Undo it.
 - Start a new game.
 - Drop another chip.
 - Often, the program crashes.

There seems to be something wrong with the key handler enabling/disabling
mechanism when an undo is done. When undoing, key combinations can occur
(as if nothing was ever disabled when animating). Also, when the program
crashed, I often get this assertion:

```
ssertion failed at cxgui/src/GameView.cpp: line 304.
  Function   : DisableKeyHandlers
  Expression : m_parent
```

### Definition of done

 - The program no longer crashes.
 - After an undo/redo, keys are properly handled (when an animation
   is playing, they are deactivated).
 - Connect X works as expected.
 - All unit tests pass.


---------------------------------------------------------------------------------------------------
## (30-11-2021) BUG - Assertions when winning a game with a full column

### Description
Steps to reproduce:

 - Start a two players game.
 - Fill up the first column until it is no more possible to drop
   a chip in it.
 - Win the game.
 - When the game resolution dialog appears, the two assertions
   are loggued to the console.

These assertions are:

```
Assertion failed at cxgui/src/AnimatedBoard.cpp: line 592.
  Function   : GetDropPosition
  Expression : false
  Message    : Column unavailable. Check of availability first

Assertion failed at cxgui/src/AnimatedBoard.cpp: line 592.
  Function   : GetDropPosition
  Expression : false
  Message    : Column unavailable. Check of availability first
```

### Definition of done
 - Assertions are gone.
 - Connect X works as expected.
 - All unit tests pass.


---------------------------------------------------------------------------------------------------
## (21-09-2021) : Add a custom set_source_rbga clone with cxmodel::Color

### Description
In some parts of the code, the `Cairo::Context::set_source_rgba` method is used to
set the RGBA components of the context's source. This method takes 4 `double`s, which
is not compatible with `cxmodel::Color`. Calls to nomalization functions must be
added for the code to compile. For example:

```c++
    const cxmodel::IChip& chip = m_model.GetChip(p_row, p_column);
    const cxmodel::ChipColor chipColor = chip.GetColor();
    
    // ...
    
    cxgui::ContextRestoreRAII contextRestoreRAII{bufferContext};
    
    cxgui::MakeCircularPath(bufferContext, {cellWidth / 2.0, cellHeight / 2.0}, radius);
    
    bufferContext->set_source_rgba(cxmodel::NormalizedR(chipColor),
                                   cxmodel::NormalizedG(chipColor),
                                   cxmodel::NormalizedB(chipColor),
                                   cxmodel::NormalizedA(chipColor));
```

These ugly and crowded calls should be replaced by an encapsulated call
like this:

```c++
    const cxmodel::IChip& chip = m_model.GetChip(p_row, p_column);
    const cxmodel::ChipColor chipColor = chip.GetColor();
    
    // ...
    
    cxgui::ContextRestoreRAII contextRestoreRAII{bufferContext};
    
    cxgui::MakeCircularPath(bufferContext, {cellWidth / 2.0, cellHeight / 2.0}, radius);
    
    cxgui::set_source_color(bufferContext, chipColor);
```

### Definition of done
- The new call is added.
- All existing calls are replaced.
- Connect X runs as before.


---------------------------------------------------------------------------------------------------
## (XX-XX-XXXX) Title

### Description
Include all details.

### Definition of done
Include all requirements.
