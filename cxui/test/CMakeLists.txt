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
# CMake configuration file for the cxui unit test executable.
#
# @file CMakeLists.txt
# @date 2024
#
#************************************************************************************************/

set(SOURCE_FILES
  AboutWindowPresenterTestFixture.cpp
  AboutWindowPresenterTestFixture.h
  AboutWindowPresenterTests.cpp
  AnimatedBoardModelMock.cpp
  AnimatedBoardModelMock.h
  AnimatedBoardModelTests.cpp
  AnimatedBoardPresenterMock.cpp
  AnimatedBoardPresenterMock.h
  AnimatedBoardPresenterTests.cpp
  AnimationInformationsTests.cpp
  BasicConnectXGameInformationModelMock.h
  BasicConnectXLimitsModelMock.h
  ConfigurableMainWindowPresenterTestFixture.cpp
  ConfigurableMainWindowPresenterTestFixture.h
  FrameAnimationStrategyTests.cpp
  GameResolutionDialogControllerTestFixture.cpp
  GameResolutionDialogControllerTestFixture.h
  GameResolutionDialogControllerTests.cpp
  GameResolutionDialogPresenterFactoryTests.cpp
  GameViewPresenterTests.cpp
  IAnimatedBoardModelTests.cpp
  MainWindowControllerTestFixture.cpp
  MainWindowControllerTestFixture.h
  MainWindowControllerTests.cpp
  MainWindowPresenterTestFixture.cpp
  MainWindowPresenterTestFixture.h
  MainWindowPresenterTests.cpp
  MenuItemTests.cpp
  NewGameViewPresenterMock.h
  NewGameViewPresenterTests.cpp
  TieGameResolutionDialogPresenterTests.cpp
  WinGameResolutionDialogPresenterTests.cpp
)

set(LIBRARIES
  cxunit
  cxcmn
  cxinv
  cxmath
  cxmodel
  cxcmnui
  cxui
)

add_lib_unit_test(
  cxui
  SOURCES ${SOURCE_FILES}
  LIBS ${LIBRARIES}
)
