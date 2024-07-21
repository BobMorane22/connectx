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

cx::log::ILogger& ApplicationTestFixture::GetLogger()
{
    return m_logger;
}

cx::model::ModelSubject& ApplicationTestFixture::GetSubjectModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cx::model::IConnectXGameActions& ApplicationTestFixture::GetGameActionsModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cx::model::IConnectXGameInformation& ApplicationTestFixture::GetGameInformationModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cx::model::IConnectXLimits& ApplicationTestFixture::GetLimitsModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cx::model::IUndoRedo& ApplicationTestFixture::GetUndoRedoModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cx::model::IVersioning& ApplicationTestFixture::GetVersionningModel()
{
    EXPECT_TRUE(m_model);

    return *m_model;
}

cx::ModelReferences ApplicationTestFixture::GetModelReferences()
{
    EXPECT_TRUE(m_model);

    cx::ModelReferences references{
        *m_model,
        *m_model,
        *m_model,
        *m_model,
        *m_model,
        *m_model,
        *m_model
    }; 

    return references;
}

void ApplicationTestFixture::ModelApplicationMock::CreateNewGame(cx::model::NewGameInformation /*p_gameInformation*/)
{
    // Not used...
}

void ApplicationTestFixture::ModelApplicationMock::DropChip(const cx::model::IChip& /*p_chip*/, size_t p_column)
{
    ASSERT_TRUE(p_column < GetCurrentGridWidth());

    // Not used...
}

void ApplicationTestFixture::ModelApplicationMock::MoveLeftOneColumn()
{
    // Not used...
}

void ApplicationTestFixture::ModelApplicationMock::MoveRightOneColumn()
{
    // Not used...
}

const cx::model::IChip& ApplicationTestFixture::ModelApplicationMock::GetChip(size_t p_row, size_t p_column) const
{
    EXPECT_TRUE(p_row < GetCurrentGridHeight());
    EXPECT_TRUE(p_column < GetCurrentGridWidth());

    return m_ACTIVE_PLAYER->GetChip();
}

void ApplicationTestFixture::ModelApplicationMock::EndCurrentGame()
{
    // Nothing to do...
}

void ApplicationTestFixture::ModelApplicationMock::ReinitializeCurrentGame()
{
    // Nothing to do...
}
