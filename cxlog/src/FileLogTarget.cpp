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
 * @file FileLogTarget.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxlog/FileLogTarget.h>

cxlog::FileLogTarget::FileLogTarget(const std::string& p_logFileName)
{
    m_fileStream.open(p_logFileName, std::ios_base::out);

    ASSERT_MSG(FileStream().good(), "File stream is in a bad state.");
}

void cxlog::FileLogTarget::Log(const std::string& p_message)
{
    if(ASSERT(FileStream().good()))
    {
        FileStream() << p_message;
    }
}
