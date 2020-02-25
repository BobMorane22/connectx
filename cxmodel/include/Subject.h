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
 * @file Subject.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef SUBJECT_H_520FD354_27E1_4AE7_9579_71016A78DC44
#define SUBJECT_H_520FD354_27E1_4AE7_9579_71016A78DC44

#include <vector>

#include "NotificationContext.h"

namespace cxmodel
{
    class IObserver;
}

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief An object that can be subscribed to and notified from.
 *
 * @invariant All of the registered observers have an address that is not @c nullptr.
 *
 * Inherit from this to enable subscription to instances of a class. Attached observers (i.e.
 * @c IObserver instances) can be notified of any subject event and update themselves accordingly.
 * For this to occur, the @c Notify() method must be called explicitly. Not calling @c Notify()
 * will result on subscribed observers not receiving a notification.
 *
 * @see cxmodel::IObserver
 *
 ************************************************************************************************/
class Subject
{

public:

    /******************************************************************************************//**
     * @brief Default constructor.
     *
     ********************************************************************************************/
    Subject();

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     * The destructor is pure virtual to ensure that the class is abstract. Not that upon
     * destruction, all observers are automatically detached.
     *
     ********************************************************************************************/
    virtual ~Subject() = 0;

    /******************************************************************************************//**
     * @brief Attach an observer to the subject.
     *
     * @pre The new observer has a valid address.
     * @pre The new observer has not been previously attached. Note that a copy of an attached
     *      observer can be attached, but they cannot share the same address.
     *
     * @post One more observer is attached to the subject.
     *
     * @param p_newObserver The observer to attach.
     *
     * Once an observer is attached, its @c Update() method is automatically called whenever
     * @c Notify() is called from the subject.
     *
     * @warning Never call @c Update() directly from an observer. Always use @c Notify().
     *
     ********************************************************************************************/
    void Attach(IObserver* const p_newObserver);

    /******************************************************************************************//**
     * @brief Detach a specific observer from the subject.
     *
     * @pre The observer has a valid address.
     * @pre There is at least one attached observer.
     * @pre The observer has previously been attached to the subject.
     *
     * @post There is one less observer attached to the subject.
     *
     * @param p_oldObserver The observer to detach.
     *
     * Detach a specific, previously attached, observer from the subject. One this method has
     * been called, the detached observer will no longer receive any notification from the
     * subject.
     *
     ********************************************************************************************/
    void Detatch(IObserver* const p_oldObserver);

    /******************************************************************************************//**
     * @brief Detach all observers.
     *
     * @post They are no more observers attached to the subject.
     *
     * Detach all observers. Note that this can be called safely even if some observers have,
     * for some reason, been invalidated.
     *
     ********************************************************************************************/
    void DetatchAll();


protected:

    /******************************************************************************************//**
     * @brief Notifies all observers that some event has occurred.
     *
     * @param p_context The context in which the notification occurs.
     *
     * For each event that need notifying the observers, this method must be called explicitly.
     * It will in turn update to state of all attached observers.
     *
     ********************************************************************************************/
    void Notify(NotificationContext p_context);


private:

    void CheckInvariants();

    std::vector<cxmodel::IObserver*> m_observers;

};

} // namespace cxmodel

#endif // SUBJECT_H_520FD354_27E1_4AE7_9579_71016A78DC44
