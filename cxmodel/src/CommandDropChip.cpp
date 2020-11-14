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

#include <cxinv/include/assertion.h>
#include <cxlog/include/ILogger.h>

#include <IChip.h>
#include <CommandDropChip.h>
#include <Subject.h>

namespace
{

// Update the player index in a circular buffer way:
void UpdatePlayerIndex(size_t& p_playerIndex, size_t p_nbOfPlayers)
{
    if(p_playerIndex == p_nbOfPlayers - 1)
    {
        p_playerIndex = 0u;
    }
    else
    {
        ++p_playerIndex;
    }
}

} // namespace

cxmodel::CommandDropChip::CommandDropChip(cxlog::ILogger& p_logger,
                                          cxmodel::IBoard& p_board,
                                          cxmodel::PlayerInformation& p_playerInfo,
                                          const cxmodel::IChip& p_droppedChip,
                                          const size_t p_column,
                                          std::vector<IBoard::Position>& p_takenPositions)
 : m_logger{p_logger}
 , m_board{p_board}
 , m_playerInfo{p_playerInfo}
 , m_droppedChip{p_droppedChip}
 , m_column{p_column}
 , m_takenPositions{p_takenPositions}
{

}

void cxmodel::CommandDropChip::Execute()
{
    IF_PRECONDITION_NOT_MET_DO(m_column < m_board.GetNbColumns(), return;);

    const Player& activePlayer = m_playerInfo.m_players[m_playerInfo.m_activePlayerIndex];
    if(!PRECONDITION(activePlayer.GetChip() == m_droppedChip))
    {
        const IChip& activePlayerChip = activePlayer.GetChip();
        std::ostringstream logStream;
        logStream << "Active player's color: (" << activePlayerChip.GetColor().R() << ", "
                                                << activePlayerChip.GetColor().G() << ", "
                                                << activePlayerChip.GetColor().B() << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

        logStream.str("");
        logStream << "Dropped disc color: (" << m_droppedChip.GetColor().R() << ", "
                                             << m_droppedChip.GetColor().G() << ", "
                                             << m_droppedChip.GetColor().B() << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

        return;
    }

    IBoard::Position droppedPosition;
    if(m_board.DropChip(m_column, m_droppedChip, droppedPosition))
    {
        // Update player information:
        UpdatePlayerIndex(m_playerInfo.m_activePlayerIndex, m_playerInfo.m_players.size());
        UpdatePlayerIndex(m_playerInfo.m_nextPlayerIndex, m_playerInfo.m_players.size());

        IF_CONDITION_NOT_MET_DO(m_playerInfo.m_activePlayerIndex < m_playerInfo.m_players.size(), return;);
        IF_CONDITION_NOT_MET_DO(m_playerInfo.m_nextPlayerIndex < m_playerInfo.m_players.size(), return;);
        IF_CONDITION_NOT_MET_DO(m_playerInfo.m_activePlayerIndex != m_playerInfo.m_nextPlayerIndex, return;);

        // Update taken positions:
        const bool isPositionFree = std::find(m_takenPositions.cbegin(), m_takenPositions.cend(), droppedPosition) == m_takenPositions.cend();
        IF_CONDITION_NOT_MET_DO(isPositionFree, return;);

        m_takenPositions.push_back(droppedPosition);

        std::ostringstream stream;
        stream << activePlayer.GetName() << "'s chip dropped at (" << droppedPosition.m_row << ", " << droppedPosition.m_column << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());
    }
    else
    {
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip drop failed for " + activePlayer.GetName());
    }
}

void cxmodel::CommandDropChip::Undo()
{
    ASSERT_ERROR_MSG("Not implemented.");
}
