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

#include <cxmodel/include/IConnectXGameActions.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/IConnectXLimits.h>
#include <cxmodel/include/IVersioning.h>
#include <cxmodel/include/Subject.h>
#include <cxgui/include/IMainWindowPresenter.h>

class MainWindowPresenterTestFixture : public testing::Test
{

public:

    MainWindowPresenterTestFixture();

    cxgui::IMainWindowPresenter& GetPresenter();
    cxgui::IGameViewPresenter& GetGameViewPresenter();
    cxgui::INewGameViewPresenter& GetNewGameViewPresenter();

    cxmodel::IConnectXGameActions& GetActionsModel();
    cxmodel::IConnectXLimits& GetLimitsModel();

private:

    class MainWindowPresenterModelMock : public cxmodel::Subject,
                                         public cxmodel::IVersioning,
                                         public cxmodel::IConnectXGameActions,
                                         public cxmodel::IConnectXGameInformation,
                                         public cxmodel::IConnectXLimits
    {
    public:

        ~MainWindowPresenterModelMock() override = default;

        // IVersionning:
        std::string GetName() const override {return "Connect X";}
        std::string GetVersionNumber() const override {return "v0.0;";}

        // IConnectXGameActions:
        void CreateNewGame(const cxmodel::NewGameInformation& p_gameInformation) override
        {
            (void)p_gameInformation;

            // Here we only notify and let the presenter feed from the hardcoded
            // model mock values. The values in themselves are not important.
            Notify(cxmodel::NotificationContext::CREATE_NEW_GAME);
        }

        // IConnectXGameInformation:
        size_t GetCurrentGridHeight() const override {return 6u;}
        size_t GetCurrentGridWidth() const override {return 7u;};
        size_t GetCurrentInARowValue() const override {return 4u;};
        const cxmodel::Player& GetActivePlayer() const override {return m_ACTIVE_PLAYER;};
        const cxmodel::Player& GetNextPlayer() const override {return m_NEXT_PLAYER;};
        bool IsWon() const override {throw std::logic_error("Not implemented!");};
        bool IsTie() const override {throw std::logic_error("Not implemented!");};
        bool IsEarlyTie() const override {throw std::logic_error("Not implemented!");};

        // IConnectXLimits:
        size_t GetMinimumGridHeight() const override {return 7u;};
        size_t GetMinimumGridWidth() const override {return 6u;};
        size_t GetMinimumInARowValue() const override {return 3u;};
        size_t GetMaximumGridHeight() const override {return 64u;};
        size_t GetMaximumGridWidth() const override {return 7u;};
        size_t GetMaximumInARowValue() const override {return 8u;};
        size_t GetMinimumNumberOfPlayers() const override {return 2u;};
        size_t GetMaximumNumberOfPlayers() const override {return 10u;};

    private:

        const cxmodel::Player m_ACTIVE_PLAYER{"John Doe", cxmodel::MakeRed()};
        const cxmodel::Player m_NEXT_PLAYER{"Jane Doe", cxmodel::MakeBlue()};
    };

private:

    std::unique_ptr<cxgui::IMainWindowPresenter> m_presenter;
    std::unique_ptr<MainWindowPresenterModelMock> m_model;
};

#endif // MAINWINDOWPRESENTERTESTFIXTURE_H_BF5C449E_46ED_4C25_A8AE_98F606AEC840
