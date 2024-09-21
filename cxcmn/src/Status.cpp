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
 * @file Status.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxcmn/Status.h>

cx::cmn::Status::Status()
: m_status{true}
{
    // Nothing to do...
}

cx::cmn::Status::Status(const std::string& p_errorMessage)
: m_status{false}
, m_errorMessage{p_errorMessage}
{
    // Nothing to do...
}

bool cx::cmn::Status::IsSuccess() const
{
    return m_status;
}

const std::string& cx::cmn::Status::GetMessage() const
{
    return m_errorMessage;
}

cx::cmn::Status cx::cmn::MakeSuccess()
{
    return cx::cmn::Status();
}

cx::cmn::Status cx::cmn::MakeError(const std::string& p_errorMessage)
{
    return cx::cmn::Status(p_errorMessage);
}
