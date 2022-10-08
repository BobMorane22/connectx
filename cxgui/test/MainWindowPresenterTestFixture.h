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
#include <cxgui/IMainWindowPresenter.h>

class MainWindowPresenterTestFixture : public testing::Test
{

public:

    MainWindowPresenterTestFixture();

    void SendNotification(cxmodel::ModelNotificationContext p_context);

    cxgui::IMainWindowPresenter& GetPresenter();
    cxgui::IGameViewPresenter& GetGameViewPresenter();
    cxgui::INewGameViewPresenter& GetNewGameViewPresenter();

    cxmodel::IConnectXGameActions& GetActionsModel();
    cxmodel::IConnectXGameInformation& GetGameInformationModel();
    cxmodel::IConnectXLimits& GetLimitsModel();
    cxmodel::IUndoRedo& GetUndoRedoModel();

    void UpdatePlayerState(const cxmodel::IPlayer& p_player, cxmodel::PlayerType p_newPlayerType);

private:

    class MainWindowPresenterModelMock : public cxmodel::ModelSubject,
                                         public cxmodel::IVersioning,
                                         public cxmodel::IConnectXGameActions,
                                         public cxmodel::IConnectXGameInformation,
                                         public cxmodel::IConnectXLimits,
                                         public cxmodel::IUndoRedo,
                                         public cxmodel::IConnectXAI
    {
    public:

        ~MainWindowPresenterModelMock() override = default;

        void SendNotification(cxmodel::ModelNotificationContext p_context);
        void UpdatePlayerState(const cxmodel::IPlayer& p_player, cxmodel::PlayerType p_newPlayerType);

        // IVersionning:
        std::string GetName() const override {return "Connect X";}
        std::string GetVersionNumber() const override {return "v0.0;";}

        // IConnectXGameActions:
        void CreateNewGame(cxmodel::NewGameInformation p_gameInformation) override;
        void DropChip(const cxmodel::IChip& p_chip, size_t p_column) override;
        void MoveLeftOneColumn() override;
        void MoveRightOneColumn() override;
        void EndCurrentGame() override;
        void ReinitializeCurrentGame() override;

        // IConnectXGameInformation:
        size_t GetCurrentGridHeight() const override {return 6u;}
        size_t GetCurrentGridWidth() const override {return 7u;};
        size_t GetCurrentInARowValue() const override {return 4u;};
        const cxmodel::IPlayer& GetActivePlayer() const override {return *m_activePlayer;};
        const cxmodel::IPlayer& GetNextPlayer() const override {return *m_nextPlayer;};
        const cxmodel::IChip& GetChip(size_t p_row, size_t p_column) const override;
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
        void ComputeNextDropColumn(cxmodel::DropColumnComputation /*p_algorithm*/) override {};
        [[nodiscard]] size_t GetCurrentBotTarget() const override {return 5u;};


    private:

        std::unique_ptr<cxmodel::IPlayer> m_activePlayer = cxmodel::CreatePlayer("John Doe", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN);
        std::unique_ptr<cxmodel::IPlayer> m_nextPlayer = cxmodel::CreatePlayer("Jane Doe", cxmodel::MakeBlue(), cxmodel::PlayerType::HUMAN);
    };

private:

    std::unique_ptr<cxgui::IMainWindowPresenter> m_presenter;
    std::unique_ptr<MainWindowPresenterModelMock> m_model;
};

#endif // MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840
