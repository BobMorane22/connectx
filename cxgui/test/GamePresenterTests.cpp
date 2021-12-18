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
 * @file GamePresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "MainWindowPresenterTestFixture.h"

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetTitle_GamePresenter_TitleReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewTitle(), "Game");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetActivePlayerChipColor_GamePresenterNoUpdate_NoColorReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewActivePlayerChipColor(), cxmodel::MakeTransparent());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNextPlayerChipColor_GamePresenterNoUpdate_NoColorReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewNextPlayerChipColor(), cxmodel::MakeTransparent());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetActivePlayerLabelText_GamePresenter_LabelTextReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewActivePlayerLabelText(), "  Active player: ");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNextPlayerLabelText_GamePresenter_LabelTextReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewNextPlayerLabelText(), "  Next player: ");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetActivePlayerName_GamePresenterNoUpdate_NoNameReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewActivePlayerName(), "--");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNextPlayerName_GamePresenterNoUpdate_NoNameReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewNextPlayerName(), "--");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetBoardWidth_GamePresenterNoUpdate_MinimumReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewBoardWidth(), GetLimitsModel().GetMinimumGridWidth());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetBoardHeight_GamePresenterNoUpdate_MinimumReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewBoardHeight(), GetLimitsModel().GetMinimumGridHeight());
}
