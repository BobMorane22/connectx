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

${MAKE} cxinv/libcxinv.a
${MAKE} cxlog/libcxlog.a
${MAKE} cxmodel/libcxmodel.a
${MAKE} cxgui/libcxgui.a
${MAKE} cxexec/libcxexec.a
${MAKE} connectx/connectx
