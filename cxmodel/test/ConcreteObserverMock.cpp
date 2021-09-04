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
 * @file ConcreteObserverMock.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxinv/include/assertion.h>

#include <ConcreteObserverMock.h>
#include <ConcreteSubjectMock.h>

ConcreteObserverMock::ConcreteObserverMock()
 : m_data{0}
{
}

int ConcreteObserverMock::GetData() const
{
    return m_data;
}

void ConcreteObserverMock::Update(cxmodel::NotificationContext, cxmodel::ModelSubject* p_subject)
{
    ConcreteSubjectMock* subject = static_cast<ConcreteSubjectMock*>(p_subject);

    ASSERT_TRUE(subject != nullptr);

    m_data = subject->GetData();
}
