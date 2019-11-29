#*************************************************************************************************
#  This file is part of Connect X.
#
#  Connect X is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  Connect X is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
#
#************************************************************************************************/

#*************************************************************************************************
# This file is the main Makefile for building and installing Connect X.
#
# @file Makefile
# @date 2019
#
# Mostly, it forwards the work to the top level "Rules.mk" file which is responsible to start the
# recursive include process. This is heavily inspired by Emile van Bergen's excellent 2002 paper
# "Implementing non-recursive make"[1].
#
# Source:
#
#   [1] http://sites.e-advies.nl/nonrecursive-make.html
#
#************************************************************************************************/

### Standard parts
#
SHELL = /bin/sh


### Build flags for all targets
#
#  CF_ALL : Global compiler flags
#  LF_ALL : Global linker flags
#  LL_ALL : Global link libraries
#
CF_ALL          = -std=c++14
LF_ALL          = 
LL_ALL          = 


### Build tools
#
# These variables will be defined for each target, in their respective
# "Rules.mk" file.
#
#  CF_TGT : Target specific compiler flags
#  LF_TGT : Target specific linker flags
#  LL_TGT : Target specific link libraries
#
# Their expansion will recursively happen for each target. We also have the following
# definitions, which are heavily used in included makefile portions:
#
#  COMP     : compile only.
#  LINK     : link only.
#  COMPLINK : compile AND link in a single pass.
#
CXX             = g++
ARCHIVE         = ar rc $@ $^
COMP            = $(CXX) $(CF_ALL) $(CF_TGT) -o $@ -c $<
LINK            = $(CXX) $(LF_ALL) $(LF_TGT) -o $@ $^ $(LL_TGT) $(LL_ALL)
COMPLINK        = $(CXX) $(CF_ALL) $(CF_TGT) $(LF_ALL) $(LF_TGT) -o $@ $< $(LL_TGT) $(LL_ALL)


### Standard parts
#
# This file starts the recursive include process necessary to ensure a non-recursive
# build process.
#
include Rules.mk