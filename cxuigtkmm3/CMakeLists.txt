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
# CMake configuration file for the cxuigtkmm3 library.
#
# @file CMakeLists.txt
# @date 2024
#
#************************************************************************************************/

set(TARGET_NAME cxuigtkmm3)

add_library(${TARGET_NAME}
  src/Gtkmm3AboutWindow.cpp
  src/Gtkmm3AbstractConnectXWidgetsFactory.cpp
  src/Gtkmm3AnimatedBoard.cpp
  src/Gtkmm3AnimatedBoardTimerRAII.cpp
  src/Gtkmm3BoardElementCache.cpp
  src/Gtkmm3Chip.cpp
  src/Gtkmm3ColorPicker.cpp
  src/Gtkmm3ContextRestoreRAII.cpp
  src/Gtkmm3DiscChip.cpp
  src/Gtkmm3GameResolutionDialog.cpp
  src/Gtkmm3GameView.cpp
  src/Gtkmm3MainWindow.cpp
  src/Gtkmm3NewGameView.cpp
  src/Gtkmm3NewPlayersList.cpp
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
  PRIVATE cxuicmn
  PRIVATE cxui
  PRIVATE cxuicmngtkmm3
  PRIVATE ${GTKMM_LIBRARIES}
)
