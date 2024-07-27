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
 * @file MainWindowPresenterTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <algorithm>

#include <gtest/gtest.h>

#include <cxmodel/Disc.h>
#include <cxmodel/NewGameInformation.h>

#include "BasicConnectXGameInformationModelMock.h"
#include "BasicConnectXLimitsModelMock.h"
#include "ConfigurableMainWindowPresenterTestFixture.h"
#include "MainWindowPresenterTestFixture.h"

namespace
{

/*********************************************************************************************//**
 * @brief Mock testing when undoing and redoing should be unlocked.
 *
 * Override this to make undo or redo available (i.e. "unlocked").
 *
 ************************************************************************************************/
class CanUndoRedoModel : public cx::model::IUndoRedo
{

public:

    void Undo() override {throw cx::unit::NotImplementedException();}
    void Redo() override {throw cx::unit::NotImplementedException();}
    bool CanUndo() const override {return false;}
    bool CanRedo() const override {return false;}

};

/*********************************************************************************************//**
 * @brief Mock for testing the effect of undo operations on the main window presenter.
 *
 ************************************************************************************************/
class UndoConnectXGameInformationModelMock : public BasicConnectXGameInformationModelMock,
                                             public cx::model::ModelSubject
{

public:

    UndoConnectXGameInformationModelMock(bool p_makeEmpty = true)
    {
        for(size_t row = 0u; row < GetCurrentGridHeight(); ++row)
        {
            m_board.push_back(std::vector<cx::model::Disc>());
            for(size_t column = 0u; column < GetCurrentGridWidth(); ++column)
            {
                m_board[row].push_back(cx::model::Disc::MakeTransparentDisc());
            }
        }

        if(!p_makeEmpty)
        {
            m_board[0][0] = cx::model::Disc{cx::model::MakeRed()};
        }
    }

    void NotifyCreateNewGame()
    {
        Notify(cx::model::ModelNotificationContext::CREATE_NEW_GAME);
    }

    void NotifyDropChip()
    {
        Notify(cx::model::ModelNotificationContext::CHIP_DROPPED);
    }

    void NotifyUndo()
    {
        Notify(cx::model::ModelNotificationContext::UNDO_CHIP_DROPPED);
    }

    const cx::model::IPlayer& GetActivePlayer() const override {return *m_activePlayer;}
    const cx::model::IPlayer& GetNextPlayer() const override {return *m_nextPlayer;}
    const cx::model::IChip& GetChip(size_t p_row, size_t p_column) const override
    {
        EXPECT_TRUE(p_row < GetCurrentGridHeight());
        EXPECT_TRUE(p_column < GetCurrentGridWidth());

        return m_board[p_row][p_column];
    }

private:

    std::unique_ptr<cx::model::IPlayer> m_activePlayer = cx::model::CreatePlayer("John Doe", cx::model::MakeRed(), cx::model::PlayerType::HUMAN);
    std::unique_ptr<cx::model::IPlayer> m_nextPlayer = cx::model::CreatePlayer("Jane Doe", cx::model::MakeGreen(), cx::model::PlayerType::HUMAN);
    std::vector<std::vector<cx::model::Disc>> m_board;
};

} // namespace

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetWindowTitle_GetWindowTitle_GetWindowTitleLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetWindowTitle(), "Connect X");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_GameMenu_GameMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::GAME), "Game");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_NewGameMenu_NewGameMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::NEW_GAME), "New");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_ReinitializeMenu_ReinitializeMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::REINITIALIZE_GAME), "Reinitialize");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_UndoMenu_UndoMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::UNDO), "Undo");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_RedoMenu_RedoMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::REDO), "Redo");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_QuitMenu_QuitMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::QUIT), "Quit");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_HelpMenu_HelpMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::HELP), "Help");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_ContentsMenu_ContentsMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::CONTENTS), "Contents");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMenuLabel_AboutMenu_AboutMenuLabelReturned)
{
    ASSERT_EQ(GetPresenter().GetMenuLabel(cx::cmn::ui::MenuItem::ABOUT), "About");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_CreateNewGame_NewGameInformationUpdated)
{
    const auto& presenter = GetPresenter();

    // Unitial presenter state:
    ASSERT_EQ(presenter.GetGameViewActivePlayerChipColor(), cx::model::MakeTransparent());
    ASSERT_EQ(presenter.GetGameViewActivePlayerName(), "--");

    ASSERT_EQ(presenter.GetGameViewNextPlayerChipColor(), cx::model::MakeTransparent());
    ASSERT_EQ(presenter.GetGameViewNextPlayerName() , "--");

    // We create a new game:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    // Updated presenter state:
    ASSERT_EQ(presenter.GetGameViewActivePlayerChipColor(), cx::model::MakeRed());
    ASSERT_EQ(presenter.GetGameViewActivePlayerName(), "John Doe");

    ASSERT_EQ(presenter.GetGameViewNextPlayerChipColor(), cx::model::MakeBlue());
    ASSERT_EQ(presenter.GetGameViewNextPlayerName() , "Jane Doe");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_ChipDropped_BoardInformationUpdated)
{
    // We create a new game to update the active player chip:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    const auto& presenter = GetPresenter();
    auto boardColors = presenter.GetGameViewChipColors();

    // Initial state:
    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [](const cx::model::ChipColor& p_color)
                                {
                                    return p_color == cx::model::MakeTransparent();
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
                                [&infoModel](const cx::model::ChipColor& p_color)
                                {
                                    const cx::model::IChip& activePlayerChip = infoModel.GetActivePlayer().GetChip();
                                    return p_color == activePlayerChip.GetColor();
                                }));
    }
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_GameReinitialized_BoardInformationUpdated)
{
    // We create a new game to update the active player chip:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    // Initial state:
    const auto& presenter = GetPresenter();
    auto boardColors = presenter.GetGameViewChipColors();

    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [](const cx::model::ChipColor& p_color)
                                {
                                    return p_color == cx::model::MakeTransparent();
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
                                [&infoModel](const cx::model::ChipColor& p_color)
                                {
                                    const cx::model::IChip& activePlayerChip = infoModel.GetActivePlayer().GetChip();
                                    return p_color == activePlayerChip.GetColor();
                                }));
    }
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_DiscDropUndone_BoardInformationUpdated)
{
    // We create a new game to update the active player chip:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    // Initial state:
    const auto& presenter = GetPresenter();
    auto boardColors = presenter.GetGameViewChipColors();

    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [](const cx::model::ChipColor& p_color)
                                {
                                    return p_color == cx::model::MakeTransparent();
                                }));
    }


    // We undo:
    auto& undoRedoModel = GetUndoRedoModel();
    undoRedoModel.Undo();

    // Updated state:
    auto& infoModel = GetGameInformationModel();
    boardColors = presenter.GetGameViewChipColors();
    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [&infoModel](const cx::model::ChipColor& p_color)
                                {
                                    const cx::model::IChip& activePlayerChip = infoModel.GetActivePlayer().GetChip();
                                    return p_color == activePlayerChip.GetColor();
                                }));
    }
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/Update_DiscDropRedone_BoardInformationUpdated)
{
    // We create a new game to update the active player chip:
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    // Initial state:
    const auto& presenter = GetPresenter();
    auto boardColors = presenter.GetGameViewChipColors();

    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [](const cx::model::ChipColor& p_color)
                                {
                                    return p_color == cx::model::MakeTransparent();
                                }));
    }


    // We redo:
    auto& undoRedoModel = GetUndoRedoModel();
    undoRedoModel.Redo();

    // Updated state:
    auto& infoModel = GetGameInformationModel();
    boardColors = presenter.GetGameViewChipColors();
    for(const auto& row : boardColors)
    {
        ASSERT_TRUE(std::all_of(row.cbegin(),
                                row.cend(),
                                [&infoModel](const cx::model::ChipColor& p_color)
                                {
                                    const cx::model::IChip& activePlayerChip = infoModel.GetActivePlayer().GetChip();
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
    SendNotification(cx::model::ModelNotificationContext::CREATE_NEW_GAME);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_ChipDroppedNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    SendNotification(cx::model::ModelNotificationContext::CHIP_DROPPED);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_GameReinitializedNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    SendNotification(cx::model::ModelNotificationContext::GAME_REINITIALIZED);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_ChipDropRedoneNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    SendNotification(cx::model::ModelNotificationContext::REDO_CHIP_DROPPED);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_ChipMovedLeftOneColumnNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    const auto& presenter = GetPresenter();

    SendNotification(cx::model::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN);
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_ChipMovedRightOneColumnNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    const auto& presenter = GetPresenter();

    SendNotification(cx::model::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(presenter.IsNewGamePossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGamePossible_AllOtherNotifications_FalseReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    const auto& presenter = GetPresenter();

    SendNotification(cx::model::ModelNotificationContext::GAME_ENDED);
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
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    SendNotification(cx::model::ModelNotificationContext::CHIP_DROPPED);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsCurrentGameReinitializationPossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentGameReinitializationPossible_ChipDroppedRedoneNotification_TrueReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    SendNotification(cx::model::ModelNotificationContext::REDO_CHIP_DROPPED);

    const auto& presenter = GetPresenter();
    ASSERT_TRUE(presenter.IsCurrentGameReinitializationPossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentGameReinitializationPossible_AllOtherNotifications_FalseReturned)
{
    auto& actionModel = GetActionsModel();
    actionModel.CreateNewGame(cx::model::NewGameInformation{});

    const auto& presenter = GetPresenter();
    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());

    SendNotification(cx::model::ModelNotificationContext::GAME_ENDED);
    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());

    SendNotification(cx::model::ModelNotificationContext::GAME_REINITIALIZED);
    ASSERT_FALSE(presenter.IsCurrentGameReinitializationPossible());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentPlayerABot_CurrentPlayerIsABot_ReturnsTrue)
{
    UpdatePlayerState(GetGameInformationModel().GetActivePlayer(), cx::model::PlayerType::BOT);
    ASSERT_TRUE(GetPresenter().IsCurrentPlayerABot());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsCurrentPlayerABot_CurrentPlayerIsNotABot_ReturnsFalse)
{
    UpdatePlayerState(GetGameInformationModel().GetActivePlayer(), cx::model::PlayerType::HUMAN);
    ASSERT_FALSE(GetPresenter().IsCurrentPlayerABot());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetBotTarget_ValidTarget_TargetReturned)
{
    ASSERT_TRUE(GetPresenter().GetBotTarget() == 5u);
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
