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

#include <cxinv/include/assertion.h>

#include <Status.h>

cxmodel::Status::Status()
: m_status{true}
{
    CheckInvariants();
}

cxmodel::Status::Status(const std::string& p_errorMessage)
: m_status{false}
, m_errorMessage{p_errorMessage}
{
    PRECONDITION(!p_errorMessage.empty());
    POSTCONDITION(!m_errorMessage.empty());

    CheckInvariants();
}

bool cxmodel::Status::IsSuccess() const
{
    return m_status;
}

const std::string& cxmodel::Status::GetMessage() const
{
    PRECONDITION(!m_errorMessage.empty());

    return m_errorMessage;
}

void cxmodel::Status::CheckInvariants()
{
    INVARIANT((IsSuccess() && m_errorMessage.empty()) || (!IsSuccess() && !m_errorMessage.empty()));
}

cxmodel::Status cxmodel::MakeSuccess()
{
    return cxmodel::Status();
}

cxmodel::Status cxmodel::MakeError(const std::string& p_errorMessage)
{
    PRECONDITION(!p_errorMessage.empty());

    return cxmodel::Status(p_errorMessage);
}
