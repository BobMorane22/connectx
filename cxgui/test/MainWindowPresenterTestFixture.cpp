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
 * @file MainWindowPresenterTestFixture.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxmodel/IChip.h>
#include <cxgui/MainWindowPresenter.h>

#include "MainWindowPresenterTestFixture.h"

MainWindowPresenterTestFixture::MainWindowPresenterTestFixture()
{
    m_model = std::make_unique<MainWindowPresenterModelMock>();
    EXPECT_TRUE(m_model);

    m_presenter = std::make_unique<cx::gui::MainWindowPresenter>(*m_model, *m_model, *m_model, *m_model);
    EXPECT_TRUE(m_presenter);

    m_model->Attach(m_presenter.get());
}

void MainWindowPresenterTestFixture::SendNotification(cx::model::ModelNotificationContext p_context)
{
    EXPECT_TRUE(m_model);
    m_model->SendNotification(p_context);
}

cx::gui::IMainWindowPresenter& MainWindowPresenterTestFixture::GetPresenter()
{
    EXPECT_TRUE(m_presenter);
    return *m_presenter;
}

cx::gui::IGameViewPresenter& MainWindowPresenterTestFixture::GetGameViewPresenter()
{
    EXPECT_TRUE(m_presenter);
    return *m_presenter;
}

cx::gui::INewGameViewPresenter& MainWindowPresenterTestFixture::GetNewGameViewPresenter()
{
    EXPECT_TRUE(m_presenter);
    return *m_presenter;
}

cx::model::IConnectXGameActions& MainWindowPresenterTestFixture::GetActionsModel()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

cx::model::IConnectXGameInformation& MainWindowPresenterTestFixture::GetGameInformationModel()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

cx::model::IConnectXLimits& MainWindowPresenterTestFixture::GetLimitsModel()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

cx::model::IUndoRedo& MainWindowPresenterTestFixture::GetUndoRedoModel()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

void MainWindowPresenterTestFixture::UpdatePlayerState(const cx::model::IPlayer& p_player, cx::model::PlayerType p_newPlayerType)
{
    EXPECT_TRUE(m_model);
    m_model->UpdatePlayerState(p_player, p_newPlayerType);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::SendNotification(cx::model::ModelNotificationContext p_context)
{
    Notify(p_context);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::UpdatePlayerState(const cx::model::IPlayer& p_player, cx::model::PlayerType p_newPlayerType)
{
    EXPECT_TRUE(m_activePlayer);
    EXPECT_TRUE(m_nextPlayer);

    if(p_player == *m_activePlayer)    
    {
        m_activePlayer = cx::model::CreatePlayer(p_player.GetName(), p_player.GetChip().GetColor(), p_newPlayerType); 

        // Here we only notify and let the presenter feed from the hardcoded
        // model mock values. The values in themselves are not important.
        Notify(cx::model::ModelNotificationContext::CREATE_NEW_GAME);

        return;
    }
    else if(p_player == *m_nextPlayer)
    {
        m_nextPlayer = cx::model::CreatePlayer(p_player.GetName(), p_player.GetChip().GetColor(), p_newPlayerType); 

        // Here we only notify and let the presenter feed from the hardcoded
        // model mock values. The values in themselves are not important.
        Notify(cx::model::ModelNotificationContext::CREATE_NEW_GAME);

        return;
    }

    FAIL() << "The player passed as an argument should be either the active or the next player";
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::CreateNewGame(cx::model::NewGameInformation p_gameInformation)
{
    (void)p_gameInformation;

    // Here we only notify and let the presenter feed from the hardcoded
    // model mock values. The values in themselves are not important.
    Notify(cx::model::ModelNotificationContext::CREATE_NEW_GAME);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::DropChip(const cx::model::IChip& /*p_chip*/, size_t p_column)
{
    ASSERT_TRUE(p_column < GetCurrentGridWidth());

    Notify(cx::model::ModelNotificationContext::CHIP_DROPPED);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::MoveLeftOneColumn()
{
    // Nothing to do...
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::MoveRightOneColumn()
{
    // Nothing to do...
}

const cx::model::IChip& MainWindowPresenterTestFixture::MainWindowPresenterModelMock::GetChip(size_t p_row, size_t p_column) const
{
    EXPECT_TRUE(p_row < GetCurrentGridHeight());
    EXPECT_TRUE(p_column < GetCurrentGridWidth());

    return m_activePlayer->GetChip();
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::EndCurrentGame()
{
    Notify(cx::model::ModelNotificationContext::GAME_ENDED);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::ReinitializeCurrentGame()
{
    // Here we only notify and let the presenter feed from the hardcoded
    // model mock values. The values in themselves are not important.
    Notify(cx::model::ModelNotificationContext::GAME_REINITIALIZED);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::Undo()
{
    // Here we only notify and let the presenter feed from the hardcoded
    // model mock values. The values in themselves are not important.
    Notify(cx::model::ModelNotificationContext::UNDO_CHIP_DROPPED);
}

void MainWindowPresenterTestFixture::MainWindowPresenterModelMock::Redo()
{
    // Here we only notify and let the presenter feed from the hardcoded
    // model mock values. The values in themselves are not important.
    Notify(cx::model::ModelNotificationContext::REDO_CHIP_DROPPED);
}

