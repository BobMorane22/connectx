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
 * @file CommandDropChip.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDDROPCHIP_H_412DF355_E70F_413B_B531_63838B549644
#define COMMANDDROPCHIP_H_412DF355_E70F_413B_B531_63838B549644

#include <vector>

#include "ICommand.h"
#include "Player.h"

namespace cxlog
{
    class ILogger;
}

namespace cxmodel
{
    class IBoard;
    class IChip;
    class Subject;
}

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Command to drop a chip in the game board.
 *
 * This commands drops a chip into the game board.
 *
 ************************************************************************************************/
class CommandDropChip : public cxmodel::ICommand
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The column passed as argument is within the board limits.
     *
     * @param p_logger            A logger.
     * @param p_board             The game board.
     * @param p_players           The list of players.
     * @param p_activePlayerIndex The active player index in the list.
     * @param p_nextPlayerIndex   The next player index in the list.
     * @param p_droppedChip       The chip being dropped.
     * @param p_column            The column into which to drop the chip.
     *
     ********************************************************************************************/
    CommandDropChip(cxlog::ILogger& p_logger,
                    cxmodel::IBoard& p_board,
                    std::vector<Player>& p_players,
                    size_t& p_activePlayerIndex,
                    size_t& p_nextPlayerIndex,
                    const cxmodel::IChip& p_droppedChip,
                    const size_t p_column);

    // ICommand:
    void Execute() override;
    void Undo() override;

private:

    cxlog::ILogger& m_logger;

    cxmodel::IBoard& m_board;
    std::vector<cxmodel::Player>& m_players;
    size_t& m_activePlayerIndex;
    size_t& m_nextPlayerIndex;
    const cxmodel::IChip& m_droppedChip;
    const size_t m_column;

};

} // namespace cxmodel

#endif // COMMANDDROPCHIP_H_412DF355_E70F_413B_B531_63838B549644
