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
# Top level CMake configuration file for Connect X.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

cmake_minimum_required(VERSION 3.20)

project(foo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
  -Wall
  -Wextra
  -Wshadow
  -Wpedantic
  -pedantic-errors
  -Werror
)

# Modules:
include(GNUInstallDirs)

find_package(PkgConfig)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0>=3.24)

# Libraries, in build order:
add_subdirectory(cxinv)
add_subdirectory(cxlog)
add_subdirectory(cxmath)
add_subdirectory(cxmodel)
add_subdirectory(cxgui)
add_subdirectory(cxexec)

# Main Connect X executable:
add_subdirectory(connectx)
