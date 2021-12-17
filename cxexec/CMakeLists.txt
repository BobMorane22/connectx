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
# CMake configuration file for the cxexec library.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/
set(TARGET_NAME cxexec)

add_library(${TARGET_NAME}
  src/Application.cpp
  src/CmdArgHelpStrategy.cpp
  src/CmdArgInvalidStrategy.cpp
  src/CmdArgMainStrategy.cpp
  src/CmdArgNoStrategy.cpp
  src/CmdArgVerboseStrategy.cpp
  src/CmdArgVersionStrategy.cpp
  src/CmdArgWorkflowFactory.cpp
  src/GtkmmUIManager.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
  PRIVATE "${GTKMM_INCLUDE_DIRS}"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE cxinv
  PRIVATE cxlog
  PRIVATE cxmodel
  PRIVATE cxgui
  PRIVATE ${GTKMM_LIBRARIES}
)

# Unit tests:
add_subdirectory(test)
