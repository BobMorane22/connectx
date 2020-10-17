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
 * @file MainWindowControllerTestFixture.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include "MainWindowController.h"
#include "MainWindowControllerTestFixture.h"

MainWindowControllerTestFixture::MainWindowControllerTestFixture()
{
    m_model = std::make_unique<MainWindowControllerMockModel>(*this);
    m_controller = std::make_unique<cxgui::MainWindowController>(*m_model);

    EXPECT_TRUE(m_model != nullptr);
    EXPECT_TRUE(m_controller != nullptr);
}

bool MainWindowControllerTestFixture::GetNewGameCreated() const
{
    return m_newGameCreated;
}

bool MainWindowControllerTestFixture::GetChipDropped() const
{
    return m_chipDropped;
}

cxmodel::IConnectXGameActions& MainWindowControllerTestFixture::GetModel()
{
    EXPECT_TRUE(m_model != nullptr);

    return *m_model;
}

cxgui::IMainWindowController& MainWindowControllerTestFixture::GetController()
{
    EXPECT_TRUE(m_controller != nullptr);

    return *m_controller;
}

cxgui::INewGameViewController& MainWindowControllerTestFixture::GetNewGameViewController()
{
    EXPECT_TRUE(m_controller != nullptr);

    return *m_controller;
}

void MainWindowControllerTestFixture::MainWindowControllerMockModel::CreateNewGame(const cxmodel::NewGameInformation& /*p_gameInformation*/)
{
    m_outer.m_newGameCreated = true;
}

void MainWindowControllerTestFixture::MainWindowControllerMockModel::DropChip(const cxmodel::IChip& /*p_chip*/, size_t /*p_column*/)
{
    m_outer.m_chipDropped = true;
}
