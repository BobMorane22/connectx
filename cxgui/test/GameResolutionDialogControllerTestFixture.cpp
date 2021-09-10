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
 * @file GameResolutionDialogControllerTestFixture.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <GameResolutionDialogController.h>

#include "GameResolutionDialogControllerTestFixture.h"

GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerTestFixture()
{
    m_model = std::make_unique<GameResolutionDialogControllerMockModel>(*this);
    EXPECT_TRUE(m_model);

    m_controller = std::make_unique<cxgui::GameResolutionDialogController>(*m_model);
    EXPECT_TRUE(m_controller);
}

bool GameResolutionDialogControllerTestFixture::GetNewGameRequested() const
{
    return m_newGameRequested;
}

cxgui::IGameResolutionDialogController& GameResolutionDialogControllerTestFixture::GetController()
{
    EXPECT_TRUE(m_controller);
    return *m_controller;
}

GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::GameResolutionDialogControllerMockModel(GameResolutionDialogControllerTestFixture& p_outer)
: m_outer{p_outer}
{
}

void GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::CreateNewGame(const cxmodel::NewGameInformation& /*p_gameInformation*/)
{
    // Nothing to do...
}

void GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::DropChip(const cxmodel::IChip& /*p_chip*/, size_t /*p_column*/)
{
    // Nothing to do...
}

void GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::MoveLeft()
{
    // Nothing to do...
}

void GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::MoveRight()
{
    // Nothing to do...
}

void GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::EndCurrentGame()
{
    m_outer.m_newGameRequested = true;
}

void GameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::ReinitializeCurrentGame()
{
    // Nothing to do...
}
