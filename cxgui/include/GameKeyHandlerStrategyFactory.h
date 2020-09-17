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
 * @file GameKeyHandlerStrategyFactory.h
 * @date 2020
 *
 *************************************************************************************************/

#include <memory>

#include "IGameKeyHandlerStrategy.h"

namespace cxgui
{

// See: gdkkeysyms.h
using GdkKey = unsigned int;

/*********************************************************************************************//**
 * @brief Factory for key handling strategies.
 *
 * Creates the right strategy for the given keyboard key (GdkKey).
 *
 ************************************************************************************************/
class GameKeyHandlerStrategyFactory final
{

public:

    /******************************************************************************************//**
     * @brief Creates a key handling strategy from a keyboard key identifier.
     *
     * @post The returned value is never nullptr.
     *
     * @param p_key An identifier for the key to create the strategy for.
     *
     * @return The strategy, or a noop strategy if no corresponding strategy was found.
     *
     ********************************************************************************************/
    std::unique_ptr<cxgui::IGameKeyHandlerStrategy> Create(const GdkKey& p_key);

};

} // namespace cxgui
