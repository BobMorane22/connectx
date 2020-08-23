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
 * @file MainWindowPresenterTestFixture.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxgui/include/MainWindowPresenter.h>

#include "MainWindowPresenterTestFixture.h"

MainWindowPresenterTestFixture::MainWindowPresenterTestFixture()
{
    m_model = std::make_unique<MainWindowPresenterModelMock>();
    EXPECT_TRUE(m_model != nullptr);

    m_presenter = std::make_unique<cxgui::MainWindowPresenter>(*m_model);
    EXPECT_TRUE(m_presenter != nullptr);

    m_model->Attach(m_presenter.get());
}

cxgui::IMainWindowPresenter& MainWindowPresenterTestFixture::GetPresenter()
{
    EXPECT_TRUE(m_presenter != nullptr);

    return *m_presenter;
}

cxgui::IGameViewPresenter& MainWindowPresenterTestFixture::GetGameViewPresenter()
{
    EXPECT_TRUE(m_presenter != nullptr);

    return *m_presenter;
}

cxgui::INewGameViewPresenter& MainWindowPresenterTestFixture::GetNewGameViewPresenter()
{
    EXPECT_TRUE(m_presenter != nullptr);

    return *m_presenter;
}

cxmodel::IConnectXGameActions& MainWindowPresenterTestFixture::GetActionsModel()
{
    EXPECT_TRUE(m_model != nullptr);

    return *m_model;
}
