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
 * @file ModelMockController.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "ModelMockController.h"

ModelMockController::ModelMockController()
 : m_undoed{false}
 , m_redoed{false}
 , m_signaled{false}
{
}

std::string ModelMockController::GetName() const
{
    return "Connect X";
}

std::string ModelMockController::GetVersionNumber() const
{
    return "v0.0";
}

void ModelMockController::CreateNewGame(const cxmodel::GameInformation& /*p_gameInformation*/)
{
    // Not used for now.
}

cxmodel::GameInformation ModelMockController::GetGameInformation() const
{
    return {};
}

void ModelMockController::Undo()
{
    m_undoed = true;
}

void ModelMockController::Redo()
{
    m_redoed = true;
}

void ModelMockController::Signal()
{
    m_signaled = true;
}

bool ModelMockController::GetUndoed() const
{
    return m_undoed;
}

bool ModelMockController::GetRedoed() const
{
    return m_redoed;
}

bool ModelMockController::GetSignaled() const
{
    return m_signaled;
}
