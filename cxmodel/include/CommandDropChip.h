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

#include "IBoard.h"
#include "ICommand.h"
#include "PlayerInformation.h"

namespace cxlog
{
    class ILogger;
}

namespace cxmodel
{
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
     * @param p_playerInfo        Information relative to the players.
     * @param p_droppedChip       The chip being dropped.
     * @param p_column            The column into which to drop the chip.
     * @param p_takenPositions    A collection of non-free positions.
     *
     ********************************************************************************************/
    CommandDropChip(cxlog::ILogger& p_logger,
                    IBoard& p_board,
                    PlayerInformation& p_playerInfo,
                    const cxmodel::IChip& p_droppedChip,
                    const size_t p_column,
                    std::vector<IBoard::Position>& p_takenPositions);

    // ICommand:
    void Execute() override;
    void Undo() override;

private:

    cxlog::ILogger& m_logger;

    cxmodel::IBoard& m_board;
    cxmodel::PlayerInformation& m_playerInfo;
    const cxmodel::IChip& m_droppedChip;
    const size_t m_column;
    std::vector<IBoard::Position>& m_takenPositions;

};

} // namespace cxmodel

#endif // COMMANDDROPCHIP_H_412DF355_E70F_413B_B531_63838B549644
