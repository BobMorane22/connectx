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
 * @file CommandDropChip.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>
#include <sstream>

#include <cxinv/assertion.h>
#include <cxlog/ILogger.h>
#include <cxmodel/CommandCompletionStatus.h>
#include <cxmodel/CommandDropChip.h>
#include <cxmodel/IChip.h>
#include <cxmodel/Subject.h>

namespace
{

// Update the player index in a circular buffer way:
void UpdatePlayerIndex(size_t& p_playerIndex, size_t p_nbOfPlayers)
{
    if(p_playerIndex == p_nbOfPlayers - 1u)
    {
        p_playerIndex = 0u;
    }
    else
    {
        ++p_playerIndex;
    }
}

} // namespace

cxmodel::CommandDropChip::CommandDropChip(cxmodel::IBoard& p_board,
                                          cxmodel::PlayerInformation& p_playersInfo,
                                          std::unique_ptr<cxmodel::IChip>&& p_droppedChip,
                                          const size_t p_column,
                                          std::vector<IBoard::Position>& p_takenPositions,
                                          cxlog::ILogger& p_logger)
 : m_board{p_board}
 , m_playersInfo{p_playersInfo}
 , m_droppedChip{std::move(p_droppedChip)}
 , m_column{p_column}
 , m_takenPositions{p_takenPositions}
 , m_logger{p_logger}
 , m_previousPlayerInformation{p_playersInfo}
 , m_previousColumn{p_column}
{
    PRECONDITION(p_column < p_board.GetNbColumns());

    POSTCONDITION(m_droppedChip);
}

cxmodel::CommandCompletionStatus cxmodel::CommandDropChip::Execute()
{
    const auto activePlayer = m_playersInfo.m_players[m_playersInfo.m_activePlayerIndex];
    if(!INL_PRECONDITION(activePlayer->GetChip() == *m_droppedChip))
    {
        const IChip& activePlayerChip = activePlayer->GetChip();
        std::ostringstream logStream;
        logStream << "Active player's color: (" << activePlayerChip.GetColor().R() << ", "
                                                << activePlayerChip.GetColor().G() << ", "
                                                << activePlayerChip.GetColor().B() << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

        logStream.str("");
        logStream << "Dropped disc color: (" << m_droppedChip->GetColor().R() << ", "
                                             << m_droppedChip->GetColor().G() << ", "
                                             << m_droppedChip->GetColor().B() << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

        return CommandCompletionStatus::FAILED_UNEXPECTED;;
    }

    if(m_board.IsColumnFull(m_column))
    {
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip drop failed for " + activePlayer->GetName());
        Notify(ModelNotificationContext::CHIP_DROPPED_FAILED);

        return CommandCompletionStatus::FAILED_EXPECTED;;
    }

    IF_CONDITION_NOT_MET_DO(m_droppedChip, return CommandCompletionStatus::FAILED_UNEXPECTED;);

    IBoard::Position droppedPosition;
    IF_CONDITION_NOT_MET_DO(m_board.DropChip(m_column, *m_droppedChip, droppedPosition), return CommandCompletionStatus::FAILED_UNEXPECTED;);
    m_previousDropPosition = droppedPosition;

    // Update player information:
    UpdatePlayerIndex(m_playersInfo.m_activePlayerIndex, m_playersInfo.m_players.size());
    UpdatePlayerIndex(m_playersInfo.m_nextPlayerIndex, m_playersInfo.m_players.size());

    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_activePlayerIndex < m_playersInfo.m_players.size(),   return CommandCompletionStatus::FAILED_UNEXPECTED;);
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_nextPlayerIndex < m_playersInfo.m_players.size(),     return CommandCompletionStatus::FAILED_UNEXPECTED;);
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_activePlayerIndex != m_playersInfo.m_nextPlayerIndex, return CommandCompletionStatus::FAILED_UNEXPECTED;);

    // Update taken positions:
    const bool isPositionFree = std::find(m_takenPositions.cbegin(), m_takenPositions.cend(), droppedPosition) == m_takenPositions.cend();
    IF_CONDITION_NOT_MET_DO(isPositionFree, return CommandCompletionStatus::FAILED_UNEXPECTED;);

    m_takenPositions.push_back(droppedPosition);

    if(m_isRedo)
    {
        Notify(ModelNotificationContext::REDO_CHIP_DROPPED);

        return CommandCompletionStatus::SUCCESS;;
    }

    std::ostringstream stream;
    stream << activePlayer->GetName() << "'s chip dropped at (" << droppedPosition.m_row << ", " << droppedPosition.m_column << ")";
    m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());

    // At this point, all successive calls to Execute are redos:
    m_isRedo = true;

    Notify(ModelNotificationContext::CHIP_DROPPED);

    return CommandCompletionStatus::SUCCESS;;
}

void cxmodel::CommandDropChip::Undo()
{
    // Put playersInfo back:
    m_playersInfo = m_previousPlayerInformation;
    
    // Erase the dropped position from the taken positions:
    m_takenPositions.erase(std::remove(m_takenPositions.begin(), m_takenPositions.end(), m_previousDropPosition),
                           m_takenPositions.end());

    // Reset the chip in the board:
    m_board.ResetChip(m_previousDropPosition);

    // Notify:
    Notify(ModelNotificationContext::UNDO_CHIP_DROPPED);
}
