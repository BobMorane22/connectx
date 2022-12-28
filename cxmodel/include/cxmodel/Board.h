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
 * @file Board.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef BOARD_H_22FBC1EE_999E_416C_B947_05B6CDF6DBB8
#define BOARD_H_22FBC1EE_999E_416C_B947_05B6CDF6DBB8

#include <memory>
#include <vector>

#include "IBoard.h"
#include "IConnectXLimits.h"

namespace cxmodel
{

/**********************************************************************************************//**
 * @brief Connect X game board.
 *
 *************************************************************************************************/
class Board : public IBoard
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_nbRows
     *      The number of rows to include in the board.
     * @param p_nbColumns
     *      The number of columns to include in the board.
     * @param p_modelAsLimits
     *      The model limits.

     * @pre
     *      The number of rows and columns fall within the model limits.
     *
     *********************************************************************************************/
    Board(size_t p_nbRows, size_t p_nbColumns, const IConnectXLimits& p_modelAsLimits);

    // cxmodel::IBoard:
    size_t GetNbRows() const override;
    size_t GetNbColumns() const override;
    size_t GetNbPositions() const override;
    const IChip& GetChip(const Position& p_position) const override;
    bool DropChip(size_t p_column, const IChip& p_chip, Position& p_droppedPosition) override;
    void ResetChip(Position& p_position) override;
    bool IsColumnFull(size_t p_column) const override;

private:

    void CheckInvariants() const;

    using Grid = std::vector<std::vector<std::unique_ptr<IChip>>>;

    Grid m_grid;
    const size_t m_nbRows;
    const size_t m_nbColumns;

    const IConnectXLimits& m_modelAsLimits;

};

} // namespace cxmodel

#endif // BOARD_H_22FBC1EE_999E_416C_B947_05B6CDF6DBB8
