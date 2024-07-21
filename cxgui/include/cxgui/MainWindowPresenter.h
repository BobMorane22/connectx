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

#include <cxmodel/IPlayer.h>

#include "IMainWindowPresenter.h"

namespace cx::model
{
    class IConnectXGameInformation;
    class IConnectXLimits;
    class IUndoRedo;
    class IConnectXAI;
}

namespace cx::gui
{

/**********************************************************************************************//**
 * @brief Main window presenter.
 *
 *************************************************************************************************/
class MainWindowPresenter : public cx::gui::IMainWindowPresenter
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_modelAsLimits
     *      A Connect X model (model and game limits).
     * @param p_modelAsGameInformation
     *      A Connect X model (information about the current game).
     * @param p_modelAsUndoRedo
     *      A Connect X model (undo and redo).
     * @param p_modelAsAI
     *      A Connect X model (managed players).
     *
     *********************************************************************************************/
    MainWindowPresenter(const cx::model::IConnectXLimits& p_modelAsLimits,
                        const cx::model::IConnectXGameInformation& p_modelAsGameInformation,
                        const cx::model::IUndoRedo& p_modelAsUndoRedo,
                        const cx::model::IConnectXAI& p_modelAsAI);

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
    std::string GetNewGameViewIsManagedColumnHeaderText() const override;

    std::string GetNewGameViewRemovePlayerButtonText() const override;
    std::string GetNewGameViewAddPlayerButtonText() const override;
    [[nodiscard]] bool CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const override;
    [[nodiscard]] bool CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const override;

    std::string GetNewGameViewStartButtonText() const override;

    size_t GetNewGameViewMinInARowValue() const override;
    size_t GetNewGameViewMaxInARowValue() const override;
    size_t GetNewGameViewMinBoardWidthValue() const override;
    size_t GetNewGameViewMaxBoardWidthValue() const override;
    size_t GetNewGameViewMinBoardHeightValue() const override;
    size_t GetNewGameViewMaxBoardHeightValue() const override;

    [[nodiscard]] size_t GetDefaultInARowValue() const override;
    [[nodiscard]] size_t GetDefaultBoardHeightValue() const override;
    [[nodiscard]] size_t GetDefaultBoardWidthValue() const override;
    [[nodiscard]] std::string GetDefaultPlayerName(size_t p_playerIndex) const override;
    [[nodiscard]] cx::model::ChipColor GetDefaultChipColor(size_t p_playerIndex) const override;
    [[nodiscard]] std::vector<cx::model::ChipColor> GetDefaultChipColors() const override;
    [[nodiscard]] cx::model::PlayerType GetDefaultPlayerType(size_t p_playerIndex) const override;

    cx::model::Status IsInARowValueValid(size_t p_inARowValue) const override;
    cx::model::Status AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) const override;
    cx::model::Status ArePlayerNamesValid(const std::vector<std::string>& p_playerNames) const override;
    cx::model::Status ArePlayerChipColorsValid(const std::vector<cx::model::ChipColor>& p_playerChipColors) const override;
    cx::model::Status ArePlayerTypesValid(const std::vector<cx::model::PlayerType>& p_playerTypes) const override;

    cx::model::Status IsNewGameWinnable(size_t p_inARowValue,
                                      size_t p_nbOfPlayers,
                                      size_t p_boardHeight,
                                      size_t p_boardWidth) const override;

///@}

///@{ @name Game View
// -----------------------------------------------------------------------------------------------
    std::string GetGameViewTitle() const override;

    cx::model::ChipColor GetGameViewActivePlayerChipColor() const override;
    cx::model::ChipColor GetGameViewNextPlayerChipColor() const override;

    std::string GetGameViewActivePlayerLabelText() const override;
    std::string GetGameViewNextPlayerLabelText() const override;

    std::string GetGameViewActivePlayerName() const override;
    std::string GetGameViewNextPlayerName() const override;

    size_t GetGameViewBoardWidth() const override;
    size_t GetGameViewBoardHeight() const override;
    [[nodiscard]] cx::gui::Color GetGameViewBoardColor() const override;
    [[nodiscard]] cx::gui::Color GetGameViewColumnHighlightColor() const override;

    const ChipColors& GetGameViewChipColors() const override;

    [[nodiscard]] bool IsCurrentPlayerABot() const override;
    [[nodiscard]] size_t GetBotTarget() const override;

///@}

private:

    void Update(cx::model::ModelNotificationContext p_context, cx::model::ModelSubject* p_subject) override;

    void UpdateCreateNewGame();
    void UpdateChipDropped();
    void UpdateGameReinitialized();

    bool IsBoardEmpty() const;

    const cx::model::IConnectXLimits& m_modelAsLimits;
    const cx::model::IConnectXGameInformation& m_modelAsGameInformation;
    const cx::model::IUndoRedo& m_modelAsUndoRedo;
    const cx::model::IConnectXAI& m_modelAsAI;
    
    bool m_canRequestNewGame;
    bool m_canCurrentGameBeReinitialized;

    size_t m_currentBoardWidth;
    size_t m_currentBoardHeight;

    std::unique_ptr<cx::model::IPlayer> m_activePlayer;
    std::unique_ptr<cx::model::IPlayer> m_nextPlayer;

    std::vector<std::vector<cx::model::ChipColor>> m_chipColors;
};

} // namespace cx::gui

#endif // MAINWINDOWPRESENTER_H_B80CACC4_E075_49C0_9DFD_29C6C1BCFE67
