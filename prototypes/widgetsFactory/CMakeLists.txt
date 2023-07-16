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
# @file CMakeLists.txt
# @date 2023
#
#************************************************************************************************/

set(TARGET_NAME widgetsFactory)

add_executable(${TARGET_NAME}
  Gtkmm3Button.cpp
  Gtkmm3EditBox.cpp
  Gtkmm3Layout.cpp
  Gtkmm3WidgetsFactory.cpp
  IAbstractWidgetsFactory.cpp
  main.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
  PRIVATE "${GTKMM_INCLUDE_DIRS}"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE ${GTKMM_LIBRARIES}
)
