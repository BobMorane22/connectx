#pragma once

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
 * @file IGameKeyHandlerStrategy.h
 * @date 2020
 *
 *************************************************************************************************/

#include <gtkmm/window.h>

namespace cxgui
{
    class Board;
    class IGameViewController;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Key press handling strategy interface.
 *
 * Implement this to create a new keypress strategy on the board.
 *
 ************************************************************************************************/
class IGameKeyHandlerStrategy
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IGameKeyHandlerStrategy() = default;

    /******************************************************************************************//**
     * @brief Handle key press on the board.
     *
     * @param p_controller The Game View controller.
     * @param p_gameBoard  The board to act on.
     *
     * @return `true` if the handling must stop propagating, `false` otherwise.
     *
     ********************************************************************************************/
    virtual bool Handle(IGameViewController& p_controller, Board& p_gameBoard) = 0;

};

/*********************************************************************************************//**
 * @brief No-op strategy.
 *
 * Used when no suitable strategy is accessible.
 *
 ************************************************************************************************/
class GameKeyHandlerNoStrategy : public IGameKeyHandlerStrategy
{
    bool Handle(IGameViewController& /*p_controller*/, Board& /*p_gameBoard*/) override
    {
        return false; // propagate...
    }
};

} // namespace cxgui
