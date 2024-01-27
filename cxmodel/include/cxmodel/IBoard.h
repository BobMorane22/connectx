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

#include <cstddef>

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

    /*****************************************************************************************//**
     * @brief Structure to store a position within the board.
     *
     ********************************************************************************************/
    struct Position
    {

        /*************************************************************************************//**
         * @brief Default constructor.
         *
         * Constructs a position at (0,0).
         *
         ****************************************************************************************/
        constexpr Position()
        : m_row{0u}
        , m_column{0u}
        {
        }

        /*************************************************************************************//**
         * @brief Constructor.
         *
         * @param p_row
         *      The row position.
         * @param p_column
         *      The column position.
         *
         ****************************************************************************************/
        constexpr Position(size_t p_row, size_t p_column)
        : m_row{p_row}
        , m_column{p_column}
        {
        }

        /** The row position. */
        size_t m_row;

        /** The column position. */
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
     * @return
     *      The number of rows in the GameBoard.
     *
     **********************************************************************************************/
    virtual size_t GetNbRows() const = 0;

    /*******************************************************************************************//**
     * @brief Accessor for the number of columns in the GameBoard.
     *
     * @return
     *      The number of columns in the GameBoard.
     *
     **********************************************************************************************/
    virtual size_t GetNbColumns() const = 0;

    /*******************************************************************************************//**
     * @brief Accessor for the total number of positions in the board.
     *
     * @return
     *      The total number of positions in the board.
     *
     **********************************************************************************************/
    virtual size_t GetNbPositions() const = 0;

    /*******************************************************************************************//**
     * @brief Chip accessor.
     *
     * Gives access to the chip located at the needed position on the board. Positions follow a
     * Cartesian-like convention. The correct way to visualize a board is as follow:
     *
     @verbatim

        Columns up
            ^
            |
            |
        | (0,1) |
        | (0,0) | (1,0) | --> Rows up

     @endverbatim
     *
     * @param p_position
     *      The Position at which the needed Disc is located on the grid.
     *
     * @return
     *      The chip at the requested position. If the position is invalid for the board, an
     *      invalid chip is returned (i.e transparent).
     *
     **********************************************************************************************/
    virtual const IChip& GetChip(const Position& p_position) const = 0;

    /*******************************************************************************************//**
     * @brief Drops a chip in a specific column (if possible).
     *
     * Just like in the classic Connect 4 game, the chip is inserted in a specific column and sets
     * to the bottom-most available position. For example:
     *
     @verbatim
     
       | N | <- Last dropped disc (unless already full, see below)
       | R |
       | N |
       | R |
       | N |
       | R | <- First dropped disc.
     
     @endverbatim
     *
     * If the column is already full, the action is ignored and the top-most position is returned.
     *
     * @pre The p_column argument is between 0 and the maximum column number for the model.

     * @param p_column
     *      The column where to insert the chip.
     * @param p_chip
     *      The chip to insert.
     * @param p_droppedPosition
     *      The position where the chip was dropped. If the chip could not be dropped because
     *      the specified column is full, the top-most column position is returned.
     *
     * @return
     *      `true` if the chip could be dropped, `false` otherwise.
     *
     **********************************************************************************************/
    virtual bool DropChip(size_t p_column, const IChip& p_chip, Position& p_droppedPosition) = 0;

    /*******************************************************************************************//**
     * @brief Resets the chip at the specified position.
     *
     * When a chip has been reset, it has no more color associated to it.
     *
     * @pre
     *      The position exist on the board.
     * @pre
     *      The chip at the specified position is not transparent.
     *
     * @param p_position
     *      The position on the board where the chip to reset is located.
     *
     **********************************************************************************************/
    virtual void ResetChip(Position& p_position) = 0;

    /*******************************************************************************************//**
     * @brief Indicates if a column is full.
     *
     * @pre
     *      The p_column argument is between 0 and the maximum column number for the model.
     *
     * @param p_column
     *      The column to check.
     *
     * @return
     *      `true` if the column is full, `false` otherwise.
     *
     **********************************************************************************************/
    virtual bool IsColumnFull(size_t p_column) const = 0;

};

/***********************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs
 *      The left hand position.
 * @param p_rhs
 *      The right hand position.
 *
 * @return
 *      `true` if both positions represent the same position on the board, `false` otherwise
 *
 **************************************************************************************************/
bool operator==(const IBoard::Position& p_lhs, const IBoard::Position& p_rhs);

/***********************************************************************************************//**
 * @brief Not-equal-to operator.
 *
 * @param p_lhs
 *      The left hand position.
 * @param p_rhs
 *      The right hand position.
 *
 * @return
 *      `true` if the positions do not represent the same position on the board, `false` otherwise
 *
 **************************************************************************************************/
bool operator!=(const IBoard::Position& p_lhs, const IBoard::Position& p_rhs);

} // namespace cxmodel

#endif // IBOARD_H_0D53584F_433F_4007_86CD_A0CF3135BAF3
