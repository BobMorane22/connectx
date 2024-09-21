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
#include <cxui/MainWindowPresenter.h>

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

cx::ui::MainWindowPresenter::MainWindowPresenter(const cx::model::IConnectXLimits& p_modealAsLimits,
                                                const cx::model::IConnectXGameInformation& p_modelAsGameInformation,
                                                const cx::model::IUndoRedo& p_modelAsUndoRedo,
                                                const cx::model::IConnectXAI& p_modelAsAI)
 : m_modelAsLimits{p_modealAsLimits}
 , m_modelAsGameInformation{p_modelAsGameInformation}
 , m_modelAsUndoRedo{p_modelAsUndoRedo}
 , m_modelAsAI{p_modelAsAI}
 , m_canRequestNewGame{false}
 , m_canCurrentGameBeReinitialized{false}
 , m_currentBoardWidth{p_modealAsLimits.GetMinimumGridWidth()}
 , m_currentBoardHeight{p_modealAsLimits.GetMinimumGridHeight()}
{
    m_activePlayer = cx::model::CreatePlayer("--", cx::model::MakeTransparent(), cx::model::PlayerType::HUMAN);
    m_nextPlayer = cx::model::CreatePlayer("--", cx::model::MakeTransparent(), cx::model::PlayerType::HUMAN);
}

void cx::ui::MainWindowPresenter::Update(cx::model::ModelNotificationContext p_context, cx::model::ModelSubject* p_subject)
{
    if(INL_PRECONDITION(p_subject))
    {
        m_canRequestNewGame = false;
        m_canCurrentGameBeReinitialized = false;

        switch(p_context)
        {
            case cx::model::ModelNotificationContext::CREATE_NEW_GAME:
            {
                m_canRequestNewGame = true;
                UpdateCreateNewGame();
                break;
            }
            case cx::model::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN:
            case cx::model::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN:
            {
                m_canRequestNewGame = true;
                break;
            }
            case cx::model::ModelNotificationContext::CHIP_DROPPED:
            {
                m_canRequestNewGame = true;
                m_canCurrentGameBeReinitialized = true;
                UpdateChipDropped();
                break;
            }
            case cx::model::ModelNotificationContext::GAME_REINITIALIZED:
            {
                m_canRequestNewGame = true;
                UpdateGameReinitialized();
                break;
            }
            case cx::model::ModelNotificationContext::UNDO_CHIP_DROPPED:
            {
                m_canRequestNewGame = true;
                m_canCurrentGameBeReinitialized = !IsBoardEmpty();

                UpdateChipDropped();
                break;
            }
            case cx::model::ModelNotificationContext::REDO_CHIP_DROPPED:
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

std::string cx::ui::MainWindowPresenter::GetWindowTitle() const
{
    return "Connect X";
}

std::string cx::ui::MainWindowPresenter::GetMenuLabel(MenuItem p_menuItem) const
{
    return MakeLabel(p_menuItem);
}

bool cx::ui::MainWindowPresenter::IsNewGamePossible() const
{
    return m_canRequestNewGame;
}

bool cx::ui::MainWindowPresenter::IsCurrentGameReinitializationPossible() const
{
    return m_canCurrentGameBeReinitialized;
}

bool cx::ui::MainWindowPresenter::IsUndoPossible() const
{
    return m_modelAsUndoRedo.CanUndo();
}

bool cx::ui::MainWindowPresenter::IsRedoPossible() const
{
    return m_modelAsUndoRedo.CanRedo();
}


/**************************************************************************************************
 *
 *                                            New Game View
 *
 *************************************************************************************************/

std::string cx::ui::MainWindowPresenter::GetNewGameViewTitle() const
{
    return "New Game";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewGameSectionTitle() const
{
    return "Game";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewInARowLabelText() const
{
    return "In a row:";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewBoardSectionTitle() const
{
    return "Board";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewWidthLabelText() const
{
    return "Width:";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewHeightLabelText() const
{
    return "Height:";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewPlayersSectionTitle() const
{
    return "Players";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewNameColumnHeaderText() const
{
    return "Name";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewDiscColumnHeaderText() const
{
    return "Disc";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewIsManagedColumnHeaderText() const
{
    return "Bot";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewRemovePlayerButtonText() const
{
    return "Remove player";
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewAddPlayerButtonText() const
{
    return "Add player";
}

bool cx::ui::MainWindowPresenter::CanRemoveAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers >= m_modelAsLimits.GetMinimumNumberOfPlayers());
    PRECONDITION(p_currentNumberOfPlayers <= m_modelAsLimits.GetMaximumNumberOfPlayers());

    return p_currentNumberOfPlayers > m_modelAsLimits.GetMinimumNumberOfPlayers();
}

bool cx::ui::MainWindowPresenter::CanAddAnotherPlayer(std::size_t p_currentNumberOfPlayers) const
{
    PRECONDITION(p_currentNumberOfPlayers <= m_modelAsLimits.GetMaximumNumberOfPlayers());

    return p_currentNumberOfPlayers < m_modelAsLimits.GetMaximumNumberOfPlayers();
}

std::string cx::ui::MainWindowPresenter::GetNewGameViewStartButtonText() const
{
    return "Start";
}

size_t cx::ui::MainWindowPresenter::GetNewGameViewMinInARowValue() const
{
    return m_modelAsLimits.GetMinimumInARowValue();
}

size_t cx::ui::MainWindowPresenter::GetNewGameViewMaxInARowValue() const
{
    return m_modelAsLimits.GetMaximumInARowValue();
}

size_t cx::ui::MainWindowPresenter::GetNewGameViewMinBoardWidthValue() const
{
    return m_modelAsLimits.GetMinimumGridWidth();
}

size_t cx::ui::MainWindowPresenter::GetNewGameViewMaxBoardWidthValue() const
{
    return m_modelAsLimits.GetMaximumGridWidth();
}

size_t cx::ui::MainWindowPresenter::GetNewGameViewMinBoardHeightValue() const
{
    return m_modelAsLimits.GetMinimumGridHeight();
}

size_t cx::ui::MainWindowPresenter::GetNewGameViewMaxBoardHeightValue() const
{
    return m_modelAsLimits.GetMaximumGridHeight();
}

size_t cx::ui::MainWindowPresenter::GetDefaultInARowValue() const
{
    return 4u;
}

size_t cx::ui::MainWindowPresenter::GetDefaultBoardHeightValue() const
{
    return 6u;
}

size_t cx::ui::MainWindowPresenter::GetDefaultBoardWidthValue() const
{
    return 7u;
}

std::string cx::ui::MainWindowPresenter::GetDefaultPlayerName(size_t p_playerIndex) const
{
    std::ostringstream oss;
    oss << "-- Player " << p_playerIndex << " --";

    return oss.str();
}

cx::model::ChipColor cx::ui::MainWindowPresenter::GetDefaultChipColor(size_t p_playerIndex) const
{
    if(p_playerIndex == 2u)
    {
        return cx::model::MakeGreen();
    }

    return cx::model::MakeRed();
}

std::vector<cx::model::ChipColor> cx::ui::MainWindowPresenter::GetDefaultChipColors() const
{
    std::vector<cx::model::ChipColor> colors;

    colors.push_back(cx::model::MakeRed());
    colors.push_back(cx::model::MakeGreen());
    colors.push_back(cx::model::MakeYellow());
    colors.push_back(cx::model::MakeBlue());
    colors.push_back(cx::model::MakePink());
    colors.push_back(cx::model::MakeOrange());
    colors.push_back(cx::model::MakeAqua());
    colors.push_back(cx::model::MakeBlack());
    colors.push_back(cx::model::MakeLilac());
    colors.push_back(cx::model::MakeSalmon());

    return colors;
}

cx::model::PlayerType cx::ui::MainWindowPresenter::GetDefaultPlayerType(size_t p_playerIndex) const
{
    if(p_playerIndex == 1u)
    {
        return cx::model::PlayerType::HUMAN;
    }

    return cx::model::PlayerType::BOT;
}

cx::cmn::Status cx::ui::MainWindowPresenter::IsInARowValueValid(size_t p_inARowValue) const
{
    if(p_inARowValue < GetNewGameViewMinInARowValue() || p_inARowValue > GetNewGameViewMaxInARowValue())
    {
        const std::string errorMessage = MakeInARowValueOutOfLimitsWarningDialog(GetNewGameViewMinInARowValue(),
                                                                                 GetNewGameViewMaxInARowValue());
        return cx::cmn::MakeError(errorMessage);
    }

    return cx::cmn::MakeSuccess();
}

cx::cmn::Status cx::ui::MainWindowPresenter::AreBoardDimensionsValid(size_t p_boardHeight, size_t p_boardWidth) const
{
    if(p_boardHeight < GetNewGameViewMinBoardHeightValue() ||
       p_boardHeight > GetNewGameViewMaxBoardHeightValue())
    {
        const std::string errorMessage = MakeBoardHeightValueOutOfLimitsWarningDialog(GetNewGameViewMinBoardHeightValue(),
                                                                                      GetNewGameViewMaxBoardHeightValue());
        return cx::cmn::MakeError(errorMessage);
    }

    if(p_boardWidth < GetNewGameViewMinBoardWidthValue() ||
       p_boardWidth > GetNewGameViewMaxBoardWidthValue())
    {
        const std::string errorMessage = MakeBoardWidthValueOutOfLimitsWarningDialog(GetNewGameViewMinBoardWidthValue(),
                                                                                     GetNewGameViewMaxBoardWidthValue());
        return cx::cmn::MakeError(errorMessage);
    }

    return cx::cmn::MakeSuccess();
}

cx::cmn::Status cx::ui::MainWindowPresenter::ArePlayerNamesValid(const std::vector<std::string>& p_playerNames) const
{
    if(std::any_of(p_playerNames.cbegin(),
                   p_playerNames.cend(),
                   [](const std::string& p_name)
                   {
                       return p_name.empty();
                   }))
              {
                  return cx::cmn::MakeError("Player names cannot be empty.");
              }

    return cx::cmn::MakeSuccess();
}

cx::cmn::Status cx::ui::MainWindowPresenter::ArePlayerChipColorsValid(const std::vector<cx::model::ChipColor>& p_playerChipColors) const
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
       return cx::cmn::MakeError("Discs must have different colors.");
   }

   return cx::cmn::MakeSuccess();
}

cx::cmn::Status cx::ui::MainWindowPresenter::ArePlayerTypesValid(const std::vector<cx::model::PlayerType>& p_playerTypes) const
{
    if(std::any_of(p_playerTypes.cbegin(),
                   p_playerTypes.cend(),
                   [](cx::model::PlayerType p_type)
                   {
                       return p_type == cx::model::PlayerType::HUMAN;
                   }))
              {
                  return cx::cmn::MakeSuccess();
              }

    return cx::cmn::MakeError("At least one player must not be a bot.");
}

cx::cmn::Status cx::ui::MainWindowPresenter::IsNewGameWinnable(size_t p_inARowValue,
                                                              size_t p_nbOfPlayers,
                                                              size_t p_boardHeight,
                                                              size_t p_boardWidth) const
{
    // Are there enough locations on the board so that the minimum amount
    // of moves required by a user to win is reachable?
    const size_t nbLocations = p_boardHeight * p_boardWidth;
    if(nbLocations < (p_nbOfPlayers - 1u)*(p_inARowValue - 1u) + p_inARowValue)
    {
        return cx::cmn::MakeError("There is not enough room on the board. Adjust the number of players or the in-a-row value.");
    }

    // Can the in-a-row value fit on the board?
    if(p_inARowValue > std::max<size_t>(p_boardHeight, p_boardWidth))
    {
        return cx::cmn::MakeError("The in-a-row value does not fit on the board.");
    }

    return cx::cmn::MakeSuccess();
}

/**************************************************************************************************
 *
 *                                              Game View
 *
 *************************************************************************************************/

std::string cx::ui::MainWindowPresenter::GetGameViewTitle() const
{
    return "Game";
}

cx::model::ChipColor cx::ui::MainWindowPresenter::GetGameViewActivePlayerChipColor() const
{
    const cx::model::IChip& activePlayerChip = m_activePlayer->GetChip();

    return activePlayerChip.GetColor();
}

cx::model::ChipColor cx::ui::MainWindowPresenter::GetGameViewNextPlayerChipColor() const
{
    const cx::model::IChip& nextPlayerChip = m_nextPlayer->GetChip();

    return nextPlayerChip.GetColor();
}

std::string cx::ui::MainWindowPresenter::GetGameViewActivePlayerLabelText() const
{
    return "  Active player: ";
}

std::string cx::ui::MainWindowPresenter::GetGameViewNextPlayerLabelText() const
{
    return "  Next player: ";
}

std::string cx::ui::MainWindowPresenter::GetGameViewActivePlayerName() const
{
    return m_activePlayer->GetName();
}

std::string cx::ui::MainWindowPresenter::GetGameViewNextPlayerName() const
{
    return m_nextPlayer->GetName();
}

size_t cx::ui::MainWindowPresenter::GetGameViewBoardWidth() const
{
    return m_currentBoardWidth;
}

size_t cx::ui::MainWindowPresenter::GetGameViewBoardHeight() const
{
    return m_currentBoardHeight;
}

cx::cmn::ui::Color cx::ui::MainWindowPresenter::GetGameViewBoardColor() const
{
    return cx::cmn::ui::Color{8481u, 8481u, 51143u};
}

cx::cmn::ui::Color cx::ui::MainWindowPresenter::GetGameViewColumnHighlightColor() const
{
    return cx::cmn::ui::Color{19660u, 19660u, 19660u, 32767u};
}

const cx::ui::IGameViewPresenter::ChipColors& cx::ui::MainWindowPresenter::GetGameViewChipColors() const
{
    return m_chipColors;
}

void cx::ui::MainWindowPresenter::UpdateCreateNewGame()
{
    m_chipColors.clear();

    m_currentBoardWidth = m_modelAsGameInformation.GetCurrentGridWidth();
    m_currentBoardHeight = m_modelAsGameInformation.GetCurrentGridHeight();

    m_activePlayer = cx::model::CreatePlayer(m_modelAsGameInformation.GetActivePlayer().GetName(),
                                           m_modelAsGameInformation.GetActivePlayer().GetChip().GetColor(),
                                           m_modelAsGameInformation.GetActivePlayer().IsManaged() ? cx::model::PlayerType::BOT : cx::model::PlayerType::HUMAN);

    m_nextPlayer = cx::model::CreatePlayer(m_modelAsGameInformation.GetNextPlayer().GetName(),
                                         m_modelAsGameInformation.GetNextPlayer().GetChip().GetColor(),
                                         m_modelAsGameInformation.GetNextPlayer().IsManaged() ? cx::model::PlayerType::BOT : cx::model::PlayerType::HUMAN);

    // Reserve the board color memory:
    for(size_t row = 0u; row < m_currentBoardHeight; ++row)
    {
        m_chipColors.push_back(std::vector<cx::model::ChipColor>(m_currentBoardWidth, cx::model::MakeTransparent()));
    }
}

void cx::ui::MainWindowPresenter::UpdateChipDropped()
{
    // Update players information:
    m_activePlayer = cx::model::CreatePlayer(m_modelAsGameInformation.GetActivePlayer().GetName(),
                                           m_modelAsGameInformation.GetActivePlayer().GetChip().GetColor(),
                                           m_modelAsGameInformation.GetActivePlayer().IsManaged() ? cx::model::PlayerType::BOT : cx::model::PlayerType::HUMAN);

    m_nextPlayer = cx::model::CreatePlayer(m_modelAsGameInformation.GetNextPlayer().GetName(),
                                         m_modelAsGameInformation.GetNextPlayer().GetChip().GetColor(),
                                         m_modelAsGameInformation.GetNextPlayer().IsManaged() ? cx::model::PlayerType::BOT : cx::model::PlayerType::HUMAN);
    // Update board information:
    for(size_t row = 0u; row < m_currentBoardHeight; ++row)
    {
        for(size_t column = 0u; column < m_currentBoardWidth; ++column)
        {
            const cx::model::IChip& chip = m_modelAsGameInformation.GetChip(row, column);
            m_chipColors[m_currentBoardHeight - row - 1][column] = chip.GetColor();
        }
    }
}

void cx::ui::MainWindowPresenter::UpdateGameReinitialized()
{
    UpdateChipDropped();
}

bool cx::ui::MainWindowPresenter::IsBoardEmpty() const
{
    bool isBoardEmpty = true;
    for(size_t row = 0u; row < m_modelAsGameInformation.GetCurrentGridHeight(); ++row)
    {
        for(size_t column = 0u; column < m_modelAsGameInformation.GetCurrentGridWidth(); ++column)
        {
            const cx::model::IChip& chip = m_modelAsGameInformation.GetChip(row, column);
            if(chip.GetColor() != cx::model::MakeTransparent())
            {
                isBoardEmpty = false;
                break;
            }
        }
    }

    return isBoardEmpty;
}

bool cx::ui::MainWindowPresenter::IsCurrentPlayerABot() const
{
    return m_activePlayer->IsManaged();
}

size_t cx::ui::MainWindowPresenter::GetBotTarget() const
{
    return m_modelAsAI.GetCurrentBotTarget();
}
