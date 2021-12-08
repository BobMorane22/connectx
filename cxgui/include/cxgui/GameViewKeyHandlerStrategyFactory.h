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
 * @file GameViewKeyHandlerStrategyFactory.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMEKEYHANDLERSTRATEGYFACTORY_H_77F63BBC_46CA_4EF9_99A9_D6A93968231C
#define GAMEKEYHANDLERSTRATEGYFACTORY_H_77F63BBC_46CA_4EF9_99A9_D6A93968231C

#include <memory>

#include <gdk/gdk.h>

#include "IGameViewKeyHandlerStrategy.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Factory for key handling strategies.
 *
 * Creates the right strategy for the given keyboard key (GdkKey).
 *
 ************************************************************************************************/
class GameViewKeyHandlerStrategyFactory final
{

public:

    /******************************************************************************************//**
     * @brief Creates a key handling strategy from a keyboard key identifier.
     *
     * @param p_event Describes a key press/release event.

     * @pre `p_event` is valid.
     *
     * @return The strategy, `nullptr` otherwise.
     *
     ********************************************************************************************/
    static std::unique_ptr<cxgui::IGameViewKeyHandlerStrategy> Create(GdkEventKey* p_event);

};

} // namespace cxgui

#endif // GAMEKEYHANDLERSTRATEGYFACTORY_H_77F63BBC_46CA_4EF9_99A9_D6A93968231C
