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
 * @file HandleAssertTestFixture.cpp
 * @date 2019
 *
 *************************************************************************************************/

#ifndef NDEBUG

#include "HandleAssertTestFixture.h"

std::string HandleAssertTestFixture::GetStdOutContents() const
{
    return m_disableStreamsRAII.GetStdOutContents();
}

std::string HandleAssertTestFixture::GetStdErrContents() const
{
    return m_disableStreamsRAII.GetStdErrContents();
}

std::string HandleAssertTestFixture::MakeExpectedMessage(cxinv::AssertLabel p_label, const char* p_message) const
{
    std::ostringstream stream;

    if(p_label == cxinv::AssertLabel::ASSERTION)
    {
        stream << "Assertion failed at ";
    }
    else
    {
        switch(p_label)
        {
            case cxinv::AssertLabel::PRECONDITION:
                stream << "Precondition";
                break;

            case cxinv::AssertLabel::POSTCONDITION:
                stream << "Postcondition";
                break;

            case cxinv::AssertLabel::INVARIANT:
                stream << "Invariant";
                break;

            default:
                return {};
        }

        stream << " violation at ";
    }

    stream << m__FILE_ << ": line " << m__LINE_ << "." << std::endl;
    stream << "  Function   : " << m__FUNCTION_ << std::endl;
    stream << "  Expression : " << m_CONDITION_EXPRESSION << std::endl;

    if(p_message)
    {
        stream << "  Message    : " << p_message << std::endl;
    }

    stream << std::endl;

    return stream.str();
}

#endif // NDEBUG
