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

#include <algorithm>

#include <gtest/gtest.h>

#include <cxmodel/include/NewGameInformation.h>

#include "MainWindowPresenterTestFixture.h"

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetWindowTitle_GetWindowTitle_GetWindowTitleLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetWindowTitle(), "Connect X");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_GameMenu_GameMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::GAME), "Game");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_QuitMenu_QuitMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::QUIT), "Quit");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_HelpMenu_HelpMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::HELP), "Help");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_AboutMenu_AboutMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::ABOUT), "About");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_CreateNewGame_NewGameInformationUpdated)
{
    const auto& presenter = GetPresenter();

    // Unitial presenter state:
    ASSERT_EQ(presenter.GetGameViewActivePlayerChipColor(), cxmodel::MakeTransparent());
    ASSERT_EQ(presenter.GetGameViewActivePlayerName(), "--");

    ASSERT_EQ(presenter.GetGameViewNextPlayerChipColor(), cxmodel::MakeTransparent());
    ASSERT_EQ(presenter.GetGameViewNextPlayerName() , "--");

    // We create a new game:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    // Updated presenter state:
    ASSERT_EQ(presenter.GetGameViewActivePlayerChipColor(), cxmodel::MakeRed());
    ASSERT_EQ(presenter.GetGameViewActivePlayerName(), "John Doe");

    ASSERT_EQ(presenter.GetGameViewNextPlayerChipColor(), cxmodel::MakeBlue());
    ASSERT_EQ(presenter.GetGameViewNextPlayerName() , "Jane Doe");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_ChipDropped_BoardInformationUpdated)
{
    // We create a new game to update the active player chip:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    const auto& presenter = GetPresenter();
    auto boardColors = presenter.GetGameViewChipColors();

    // Initial state:
    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [](const cxmodel::ChipColor& p_color)
                                {
                                    return p_color == cxmodel::MakeTransparent();
                                }));
    }

    // We drop a chip:
    auto& infoModel = GetGameInformationModel();
    actionModel.DropChip(infoModel.GetActivePlayer().GetChip(), 0u);

    // Updated state:
    boardColors = presenter.GetGameViewChipColors();

    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [&infoModel](const cxmodel::ChipColor& p_color)
                                {
                                    const cxmodel::IChip& activePlayerChip = infoModel.GetActivePlayer().GetChip();
                                    return p_color == activePlayerChip.GetColor();
                                }));
    }
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_GameReinitialized_BoardInformationUpdated)
{
    // We create a new game to update the active player chip:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    // Initial state:
    const auto& presenter = GetPresenter();
    auto boardColors = presenter.GetGameViewChipColors();

    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [](const cxmodel::ChipColor& p_color)
                                {
                                    return p_color == cxmodel::MakeTransparent();
                                }));
    }


    // We reinitialize the game:
    actionModel.ReinitializeCurrentGame();

    // Updated state:
    auto& infoModel = GetGameInformationModel();
    boardColors = presenter.GetGameViewChipColors();
    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [&infoModel](const cxmodel::ChipColor& p_color)
                                {
                                    const cxmodel::IChip& activePlayerChip = infoModel.GetActivePlayer().GetChip();
                                    return p_color == activePlayerChip.GetColor();
                                }));
    }
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_NoNotification_FalseReturned)
{
    const auto& presenter = GetPresenter();

    ASSERT_FALSE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_CreateNewGameNotification_TrueReturned)
{
    SendNotification(cxmodel::NotificationContext::CREATE_NEW_GAME);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_ChipDroppedNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    SendNotification(cxmodel::NotificationContext::CHIP_DROPPED);
    
    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_AllOtherNotifications_FalseReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    const auto& presenter = GetPresenter();

    SendNotification(cxmodel::NotificationContext::GAME_ENDED);
    ASSERT_FALSE(presenter.IsNewGamePossible());

    SendNotification(cxmodel::NotificationContext::GAME_REINITIALIZED);
    ASSERT_FALSE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentGameReinitializationPossible_NoNotification_FalseReturned)
{
    const auto& presenter = GetPresenter();

    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentGameReinitializationPossible_ChipDroppedNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    SendNotification(cxmodel::NotificationContext::CHIP_DROPPED);
    
    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsCurrentGameReinitializationPossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentGameReinitializationPossible_AllOtherNotifications_FalseReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    const auto& presenter = GetPresenter();
    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());

    SendNotification(cxmodel::NotificationContext::GAME_ENDED);
    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());

    SendNotification(cxmodel::NotificationContext::GAME_REINITIALIZED);
    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());
}
