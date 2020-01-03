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
# Makefile to build the Connect X code coverage report.
#
# @file Rules.mk
# @date 2020
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
# To the global variable "TGT_BIN", we add the Connect X executable.
#
# To the global variable "CLEAN", we add the files that the rules present here may create,
# i.e. the ones we want deleted by a "make clean" command.
#
# Note that 'find' is not part of the utilities one can use in a Makefile according
# to the GNU Coding style. See
#
#     https://www.gnu.org/prep/standards/standards.html#Utilities-in-Makefiles
#
# for more information.
#
CLEAN := $(CLEAN) $(shell find . -type f -name '*.gcno' -or \
                                 -type f -name '*.gcda' -or \
                                 -type f -name '*.gcov' -or \
                                 -type f -wholename './coverage/*.info' -or \
                                 -type f -wholename './coverage/report/*' -or \
                                 -type d -wholename './coverage/*')


### Local rules
#
# Report is created.
#
.PHONY: coverage
coverage: 
	@echo ~~~ Generating code coverage report ~~~
	$(SHELL) -c ./tools/coverage.sh


### Restoring stack
#
# The stack pointer is "decremented" and the last current directory is restored.
#
-include $(DEPS_$(d))

d := $(dirstack_$(sp))
sp := $(basename $(sp))