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
#include "Subject.h"

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
 * It is the caller's responsibility to make sure the arguments are valid and that all conditions
 * for a successful drop are met. This command only performs the drop, without asking questions.
 *
 ************************************************************************************************/
class CommandDropChip : public ICommand,
                        public Subject
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The column passed as argument is within the board limits.
     *
     * @param p_board             The game board.
     * @param p_playersInfo       Information relative to the players.
     * @param p_droppedChip       The chip being dropped.
     * @param p_column            The column into which to drop the chip.
     * @param p_takenPositions    A collection of non-free positions.
     *
     ********************************************************************************************/
    CommandDropChip(IBoard& p_board,
                    PlayerInformation& p_playersInfo,
                    const cxmodel::IChip& p_droppedChip,
                    const size_t p_column,
                    std::vector<IBoard::Position>& p_takenPositions);

    // ICommand:
    void Execute() override;
    void Undo() override;

private:

    IBoard& m_board;
    PlayerInformation& m_playersInfo;
    const cxmodel::IChip& m_droppedChip;
    const size_t m_column;
    std::vector<IBoard::Position>& m_takenPositions;

    // Members stored for undoing the drop:
    const PlayerInformation m_previousPlayerInformation;
    const ChipColor m_previousChipColor;
    const size_t m_previousColumn;
    IBoard::Position m_previousDropPosition;
};

} // namespace cxmodel

#endif // COMMANDDROPCHIP_H_412DF355_E70F_413B_B531_63838B549644
