#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This scripts generates all of the necessary documents for adding a changelog.
#
# Usage: The following:
#
#   > ./generateChangelog.sh vX.Y
#
# will generate the following files under the `doc` directory:
#
#     changelogs
#     ├── ...
#     └── vX-Y
#         ├── user
#         │   └── user.md
#         └── dev
#             └── dev.md
#
# Note that if a vX-Y directory already exists, the script will fail. The `user.md` and `dev.md`
# changelogs will be added generic contents.
#
# @file generateChangelog.sh
# @date 2021
#
#---------------------------------------------------------------------------------------------------

VERSION=$1

MAJOR=${VERSION:1:1}
MINOR=${VERSION:3:3}

CHANGELOGDIR="v${MAJOR}-${MINOR}"

# Abort on error:
set -e

# 1. Check preconditions:
if [[ -d "./changelogs/${CHANGELOGDIR}" ]]
then
    echo "Directory ``./changelogs/${CHANGELOGDIR}`` already exists. Aborting."
    exit 1
else
    echo "Generating changelogs for ${CHANGELOGDIR}..."
fi


# 2. Generate the necessary files and directories:
USERDIR=./changelogs/${CHANGELOGDIR}/user
DEVDIR=./changelogs/${CHANGELOGDIR}/dev

mkdir -p ${USERDIR}
echo "User directory changelog created successfully"

mkdir -p ${DEVDIR}
echo "Dev directory changelog created successfully"

USERCHANGELOG=${USERDIR}/user.md
DEVCHANGELOG=${DEVDIR}/dev.md

touch ${USERCHANGELOG}
echo "User changelog created successfully"

touch ${DEVCHANGELOG}
echo "Dev changelog created successfully"


# 3. Write templates to the changelog files:

## User changelog:
echo "# Connect X v${MAJOR}.${MINOR} (Month DD, YYYY)" >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "## New features"                                 >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "In this iteration:"                              >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "1. Short description of new feature"             >> ${USERCHANGELOG}
echo "2. Another short description"                    >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "## Feature 1"                                    >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "Description for feature 1 here..."               >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "## Feature 2"                                    >> ${USERCHANGELOG}
echo ""                                                >> ${USERCHANGELOG}
echo "Description for feature 2 here..."               >> ${USERCHANGELOG}

## Dev changelog:
echo "# Connect X v${MAJOR}.${MINOR} (Month DD, YYYY)" >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "## New features"                                 >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "In this iteration:"                              >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "1. Short description of new feature"             >> ${DEVCHANGELOG}
echo "2. Another short description"                    >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "## Feature 1"                                    >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "Description for feature 1 here..."               >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "## Feature 2"                                    >> ${DEVCHANGELOG}
echo ""                                                >> ${DEVCHANGELOG}
echo "Description for feature 2 here..."               >> ${DEVCHANGELOG}
