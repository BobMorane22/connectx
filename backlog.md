# BACKLOG

List of all tasks which should eventually be documented in the project management tool.

## (29-08-2020) `M_PI` not in the standard
Add my own `constexpr` function for this value.

## (29-08-2020) Flicker when changing to the Game View with disc
Create a new game and when clicking on Start, then view flickers (it seems like there
is a big disc which is resized). I think this is due to the resizing hack.

## (29-08-2020) Create script to automatically create documentation template
Every sprint, I have to create the following, in the `doc` directory: 
 doc
  -vX.Y
    - user/user.md
    - dev/dev.md

and copy the sections from the past documentation to each file. I would like for a script
to do this automatically for me:
 - Create the directory structure and the files
 - Populate the files with the appropritate template sections.

## (30-08-2020) Add an architectural boundary between the mode and the OS
For now, these is an `OS.h/Os.cpp` pair of files that handle all OS interractions. In these
files, all code is OS specific (i.e. makes Linux system calls) and therefore is a liability
to the model. All these services should be interfaced and isolated from the model.

## (30-08-2020) Add the possibility to generate coverage for templated headers
For now, it is impossible to get coverage information for the `cxmodel::Color` class. It
is easy to forget to add unit tests for this class.
