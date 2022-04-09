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
# CMake configuration file for the cxmodel unit test executable.
#
# @file CMakeLists.txt
# @date 2021
#
#************************************************************************************************/

set(SOURCE_FILES
  BoardTests.cpp
  ChipColorTests.cpp
  ColorTests.cpp
  CommandAddTwoMock.cpp
  CommandCreateNewGameTests.cpp
  CommandDropChipTests.cpp
  CommandStackMock.cpp
  CommandStackTestFixture.cpp
  CommandStackTests.cpp
  CommandTimesThreeMock.cpp
  ConcreteObserverMock.cpp
  ConcreteSubjectMock.cpp
  DiscTests.cpp
  GameResolutionStrategyFactoryTests.cpp
  GameResolutionStrategyTestFixture.cpp
  IBoardTests.cpp
  INextDropColumnComputationStrategyTests.cpp
  IPlayerTests.cpp
  LoggerMock.cpp
  ModelTestFixture.cpp
  ModelTestHelpers.cpp
  ModelTests.cpp
  NewGameInformationTests.cpp
  StatusTests.cpp
  SubjectTestFixture.cpp
  SubjectTests.cpp
  Tie8By7BoardGameResolutionStrategyTests.cpp
  TieClassicGameResolutionStrategyTests.cpp
  TieEdgeCasesGameResolutionStrategyTests.cpp
  TieLegacyGameResolutionStrategyTests.cpp
  TieSquareBoardGameResolutionStrategyTests.cpp
  Win8By7BoardGameResolutionStrategyTests.cpp
  WinClassicGameResolutionStrategyTests.cpp
  WinEdgeCasesGameResolutionStrategyTests.cpp
  WinSquareBoardGameResolutionStrategyTests.cpp
)

set(LIBRARIES
  cxunit
  cxinv
  cxlog
)

add_lib_unit_test(
  cxmodel
  SOURCES ${SOURCE_FILES}
  LIBS ${LIBRARIES}
)
