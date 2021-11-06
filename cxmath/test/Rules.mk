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
#
#*************************************************************************************************
# @file Rules.mk
# @date 2021
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


### Local variables
#
# To the global variable "TGT_BIN", we add the "cxmath" unit test executable.
#
# To the global variable "CLEAN", we add the files that the rules present here may create,
# i.e. the ones we want deleted by a "make clean" command.
#
TGTS_$(d) := $(d)/cxmathtests
OBJS_$(d) := $(d)/mathTests.o \
             $(d)/PositionTests.o \
             cxunit/libcxunit.a \
             cxmath/libcxmath.a

# We include all the generated rules. These are created by GCC to make sure that
# changes to header files are recognized by make.
DEPS_$(d) := $(wildcard $(d)/*.d)

TGT_BIN := $(TGT_BIN) $(TGTS_$(d))

CLEAN := $(CLEAN) $(OBJS_$(d)) $(TGTS_$(d)) $(DEPS_$(d))


### Local rules
#
# Executable is compiled and linked.
#
$(TGTS_$(d)): CF_TGT := -I$(d)/../include -I$(d) -I.
$(TGTS_$(d)): LL_TGT := cxunit/libcxunit.a cxmath/libcxmath.a cxinv/libcxinv.a -lgtest -lgtest_main -lpthread

$(TGTS_$(d)): $(OBJS_$(d)) $(LL_TGT)
	@echo ~~~ Generating the cxmodel unit tests executable ~~~
	$(LINK)
	$(SHELL) -c $@


### Restoring stack
#
# The stack pointer is "decremented" and the last current directory is restored.
#
-include $(DEPS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))
