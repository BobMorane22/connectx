#!/bin/bash

# --------------------------------------------------------------------------
# FIND AND REPLACE
# --------------------------------------------------------------------------
OLD=cx::cmn::ui
NEW=cx::cmn::ui::gtkmm3

## Find and replace globally.
## -------------------------------------------------------------------------
#cx -f h   $OLD $NEW
#cx -f cpp $OLD $NEW
#cx -f dox $OLD $NEW
#cx -f in  $OLD $NEW

## Find and replace in specific directory.
## -------------------------------------------------------------------------
TARGET=/home/bob/Programming/connectx/cxcmnuigtkmm3/include/cxcmnuigtkmm3

echo "Executing : find -D exec $TARGET -type f -exec sed -i s/$OLD/$NEW/g {} \;"
find -D exec $TARGET -type f -exec sed -i s/$OLD/$NEW/g {} \;
