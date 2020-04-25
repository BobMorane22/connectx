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
 * @file NewGamePresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "MainWindowPresenterTestFixture.h"

TEST_F(MainWindowPresenterTestFixture, GetTitle_GetTitle_TitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewTitle(), "New Game");
}

TEST_F(MainWindowPresenterTestFixture, GetGameSectionTitle_GetGameSectionTitle_GameSectionTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewGameSectionTitle(), "Game");
}

TEST_F(MainWindowPresenterTestFixture, GetNewGameViewInARowLabelText_GetNewGameViewInARowLabelText_NewGameViewTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewInARowLabelText(), "In a row:");
}

TEST_F(MainWindowPresenterTestFixture, GetNGridSectionTitle_GetGridSectionTitle_GridSectionTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewGridSectionTitle(), "Grid");
}

TEST_F(MainWindowPresenterTestFixture, GetWidthLabelText_GetWidthLabelText_WidthLabelTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewWidthLabelText(), "Width:");
}

TEST_F(MainWindowPresenterTestFixture, GetHeightLabelText_GetHeightLabelText_HeightLabelTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewHeightLabelText(), "Height:");
}

TEST_F(MainWindowPresenterTestFixture, GetPlayersSectionTitle_GetPlayersSectionTitle_PlayersSectionTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewPlayersSectionTitle(), "Players");
}

TEST_F(MainWindowPresenterTestFixture, GetNameColumnHeaderText_GetNameColumnHeaderText_NameColumnHeaderTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewNameColumnHeaderText(), "Name");
}

TEST_F(MainWindowPresenterTestFixture, GetDiscColumnHeaderText_GetDiscColumnHeaderText_DiscColumnHeaderTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewDiscColumnHeaderText(), "Disc");
}

TEST_F(MainWindowPresenterTestFixture, GetStartButtonText_GetStartButtonText_StartButtonTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewStartButtonText(), "Start");
}
