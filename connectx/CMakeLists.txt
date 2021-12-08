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
# CMake configuration file for the Connect X executable.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

set(TARGET_NAME connectx)

add_executable(${TARGET_NAME}
  main.cpp
)

target_link_libraries(${TARGET_NAME}
  PRIVATE cxinv
  PRIVATE cxlog
  PRIVATE cxmath
  PRIVATE cxmodel
  PRIVATE cxgui
  PRIVATE cxexec
)
