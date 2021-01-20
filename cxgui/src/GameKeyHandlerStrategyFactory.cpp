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

#include <cxinv/include/assertion.h>

#include "GameKeyHandlerStrategyFactory.h"

#include "GameCtrlZKeyHandlerStrategy.h"
#include "GameDownKeyHandlerStrategy.h"
#include "GameLeftKeyHandlerStrategy.h"
#include "GameRightKeyHandlerStrategy.h"

std::unique_ptr<cxgui::IGameKeyHandlerStrategy> cxgui::GameKeyHandlerStrategyFactory::Create(GdkEventKey* p_event)
{
    IF_CONDITION_NOT_MET_DO(p_event, return std::make_unique<cxgui::GameKeyHandlerNoStrategy>(););

    switch(p_event->keyval)
    {
        case GDK_KEY_Left:
            return std::make_unique<cxgui::GameLeftKeyHandlerStrategy>();

        case GDK_KEY_Right:
            return std::make_unique<cxgui::GameRightKeyHandlerStrategy>();

        case GDK_KEY_Down:
            return std::make_unique<cxgui::GameDownKeyHandlerStrategy>();

        case GDK_KEY_z:
        {
            if(p_event->state & GDK_CONTROL_MASK)
            {
                return std::make_unique<cxgui::GameCtrlZKeyHandlerStrategy>();
            }

            return std::make_unique<cxgui::GameKeyHandlerNoStrategy>();
        }

        default:
            return std::make_unique<cxgui::GameKeyHandlerNoStrategy>();
    }
}
