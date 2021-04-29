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

#include <cxmodel/include/Disc.h>
#include <cxmodel/include/NewGameInformation.h>

#include "BasicConnectXGameInformationModelMock.h"
#include "BasicConnectXLimitsModelMock.h"
#include "ConfigurableMainWindowPresenterTestFixture.h"
#include "MainWindowPresenterTestFixture.h"

namespace
{

/*********************************************************************************************//**
 * @brief Mock testing when undoing and redoing should be unlocked.
 *
 ************************************************************************************************/
class CanUndoRedoModel : public cxmodel::IUndoRedo
{

public:

    void Undo() override {throw cxunit::NotImplementedException();}
    void Redo() override {throw cxunit::NotImplementedException();}
    bool CanUndo() const override {return false;}
    bool CanRedo() const override {return false;}

};

/*********************************************************************************************//**
 * @brief Mock for testing the effect of undo operations on the main window presenter.
 *
 ************************************************************************************************/
class UndoConnectXGameInformationModelMock : public BasicConnectXGameInformationModelMock,
                                             public cxmodel::Subject
{

public:

    UndoConnectXGameInformationModelMock(bool p_makeEmpty = true)
    {
        for(size_t row = 0u; row < GetCurrentGridHeight(); ++row)
        {
            m_board.push_back(std::vector<cxmodel::Disc>());
            for(size_t column = 0u; column < GetCurrentGridWidth(); ++column)
            {
                m_board[row].push_back(cxmodel::Disc::MakeTransparentDisc());
            }
        }

        if(!p_makeEmpty)
        {
            m_board[0][0] = cxmodel::Disc{cxmodel::MakeRed()};
        }
    }

    void NotifyCreateNewGame()
    {
        Notify(cxmodel::NotificationContext::CREATE_NEW_GAME);
    }

    void NotifyDropChip()
    {
        Notify(cxmodel::NotificationContext::CHIP_DROPPED);
    }

    void NotifyUndo()
    {
        Notify(cxmodel::NotificationContext::UNDO_CHIP_DROPPED);
    }

    const cxmodel::Player& GetActivePlayer() const override {return m_activePlayer;}
    const cxmodel::Player& GetNextPlayer() const override {return m_nextPlayer;}
    const cxmodel::IChip& GetChip(size_t p_row, size_t p_column) const override
    {
        EXPECT_TRUE(p_row < GetCurrentGridHeight());
        EXPECT_TRUE(p_column < GetCurrentGridWidth());

        return m_board[p_row][p_column];
    }

private:

    cxmodel::Player m_activePlayer{"John Doe", cxmodel::MakeRed()};
    cxmodel::Player m_nextPlayer{"Jane Doe", cxmodel::MakeGreen()};
    std::vector<std::vector<cxmodel::Disc>> m_board;
};

} // namespace

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetWindowTitle_GetWindowTitle_GetWindowTitleLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetWindowTitle(), "Connect X");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_GameMenu_GameMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::GAME), "Game");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_NewGameMenu_NewGameMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::NEW_GAME), "New");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_ReinitializeMenu_ReinitializeMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::REINITIALIZE_GAME), "Reinitialize");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_UndoMenu_UndoMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::UNDO), "Undo");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_RedoMenu_RedoMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::REDO), "Redo");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_QuitMenu_QuitMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::QUIT), "Quit");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_HelpMenu_HelpMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::HELP), "Help");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_ContentsMenu_ContentsMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cxgui::MenuItem::CONTENTS), "Contents");
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

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/Update_DiscDropUndoedToInitialState_GameIsNotReinitializable)
{
    constexpr bool BOARD_EMPTY = true;
    auto model = std::make_unique<UndoConnectXGameInformationModelMock>(BOARD_EMPTY);
    ASSERT_TRUE(model);

    auto* modelRef = model.get();

    SetGameInformationModel(std::move(model)); // model moved from here, do not use anymore.

    ASSERT_FALSE(GetPresenter().IsCurrentGameReinitializationPossible());

    modelRef->Attach(&GetPresenter());
    modelRef->NotifyCreateNewGame();
    modelRef->NotifyUndo();

    ASSERT_FALSE(GetPresenter().IsCurrentGameReinitializationPossible());
}

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/Update_DiscDropUndoedToSomeState_GameIsReinitializable)
{
    constexpr bool BOARD_NOT_EMPTY = false;
    auto model = std::make_unique<UndoConnectXGameInformationModelMock>(BOARD_NOT_EMPTY);
    ASSERT_TRUE(model);

    auto* modelRef = model.get();

    SetGameInformationModel(std::move(model)); // model moved from here, do not use anymore.

    ASSERT_FALSE(GetPresenter().IsCurrentGameReinitializationPossible());

    modelRef->Attach(&GetPresenter());
    modelRef->NotifyCreateNewGame();
    modelRef->NotifyUndo();

    ASSERT_TRUE(GetPresenter().IsCurrentGameReinitializationPossible());
}

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/Update_DiscDropUndoedToInitialState_NewGameIsPossible)
{
    constexpr bool BOARD_EMPTY = false;
    auto model = std::make_unique<UndoConnectXGameInformationModelMock>(BOARD_EMPTY);
    ASSERT_TRUE(model);

    auto* modelRef = model.get();

    SetGameInformationModel(std::move(model)); // model moved from here, do not use anymore.

    ASSERT_FALSE(GetPresenter().IsNewGamePossible());

    modelRef->Attach(&GetPresenter());
    modelRef->NotifyCreateNewGame();
    modelRef->NotifyUndo();

    ASSERT_TRUE(GetPresenter().IsNewGamePossible());
}

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/Update_DiscDropUndoedToSomeState_NewGameIsPossible)
{
    constexpr bool BOARD_NOT_EMPTY = false;
    auto model = std::make_unique<UndoConnectXGameInformationModelMock>(BOARD_NOT_EMPTY);
    ASSERT_TRUE(model);

    auto* modelRef = model.get();

    SetGameInformationModel(std::move(model)); // model moved from here, do not use anymore.

    ASSERT_FALSE(GetPresenter().IsNewGamePossible());

    modelRef->Attach(&GetPresenter());
    modelRef->NotifyCreateNewGame();
    modelRef->NotifyUndo();

    ASSERT_TRUE(GetPresenter().IsNewGamePossible());
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

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_GameReinitializedNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cxmodel::NewGameInformation{});

    SendNotification(cxmodel::NotificationContext::GAME_REINITIALIZED);

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

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/IsUndoPossible_ModelCanUndo_TrueReturned)
{
    class CanUndoModel : public CanUndoRedoModel
    {

    public:

        // Unlock undoing:
        bool CanUndo() const override {return true;}

    };

    SetUndoRedoModel(std::make_unique<CanUndoModel>());

    ASSERT_TRUE(GetPresenter().IsUndoPossible());
    ASSERT_FALSE(GetPresenter().IsRedoPossible());
}

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/IsUndoPossible_ModelCannotUndo_FalseReturned)
{
    class CannotUndoModel : public CanUndoRedoModel
    {

    public:

        // Lock undoing:
        bool CanUndo() const override {return false;}

    };

    SetUndoRedoModel(std::make_unique<CannotUndoModel>());

    ASSERT_FALSE(GetPresenter().IsUndoPossible());
    ASSERT_FALSE(GetPresenter().IsRedoPossible());
}

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/IsRedoPossible_ModelCanUndo_TrueReturned)
{
    class CanRedoModel : public CanUndoRedoModel
    {

    public:

        // Unlock redoing:
        bool CanRedo() const override {return true;}

    };

    SetUndoRedoModel(std::make_unique<CanRedoModel>());

    ASSERT_FALSE(GetPresenter().IsUndoPossible());
    ASSERT_TRUE(GetPresenter().IsRedoPossible());
}

TEST_F(ConfigurableMainWindowPresenterTestFixture, /*DISABLED_*/IsRedoPossible_ModelCannotUndo_FalseReturned)
{
    class CannotRedoModel : public CanUndoRedoModel
    {

    public:

        // Lock redoing:
        bool CanRedo() const override {return false;}

    };

    SetUndoRedoModel(std::make_unique<CannotRedoModel>());

    ASSERT_FALSE(GetPresenter().IsUndoPossible());
    ASSERT_FALSE(GetPresenter().IsRedoPossible());
}
