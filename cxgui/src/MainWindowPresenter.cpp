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

cx::gui::MainWindowPresenter::MainWindowPresenter(const cxmodel::IConnectXLimits& p_modealAsLimits,
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

void cx::gui::MainWindowPresenter::Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject)
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

std::string cx::gui::MainWindowPresenter::GetWindowTitle() const
{
    return "Connect X";
}

std::string cx::gui::MainWindowPresenter::GetMenuLabel(MenuItem p_menuItem) const
{
    return MakeLabel(p_menuItem);
}

bool cx::gui::MainWindowPresenter::IsNewGamePossible() const
{
    return m_canRequestNewGame;
}

bool cx::gui::MainWindowPresenter::IsCurrentGameReinitializationPossible() const
{
    return m_canCurrentGameBeReinitialized;
}

bool cx::gui::MainWindowPresenter::IsUndoPossible() const
{
    return m_modelAsUndoRedo.CanUndo();
}

bool cx::gui::MainWindowPresenter::IsRedoPossible() const
{
    return m_modelAsUndoRedo.CanRedo();
}


/**************************************************************************************************
 *
 *                                            New Game View
 *
 *************************************************************************************************/

std::string cx::gui::MainWindowPresenter::GetNewGameViewTitle() const
{
    return "New Game";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewGameSectionTitle() const
{
    return "Game";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewInARowLabelText() const
{
    return "In a row:";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewBoardSectionTitle() const
{
    return "Board";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewWidthLabelText() const
{
    return "Width:";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewHeightLabelText() const
{
    return "Height:";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewPlayersSectionTitle() const
{
    return "Players";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewNameColumnHeaderText() const
{
    return "Name";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewDiscColumnHeaderText() const
{
    return "Disc";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewIsManagedColumnHeaderText() const
{
    return "Bot";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewRemovePlayerButtonText() const
{
    return "Remove player";
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewAddPlayerButtonText() const
{
    return "Add player";
}

bool cx::gui::MainWindowPresenter::CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers <= m_modelAsLimits.GetMaximumNumberOfPlayers());

    return p_currentNumberOfPlayers > m_modelAsLimits.GetMinimumNumberOfPlayers();
}

bool cx::gui::MainWindowPresenter::CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers <= m_modelAsLimits.GetMaximumNumberOfPlayers());

    return p_currentNumberOfPlayers < m_modelAsLimits.GetMaximumNumberOfPlayers();
}

std::string cx::gui::MainWindowPresenter::GetNewGameViewStartButtonText() const
{
    return "Start";
}

size_t cx::gui::MainWindowPresenter::GetNewGameViewMinInARowValue() const
{
    return m_modelAsLimits.GetMinimumInARowValue();
}

size_t cx::gui::MainWindowPresenter::GetNewGameViewMaxInARowValue() const
{
    return m_modelAsLimits.GetMaximumInARowValue();
}

size_t cx::gui::MainWindowPresenter::GetNewGameViewMinBoardWidthValue() const
{
    return m_modelAsLimits.GetMinimumGridWidth();
}

size_t cx::gui::MainWindowPresenter::GetNewGameViewMaxBoardWidthValue() const
{
    return m_modelAsLimits.GetMaximumGridWidth();
}

size_t cx::gui::MainWindowPresenter::GetNewGameViewMinBoardHeightValue() const
{
    return m_modelAsLimits.GetMinimumGridHeight();
}

size_t cx::gui::MainWindowPresenter::GetNewGameViewMaxBoardHeightValue() const
{
    return m_modelAsLimits.GetMaximumGridHeight();
}

size_t cx::gui::MainWindowPresenter::GetDefaultInARowValue() const
{
    return 4u;
}

size_t cx::gui::MainWindowPresenter::GetDefaultBoardHeightValue() const
{
    return 6u;
}

size_t cx::gui::MainWindowPresenter::GetDefaultBoardWidthValue() const
{
    return 7u;
}

std::string cx::gui::MainWindowPresenter::GetDefaultPlayerName(size_t p_playerIndex) const
{
    std::ostringstream oss;
    oss << "-- Player " << p_playerIndex << " --";

    return oss.str();
}

cxmodel::ChipColor cx::gui::MainWindowPresenter::GetDefaultChipColor(size_t p_playerIndex) const
{
    if(p_playerIndex == 2u)
    {
        return cxmodel::MakeGreen();
    }

    return cxmodel::MakeRed();
}

std::vector<cxmodel::ChipColor> cx::gui::MainWindowPresenter::GetDefaultChipColors() const
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

cxmodel::PlayerType cx::gui::MainWindowPresenter::GetDefaultPlayerType(size_t p_playerIndex) const
{
    if(p_playerIndex == 1u)
    {
        return cxmodel::PlayerType::HUMAN;
    }

    return cxmodel::PlayerType::BOT;
}

cxmodel::Status cx::gui::MainWindowPresenter::IsInARowValueValid(size_t p_inARowValue) const
{
    if(p_inARowValue < GetNewGameViewMinInARowValue() || p_inARowValue > GetNewGameViewMaxInARowValue())
    {
        const std::string errorMessage = MakeInARowValueOutOfLimitsWarningDialog(GetNewGameViewMinInARowValue(),
                                                                                 GetNewGameViewMaxInARowValue());
        return cxmodel::MakeError(errorMessage);
    }

    return cxmodel::MakeSuccess();
}

cxmodel::Status cx::gui::MainWindowPresenter::AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) const
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

cxmodel::Status cx::gui::MainWindowPresenter::ArePlayerNamesValid(const std::vector<std::string>& p_playerNames) const
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

cxmodel::Status cx::gui::MainWindowPresenter::ArePlayerChipColorsValid(const std::vector<cxmodel::ChipColor>& p_playerChipColors) const
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

cxmodel::Status cx::gui::MainWindowPresenter::ArePlayerTypesValid(const std::vector<cxmodel::PlayerType>& p_playerTypes) const
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

cxmodel::Status cx::gui::MainWindowPresenter::IsNewGameWinnable(size_t p_inARowValue,
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

std::string cx::gui::MainWindowPresenter::GetGameViewTitle() const
{
    return "Game";
}

cxmodel::ChipColor cx::gui::MainWindowPresenter::GetGameViewActivePlayerChipColor() const
{
    const cxmodel::IChip& activePlayerChip = m_activePlayer->GetChip();

    return activePlayerChip.GetColor();
}

cxmodel::ChipColor cx::gui::MainWindowPresenter::GetGameViewNextPlayerChipColor() const
{
    const cxmodel::IChip& nextPlayerChip = m_nextPlayer->GetChip();

    return nextPlayerChip.GetColor();
}

std::string cx::gui::MainWindowPresenter::GetGameViewActivePlayerLabelText() const
{
    return "  Active player: ";
}

std::string cx::gui::MainWindowPresenter::GetGameViewNextPlayerLabelText() const
{
    return "  Next player: ";
}

std::string cx::gui::MainWindowPresenter::GetGameViewActivePlayerName() const
{
    return m_activePlayer->GetName();
}

std::string cx::gui::MainWindowPresenter::GetGameViewNextPlayerName() const
{
    return m_nextPlayer->GetName();
}

size_t cx::gui::MainWindowPresenter::GetGameViewBoardWidth() const
{
    return m_currentBoardWidth;
}

size_t cx::gui::MainWindowPresenter::GetGameViewBoardHeight() const
{
    return m_currentBoardHeight;
}

cx::gui::Color cx::gui::MainWindowPresenter::GetGameViewBoardColor() const
{
    return cx::gui::Color{8481u, 8481u, 51143u};
}

cx::gui::Color cx::gui::MainWindowPresenter::GetGameViewColumnHighlightColor() const
{
    return cx::gui::Color{19660u, 19660u, 19660u, 32767u};
}

const cx::gui::IGameViewPresenter::ChipColors& cx::gui::MainWindowPresenter::GetGameViewChipColors() const
{
    return m_chipColors;
}

void cx::gui::MainWindowPresenter::UpdateCreateNewGame()
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

void cx::gui::MainWindowPresenter::UpdateChipDropped()
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

void cx::gui::MainWindowPresenter::UpdateGameReinitialized()
{
    UpdateChipDropped();
}

bool cx::gui::MainWindowPresenter::IsBoardEmpty() const
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

bool cx::gui::MainWindowPresenter::IsCurrentPlayerABot() const
{
    return m_activePlayer->IsManaged();
}

size_t cx::gui::MainWindowPresenter::GetBotTarget() const
{
    return m_modelAsAI.GetCurrentBotTarget();
}
