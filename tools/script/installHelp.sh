#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script is a temporary hack to install documentation files on the host system for Yelp
# to find. It should be replaced by a better solution when TG-182 is completed.
#
# @file installHelp.sh
# @date 2021
#
#---------------------------------------------------------------------------------------------------

TARGET=~/.local/share

if [[ -d "${TARGET}/" ]]
then
    cp -r ./doc/help ${TARGET}
else
    echo "Error: ${TARGET} does not exist."
fi
