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
# CMake configuration file for the cxmodel library.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

set(TARGET_NAME cxmodel)

add_library(${TARGET_NAME}
  src/Board.cpp
  src/ChipColor.cpp
  src/CommandCreateNewGame.cpp
  src/CommandDropChip.cpp
  src/CommandStack.cpp
  src/Disc.cpp
  src/GameResolutionStrategyFactory.cpp
  src/IBoard.cpp
  src/IChip.cpp
  src/Model.cpp
  src/NewGameInformation.cpp
  src/OS.cpp
  src/Player.cpp
  src/Status.cpp
  src/TieGameResolutionStrategy.cpp
  src/WinGameResolutionStragegy.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE cxinv
  PRIVATE cxlog
  PRIVATE cxmath
)

# Unit tests:
add_subdirectory(test)
