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
 * @file GameKeyHandlerStrategyFactory.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include "GameKeyHandlerStrategyFactory.h"

#include "GameDownKeyHandlerStrategy.h"
#include "GameLeftKeyHandlerStrategy.h"
#include "GameRightKeyHandlerStrategy.h"

std::unique_ptr<cxgui::IGameKeyHandlerStrategy> cxgui::GameKeyHandlerStrategyFactory::Create(const GdkKey& p_key)
{
    switch(p_key)
    {
        case GDK_KEY_Left:
            return std::make_unique<cxgui::GameLeftKeyHandlerStrategy>();

        case GDK_KEY_Right:
            return std::make_unique<cxgui::GameRightKeyHandlerStrategy>();

        case GDK_KEY_Down:
            return std::make_unique<cxgui::GameDownKeyHandlerStrategy>();

        default:
            return std::make_unique<cxgui::GameKeyHandlerNoStrategy>();
    }
}
