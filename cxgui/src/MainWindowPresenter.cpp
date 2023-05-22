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

#include <cxinv/assertion.h>
#include <cxmodel/Disc.h>
#include <cxmodel/NewGameInformation.h>
#include <cxmodel/IConnectXAI.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IConnectXLimits.h>
#include <cxmodel/IUndoRedo.h>
#include <cxgui/MainWindowPresenter.h>

namespace
{

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
                                                const cxmodel::IConnectXGameInformation& p_modelAsGameInformation,
                                                const cxmodel::IUndoRedo& p_modelAsUndoRedo,
                                                const cxmodel::IConnectXAI& p_modelAsAI)
 : m_modelAsLimits{p_modealAsLimits}
 , m_modelAsGameInformation{p_modelAsGameInformation}
 , m_modelAsUndoRedo{p_modelAsUndoRedo}
 , m_modelAsAI{p_modelAsAI}
 , m_canRequestNewGame{false}
 , m_canCurrentGameBeReinitialized{false}
 , m_currentBoardWidth{p_modealAsLimits.GetMinimumGridWidth()}
 , m_currentBoardHeight{p_modealAsLimits.GetMinimumGridHeight()}
{
    m_activePlayer = cxmodel::CreatePlayer("--", cxmodel::MakeTransparent(), cxmodel::PlayerType::HUMAN);
    m_nextPlayer = cxmodel::CreatePlayer("--", cxmodel::MakeTransparent(), cxmodel::PlayerType::HUMAN);
}

void cxgui::MainWindowPresenter::Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject)
{
    if(INL_PRECONDITION(p_subject))
    {
        m_canRequestNewGame = false;
        m_canCurrentGameBeReinitialized = false;

        switch(p_context)
        {
            case cxmodel::ModelNotificationContext::CREATE_NEW_GAME:
            {
                m_canRequestNewGame = true;
                UpdateCreateNewGame();
                break;
            }
            case cxmodel::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN:
            case cxmodel::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN:
            {
                m_canRequestNewGame = true;
                break;
            }
            case cxmodel::ModelNotificationContext::CHIP_DROPPED:
            {
                m_canRequestNewGame = true;
                m_canCurrentGameBeReinitialized = true;
                UpdateChipDropped();
                break;
            }
            case cxmodel::ModelNotificationContext::GAME_REINITIALIZED:
            {
                m_canRequestNewGame = true;
                UpdateGameReinitialized();
                break;
            }
            case cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED:
            {
                m_canRequestNewGame = true;
                m_canCurrentGameBeReinitialized = !IsBoardEmpty();

                UpdateChipDropped();
                break;
            }
            case cxmodel::ModelNotificationContext::REDO_CHIP_DROPPED:
            {
                m_canRequestNewGame = true;
                m_canCurrentGameBeReinitialized = true;
                UpdateChipDropped();
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

bool cxgui::MainWindowPresenter::IsUndoPossible() const
{
    return m_modelAsUndoRedo.CanUndo();
}

bool cxgui::MainWindowPresenter::IsRedoPossible() const
{
    return m_modelAsUndoRedo.CanRedo();
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

std::string cxgui::MainWindowPresenter::GetNewGameViewIsManagedColumnHeaderText() const
{
    return "Bot";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewRemovePlayerButtonText() const
{
    return "Remove player";
}

std::string cxgui::MainWindowPresenter::GetNewGameViewAddPlayerButtonText() const
{
    return "Add player";
}

bool cxgui::MainWindowPresenter::CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers <= m_modelAsLimits.GetMaximumNumberOfPlayers());

    return p_currentNumberOfPlayers > m_modelAsLimits.GetMinimumNumberOfPlayers();
}

bool cxgui::MainWindowPresenter::CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers <= m_modelAsLimits.GetMaximumNumberOfPlayers());

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

size_t cxgui::MainWindowPresenter::GetDefaultInARowValue() const
{
    return 4u;
}

size_t cxgui::MainWindowPresenter::GetDefaultBoardHeightValue() const
{
    return 6u;
}

size_t cxgui::MainWindowPresenter::GetDefaultBoardWidthValue() const
{
    return 7u;
}

std::string cxgui::MainWindowPresenter::GetDefaultPlayerName(size_t p_playerIndex) const
{
    std::ostringstream oss;
    oss << "-- Player " << p_playerIndex << " --";

    return oss.str();
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetDefaultChipColor(size_t p_playerIndex) const
{
    if(p_playerIndex == 2u)
    {
        return cxmodel::MakeGreen();
    }

    return cxmodel::MakeRed();
}

std::vector<cxmodel::ChipColor> cxgui::MainWindowPresenter::GetDefaultChipColors() const
{
    std::vector<cxmodel::ChipColor> colors;

    colors.push_back(cxmodel::MakeRed());
    colors.push_back(cxmodel::MakeGreen());
    colors.push_back(cxmodel::MakeYellow());
    colors.push_back(cxmodel::MakeBlue());
    colors.push_back(cxmodel::MakePink());
    colors.push_back(cxmodel::MakeOrange());
    colors.push_back(cxmodel::MakeAqua());
    colors.push_back(cxmodel::MakeBlack());
    colors.push_back(cxmodel::MakeLilac());
    colors.push_back(cxmodel::MakeSalmon());

    return colors;
}

cxmodel::PlayerType cxgui::MainWindowPresenter::GetDefaultPlayerType(size_t p_playerIndex) const
{
    if(p_playerIndex == 1u)
    {
        return cxmodel::PlayerType::HUMAN;
    }

    return cxmodel::PlayerType::BOT;
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

cxmodel::Status cxgui::MainWindowPresenter::AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) const
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

cxmodel::Status cxgui::MainWindowPresenter::ArePlayerNamesValid(const std::vector<std::string>& p_playerNames) const
{
    if(std::any_of(p_playerNames.cbegin(),
                   p_playerNames.cend(),
                   [](const std::string& p_name)
                   {
                       return p_name.empty();
                   }))
              {
                  return cxmodel::MakeError("Player names cannot be empty.");
              }

    return cxmodel::MakeSuccess();
}

cxmodel::Status cxgui::MainWindowPresenter::ArePlayerChipColorsValid(const std::vector<cxmodel::ChipColor>& p_playerChipColors) const
{
   // Chip colors (should not have duplicates):
   bool duplicateColorsExist = false;
   for(const auto& color : p_playerChipColors)
   {
       const size_t count = std::count(p_playerChipColors.cbegin(), p_playerChipColors.cend(), color);

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

cxmodel::Status cxgui::MainWindowPresenter::ArePlayerTypesValid(const std::vector<cxmodel::PlayerType>& p_playerTypes) const
{
    if(std::any_of(p_playerTypes.cbegin(),
                   p_playerTypes.cend(),
                   [](cxmodel::PlayerType p_type)
                   {
                       return p_type == cxmodel::PlayerType::HUMAN;
                   }))
              {
                  return cxmodel::MakeSuccess();
              }

    return cxmodel::MakeError("At least one player must not be a bot.");
}

cxmodel::Status cxgui::MainWindowPresenter::IsNewGameWinnable(size_t p_inARowValue,
                                                              size_t p_nbOfPlayers,
                                                              size_t p_boardHeight,
                                                              size_t p_boardWidth) const
{
    // Are there enough locations on the board so that the minimum amount
    // of moves required by a user to win is reachable?
    const size_t nbLocations = p_boardHeight * p_boardWidth;
    if(nbLocations < (p_nbOfPlayers - 1u)*(p_inARowValue - 1u) + p_inARowValue)
    {
        return cxmodel::MakeError("There is not enough room on the board. Adjust the number of players or the in-a-row value.");
    }

    // Can the in-a-row value fit on the board?
    if(p_inARowValue > std::max<size_t>(p_boardHeight, p_boardWidth))
    {
        return cxmodel::MakeError("The in-a-row value does not fit on the board.");
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
    const cxmodel::IChip& activePlayerChip = m_activePlayer->GetChip();

    return activePlayerChip.GetColor();
}

cxmodel::ChipColor cxgui::MainWindowPresenter::GetGameViewNextPlayerChipColor() const
{
    const cxmodel::IChip& nextPlayerChip = m_nextPlayer->GetChip();

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
    return m_activePlayer->GetName();
}

std::string cxgui::MainWindowPresenter::GetGameViewNextPlayerName() const
{
    return m_nextPlayer->GetName();
}

size_t cxgui::MainWindowPresenter::GetGameViewBoardWidth() const
{
    return m_currentBoardWidth;
}

size_t cxgui::MainWindowPresenter::GetGameViewBoardHeight() const
{
    return m_currentBoardHeight;
}

cxgui::Color cxgui::MainWindowPresenter::GetGameViewBoardColor() const
{
    return cxgui::Color{8481u, 8481u, 51143u};
}

cxgui::Color cxgui::MainWindowPresenter::GetGameViewColumnHighlightColor() const
{
    return cxgui::Color{19660u, 19660u, 19660u, 32767u};
}

const cxgui::IGameViewPresenter::ChipColors& cxgui::MainWindowPresenter::GetGameViewChipColors() const
{
    return m_chipColors;
}

void cxgui::MainWindowPresenter::UpdateCreateNewGame()
{
    m_chipColors.clear();

    m_currentBoardWidth = m_modelAsGameInformation.GetCurrentGridWidth();
    m_currentBoardHeight = m_modelAsGameInformation.GetCurrentGridHeight();

    m_activePlayer = cxmodel::CreatePlayer(m_modelAsGameInformation.GetActivePlayer().GetName(),
                                           m_modelAsGameInformation.GetActivePlayer().GetChip().GetColor(),
                                           m_modelAsGameInformation.GetActivePlayer().IsManaged() ? cxmodel::PlayerType::BOT : cxmodel::PlayerType::HUMAN);

    m_nextPlayer = cxmodel::CreatePlayer(m_modelAsGameInformation.GetNextPlayer().GetName(),
                                         m_modelAsGameInformation.GetNextPlayer().GetChip().GetColor(),
                                         m_modelAsGameInformation.GetNextPlayer().IsManaged() ? cxmodel::PlayerType::BOT : cxmodel::PlayerType::HUMAN);

    // Reserve the board color memory:
    for(size_t row = 0u; row < m_currentBoardHeight; ++row)
    {
        m_chipColors.push_back(std::vector<cxmodel::ChipColor>(m_currentBoardWidth, cxmodel::MakeTransparent()));
    }
}

void cxgui::MainWindowPresenter::UpdateChipDropped()
{
    // Update players information:
    m_activePlayer = cxmodel::CreatePlayer(m_modelAsGameInformation.GetActivePlayer().GetName(),
                                           m_modelAsGameInformation.GetActivePlayer().GetChip().GetColor(),
                                           m_modelAsGameInformation.GetActivePlayer().IsManaged() ? cxmodel::PlayerType::BOT : cxmodel::PlayerType::HUMAN);

    m_nextPlayer = cxmodel::CreatePlayer(m_modelAsGameInformation.GetNextPlayer().GetName(),
                                         m_modelAsGameInformation.GetNextPlayer().GetChip().GetColor(),
                                         m_modelAsGameInformation.GetNextPlayer().IsManaged() ? cxmodel::PlayerType::BOT : cxmodel::PlayerType::HUMAN);
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

bool cxgui::MainWindowPresenter::IsBoardEmpty() const
{
    bool isBoardEmpty = true;
    for(size_t row = 0u; row < m_modelAsGameInformation.GetCurrentGridHeight(); ++row)
    {
        for(size_t column = 0u; column < m_modelAsGameInformation.GetCurrentGridWidth(); ++column)
        {
            const cxmodel::IChip& chip = m_modelAsGameInformation.GetChip(row, column);
            if(chip.GetColor() != cxmodel::MakeTransparent())
            {
                isBoardEmpty = false;
                break;
            }
        }
    }

    return isBoardEmpty;
}

bool cxgui::MainWindowPresenter::IsCurrentPlayerABot() const
{
    return m_activePlayer->IsManaged();
}

size_t cxgui::MainWindowPresenter::GetBotTarget() const
{
    return m_modelAsAI.GetCurrentBotTarget();
}
