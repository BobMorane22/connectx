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
 * @file MainWindowPresenter.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <algorithm>
#include <sstream>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/Disc.h>
#include <cxmodel/include/NewGameInformation.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/IConnectXLimits.h>

#include <MainWindowPresenter.h>

namespace
{

const cxmodel::Player NO_PLAYER = {"--", cxmodel::MakeTransparent()};

std::string MakeValueOutOfLimitsWarningDialog(const std::string& p_valueName, size_t p_lower, size_t p_upper)
{
    std::ostringstream oss;

    oss << "The " << p_valueName << " value should be between " << p_lower << " and " << p_upper << " inclusively.";

    return oss.str();
}

std::string MakeInARowValueOutOfLimitsWarningDialog(size_t p_lower, size_t p_upper)
{
    return MakeValueOutOfLimitsWarningDialog("in-a-row", p_lower, p_upper);
}

std::string MakeBoardWidthValueOutOfLimitsWarningDialog(size_t p_lower, size_t p_upper)
{
    return MakeValueOutOfLimitsWarningDialog("board width", p_lower, p_upper);
}

std::string MakeBoardHeightValueOutOfLimitsWarningDialog(size_t p_lower, size_t p_upper)
{
    return MakeValueOutOfLimitsWarningDialog("board height", p_lower, p_upper);
}

} // namespace

cxgui::MainWindowPresenter::MainWindowPresenter(const cxmodel::IConnectXLimits& p_modealAsLimits,
                                                const cxmodel::IConnectXGameInformation& p_modelAsGameInformation)
 : m_modelAsLimits{p_modealAsLimits}
 , m_modelAsGameInformation{p_modelAsGameInformation}
 , m_canRequestNewGame{false}
 , m_canCurrentGameBeReinitialized{false}
 , m_currentBoardWidth{p_modealAsLimits.GetMinimumGridWidth()}
 , m_currentBoardHeight{p_modealAsLimits.GetMinimumGridHeight()}
 , m_activePlayer{NO_PLAYER}
 , m_nextPlayer{NO_PLAYER}
{
}

void cxgui::MainWindowPresenter::Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject)
{
    if(PRECONDITION(p_subject))
    {
        m_canRequestNewGame = false;
        m_canCurrentGameBeReinitialized = false;

        switch(p_context)
        {
            case cxmodel::NotificationContext::CREATE_NEW_GAME:
            {
                m_canRequestNewGame = true;
                UpdateCreateNewGame();
                break;
            }
            case cxmodel::NotificationContext::CHIP_DROPPED:
            {
                m_canRequestNewGame = true;
                m_canCurrentGameBeReinitialized = true;
                UpdateChipDropped();
                break;
            }
            case cxmodel::NotificationContext::GAME_REINITIALIZED:
            {
                m_canRequestNewGame = true;
                UpdateGameReinitialized();
                break;
            }
            default:
                break;
        }

        Notify(p_context);
    }
}

std::string cxgui::MainWindowPresenter::GetWindowTitle() const
{
    return "Connect X";
}

std::string cxgui::MainWindowPresenter::GetMenuLabel(MenuItem p_menuItem) const
{
    return MakeLabel(p_menuItem);
}

bool cxgui::MainWindowPresenter::IsNewGamePossible() const
{
    return m_canRequestNewGame;
}

bool cxgui::MainWindowPresenter::IsCurrentGameReinitializationPossible() const
{
    return m_canCurrentGameBeReinitialized;
}

/**************************************************************************************************
 *
 *                                            New Game View
 *
 *************************************************************************************************/

std::string cxgui::MainWindowPresenter::GetNewGameViewTitle() const
{
    return "New Game";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewGameSectionTitle() const
{
    return "Game";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewInARowLabelText() const
{
    return "In a row:";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewBoardSectionTitle() const
{
    return "Board";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewWidthLabelText() const
{
    return "Width:";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewHeightLabelText() const
{
    return "Height:";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewPlayersSectionTitle() const
{
    return "Players";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewNameColumnHeaderText() const
{
    return "Name";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewDiscColumnHeaderText() const
{
    return "Disc";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewRemovePlayerButtonText() const
{
    return "Remove player";
}

bool cxgui::MainWindowPresenter::CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers < (m_modelAsLimits.GetMaximumNumberOfPlayers() + 1));

    return p_currentNumberOfPlayers > m_modelAsLimits.GetMinimumNumberOfPlayers();
}

std::string cxgui::MainWindowPresenter::GetNewGameViewAddPlayerButtonText() const
{
    return "Add player";
}

bool cxgui::MainWindowPresenter::CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers < (m_modelAsLimits.GetMaximumNumberOfPlayers() + 1));

    return p_currentNumberOfPlayers < m_modelAsLimits.GetMaximumNumberOfPlayers();
}

std::string cxgui::MainWindowPresenter::GetNewGameViewStartButtonText() const
{
    return "Start";
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMinInARowValue() const
{
    return m_modelAsLimits.GetMinimumInARowValue();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMaxInARowValue() const
{
    return m_modelAsLimits.GetMaximumInARowValue();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMinBoardWidthValue() const
{
    return m_modelAsLimits.GetMinimumGridWidth();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMaxBoardWidthValue() const
{
    return m_modelAsLimits.GetMaximumGridWidth();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMinBoardHeightValue() const
{
    return m_modelAsLimits.GetMinimumGridHeight();
}

size_t cxgui::MainWindowPresenter::GetNewGameViewMaxBoardHeightValue() const
{
    return m_modelAsLimits.GetMaximumGridHeight();
}

cxmodel::Status cxgui::MainWindowPresenter::IsInARowValueValid(size_t p_inARowValue) const
{
    if(p_inARowValue < GetNewGameViewMinInARowValue() || p_inARowValue > GetNewGameViewMaxInARowValue())
    {
        const std::string errorMessage = MakeInARowValueOutOfLimitsWarningDialog(GetNewGameViewMinInARowValue(),
                                                                                 GetNewGameViewMaxInARowValue());
        return cxmodel::MakeError(errorMessage);
    }

    return cxmodel::MakeSuccess();
}

cxmodel::Status cxgui::MainWindowPresenter::AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth)
{
    if(p_boardHeight < GetNewGameViewMinBoardHeightValue() ||
       p_boardHeight > GetNewGameViewMaxBoardHeightValue())
    {
        const std::string errorMessage = MakeBoardHeightValueOutOfLimitsWarningDialog(GetNewGameViewMinBoardHeightValue(),
                                                                                      GetNewGameViewMaxBoardHeightValue());
        return cxmodel::MakeError(errorMessage);
    }

    if(p_boardWidth < GetNewGameViewMinBoardWidthValue() ||
       p_boardWidth > GetNewGameViewMaxBoardWidthValue())
    {
        const std::string errorMessage = MakeBoardWidthValueOutOfLimitsWarningDialog(GetNewGameViewMinBoardWidthValue(),
                                                                                     GetNewGameViewMaxBoardWidthValue());
        return cxmodel::MakeError(errorMessage);
    }

    return cxmodel::MakeSuccess();
}

cxmodel::Status cxgui::MainWindowPresenter::ArePlayersInformationValid(const std::vector<std::string>& p_playerNames,
                                                                       const std::vector<cxmodel::ChipColor>& p_chipColors)
{
    // Player names (should not be empty):
    const bool emptyNamesExist = std::any_of(p_playerNames.cbegin(),
                                             p_playerNames.cend(),
                                             [](const std::string& p_name)
                                             {
                                                 return p_name.empty();
                                             });

   if(emptyNamesExist)
   {
       return cxmodel::MakeError("Player names cannot be empty.");
   }

   // Chip colors (should not have duplicates):
   bool duplicateColorsExist = false;
   for(const auto& color : p_chipColors)
   {
       const size_t count = std::count(p_chipColors.cbegin(), p_chipColors.cend(), color);

       if(count > 1)
       {
           duplicateColorsExist = true;
           break;
       }
   }

   if(duplicateColorsExist)
   {
       return cxmodel::MakeError("Discs must have different colors.");
   }

   return cxmodel::MakeSuccess();
}


/**************************************************************************************************
 *
 *                                              Game View
 *
 *************************************************************************************************/

std::string cxgui::MainWindowPresenter::GetGameViewTitle() const
{
    return "Game";
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetGameViewActivePlayerChipColor() const
{
    const cxmodel::IChip& activePlayerChip = m_activePlayer.GetChip();

    return activePlayerChip.GetColor();
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetGameViewNextPlayerChipColor() const
{
    const cxmodel::IChip& nextPlayerChip = m_nextPlayer.GetChip();

    return nextPlayerChip.GetColor();
}

std::string cxgui::MainWindowPresenter::GetGameViewActivePlayerLabelText() const
{
    return "  Active player: ";
}

std::string cxgui::MainWindowPresenter::GetGameViewNextPlayerLabelText() const
{
    return "  Next player: ";
}

std::string cxgui::MainWindowPresenter::GetGameViewActivePlayerName() const
{
    return m_activePlayer.GetName();
}

std::string cxgui::MainWindowPresenter::GetGameViewNextPlayerName() const
{
    return m_nextPlayer.GetName();
}

size_t cxgui::MainWindowPresenter::GetGameViewBoardWidth() const
{
    return m_currentBoardWidth;
}

size_t cxgui::MainWindowPresenter::GetGameViewBoardHeight() const
{
    return m_currentBoardHeight;
}

const cxgui::IGameViewPresenter::ChipColors& cxgui::MainWindowPresenter::GetGameViewChipColors() const
{
    return m_chipColors;
}

void cxgui::MainWindowPresenter::UpdateCreateNewGame()
{
    m_currentBoardWidth = m_modelAsGameInformation.GetCurrentGridWidth();
    m_currentBoardHeight = m_modelAsGameInformation.GetCurrentGridHeight();

    m_activePlayer = m_modelAsGameInformation.GetActivePlayer();
    m_nextPlayer = m_modelAsGameInformation.GetNextPlayer();

    // Reserve the board color memory:
    for(size_t row = 0u; row < m_currentBoardHeight; ++row)
    {
        m_chipColors.push_back(std::vector<cxmodel::ChipColor>(m_currentBoardWidth, cxmodel::MakeTransparent()));
    }
}

void cxgui::MainWindowPresenter::UpdateChipDropped()
{
    // Update players information:
    m_activePlayer = m_modelAsGameInformation.GetActivePlayer();
    m_nextPlayer = m_modelAsGameInformation.GetNextPlayer();

    // Update board information:
    for(size_t row = 0u; row < m_currentBoardHeight; ++row)
    {
        for(size_t column = 0u; column < m_currentBoardWidth; ++column)
        {
            const cxmodel::IChip& chip = m_modelAsGameInformation.GetChip(row, column);
            m_chipColors[m_currentBoardHeight - row - 1][column] = chip.GetColor();
        }
    }
}

void cxgui::MainWindowPresenter::UpdateGameReinitialized()
{
    UpdateChipDropped();
}
