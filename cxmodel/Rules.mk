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
# Makefile to build the 'cxmodel' library.
#
# @file Rules.mk
# @date 2019
#
#************************************************************************************************/

### Updating current directory on stack
#
# Saves the variable "d" that holds the current directory on the stack, and sets it to the current
# directory given in "dir" (a parameter to the make fragment file).
#
# A textual "stack pointer" (sp) is used to keep track of the recursion depth of the include
# process. We "increment it" by adding a ".x" suffix to it.
#
sp := $(sp).x
dirstack_$(sp) := $(d)
d := $(dir)


### Subdirectories, in build order.
#
dir := $(d)/test
include $(dir)/Rules.mk


### Local variables
#
# Object files and dependencies are defined here.
#
# To the global variable "CLEAN", we add the files that the rules present here may create,
# i.e. the ones we want deleted by a "make clean" command.
#
OBJS_$(d) := $(d)/src/CommandCreateNewGame.o \
             $(d)/src/CommandStack.o \
             $(d)/src/Disc.o \
             $(d)/src/IChip.o \
             $(d)/src/Model.o \
             $(d)/src/NewGameInformation.o \
             $(d)/src/Player.o \
             $(d)/src/Subject.o \
             $(d)/src/OS.o \
             cxinv/libcxinv.a \
             cxlog/libcxlog.a

# We include all the generated rules. These are created by GCC to make sure that
# changes to header files are recognized by make.
DEPS_$(d) := $(wildcard $(d)/src/*.d)

-include $(DEPS_$(d))

CLEAN := $(CLEAN) $(OBJS_$(d)) $(DEPS_$(d)) \
         $(d)/lib$(d).a


### Local rules
#
# Objects are compiled and archived (static library).
#
# The local include path is added to the local target compiler flags variable "CF_TGT" so that
# includes seem natural within the library. For example, #include <localfile.h> can be used
# instead of having to include the path.
#
$(OBJS_$(d)): CF_TGT := -I. -I$(d)/include
$(TGTS_$(d)): LL_TGT := cxlog/libcxlog.a cxinv/libcxinv.a

$(d)/lib$(d).a: $(OBJS_$(d))
	@echo ~~~ Generating the libcxmodel.a static library ~~~
	$(ARCHIVE)


### Restoring stack
#
# The stack pointer is "decremented" and the last current directory is restored.
#
-include $(DEPS_$(d))
d := $(dirstack_$(sp))
sp := $(basename $(sp))