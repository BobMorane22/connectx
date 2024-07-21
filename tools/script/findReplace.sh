#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script helps finding and replacing string values at the project level.
#
# Usage:
#
#   > ./findreplace.sh OLD_VALUE NEW_VALUE
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
    echo "Error : no replacement value has been specified."
    return;
fi

if [ -z "$2" ]; then
    echo "Error : no value to replace has been specified."
    return;
fi

oldValue=$1
newValue=$2

cx -f "cpp" "${oldValue}" "${newValue}"
cx -f "cc"  "${oldValue}" "${newValue}"
cx -f "h"   "${oldValue}" "${newValue}"
cx -f "hpp" "${oldValue}" "${newValue}"
cx -f "ipp" "${oldValue}" "${newValue}"
cx -f "dox" "${oldValue}" "${newValue}"
cx -f "txt" "${oldValue}" "${newValue}"
