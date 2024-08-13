#!/bin/bash

# --------------------------------------------------------------------------
# FIND AND REPLACE
# --------------------------------------------------------------------------
OLD=::Gtkmm3Gtkmm3
NEW=::Gtkmm3

## Find and replace globally.
## -------------------------------------------------------------------------
#cx -f h   $OLD $NEW
#cx -f cpp $OLD $NEW
#cx -f dox $OLD $NEW
#cx -f in  $OLD $NEW

## Find and replace in specific directory.
## -------------------------------------------------------------------------
TARGET=/home/bob/Programming/connectx/cxuigtkmm3/src

echo "Executing : find -D exec $TARGET -type f -exec sed -i s/"$OLD"/"$NEW"/g {} \;"
find -D exec $TARGET -type f -exec sed -i s/$OLD/$NEW/g {} \;
