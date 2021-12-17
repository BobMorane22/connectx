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
# CMake related testing facilities.
#
# @file Testing.cmake
# @date 2021
#
#************************************************************************************************/

#*************************************************************************************************
# Generates a unit test executable target for a library.
#
# Example: for some library `foo`, will create a target named `footests`. This target is an
#          executable running all unit tests for `foo`.
#
# This function assumes that the package GTest was imported before use. For more information,
# see the following:
#
#                https://cmake.org/cmake/help/latest/module/FindGTest.html
#
# Parameters:
#
#    p_libName
#        The name of the library to test.
#
#    ARGN
#        A list of dependencies. Inlcude all unit test source files after the `SOURCES` keyword
#        and all library dependencies after the `LIBS` keyword.
#
# Note: This function was inspired by the `add_mytest` function described in Craig Scott in his
#       excellent book "Professional CMake: A Practical Guide", version 1.0.0. See section
#       8.2 on page 70.
#
#*************************************************************************************************
function(add_lib_unit_test p_libName)

  # The supported set of keywords:
  set(prefix DEPENDENCIES)
  set(allDependencies SOURCES LIBS)

  # Needed only for CMake 3.4 and earlier. This is included only to ensure compatibility
  # with earlier CMake versions. In recent versions, it does nothing.
  include(CMakeParseArguments)

  # Parsing the arguments for the dependencies:
  cmake_parse_arguments(${prefix}
                        ""
                        ""
                        "${allDependencies}"
                        ${ARGN}
  )

  set(targetName "${p_libName}tests")
  add_executable(${targetName} ${DEPENDENCIES_SOURCES})

  # Adding include paths for every needed library:
  foreach(lib ${DEPENDENCIES_LIBS})
    target_include_directories(${targetName}
      PRIVATE "${CMAKE_SOURCE_DIR}/${lib}/include"
    )
  endforeach()

  # Linking with GTest and the tested library:
  target_link_libraries(${targetName}
    PRIVATE GTest::GTest
    PRIVATE GTest::Main
    PUBLIC ${p_libName}
  )

  # Linking with any needed library:
  foreach(lib ${DEPENDENCIES_LIBS})
    target_link_libraries(${targetName}
      PRIVATE ${lib}
    )
  endforeach()

  add_test(
    NAME ${targetName}
    COMMAND ${targetName}
  )

endfunction()
