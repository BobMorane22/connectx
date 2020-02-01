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
 * @file Logger.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <Logger.h>

void cxlog::Logger::SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel)
{
    m_verbosityLevel = p_verbosityLevel;
}

cxlog::VerbosityLevel cxlog::Logger::GetVerbosityLevel() const
{
    return m_verbosityLevel;
}
