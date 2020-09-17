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
# Makefile to build the 'cxgui' library.
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
OBJS_$(d) := $(d)/src/About.o \
             $(d)/src/AboutWindowPresenter.o \
             $(d)/src/Board.o \
             $(d)/src/Chip.o \
             $(d)/src/ColorComboBox.o \
             $(d)/src/DiscChip.o \
             $(d)/src/GameDownKeyHandlerStrategy.o \
             $(d)/src/GameKeyHandlerStrategyFactory.o \
             $(d)/src/GameLeftKeyHandlerStrategy.o \
             $(d)/src/GameRightKeyHandlerStrategy.o \
             $(d)/src/GameView.o \
             $(d)/src/MainWindow.o \
             $(d)/src/MainWindowController.o \
             $(d)/src/MainWindowPresenter.o \
             $(d)/src/MenuItem.o \
             $(d)/src/NewGameView.o \
             $(d)/src/NewPlayerList.o \
             $(d)/src/StatusBar.o \
             $(d)/src/StatusBarPresenter.o \
             cxinv/libcxinv.a \
             cxmodel/libcxmodel.a

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
$(OBJS_$(d)): CF_TGT := -I. -I$(d)/include `pkg-config gtkmm-3.0 --cflags --libs`
$(OBJS_$(d)): LL_TGT := cxinv/libcxinv.a cxmodel/libcxmodel.a

$(d)/lib$(d).a: $(OBJS_$(d))
	@echo ~~~ Generating the libcxgui.a static library ~~~
	$(ARCHIVE)


### Restoring stack
#
# The stack pointer is "decremented" and the last current directory is restored.
#
-include $(DEPS_$(d))
d := $(dirstack_$(sp))
sp := $(basename $(sp))