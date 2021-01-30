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
 * @file ConfigurableMainWindowPresenterTestFixture.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <exception>

#include <cxgui/include/MainWindowPresenter.h>

#include "BasicConnectXGameInformationModelMock.h"
#include "BasicConnectXLimitsModelMock.h"
#include "ConfigurableMainWindowPresenterTestFixture.h"

ConfigurableMainWindowPresenterTestFixture::ConfigurableMainWindowPresenterTestFixture()
{
    m_modelAsGameInformation = std::make_unique<BasicConnectXGameInformationModelMock>();
    EXPECT_TRUE(m_modelAsGameInformation);

    m_modelAsLimits = std::make_unique<BasicConnectXLimitsModelMock>();
    EXPECT_TRUE(m_modelAsLimits);

    m_presenter = std::make_unique<cxgui::MainWindowPresenter>(*m_modelAsLimits, *m_modelAsGameInformation);
    EXPECT_TRUE(m_presenter);
}

cxgui::IMainWindowPresenter& ConfigurableMainWindowPresenterTestFixture::GetPresenter()
{
    EXPECT_TRUE(m_presenter);
    return *m_presenter;
}

void ConfigurableMainWindowPresenterTestFixture::SetGameInformationModel(std::unique_ptr<cxmodel::IConnectXGameInformation>&& p_model)
{
    EXPECT_TRUE(p_model);
    m_modelAsGameInformation = std::move(p_model);

    m_presenter = std::make_unique<cxgui::MainWindowPresenter>(*m_modelAsLimits, *m_modelAsGameInformation);
    EXPECT_TRUE(m_presenter);
}

void ConfigurableMainWindowPresenterTestFixture::SetLimitsModel(std::unique_ptr<cxmodel::IConnectXLimits>&& p_model)
{
    EXPECT_TRUE(p_model);
    m_modelAsLimits = std::move(p_model);

    m_presenter = std::make_unique<cxgui::MainWindowPresenter>(*m_modelAsLimits, *m_modelAsGameInformation);
    EXPECT_TRUE(m_presenter);
}

cxmodel::IConnectXGameInformation& ConfigurableMainWindowPresenterTestFixture::GetGameInformationModel()
{
    EXPECT_TRUE(m_modelAsGameInformation);
    return *m_modelAsGameInformation;
}

cxmodel::IConnectXLimits& ConfigurableMainWindowPresenterTestFixture::GetLimitsModel()
{
    EXPECT_TRUE(m_modelAsLimits);
    return *m_modelAsLimits;
}
