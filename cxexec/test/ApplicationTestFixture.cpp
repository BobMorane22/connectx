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
 * @file ApplicationTestFixture.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include "ApplicationTestFixture.h"

ApplicationTestFixture::ApplicationTestFixture()
 : m_model{std::make_unique<ModelApplicationMock>()}
{
}

cxlog::ILogger& ApplicationTestFixture::GetLogger()
{
    return m_logger;
}

cxmodel::Subject& ApplicationTestFixture::GetSubjectModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cxmodel::IConnectXGameActions& ApplicationTestFixture::GetGameActionsModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cxmodel::IConnectXGameInformation& ApplicationTestFixture::GetGameInformationModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cxmodel::IConnectXLimits& ApplicationTestFixture::GetLimitsModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cxmodel::IVersioning& ApplicationTestFixture::GetVersionningModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

std::string ApplicationTestFixture::GetStdOutContents() const
{
    return m_disableStreamsRAII.GetStdOutContents();
}

std::string ApplicationTestFixture::GetStdErrContents() const
{
    return m_disableStreamsRAII.GetStdErrContents();
}

void ApplicationTestFixture::ModelApplicationMock::CreateNewGame(const cxmodel::NewGameInformation& /*p_gameInformation*/)
{
    // Not used...
}

void ApplicationTestFixture::ModelApplicationMock::DropChip(const cxmodel::IChip& /*p_chip*/, size_t p_column)
{
    ASSERT_TRUE(p_column < GetCurrentGridWidth());

    // Not used...
}

const cxmodel::IChip& ApplicationTestFixture::ModelApplicationMock::GetChip(size_t p_row, size_t p_column) const
{
    EXPECT_TRUE(p_row < GetCurrentGridHeight());
    EXPECT_TRUE(p_column < GetCurrentGridWidth());

    return m_ACTIVE_PLAYER.GetChip();
}

void ApplicationTestFixture::ModelApplicationMock::EndCurrentGame()
{
    // Nothing to do...
}

void ApplicationTestFixture::ModelApplicationMock::ReinitializeCurrentGame()
{
    // Nothing to do...
}
