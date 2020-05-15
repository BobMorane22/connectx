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
 * @file assertion.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <assertion.h>

#ifndef NDEBUG
#include <iostream>

namespace
{

void AbortIfNeeded()
{
#ifdef ABORT_ON_ERROR
    std::abort();
#endif // ABORT_ON_ERROR
}

const char* GetLabelAsString(cxinv::AssertLabel p_label)
{
    switch(p_label)
    {
        case cxinv::AssertLabel::ASSERTION:     return "Assertion";
        case cxinv::AssertLabel::PRECONDITION:  return "Precondition";
        case cxinv::AssertLabel::POSTCONDITION: return "Postcondition";
        case cxinv::AssertLabel::INVARIANT:     return "Invariant";
        default:                                        // LCOV_EXCL_LINE
            std::abort(); // Label type unknown...      // LCOV_EXCL_LINE
    }
}

} // namespace

void cxinv::HandleAssert(const cxinv::AssertLabel  p_label,
                         const bool                p_conditionRes,
                         const char*               p_conditionExpr,
                         const char*               p_fileName,
                         const char*               p_functionName,
                         const long                p_lineNumber,
                         const char*               p_message)
{
    // LCOV_EXCL_START
    // This code is reached through death tests, and hence are ignored by the coverage
    // tool. Consequently, we exclude it from the analysis.
    if(!p_conditionExpr ||
       !p_fileName      ||
       !p_functionName)
    {
        std::cerr << __FILE__ << ": Assertion error. Invalid arguments given to cxinv::handleAssert.";

        std::abort();
    }
    // LCOV_EXCL_STOP

    if(!(p_conditionRes))
    {
        if(p_label == AssertLabel::ASSERTION)
        {
            std::cerr << "Assertion failed at ";
        }
        else
        {
            std::cerr << GetLabelAsString(p_label) << " violation at ";
        }

        std::cerr << p_fileName << ": line " << p_lineNumber << "." << std::endl;
        std::cerr << "  Function   : " << p_functionName << std::endl;
        std::cerr << "  Expression : " << p_conditionExpr << std::endl;

        if(p_message)
        {
            std::cerr << "  Message    : " << p_message << std::endl;
        }

        std::cerr << std::endl;

        AbortIfNeeded();
    }
}

#endif // NDEBUG
