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
 * @file MenuItemTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxuicmn/MenuItem.h>

TEST(MenuItem, /*DISABLED_*/MakeLabel_Game_GameLabelReturned)
{
    ASSERT_EQ("Game", cx::ui::cmn::MakeLabel(cx::ui::cmn::MenuItem::GAME));
}

TEST(MenuItem, /*DISABLED_*/MakeLabel_Quit_QuitLabelReturned)
{
    ASSERT_EQ("Quit", cx::ui::cmn::MakeLabel(cx::ui::cmn::MenuItem::QUIT));
}

TEST(MenuItem, /*DISABLED_*/MakeLabel_NewGame_NewGameLabelReturned)
{
    ASSERT_EQ("New", cx::ui::cmn::MakeLabel(cx::ui::cmn::MenuItem::NEW_GAME));
}

TEST(MenuItem, /*DISABLED_*/MakeLabel_Reinitialize_ReinitializeLabelReturned)
{
    ASSERT_EQ("Reinitialize", cx::ui::cmn::MakeLabel(cx::ui::cmn::MenuItem::REINITIALIZE_GAME));
}

TEST(MenuItem, /*DISABLED_*/MakeLabel_Help_HelpLabelReturned)
{
    ASSERT_EQ("Help", cx::ui::cmn::MakeLabel(cx::ui::cmn::MenuItem::HELP));
}

TEST(MenuItem, /*DISABLED_*/MakeLabel_About_AboutLabelReturned)
{
    ASSERT_EQ("About", cx::ui::cmn::MakeLabel(cx::ui::cmn::MenuItem::ABOUT));
}
