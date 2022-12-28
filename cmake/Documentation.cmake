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

# =================================================================================================
# Setups all options related to the doxyfile.
#
# Note that all these options are specific to Connect X and may need to be reviewed for other
# projects. All options appear in the other they are documented online.
#
# See : https://www.doxygen.nl/manual/config.html
#
# =================================================================================================
macro(setup_doxyfile)

  #--------------------------------------------------------------------------------------------
  # Project related configuration options
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_PROJECT_NAME ${p_projectPrettyName})
  set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
  set(DOXYGEN_MARKDOWN_SUPPORT YES)


  #--------------------------------------------------------------------------------------------
  # Build related configuration options
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_EXTRACT_ALL NO)
  set(DOXYGEN_EXTRACT_LOCAL_CLASSES NO)
  set(DOXYGEN_SHOW_USED_FILES NO)
  set(DOXYGEN_SHOW_FILES NO)


  #--------------------------------------------------------------------------------------------
  # Configuration options related to warning and progress messages
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_WARNINGS YES)
  set(DOXYGEN_WARN_IF_UNDOCUMENTED YES)
  set(DOXYGEN_WARN_IF_DOC_ERROR YES)
  set(DOXYGEN_WARN_IF_INCOMPLETE_DOC YES)
  set(DOXYGEN_WARN_NO_PARAMDOC YES)
  #set(DOXYGEN_WARN_AS_ERROR YES)
  set(DOXYGEN_WARN_LOGFILE ${CMAKE_CURRENT_BINARY_DIR}/doxygen/build.log)


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the input files
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_FILE_PATTERNS
    "*.h"
    "*.cpp"
    "*.dox"
    "*.md"
    "*.png"
  )
  set(DOXYGEN_EXCLUDE_PATTERNS
    "*/src/*"
    "*/test/*"
    "*/build/*"
    "*/changelogs/v*/dev/*"
    "*/tools/*"
    "*/help/*"
    "*/data/*"
    "*backlog.md"
    "*wishlist.md"
  )
  set(DOXYGEN_IMAGE_PATH
    "changelogs/v0-1/user"
    "changelogs/v0-2/user"
    "changelogs/v0-3/user"
    "changelogs/v0-4/user"
    "changelogs/v0-5/user"
    "changelogs/v0-6/user"
    "changelogs/v0-7/user"
    "changelogs/v0-8/user"
    "changelogs/v0-9/user"
    "changelogs/v0-10/user"
    "changelogs/v0-11/user"
    "changelogs/v0-12/user"
    "changelogs/v0-13/user"
    "changelogs/v0-14/user"
    "changelogs/v0-15/user"
    "changelogs/v0-16/user"
    "changelogs/v0-17/user"
    "changelogs/v0-18/user"
    "changelogs/v0-19/user"
    "changelogs/v0-20/user"
    "changelogs/v0-21/user"
    "changelogs/v0-22/user"
    "changelogs/v0-23/user"
    "changelogs/v0-24/user"
    "changelogs/v0-25/user"
    "changelogs/v0-26/user"
    "changelogs/v0-27/user"
    "changelogs/v0-28/user"
    "changelogs/v0-29/user"
    "changelogs/v0-30/user"
    "changelogs/v0-31/user"
    "changelogs/v0-32/user"
    "changelogs/v0-33/user"
    "changelogs/v0-34/user"
  )
  set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "README.md")


  #--------------------------------------------------------------------------------------------
  # Configuration options related to source browsing
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_VERBATIM_HEADERS NO)


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the alphabetical class index
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the HTML output
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_USE_MATHJAX YES)


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the LaTeX output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the RTF output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the man page output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the XML output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the DOCBOOK output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options for the AutoGen Definitions output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to Sqlite3 output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the Perl module output
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the preprocessor
  #--------------------------------------------------------------------------------------------
  set(DOXYGEN_ENABLE_PREPROCESSING YES)


  #--------------------------------------------------------------------------------------------
  # Configuration options related to external references
  #--------------------------------------------------------------------------------------------


  #--------------------------------------------------------------------------------------------
  # Configuration options related to the
  #--------------------------------------------------------------------------------------------


endmacro()

# =================================================================================================
# Adds a target to build Doxygen documentation.
#
# This function will add a target named `p_targetName` to build the Doxygen documentation. It
# only supports HTML output type. The generated documentation will be in the build directory,
# under a directory names `doxygen`.
#
# Notes:
#
#   1. Obviously, Doxygen must be installed for this to work. Also, Dot must be installed
#      as well (see package `graphivz`) to generate the graphs. See:
#
#                 https://cmake.org/cmake/help/latest/module/FindDoxygen.html
#
#      for more information.
#
#   2. The Doxygen documentation generation is not added to ALL with this. The goal is to
#      allow users to build the software, even though they do not have Doxygen installed
#      on their system (which is the typical workflow).
#
# Parameters:
#        p_targetName
#            The target name.
#
#        p_projectPrettyName
#            A string containing the "prettyfied" name of the projet. The project() CMake
#            command seems to only accept project names without spaces. Since this value
#            is used by default by this Doxygen utility, it can lead to the documentation
#            having an ugly projet name. This parameter allows overriding it.
#
# =================================================================================================
function(generate_doxygen_documentation p_targetName p_projectPrettyName)

  # Find the Doxygen package:
  find_package(Doxygen
    REQUIRED dot
  )

  # At this point, Doxygen was found, so we can proceed. We configure the generated doxyfile:
  setup_doxyfile()

  # We add the target:
  doxygen_add_docs(${p_targetName}
    ${CMAKE_SOURCE_DIR}
  )

endfunction()
