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
# CMake configuration file for the cxgui library.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

set(TARGET_NAME cxgui)

add_library(${TARGET_NAME}
  src/About.cpp
  src/AboutWindowPresenter.cpp
  src/AnimatedBoard.cpp
  src/AnimatedBoardModel.cpp
  src/AnimatedBoardPresenter.cpp
  src/BoardElementCache.cpp
  src/Chip.cpp
  src/ColorComboBox.cpp
  src/ContextRestoreRAII.cpp
  src/Dimensions.cpp
  src/DiscChip.cpp
  src/extractRawUserInput.cpp
  src/GameResolutionDialogController.cpp
  src/GameResolutionDialog.cpp
  src/GameResolutionDialogPresenterFactory.cpp
  src/GameView.cpp
  src/GameViewDownKeyHandlerStrategy.cpp
  src/GameViewKeyHandlerStrategyFactory.cpp
  src/GameViewLeftKeyHandlerStrategy.cpp
  src/GameViewRightKeyHandlerStrategy.cpp
  src/MainWindowController.cpp
  src/MainWindow.cpp
  src/MainWindowPresenter.cpp
  src/MenuItem.cpp
  src/NewGameView.cpp
  src/NewPlayerList.cpp
  src/pathHelpers.cpp
  src/StatusBar.cpp
  src/StatusBarPresenter.cpp
  src/TieGameResolutionDialogPresenter.cpp
  src/WinGameResolutionDialogPresenter.cpp
)

target_include_directories(${TARGET_NAME}
  PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include"
  PRIVATE "${GTKMM_INCLUDE_DIRS}"
)

target_link_libraries(${TARGET_NAME}
  PRIVATE cxinv
  PRIVATE cxmath
  PRIVATE cxmodel
  PRIVATE ${GTKMM_LIBRARIES}
)

# Unit tests:
add_subdirectory(test)