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

#include <IChip.h>
#include <CommandDropChip.h>
#include <Subject.h>

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
                                          std::vector<IBoard::Position>& p_takenPositions)
 : m_board{p_board}
 , m_playersInfo{p_playersInfo}
 , m_droppedChip{std::move(p_droppedChip)}
 , m_column{p_column}
 , m_takenPositions{p_takenPositions}
 , m_previousPlayerInformation{p_playersInfo}
 , m_previousColumn{p_column}
{
    PRECONDITION(p_column < p_board.GetNbColumns());

    POSTCONDITION(m_droppedChip);
}

void cxmodel::CommandDropChip::Execute()
{
    IF_CONDITION_NOT_MET_DO(m_droppedChip, return;);

    IBoard::Position droppedPosition;
    IF_CONDITION_NOT_MET_DO(m_board.DropChip(m_column, *m_droppedChip, droppedPosition), return;);
    m_previousDropPosition = droppedPosition;

    // Update player information:
    UpdatePlayerIndex(m_playersInfo.m_activePlayerIndex, m_playersInfo.m_players.size());
    UpdatePlayerIndex(m_playersInfo.m_nextPlayerIndex, m_playersInfo.m_players.size());

    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_activePlayerIndex < m_playersInfo.m_players.size(), return;);
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_nextPlayerIndex < m_playersInfo.m_players.size(), return;);
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_activePlayerIndex != m_playersInfo.m_nextPlayerIndex, return;);

    // Update taken positions:
    const bool isPositionFree = std::find(m_takenPositions.cbegin(), m_takenPositions.cend(), droppedPosition) == m_takenPositions.cend();
    IF_CONDITION_NOT_MET_DO(isPositionFree, return;);

    m_takenPositions.push_back(droppedPosition);

    // Send notifications for the drop:
    Notify(ModelNotificationContext::CHIP_DROPPED);
}

void cxmodel::CommandDropChip::Undo()
{
    const size_t takenPositionsInitialSize = m_takenPositions.size();

    // Put playersInfo back:
    m_playersInfo = m_previousPlayerInformation;
    
    // Erase the dropped position from the taken positions:
    m_takenPositions.erase(std::remove(m_takenPositions.begin(), m_takenPositions.end(), m_previousDropPosition),
                           m_takenPositions.end());
    ASSERT(m_takenPositions.size() == takenPositionsInitialSize - 1u);

    // Reset the chip in the board:
    m_board.ResetChip(m_previousDropPosition);

    // Notify:
    Notify(ModelNotificationContext::UNDO_CHIP_DROPPED);
}
