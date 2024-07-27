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
 * @file MainWindowPresenterTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840
#define MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840

#include <exception>
#include <memory>

#include <cxmodel/IConnectXAI.h>
#include <cxmodel/IConnectXGameActions.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IConnectXLimits.h>
#include <cxmodel/IUndoRedo.h>
#include <cxmodel/IVersioning.h>
#include <cxmodel/ModelNotificationContext.h>
#include <cxuicmn/IMainWindowPresenter.h>

class MainWindowPresenterTestFixture : public testing::Test
{

public:

    MainWindowPresenterTestFixture();

    void SendNotification(cx::model::ModelNotificationContext p_context);

    cx::cmn::ui::IMainWindowPresenter& GetPresenter();
    cx::cmn::ui::IGameViewPresenter& GetGameViewPresenter();
    cx::cmn::ui::INewGameViewPresenter& GetNewGameViewPresenter();

    cx::model::IConnectXGameActions& GetActionsModel();
    cx::model::IConnectXGameInformation& GetGameInformationModel();
    cx::model::IConnectXLimits& GetLimitsModel();
    cx::model::IUndoRedo& GetUndoRedoModel();

    void UpdatePlayerState(const cx::model::IPlayer& p_player, cx::model::PlayerType p_newPlayerType);

private:

    class MainWindowPresenterModelMock : public cx::model::ModelSubject,
                                         public cx::model::IVersioning,
                                         public cx::model::IConnectXGameActions,
                                         public cx::model::IConnectXGameInformation,
                                         public cx::model::IConnectXLimits,
                                         public cx::model::IUndoRedo,
                                         public cx::model::IConnectXAI
    {
    public:

        ~MainWindowPresenterModelMock() override = default;

        void SendNotification(cx::model::ModelNotificationContext p_context);
        void UpdatePlayerState(const cx::model::IPlayer& p_player, cx::model::PlayerType p_newPlayerType);

        // IVersionning:
        std::string GetName() const override {return "Connect X";}
        std::string GetVersionNumber() const override {return "v0.0;";}

        // IConnectXGameActions:
        void CreateNewGame(cx::model::NewGameInformation p_gameInformation) override;
        void DropChip(const cx::model::IChip& p_chip, size_t p_column) override;
        void MoveLeftOneColumn() override;
        void MoveRightOneColumn() override;
        void EndCurrentGame() override;
        void ReinitializeCurrentGame() override;

        // IConnectXGameInformation:
        size_t GetCurrentGridHeight() const override {return 6u;}
        size_t GetCurrentGridWidth() const override {return 7u;};
        size_t GetCurrentInARowValue() const override {return 4u;};
        const cx::model::IPlayer& GetActivePlayer() const override {return *m_activePlayer;};
        const cx::model::IPlayer& GetNextPlayer() const override {return *m_nextPlayer;};
        const cx::model::IChip& GetChip(size_t p_row, size_t p_column) const override;
        bool IsWon() const override {throw std::logic_error("Not implemented!");};
        bool IsTie() const override {throw std::logic_error("Not implemented!");};

        // IConnectXLimits:
        size_t GetMinimumGridHeight() const override {return 7u;};
        size_t GetMinimumGridWidth() const override {return 6u;};
        size_t GetMinimumInARowValue() const override {return 3u;};
        size_t GetMaximumGridHeight() const override {return 64u;};
        size_t GetMaximumGridWidth() const override {return 7u;};
        size_t GetMaximumInARowValue() const override {return 8u;};
        size_t GetMinimumNumberOfPlayers() const override {return 2u;};
        size_t GetMaximumNumberOfPlayers() const override {return 10u;};

        // IUndoRedo:
        void Undo() override;
        void Redo() override;
        bool CanUndo() const override {return true;}
        bool CanRedo() const override {return true;}

        // IConnectXAI:
        void ComputeNextDropColumn(cx::model::DropColumnComputation /*p_algorithm*/) override {};
        [[nodiscard]] size_t GetCurrentBotTarget() const override {return 5u;};


    private:

        std::unique_ptr<cx::model::IPlayer> m_activePlayer = cx::model::CreatePlayer("John Doe", cx::model::MakeRed(), cx::model::PlayerType::HUMAN);
        std::unique_ptr<cx::model::IPlayer> m_nextPlayer = cx::model::CreatePlayer("Jane Doe", cx::model::MakeBlue(), cx::model::PlayerType::HUMAN);
    };

private:

    std::unique_ptr<cx::cmn::ui::IMainWindowPresenter> m_presenter;
    std::unique_ptr<MainWindowPresenterModelMock> m_model;
};

#endif // MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840
