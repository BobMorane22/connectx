#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script distributes binaries of the Connect X application. When executed the script will
# create two archives:
#
#  - Release : a release archive, for users.
#  - Debug   : a debug archive, for developpers.
#
# Parameters:
#
#  $1 : The version number (e.g. vX.Y)
#
# @file distribute.sh
# @date 2020
#
#---------------------------------------------------------------------------------------------------

# Parameters:
VERSION=$1

# Globals:
RELEASE="release"
DEBUG="debug"

SUCCESS=0
ERROR_PRECONDITION=1
ERROR_UNKNOWN_TARGET=2
ERROR_CLEANING=3
ERROR_BUILDING=4
ERROR_ARCHIVING=5
ERROR_CREATING_ARCHIVE_LOCATION_DIRECTORY=6
ERROR_MOVING_ARCHIVE=7

MESSAGE_MAP[SUCCESS]="Successfully distributed Connect X"
MESSAGE_MAP[ERROR_PRECONDITION]="Precondition violation"
MESSAGE_MAP[ERROR_UNKNOWN_TARGET]="Unknown target"
MESSAGE_MAP[ERROR_CLEANING]="Unable to clean"
MESSAGE_MAP[ERROR_BUILDING]="Unable to build"
MESSAGE_MAP[ERROR_ARCHIVING]="Unable to archive"
MESSAGE_MAP[ERROR_CREATING_ARCHIVE_LOCATION_DIRECTORY]="Unable to create the archive location directory"
MESSAGE_MAP[ERROR_MOVING_ARCHIVE]="Unable to move archive to its location directory"

# Paths:
ROOT="./connectx"
EXEC="${ROOT}/connectx"
ICONS="${ROOT}/icons"

#---------------------------------------------------------------------------------------------------
# Distributes Connect X according to a specific arg.
#   
# Parameters:
#  
#  $1 : The arg ("debug" or "release"), see above.
#
# Returns:
#
#  0     : success.
#  other : failure.
#
#---------------------------------------------------------------------------------------------------
function Distribute(){
    local arg=$1

    # Preconditions:
    if [[ $arg != ${RELEASE} && $arg != ${DEBUG} ]]; then
        return ${ERROR_PRECONDITION}
    else
        # There are three phases that are nedded to distribute the Connect X executable:
        #
        #  1. Building Connect X.
        #  2. Making the appropriate archive.
        #  3. Moving the archive to the archive location.
        #

        # 1. Building Connect X:
        local target
        if [[ $arg == ${RELEASE} ]]; then
            target="NDEBUG=1"
        elif [[ $arg == ${DEBUG} ]]; then
            target="NDEBUG=0"
        else
            return ${ERROR_UNKNOWN_TARGET}
        fi

        make clean || return ${ERROR_CLEANING}
        make -j8 ${target} || return ${ERROR_BUILDING}

        # 2. Making the appropriate archive:
        archive=connectx_${arg}.tar.gz
        tar -czvf ${ROOT}/${archive} ${EXEC} ${ICONS} || return ${ERROR_ARCHIVING}

        # 3. Moving the archive to the archive location.
        mkdir -p ${ROOT}/${VERSION} || return ${ERROR_CREATING_ARCHIVE_LOCATION_DIRECTORY}
        mv ${ROOT}/${archive} ${ROOT}/${VERSION}/${archive} || return ${ERROR_MOVING_ARCHIVE}
    fi

    return ${SUCCESS}
}

#---------------------------------------------------------------------------------------------------
# Distributes Connect X (release build). 
#
#---------------------------------------------------------------------------------------------------
function DistributeRelease(){
    Distribute ${RELEASE}
    if [[ $? == ${SUCCESS} ]]; then
        echo "Successfully distributed Connect X (${RELEASE})."
    else
        echo "Error while distributing Connect X (${RELEASE}): ${MESSAGE_MAP[$?]}, aborting."
    fi
}

#---------------------------------------------------------------------------------------------------
# Distributes Connect X (debug build). 
#
#---------------------------------------------------------------------------------------------------
function DistributeDebug(){
    Distribute ${DEBUG}
    if [[ $? == ${SUCCESS} ]]; then
        echo "Successfully distributed Connect X (${DEBUG})."
    else
        echo "Error while distributing Connect X (${DEBUG}): ${MESSAGE_MAP[$?]}, aborting."
    fi
}

# The actual script:
DistributeDebug
DistributeRelease
