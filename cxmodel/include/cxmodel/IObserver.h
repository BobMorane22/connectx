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
 * @file IObserver.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IOBSERVER_H_CB32427D_3430_41D8_BE7A_992F2D139BB2
#define IOBSERVER_H_CB32427D_3430_41D8_BE7A_992F2D139BB2

#include <type_traits>

#include "ModelNotificationContext.h"

namespace cxmodel
{
    template<typename>
    class Subject;
}

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for objects that can update their state on some subject notification.
 *
 * Inherit from this to make some class capable of subscribing to notifications from some
 * Subject. For each notification, the @c IObserver instance can update its state.
 *
 * @tparam T A notification context. Must be an enum.
 *
 * @see cxmodel::Subject
 *
 ************************************************************************************************/
template<typename T>
class IObserver
{

    static_assert(std::is_enum_v<T>, "Notification context types must be enums.");

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IObserver() = default;

    /******************************************************************************************//**
     * @brief Update the state.
     *
     * Update the `IObserver` instance's state. When a subject notifies its observers that some
     * event as occurred (through its `Notify` method), this method is automatically called
     * on each of the attached observer. Each observer can implement it its own way and update
     * its state accordingly.
     *
     * @warning Never call this method directly. Only a subject, through its notifications,
     *          should call this.
     *
     * @tparam T
     *      The type of notification (must be an `enum`).
     * @param p_context
     *      The context in which the notification occurs.
     * @param p_subject
     *      The subject that has triggered the update through a notification.
     *
     ********************************************************************************************/
    virtual void Update(T p_context, Subject<T>* p_subject) = 0;

};

} // namespace cxmodel

#endif // IOBSERVER_H_CB32427D_3430_41D8_BE7A_992F2D139BB2
