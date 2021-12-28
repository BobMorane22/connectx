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
# CMake documentation related utilities.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

# =================================================================================================
# Installs Yelp compatible user documentation.
#
# This functions assumes the following project structure with respect to the help files:
#
#    [ROOT]
#      │
#      ├── help
#      │    └── C
#      │        ├── All help files... (*.page)
#      │        └── figures
#      │               └──  All help media...
#      └── ...
# 
# It this the user's reponsibility to make sure the installation path is valid and also visible
# by Yelp. Yelp looks in the 'help' subdirectory in the directories in `XDG_DATA_HOME` and
# `$XDG_DATA_DIRS` from the XDG base directory specification.
#
# Example:
#
#   The following show how to installs both `index.page` and `my_other_file.page` under
#   `${CMAKE_INSTALL_PREFIX}/share/help/C/appName` and `icon.png` and `example.png`
#   under `${CMAKE_INSTALL_PREFIX}/share/help/C/appName/figures`.
#
#      install_user_help(
#        ${CMAKE_INSTALL_PREFIX}/share/help/C/appName
#        PAGE index.page my_other_file.page
#        MEDIA icon.png example.png
#      )
#
# Parameters:
#
#    p_installDir
#        The directory under which to install help files.
#
#    ARGN
#        A list of help files and media. Include all help file names after the `PAGE` keyword,
#        and all help media files after the `MEDIA` keyword.
#
# Note: This function was inspired by the evolution mail client Cmake code, available here:
#
#          https://gitlab.gnome.org/GNOME/evolution/-/blob/master/help/CMakeLists.txt
#
# =================================================================================================
function(install_user_help p_installDir)

  # The supported set of keywords:
  set(prefix HELP_FILES)
  set(allHelpSourceFiles PAGE MEDIA)

  # Needed only for CMake 3.4 and earlier. This is included only to ensure compatibility
  # with earlier CMake versions. In recent versions, it does nothing.
  include(CMakeParseArguments)

  # Parsing the arguments for the help source files:
  cmake_parse_arguments(${prefix}
                        ""
                        ""
                        "${allHelpSourceFiles}"
                        ${ARGN}
  )

  add_custom_target(help-files ALL)
  
  # First, we install the actual help files:
  set(helpFilesToInstall)
  foreach(helpFile ${HELP_FILES_PAGE})
    list(APPEND helpFilesToInstall "${CMAKE_CURRENT_SOURCE_DIR}/C/${helpFile}")
  endforeach()
  
  install(
    FILES ${helpFilesToInstall}
    DESTINATION ${p_installDir}
  )
  
  # Then, we install the help media files:
  set(helpMediaFilesToInstall)
  foreach(helpMediaFile ${HELP_FILES_MEDIA})
    list(APPEND helpMediaFilesToInstall "${CMAKE_CURRENT_SOURCE_DIR}/C/figures/${helpMediaFile}")
  endforeach()
  
  install(
    FILES ${helpMediaFilesToInstall}
    DESTINATION ${p_installDir}/figures
  )

endfunction()
