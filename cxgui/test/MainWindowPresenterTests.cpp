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
 * @file MainWindowPresenterTest.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "MainWindowPresenterTestFixture.h"

TEST_F(MainWindowPresenterTestFixture, IsReinitializeBtnEnabled_Initial_Disabeled)
{
    ASSERT_EQ(GetPresenter().IsReinitializeBtnEnabled(), false);
}

TEST_F(MainWindowPresenterTestFixture, IsReinitializeBtnEnabled_OneIncrement_Enabled)
{
    GetModel().Increment();

    ASSERT_EQ(GetPresenter().IsReinitializeBtnEnabled(), true);
}

TEST_F(MainWindowPresenterTestFixture, GetCounterValue_Initial_Zero)
{
    ASSERT_EQ(GetPresenter().GetCounterValue(), 0);
}

TEST_F(MainWindowPresenterTestFixture, GetCounterValue_OneIncrement_One)
{
    GetModel().Increment();

    ASSERT_EQ(GetPresenter().GetCounterValue(), 1);
}

TEST_F(MainWindowPresenterTestFixture, GetWindowTitle_Initial_GoodLabel)
{
    ASSERT_EQ(GetPresenter().GetWindowTitle(), "Connect X");
}

TEST_F(MainWindowPresenterTestFixture, GetIncrementBtnLabel_Initial_GoodLabel)
{
    ASSERT_EQ(GetPresenter().GetIncrementBtnLabel(), "Increment");
}

TEST_F(MainWindowPresenterTestFixture, GetReinitializeBtnLabel_Initial_GoodLabel)
{
    ASSERT_EQ(GetPresenter().GetReinitializeBtnLabel(), "Reinitialize");
}

TEST_F(MainWindowPresenterTestFixture, GetMenuLabel_GameMenu_GameMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::GAME), "Game");
}

TEST_F(MainWindowPresenterTestFixture, GetMenuLabel_QuitMenu_QuitMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::QUIT), "Quit");
}

TEST_F(MainWindowPresenterTestFixture, GetMenuLabel_ReinitializeMenu_ReinitializeMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::REINITIALIZE), "Reinitialize");
}

