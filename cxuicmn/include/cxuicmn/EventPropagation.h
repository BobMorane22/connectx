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
 * @file EventPropagation.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef EVENTPROPAGATION_H_5B935E9A_9EBC_4972_BCF8_97E2F936E9F0
#define EVENTPROPAGATION_H_5B935E9A_9EBC_4972_BCF8_97E2F936E9F0

namespace cx::ui::cmn
{

/**********************************************************************************************//**
 * @brief Event progapation modes.
 *
 * When an event is handled, one of the two following scenarios occur:
 *
 *  1. We want the handled event to not be propagated further. I this scenario, no other handler
 *     will be invoked for the event.
 *  2. We want the handled event to propagate to parent widgets so they can handle it as well.
 *
 *************************************************************************************************/
enum class EventPropagation
{
    /** Stop other handlers from being invoked for the event. */
    STOP,

    /** Propagate the event further. */
    PROPAGATE,
};

} // namespace cx::ui::cmn

#endif // EVENTPROPAGATION_H_5B935E9A_9EBC_4972_BCF8_97E2F936E9F0
