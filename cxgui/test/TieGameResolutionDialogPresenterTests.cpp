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
 * @file TieGameResolutionDialogPresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <TieGameResolutionDialogPresenter.h>

TEST(TieGameResolutionDialogPresenter, GetTitle_ValidPresented_TitleReturned)
{
    cxgui::TieGameResolutionDialogPresenter presenter;

    ASSERT_EQ("Game tied!", presenter.GetTitle());
}

TEST(TieGameResolutionDialogPresenter, GetResolutionMessage_ValidPresenter_ResolutionMessageReturned)
{
    cxgui::TieGameResolutionDialogPresenter presenter;

    ASSERT_EQ("Nobody wins, nobody looses!", presenter.GetResolutionMessage());
}

TEST(TieGameResolutionDialogPresenter, GetStartNewGameButtonText_ValidPresenter_StartNewGameButtonTextReturned)
{
    cxgui::TieGameResolutionDialogPresenter presenter;

    ASSERT_EQ("Start new game", presenter.GetStartNewGameButtonText());
}
