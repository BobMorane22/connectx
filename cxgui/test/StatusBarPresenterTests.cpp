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

#include <StatusBarPresenter.h>

/*********************************************************************************************//**
 * @brief Concrete subject only used to call the Update method with valid parameters.
 *
 ************************************************************************************************/
class ConcreteSubject : public cxmodel::Subject
{
public:

    ~ConcreteSubject() override = default;
};

TEST(StatusBarPresenter, MakeStatusBarContextString_Increment_IncrementStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::NotificationContext::INCREMENT), "Increment.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_Reinitialize_ReinitializeStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::NotificationContext::REINITIALIZE), "Reinitialize.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_Undo_UndoStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::NotificationContext::UNDO), "Undo.");
}

TEST(StatusBarPresenter, MakeStatusBarContextString_Redo_RedoStringCreated)
{
    ASSERT_EQ(cxgui::MakeStatusBarContextString(cxmodel::NotificationContext::REDO), "Redo.");
}

TEST(StatusBarPresenter, Constructor_NoAction_NoMessage)
{
    cxgui::StatusBarPresenter presenter;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());
}

TEST(StatusBarPresenter, Update_Increment_IncrementMessageIsOn)
{
    cxgui::StatusBarPresenter presenter;
    ConcreteSubject subject;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());

    presenter.Update(cxmodel::NotificationContext::INCREMENT, &subject);

    ASSERT_EQ(presenter.GetStatusBarMessage(), "Increment.");
}

TEST(StatusBarPresenter, Update_Reinitialize_ReinitializeMessageIsOn)
{
    cxgui::StatusBarPresenter presenter;
    ConcreteSubject subject;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());

    presenter.Update(cxmodel::NotificationContext::REINITIALIZE, &subject);

    ASSERT_EQ(presenter.GetStatusBarMessage(), "Reinitialize.");
}

TEST(StatusBarPresenter, Update_Undo_UndoMessageIsOn)
{
    cxgui::StatusBarPresenter presenter;
    ConcreteSubject subject;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());

    presenter.Update(cxmodel::NotificationContext::UNDO, &subject);

    ASSERT_EQ(presenter.GetStatusBarMessage(), "Undo.");
}

TEST(StatusBarPresenter, Update_Redo_RedoMessageIsOn)
{
    cxgui::StatusBarPresenter presenter;
    ConcreteSubject subject;

    ASSERT_TRUE(presenter.GetStatusBarMessage().empty());

    presenter.Update(cxmodel::NotificationContext::REDO, &subject);

    ASSERT_EQ(presenter.GetStatusBarMessage(), "Redo.");
}
