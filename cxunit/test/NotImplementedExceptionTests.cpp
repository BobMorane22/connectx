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
 * @file NotImplementedExceptionTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/NotImplementedException.h>

class NotImplemented
{

public:

    void NotImplementedMethod()
    {
        throw cxunit::NotImplementedException();
    }
};

TEST(NotImplementedException, SomeOperation_ExceptionThrown_NotImplementedMessageRetreived)
{
    NotImplemented object;
    
    bool exceptionThrown = false;
    std::string exceptionMessage = "";

    try
    {
        object.NotImplementedMethod();
    }
    catch(const cxunit::NotImplementedException& p_exception)
    {
        exceptionThrown = true;
        exceptionMessage = p_exception.what();
    }

    ASSERT_TRUE(exceptionThrown);
    ASSERT_EQ("Not implemented.", exceptionMessage);
}
