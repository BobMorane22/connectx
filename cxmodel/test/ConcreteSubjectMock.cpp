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
 * @file ConcreteSubjectMock.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <ConcreteSubjectMock.h>

ConcreteSubjectMock::ConcreteSubjectMock(int p_data)
 : m_data{p_data}
{
}

int ConcreteSubjectMock::GetData() const
{
    return m_data;
}

void ConcreteSubjectMock::IncrementData()
{
    ++m_data;

    Notify(cxmodel::NotificationContext::CREATE_NEW_GAME);
}
