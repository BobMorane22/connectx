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

#include <algorithm>
#include <type_traits>
#include <vector>

#include <cxinv/assertion.h>
#include <cxmodel/IObserver.h>

namespace cxmodel
{
    template<typename>
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
 * @tparam T A notification context. Must be an enum.
 *
 * @see cxmodel::IObserver
 *
 ************************************************************************************************/
template<typename T>
class Subject
{

    static_assert(std::is_enum_v<T>, "Notification context types must be enums.");

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
    void Attach(IObserver<T>* const p_newObserver);

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
    void Detatch(IObserver<T>* const p_oldObserver);

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
    void Notify(T p_context);

private:

    void CheckInvariants();

    std::vector<cxmodel::IObserver<T>*> m_observers;

};

} // namespace cxmodel

template<typename T>
cxmodel::Subject<T>::Subject()
{
    CheckInvariants();
}

template<typename T>
cxmodel::Subject<T>::~Subject()
{
    DetatchAll();
}

template<typename T>
void cxmodel::Subject<T>::Attach(cxmodel::IObserver<T>* const p_newObserver)
{
    PRECONDITION(p_newObserver);

    if(p_newObserver)
    {
        const bool alreadyRegistered = std::any_of(m_observers.cbegin(),
                                                   m_observers.cend(), [p_newObserver](cxmodel::IObserver<T>* const p_observer)
                                                                      {
                                                                          return p_observer == p_newObserver;
                                                                      }
                                                   );

        PRECONDITION(!alreadyRegistered);

        if(!alreadyRegistered)
        {
            m_observers.push_back(p_newObserver);
        }
    }

    CheckInvariants();
}

template<typename T>
void cxmodel::Subject<T>::Detatch(cxmodel::IObserver<T>* const p_oldObserver)
{
    PRECONDITION(p_oldObserver);

    if(p_oldObserver)
    {
        const auto position = std::find(m_observers.cbegin(),
                                        m_observers.cend(),
                                        p_oldObserver);

        PRECONDITION(position != m_observers.cend());

        if(position != m_observers.end())
        {
            m_observers.erase(position);
        }
    }

    CheckInvariants();
}

template<typename T>
void cxmodel::Subject<T>::DetatchAll()
{
    // Here the fact that there might be no observer listed is not a problem.
    // This is the case because we are not looking to detach a specific observer,
    // but all of them, regardless of who they are. This might, for example, be
    // called as some insurance that there really are no observers listed.

    m_observers.clear();

    POSTCONDITION(m_observers.size() == 0);

    CheckInvariants();
}

template<typename T>
void cxmodel::Subject<T>::Notify(T p_context)
{
    for(const auto observer : m_observers)
    {
        if(observer)
        {
            observer->Update(p_context, this);
        }
    }

    CheckInvariants();
}

template<typename T>
void cxmodel::Subject<T>::CheckInvariants()
{
    INVARIANT(std::none_of(m_observers.cbegin(),
                           m_observers.cend(),
                           [](cxmodel::IObserver<T>* const p_observer)
                           {
                                return p_observer == nullptr;
                           }));
}

#endif // SUBJECT_H_520FD354_27E1_4AE7_9579_71016A78DC44
