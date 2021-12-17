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
# CMake configuration file for the cxgui unit test executable.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

set(SOURCE_FILES
  AboutWindowPresenterTestFixture.cpp
  AboutWindowPresenterTests.cpp
  AnimatedBoardModelTests.cpp
  AnimatedBoardPresenterTests.cpp
  ConfigurableMainWindowPresenterTestFixture.cpp
  DimensionsTests.cpp
  extractRawUserInputTests.cpp
  GamePresenterTests.cpp
  GameResolutionDialogControllerTestFixture.cpp
  GameResolutionDialogControllerTests.cpp
  GameResolutionDialogPresenterFactoryTests.cpp
  MainWindowControllerTestFixture.cpp
  MainWindowControllerTests.cpp
  MainWindowPresenterTestFixture.cpp
  MainWindowPresenterTests.cpp
  MenuItemTests.cpp
  NewGamePresenterTests.cpp
  ScalingRatiosTests.cpp
  StatusBarPresenterTests.cpp
  TieGameResolutionDialogPresenterTests.cpp
  WinGameResolutionDialogPresenterTests.cpp
)

set(LIBRARIES
  cxunit
  cxinv
  cxmath
  cxmodel
)

add_lib_unit_test(
  cxgui
  SOURCES ${SOURCE_FILES}
  LIBS ${LIBRARIES}
)
