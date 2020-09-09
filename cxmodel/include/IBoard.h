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
 * @file IBoard.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IBOARD_H_0D53584F_433F_4007_86CD_A0CF3135BAF3
#define IBOARD_H_0D53584F_433F_4007_86CD_A0CF3135BAF3

#include "IChip.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for Connect X compliant game boards.
 *
 ************************************************************************************************/
class IBoard
{

public:

    /*******************************************************************************************//**
     * @brief Structure to store a position within the board.
     *
     **********************************************************************************************/
    struct Position
    {
        constexpr Position()
        : m_row{0u}
        , m_column{0u}
        {
        }

        constexpr Position(size_t p_row, size_t p_column)
        : m_row{p_row}
        , m_column{p_column}
        {
        }

        size_t m_row;
        size_t m_column;
    };

public:

    /*******************************************************************************************//**
     * @brief Destructor.
     *
     **********************************************************************************************/
    virtual ~IBoard() = default;

    /*******************************************************************************************//**
     * @brief Accessor for the number of rows in the board.
     *
     * @return The number of rows in the GameBoard.
     *
     **********************************************************************************************/
    virtual size_t GetNbRows() const = 0;

    /*******************************************************************************************//**
     * @brief Accessor for the number of columns in the GameBoard.
     *
     * @return The number of columns in the GameBoard.
     *
     **********************************************************************************************/
    virtual size_t GetNbColumns() const = 0;

    /*******************************************************************************************//**
     * @brief Accessor for the total number of positions in the board.
     *
     * @return The total number of positions in the board.
     *
     **********************************************************************************************/
    virtual size_t GetNbPositions() const = 0;

    /*******************************************************************************************//**
     * @brief Chip accessor.
     *
     * Gives access to the chip located at the needed position on the board. Positions follow a
     * Cartesian-like convention. The correct way to visualize a board is as follow:
     *
     * @verbatim
     *
     *    Columns up
     *        ^
     *        |
     *        |
     *    | (0,1) |
     *    | (0,0) | (1,0) | --> Rows up
     *
     * @endverbatim
     *
     * @param[in] p_position The Position at which the needed Disc is located on the grid.
     *
     **********************************************************************************************/
    virtual const IChip& GetChip(const Position& p_position) const = 0;

    /*******************************************************************************************//**
     * @brief Drops a chip in a specific column (if possible).
     *
     * Just like in the classic Connect 4 game, the chip is inserted in a specific column and sets
     * to the bottom-most available position. For example:
     *
     *   @verbatim
     *
     *      | N | <- Last dropped disc (unless already full, see below)
     *      | R |
     *      | N |
     *      | R |
     *      | N |
     *      | R | <- First dropped disc.
     *
     *   @endverbatim
     *
     * If the column is already full, the action is ignored and the top-most position is returned.
     *
     * @param p_column          The column where to insert the chip.
     * @param p_chip            The chip to insert.
     * @param p_droppedPosition The position where the chip was dropped. If the chip could not be
     *                          dropped because the specified column is full, the top-most column
     *                          position is returned.
     *
     * @return `true` if the chip could be dropped, `false` otherwise.
     *
     * @pre The p_column argument is between 0 and the maximum column number for the model.
     *
     **********************************************************************************************/
    virtual bool DropChip(size_t p_column, const IChip& p_chip, Position& p_droppedPosition) = 0;

};

} // namespace cxmodel

#endif // IBOARD_H_0D53584F_433F_4007_86CD_A0CF3135BAF3
