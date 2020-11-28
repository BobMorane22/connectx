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
 * @file WinGameResolutionDialogControllerTestFixture.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <WinGameResolutionDialogController.h>

#include "WinGameResolutionDialogControllerTestFixture.h"

WinGameResolutionDialogControllerTestFixture::WinGameResolutionDialogControllerTestFixture()
{
    m_model = std::make_unique<GameResolutionDialogControllerMockModel>(*this);
    EXPECT_TRUE(m_model);

    m_controller = std::make_unique<cxgui::WinGameResolutionDialogController>(*m_model);
    EXPECT_TRUE(m_controller);
}

bool WinGameResolutionDialogControllerTestFixture::GetNewGameRequested() const
{
    return m_newGameRequested;
}

cxgui::IGameResolutionDialogController& WinGameResolutionDialogControllerTestFixture::GetController()
{
    EXPECT_TRUE(m_controller);
    return *m_controller;
}

WinGameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::GameResolutionDialogControllerMockModel(WinGameResolutionDialogControllerTestFixture& p_outer)
: m_outer{p_outer}
{
}

void WinGameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::CreateNewGame(const cxmodel::NewGameInformation& /*p_gameInformation*/)
{
    // Nothing to do...
}

void WinGameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::DropChip(const cxmodel::IChip& /*p_chip*/, size_t /*p_column*/)
{
    // Nothing to do...
}

void WinGameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::EndCurrentGame()
{
    m_outer.m_newGameRequested = true;
}

void WinGameResolutionDialogControllerTestFixture::GameResolutionDialogControllerMockModel::ReinitializeCurrentGame()
{
    // Nothing to do...
}
