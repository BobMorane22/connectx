#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script helps finding and replacing string values at the project level.
#
# Usage:
#
#   > ./findreplace.sh NEW_VALUE OLD_VALUE
#
# After which every occurence of 'OLD_VALUE' in the projet will have been replaced by 'NEW_VALUE'.
# Search and replacement will only work for the following file types: cpp, cc, h, hpp and ipp. For
# other file types, you should not use this script.
#
# @file findreplace.sh
# @date 2021
#
#---------------------------------------------------------------------------------------------------

if [ -z "$1" ]; then
    echo "Error : mo replacement value has been specified."
    return;
fi

if [ -z "$2" ]; then
    echo "Error : no value to replace has been specified."
    return;
fi

oldValue=$1
newValue=$2

find . -name *.cpp | xargs sed -i "s/${oldValue}/${newValue}/"
find . -name *.cc | xargs sed -i "s/${oldValue}/${newValue}/"
find . -name *.h | xargs sed -i "s/${oldValue}/${newValue}/"
find . -name *.hpp | xargs sed -i "s/${oldValue}/${newValue}/"
find . -name *.ipp | xargs sed -i "s/${oldValue}/${newValue}/"
