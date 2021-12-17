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
 * @file StatusBarPresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxgui/StatusBarPresenter.h>

/*********************************************************************************************//**
 * @brief Concrete subject only used to call the Update method with valid parameters.
 *
 ************************************************************************************************/
class ConcreteSubject : public cxmodel::ModelSubject
{
public:

    ~ConcreteSubject() override = default;
};

TEST(StatusBarPresenter, MakeStatusBarContextString_CreateNewGame_NewGameCreatedStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::CREATE_NEW_GAME), "New game created.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_ChipDropped_ChipDroppedStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::CHIP_DROPPED), "Chip dropped.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_ChipDroppedFailed_NoMessage)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::CHIP_DROPPED_FAILED), "");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_ChipMovedLeft_NoMessage)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::CHIP_MOVED_LEFT), "");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_ChipMovedRight_NoMessage)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::CHIP_MOVED_RIGHT), "");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_Undo_UndoStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED), "Undo.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_Redo_RedoStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::REDO_CHIP_DROPPED), "Redo.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_GameWon_GameWonStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::GAME_WON), "Game won!");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_GameTied_GameTiedStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::GAME_TIED), "Game tied!");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_GameEnded_NoMessage)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::GAME_ENDED), "");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_GameReinitialized_GameReinitializedStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::ModelNotificationContext::GAME_REINITIALIZED), "Game reinitialized.");
}

TEST(StatusBarPresenter, Constructor_NoAction_NoMessage)
{
    cxgui::StatusBarPresenter presenter;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());
}

TEST(StatusBarPresenter, Update_Undo_UndoMessageIsOn)
{
    cxgui::StatusBarPresenter presenter;
    ConcreteSubject subject;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());

    presenter.Update(cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED, &subject);

    ASSERT_EQ(presenter.GetStatusBarMessage(), "Undo.");
}
