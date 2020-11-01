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
 * @file Subject.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <algorithm>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/IObserver.h>

#include <Subject.h>

cxmodel::Subject::Subject()
{
    CheckInvariants();
}

cxmodel::Subject::~Subject()
{
    DetatchAll();
}

void cxmodel::Subject::Attach(cxmodel::IObserver* const p_newObserver)
{
    PRECONDITION(p_newObserver);

    const std::size_t oldSize = m_observers.size();

    if(p_newObserver)
    {
        const bool alreadyRegistered = std::any_of(m_observers.cbegin(),
                                                   m_observers.cend(), [p_newObserver](cxmodel::IObserver* const p_observer)
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

    const std::size_t newSize = m_observers.size();

    POSTCONDITION(newSize - oldSize == 1);

    CheckInvariants();
}

void cxmodel::Subject::Detatch(cxmodel::IObserver* const p_oldObserver)
{
    PRECONDITION(p_oldObserver);

    const std::size_t oldSize = m_observers.size();
    PRECONDITION(oldSize > 0);

    std::size_t newSize = m_observers.size();

    if(p_oldObserver)
    {
        const auto position = std::find(m_observers.cbegin(),
                                        m_observers.cend(),
                                        p_oldObserver);

        PRECONDITION(position != m_observers.cend());

        if(position != m_observers.end())
        {
            m_observers.erase(position);
            newSize = m_observers.size();
        }
    }


    POSTCONDITION(oldSize - newSize == 1);

    CheckInvariants();
}

void cxmodel::Subject::DetatchAll()
{
    // Here the fact that there might be no observer listed is not a problem.
    // This is the case because we are not looking to detach a specific observer,
    // but all of them, regardless of who they are. This might, for example, be
    // called as some insurance that there really are no observers listed.

    m_observers.clear();

    POSTCONDITION(m_observers.size() == 0);

    CheckInvariants();
}

void cxmodel::Subject::Notify(NotificationContext p_context)
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

void cxmodel::Subject::CheckInvariants()
{
    INVARIANT(std::none_of(m_observers.cbegin(),
                           m_observers.cend(),
                           [](cxmodel::IObserver* const p_observer)
                           {
                                return p_observer == nullptr;
                           }));
}
