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
 * @file MainWindowPresenter.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
#define MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67

#include <string>

#include <cxmodel/include/Player.h>

#include "IMainWindowPresenter.h"

namespace cxmodel
{
    class IConnectXGameInformation;
    class IConnectXLimits;
}

namespace cxgui
{

class MainWindowPresenter : public cxgui::IMainWindowPresenter
{

public:

    MainWindowPresenter(const cxmodel::IConnectXLimits& p_modealAsLimits,
                        const cxmodel::IConnectXGameInformation& p_modelAsGameInformation);

///@{ @name Main Window
// -----------------------------------------------------------------------------------------------
    std::string GetWindowTitle() const override;
    std::string GetMenuLabel(MenuItem p_menuItem) const override;
///@}

///@{ @name New Game View
// -----------------------------------------------------------------------------------------------
    std::string GetNewGameViewTitle() const override;

    std::string GetNewGameViewGameSectionTitle() const override;
    std::string GetNewGameViewInARowLabelText() const override;

    std::string GetNewGameViewGridSectionTitle() const override;
    std::string GetNewGameViewWidthLabelText() const override;
    std::string GetNewGameViewHeightLabelText() const override;

    std::string GetNewGameViewPlayersSectionTitle() const override;
    std::string GetNewGameViewNameColumnHeaderText() const override;
    std::string GetNewGameViewDiscColumnHeaderText() const override;

    std::string GetNewGameViewRemovePlayerButtonText() const override;
    bool CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const override;

    std::string GetNewGameViewAddPlayerButtonText() const override;
    bool CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const override;

    std::string GetNewGameViewStartButtonText() const override;
///@}

///@{ @name Game View
// -----------------------------------------------------------------------------------------------
    std::string GetGameViewTitle() const override;
    std::string GetGameViewMessage() const override;

    cxmodel::ChipColor GetActivePlayerChipColor() const override;
    cxmodel::ChipColor GetNextPlayerChipColor() const override;

    std::string GetActivePlayerLabelText() const override;
    std::string GetNextPlayerLabelText() const override;

    std::string GetActivePlayerName() const override;
    std::string GetNextPlayerName() const override;

    size_t GetBoardWidth() const override;
    size_t GetBoardHeight() const override;
///@}

private:

    void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override;

    const cxmodel::IConnectXLimits& m_modelAsLimits;
    const cxmodel::IConnectXGameInformation& m_modelAsGameInformation;

    std::string m_gameViewMessage = "New game started!";

    size_t m_currentBoardWidth;
    size_t m_currentBoardHeight;

    cxmodel::Player m_activePlayer;
    cxmodel::Player m_nextPlayer;
};

} // namespace cxgui

#endif // MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
