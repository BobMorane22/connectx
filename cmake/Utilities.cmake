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
# CMake related utilities.
#
# @file Utilities.cmake
# @date 2021
#
#************************************************************************************************/

#*************************************************************************************************
# Creates a directory according to a build phase.
#
# Usage is as follow:
#
#   create_directory_at(<GENERATION|BUILD|INSTALLATIONl> <path_of_new_directory>)
#
# Options are:
#
#  1. GENERATION   : The directory is created when the build system is generated by CMake.
#                    (e.g when `cmake` is called).
#
#  2. BUILD        : The directory is created when the project is build.
#                    (e.g. when `make` is called).
#
#  3. INSTALLATION : The directory is created when the executable is installed.<
#                    (e.g. when `make install` is called).
#
#*************************************************************************************************
function(create_directory_at)

  # Arguments parsing:
  set(prefix ARG)
  set(singleValuesGeneration   GENERATION)
  set(singleValuesBuild        BUILD)
  set(singleValuesInstallation INSTALLATION)
  set(unused)


  # ---------------------------------------------------------------------------------------------
  # Build phase : build system generation.
  # ---------------------------------------------------------------------------------------------
  cmake_parse_arguments(${prefix}
                       "${unused}"
                       "${singleValuesGeneration}"
                       "${unused}"
                       ${ARGN}
  )

  list(GET singleValuesGeneration 0 buildPhase)
  set(targetDirectory ${${prefix}_${buildPhase}})

  if(NOT ${targetDirectory} STREQUAL "")
    file(MAKE_DIRECTORY ${targetDirectory})
    return()
  endif()


  # ---------------------------------------------------------------------------------------------
  # Build phase : sources build.
  # ---------------------------------------------------------------------------------------------
  cmake_parse_arguments(${prefix}
                       "${unused}"
                       "${singleValuesBuild}"
                       "${unused}"
                       ${ARGN}
  )

  list(GET singleValuesBuild 0 buildPhase)
  set(targetDirectory ${${prefix}_${buildPhase}})

  if(NOT ${targetDirectory} STREQUAL "")
    add_custom_target(build-time-make-directory
      ALL
      COMMAND ${CMAKE_COMMAND} -E make_directory ${targetDirectory}
    ) 
    return()
  endif()


  # ---------------------------------------------------------------------------------------------
  # Build phase : software installation.
  # ---------------------------------------------------------------------------------------------
  cmake_parse_arguments(${prefix}
                       "${unused}"
                       "${singleValuesInstallation}"
                       "${unused}"
                       ${ARGN}
  )

  list(GET singleValuesInstallation 0 buildPhase)
  set(targetDirectory ${${prefix}_${buildPhase}})

  if(NOT ${targetDirectory} STREQUAL "")
    install(
      DIRECTORY
      DESTINATION ${targetDirectory}
    )
    return()
  endif()

  message(FATAL_ERROR "Unknown build phase.")

endfunction()
