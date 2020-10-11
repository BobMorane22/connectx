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

#include <sstream>

#include <cxinv/include/assertion.h>
#include <cxlog/include/ILogger.h>

#include <IChip.h>
#include <CommandDropChip.h>
#include <IBoard.h>
#include <Subject.h>

#define IF_CONDITION_NOT_MET_DO_IMPL(p_assertType, p_condition, p_action) \
    if(!p_assertType(p_condition))                                        \
    {                                                                     \
        p_action                                                          \
    }                                                                     \
    (void)0                                                               \

/**********************************************************************************************//**
 * @brief Performs an action is some precondition is not met.
 *
 * @param p_precondition A boolean expression representing the precondition.
 * @param p_action       The action to perform is the precondition is not met.
 *
 *************************************************************************************************/
#define IF_PRECONDITION_NOT_MET_DO(p_precondition, p_action)             \
    IF_CONDITION_NOT_MET_DO_IMPL(PRECONDITION, p_precondition, p_action) \

/**********************************************************************************************//**
 * @brief Performs an action is some condition is not met.
 *
 * @param p_condition A boolean expression representing the condition.
 * @param p_action    The action to perform is the precondition is not met.
 *
 *************************************************************************************************/
#define IF_CONDITION_NOT_MET_DO(p_condition, p_action)          \
    IF_CONDITION_NOT_MET_DO_IMPL(ASSERT, p_condition, p_action) \

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
                                          std::vector<Player>& p_players,
                                          size_t& p_activePlayerIndex,
                                          size_t& p_nextPlayerIndex,
                                          const cxmodel::IChip& p_droppedChip,
                                          const size_t p_column)
 : m_logger{p_logger}
 , m_board{p_board}
 , m_players{p_players}
 , m_activePlayerIndex{p_activePlayerIndex}
 , m_nextPlayerIndex{p_nextPlayerIndex}
 , m_droppedChip{p_droppedChip}
 , m_column{p_column}
{

}

void cxmodel::CommandDropChip::Execute()
{
    IF_PRECONDITION_NOT_MET_DO(m_column < m_board.GetNbColumns(), return;);

    const Player& activePlayer = m_players[m_activePlayerIndex];
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
        UpdatePlayerIndex(m_activePlayerIndex, m_players.size());
        UpdatePlayerIndex(m_nextPlayerIndex, m_players.size());

        IF_CONDITION_NOT_MET_DO(m_activePlayerIndex < m_players.size(), return;);
        IF_CONDITION_NOT_MET_DO(m_nextPlayerIndex < m_players.size(), return;);
        IF_CONDITION_NOT_MET_DO(m_activePlayerIndex != m_nextPlayerIndex, return;);

        std::ostringstream stream;
        stream << activePlayer.GetName() << "'s chip dropped at (" << droppedPosition.m_row << ", " << droppedPosition.m_column << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());
    }
    {
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip drop failed for " + activePlayer.GetName());
    }
}

void cxmodel::CommandDropChip::Undo()
{
    ASSERT_ERROR_MSG("Not implemented.");
}
