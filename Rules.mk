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
# Starts the recursive include process.
#
# @file Rules.mk
# @date 2019
#
#************************************************************************************************/

### Configurations.
#
# If nothing has been specified when calling 'make' use the debug configuration. This is
# the most typical case when developping.
#
NDEBUG ?= 0

### Standard parts
#
.SUFFIXES:
.SUFFIXES: .cpp .o

all: targets


### Subdirectories, in build order.
#
# These are the lower level directories in which some "Rules.mk" file exist and must
# be handled here to ensure correct build of the target. Note that if these directories
# themselves contain subdirectories with lower level "Rules.mk" files of their own, these
# low level sub-directories must NOT be handled here. They must be handled in their parent
# directory's "Rules.mk" file for the recursive inclusion process to work as expected.
#
dir := cxinv
include $(dir)/Rules.mk

dir := cxlog
include $(dir)/Rules.mk

dir := cxmodel
include $(dir)/Rules.mk

dir := cxgui
include $(dir)/Rules.mk

dir := cxexec
include $(dir)/Rules.mk

dir := connectx
include $(dir)/Rules.mk

# Code coverage
ifeq ($(NDEBUG), 0)
dir := coverage
include $(dir)/Rules.mk
endif


### General directory independent rules
#
%.o: %.cpp
	@echo Compiling $<...
	$(COMP)

%: %.o
	@echo Linking $<...
	$(LINK)

%: %.cpp
	@echo Compiling and linking $<...
	$(COMPLINK)


### Top level rules
#
# The variables "TGT_*" and "CLEAN" may be added to by the makefile fragments in the various
# subdirectories.
#
.PHONY: targets
targets: $(TGT_BIN) $(TGT_SBIN) $(TGT_ETC) $(TGT_LIB)

.PHONY: clean
clean:
	rm -Rf $(CLEAN)

.SECONDARY: $(CLEAN)
