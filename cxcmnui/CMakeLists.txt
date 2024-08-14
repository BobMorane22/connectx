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
# CMake configuration file for the cxcmnui library.
#
# @file CMakeLists.txt
# @date 2024
#
#************************************************************************************************/

set(TARGET_NAME cxcmnui)

add_library(${TARGET_NAME}
  src/extractRawUserInput.cpp
  src/KeyboardShortcut.cpp
  src/StatusBarPresenter.cpp
  src/StdActionIcon.cpp
  src/widgetUtilities.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE cxcmn
  PRIVATE cxinv
  PRIVATE cxmath
  PRIVATE cxmodel
)

# Configuration files:
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET_NAME}/ressources.h.in" "${TARGET_NAME}/generated/ressources.h")
target_include_directories(${TARGET_NAME}
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)

# Unit tests:
add_subdirectory(test)
