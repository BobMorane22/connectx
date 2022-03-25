/**************************************************************************************************
 *  This file is part of Connect X.
 *
 *  Connect X is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Connect X is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
 *
 *************************************************************************************************/
/**********************************************************************************************//**
 * @file MainWindowControllerTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include "MainWindowControllerTestFixture.h"

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnStart_ValidGame_CreateNewGameCalledOnModel)
{
    ASSERT_FALSE(GetNewGameCreated());

    cxmodel::NewGameInformation newGameInformation;
    newGameInformation.m_inARowValue = 4;
    newGameInformation.m_gridWidth = 7;
    newGameInformation.m_gridHeight = 6;
    newGameInformation.m_players.push_back(cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN));
    newGameInformation.m_players.push_back(cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN));

    GetController().OnStart(std::move(newGameInformation));

    ASSERT_TRUE(GetNewGameCreated());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnDown_ValidChip_ChipDroppedCalledOnModel)
{
    ASSERT_FALSE(GetChipDropped());

    GetController().OnDown(cxmodel::MakeBlue(), 0u);

    ASSERT_TRUE(GetChipDropped());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnMoveLeft_ValidChip_MoveLeftCalledOnModel)
{
    ASSERT_FALSE(GetChipMovedLeft());

    GetController().OnMoveLeft();

    ASSERT_TRUE(GetChipMovedLeft());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnMoveRight_ValidChip_MoveRightCalledOnModel)
{
    ASSERT_FALSE(GetChipMovedRight());

    GetController().OnMoveRight();

    ASSERT_TRUE(GetChipMovedRight());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnNewGame_ValidGame_EndCurrentGameCalledOnModel)
{
    ASSERT_FALSE(GetCurrentGameEnded());

    GetController().OnNewGame();

    ASSERT_TRUE(GetCurrentGameEnded());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnDown_ValidGame_ReinitializeCurrentGameCalledOnModel)
{
    ASSERT_FALSE(GetCurrentGameReinitialized());

    GetController().OnReinitializeCurrentGame();

    ASSERT_TRUE(GetCurrentGameReinitialized());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnUndo_ValidGame_UndoCalledOnModel)
{
    ASSERT_FALSE(GetUndoCalled());

    GetController().OnUndo();

    ASSERT_TRUE(GetUndoCalled());
}

TEST_F(MainWindowControllerTestFixture, /*DISABLED_*/OnRedo_ValidGame_RedoCalledOnModel)
{
    ASSERT_FALSE(GetRedoCalled());

    GetController().OnRedo();

    ASSERT_TRUE(GetRedoCalled());
}
