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
 * @file Model.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <cxinv/include/assertion.h>

#include <Model.h>

cxmodel::Model::Model()
{
    m_currentValue = m_INITIAL_VALUE;
}

unsigned int cxmodel::Model::GetCurrentValue() const
{
    return m_currentValue;
}

void cxmodel::Model::Increment()
{
    const unsigned int old = m_currentValue;

    ++m_currentValue;

    Notify();

    POSTCONDITION(m_currentValue - old == 1);
}

void cxmodel::Model::Reinitialize()
{
    m_currentValue = m_INITIAL_VALUE;

    Notify();

    POSTCONDITION(m_currentValue == m_INITIAL_VALUE);
}
