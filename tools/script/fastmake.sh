#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This scripts makes only the necessary targets to build the Connect X executable. Unit tests
# executable and coverage reports are therefore excluded.
#
# @file fastmake.sh
# @date 2020
#
#---------------------------------------------------------------------------------------------------

MAKE=make

${MAKE} NDEBUG=1 cxinv/libcxinv.a
${MAKE} NDEBUG=1 cxlog/libcxlog.a
${MAKE} NDEBUG=1 cxmodel/libcxmodel.a
${MAKE} NDEBUG=1 cxgui/libcxgui.a
${MAKE} NDEBUG=1 cxexec/libcxexec.a
${MAKE} NDEBUG=1 connectx/connectx
