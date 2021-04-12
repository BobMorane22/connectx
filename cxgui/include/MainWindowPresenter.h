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
    class IUndoRedo;
}

namespace cxgui
{

class MainWindowPresenter : public cxgui::IMainWindowPresenter
{

public:

    MainWindowPresenter(const cxmodel::IConnectXLimits& p_modealAsLimits,
                        const cxmodel::IConnectXGameInformation& p_modelAsGameInformation,
                        const cxmodel::IUndoRedo& p_modelAsUndoRedo);

///@{ @name Main Window
// -----------------------------------------------------------------------------------------------
    std::string GetWindowTitle() const override;
    std::string GetMenuLabel(MenuItem p_menuItem) const override;
    bool IsNewGamePossible() const override;
    bool IsCurrentGameReinitializationPossible() const override;
    bool IsUndoPossible() const override;
    bool IsRedoPossible() const override;

///@}

///@{ @name New Game View
// -----------------------------------------------------------------------------------------------
    std::string GetNewGameViewTitle() const override;

    std::string GetNewGameViewGameSectionTitle() const override;
    std::string GetNewGameViewInARowLabelText() const override;

    std::string GetNewGameViewBoardSectionTitle() const override;
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

    size_t GetNewGameViewMinInARowValue() const override;
    size_t GetNewGameViewMaxInARowValue() const override;
    size_t GetNewGameViewMinBoardWidthValue() const override;
    size_t GetNewGameViewMaxBoardWidthValue() const override;
    size_t GetNewGameViewMinBoardHeightValue() const override;
    size_t GetNewGameViewMaxBoardHeightValue() const override;

    cxmodel::Status IsInARowValueValid(size_t p_inARowValue) const override;
    cxmodel::Status AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) override;
    cxmodel::Status ArePlayersInformationValid(const std::vector<std::string>& p_playerNames,
                                               const std::vector<cxmodel::ChipColor>& p_chipColors) override;
    cxmodel::Status IsNewGameWinnable(size_t p_inARowValue,
                                      size_t p_nbOfPlayers,
                                      size_t p_boardHeight,
                                      size_t p_boardWidth) const override;

///@}

///@{ @name Game View
// -----------------------------------------------------------------------------------------------
    std::string GetGameViewTitle() const override;

    cxmodel::ChipColor GetGameViewActivePlayerChipColor() const override;
    cxmodel::ChipColor GetGameViewNextPlayerChipColor() const override;

    std::string GetGameViewActivePlayerLabelText() const override;
    std::string GetGameViewNextPlayerLabelText() const override;

    std::string GetGameViewActivePlayerName() const override;
    std::string GetGameViewNextPlayerName() const override;

    size_t GetGameViewBoardWidth() const override;
    size_t GetGameViewBoardHeight() const override;

    const ChipColors& GetGameViewChipColors() const override;

///@}

private:

    void Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject) override;

    void UpdateCreateNewGame();
    void UpdateChipDropped();
    void UpdateGameReinitialized();

    bool IsBoardEmpty() const;

    const cxmodel::IConnectXLimits& m_modelAsLimits;
    const cxmodel::IConnectXGameInformation& m_modelAsGameInformation;
    const cxmodel::IUndoRedo& m_modelAsUndoRedo;
    
    bool m_canRequestNewGame;
    bool m_canCurrentGameBeReinitialized;

    size_t m_currentBoardWidth;
    size_t m_currentBoardHeight;

    cxmodel::Player m_activePlayer;
    cxmodel::Player m_nextPlayer;

    std::vector<std::vector<cxmodel::ChipColor>> m_chipColors;
};

} // namespace cxgui

#endif // MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
