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

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMessage_GamePresenter_MessageReturned)
{
    ASSERT_EQ(GetGameViewPresenter().GetGameViewMessage(), "New game started!");
}
