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
 * @file CommandCreateNewGameTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <CommandCreateNewGame.h>

TEST(CommandCreateNewGame, Execute_ValidNewGame_NewGameCreated)
{
    cxmodel::NewGameInformation modelInfo;
    cxmodel::NewGameInformation newGameInformation;

    newGameInformation.m_inARowValue = 4;
    newGameInformation.m_gridWidth = 7;
    newGameInformation.m_gridHeight = 6;
    newGameInformation.AddPlayer({"John Doe", "Red"});
    newGameInformation.AddPlayer({"Jane Doe", "Blue"});

    ASSERT_NE(modelInfo, newGameInformation);

    cxmodel::CommandCreateNewGame cmd{modelInfo, newGameInformation};
    cmd.Execute();

    ASSERT_EQ(modelInfo, newGameInformation);
}

TEST(CommandCreateNewGame, Undo_ValidNewGame_HasNoEffect)
{
    // To be added later...
}
