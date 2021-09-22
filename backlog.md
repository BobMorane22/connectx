# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

---
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


---
## (XX-XX-XXXX) Title

### Description
Include all details.

### Definition of done
Include all requirements.
