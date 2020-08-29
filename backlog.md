# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

## `M_PI` not in the standard
Add my own `constexpr` function for this value.

## Flicker when changing to the Game View with disc
Create a new game and when clicking on Start, then view flickers (it seems like there
is a big disc which is resized). I think this is due to the resizing hack.

## Create script to automatically create documentation template
Every sprint, I have to create the following, in the `doc` directory: 
 doc
  -vX.Y
    - user/user.md
    - dev/dev.md

and copy the sections from the past documentation to each file. I would like for a script
to do this automatically for me:
 - Create the directory structure and the files
 - Populate the files with the appropritate template sections.
