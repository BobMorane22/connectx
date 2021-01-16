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
 * @file DisableStdStreamsRAIITests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <DisableStdStreamsRAII.h>

// This test adds output to the console. In this case, it
// is fine since this is exactly what is tested.
TEST(DisableStdStreamsRAII, Constructor_WithScope_StdOutRAII)
{
    std::cout << "Hello ";
    {
        cxunit::DisableStdStreamsRAII raii;
        ASSERT_EQ(raii.GetStdOutContents(), "");
        
        std::cout << "World";

        ASSERT_EQ(raii.GetStdOutContents(), "World");
    }
}

// This test adds output to the console. In this case, it
// is fine since this is exactly what is tested.
TEST(DisableStdStreamsRAII, Constructor_WithScope_StdErrRAII)
{
    std::cerr << "Hello ";
    {
        cxunit::DisableStdStreamsRAII raii;
        ASSERT_EQ(raii.GetStdErrContents(), "");
        
        std::cerr << "World";

        ASSERT_EQ(raii.GetStdErrContents(), "World");
    }
}
