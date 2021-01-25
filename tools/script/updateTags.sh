#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script updates all tags.
#
# @file update_tags.sh
# @date 2021
#
#---------------------------------------------------------------------------------------------------

echo "Updating tag file for : $PWD"
ctags -R . --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++
