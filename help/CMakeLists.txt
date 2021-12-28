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
# CMake configuration file for user help.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

set(HELP_ID ${PROJECT_NAME})

set(HELP_FILES
  cmd-arg.page
  game.page
  getting-started.page
  index.page
  keyboard_shortcuts.page
  license.page
  new-game.page
)

set(HELP_MEDIA
  connectx.png
)

install_user_help(
  ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/help/C/${HELP_ID}
  PAGE ${HELP_FILES}
  MEDIA ${HELP_MEDIA}
)
