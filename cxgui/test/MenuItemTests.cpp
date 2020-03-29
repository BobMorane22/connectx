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

#include <MenuItem.h>

TEST(MenuItem, MakeLabel_Game_GameLabelReturned)
{
    ASSERT_EQ("Game", cxgui::MakeLabel(cxgui::MenuItem::GAME));
}

TEST(MenuItem, MakeLabel_Quit_QuitLabelReturned)
{
    ASSERT_EQ("Quit", cxgui::MakeLabel(cxgui::MenuItem::QUIT));
}

TEST(MenuItem, MakeLabel_Reinitialize_ReinitializeLabelReturned)
{
    ASSERT_EQ("Reinitialize", cxgui::MakeLabel(cxgui::MenuItem::REINITIALIZE));
}

TEST(MenuItem, MakeLabel_Help_HelpLabelReturned)
{
    ASSERT_EQ("Help", cxgui::MakeLabel(cxgui::MenuItem::HELP));
}

TEST(MenuItem, MakeLabel_About_AboutLabelReturned)
{
    ASSERT_EQ("About", cxgui::MakeLabel(cxgui::MenuItem::ABOUT));
}
