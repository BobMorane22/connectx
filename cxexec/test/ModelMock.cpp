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

std::string ModelMock::GetName() const
{
    return "Connect X";
}

std::string ModelMock::GetVersionNumber() const
{
    return "v0.0";
}

void ModelMock::CreateNewGame(const cxmodel::NewGameInformation& /*p_gameInformation*/)
{
    // Not used for now.
}

cxmodel::NewGameInformation ModelMock::GetGameInformation() const
{
    // Not used for now.
    return {};
}

void ModelMock::Undo()
{
    // Nothing to do for now...
}

void ModelMock::Redo()
{
    // Nothing to do for now...
}

void ModelMock::Signal()
{
    // Nothing to do for now...
}

