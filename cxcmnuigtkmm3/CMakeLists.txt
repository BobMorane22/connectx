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
# CMake configuration file for the cxcmnuigtkmm3 library.
#
# @file CMakeLists.txt
# @date 2024
#
#************************************************************************************************/

set(TARGET_NAME cxcmnuigtkmm3)

add_library(${TARGET_NAME}
  src/AbstractWidgetsFactory.cpp
  src/Button.cpp
  src/conversions.cpp
  src/Dialog.cpp
  src/EditBox.cpp
  src/Label.cpp
  src/Layout.cpp
  src/Menu.cpp
  src/MenuBar.cpp
  src/MenuItem.cpp
  src/OnOffSwitch.cpp
  src/SpinBox.cpp
  src/StatusBar.cpp
  src/WidgetDelegate.cpp
  src/Window.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
  PRIVATE "${GTKMM_INCLUDE_DIRS}"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE cxcmn
  PRIVATE cxinv
  PRIVATE cxmath
  PRIVATE cxmodel
  PRIVATE cxcmnui
  PRIVATE ${GTKMM_LIBRARIES}
)
