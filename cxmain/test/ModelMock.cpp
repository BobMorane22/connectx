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
 * @file ModelMock.h
 * @date 2019
 *
 *************************************************************************************************/

#include "ModelMock.h"

ModelMock::ModelMock()
 : m_currentValue{m_INITIAL_VALUE}
{
}

unsigned int ModelMock::GetCurrentValue() const
{
    return m_currentValue;
}

void ModelMock::Increment()
{
    ++m_currentValue;
}

void ModelMock::Reinitialize()
{
    m_currentValue = m_INITIAL_VALUE;
}

std::string ModelMock::GetName() const
{
    return "Connect X";
}

std::string ModelMock::GetVersionNumber() const
{
    return "v0.0";
}

void ModelMock::Undo()
{
    // Nothing to do for now...
}

void ModelMock::Redo()
{
    // Nothing to do for now...
}
