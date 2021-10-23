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
 * @file StrongTypeTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <string>

#include <gtest/gtest.h>

#include <StrongType.h>

using StrongInt = cxstd::StrongType<int, struct StrongIntPhantom>;
using StrongString = cxstd::StrongType<std::string, struct StrongStringPhantom>;

TEST(StrongType, Constructor_ByValue_ValidStrongType)
{
    int weakInt = 3;
    StrongInt sInt{weakInt};
    ASSERT_TRUE(sInt.Get() == 3);

    std::string weakString = "Hello";
    StrongString sString{weakString};
    ASSERT_TRUE(sString.Get() == "Hello");
}

TEST(StrongType, Constructor_ByRef_ValidStrongType)
{
    int weakInt = 3;
    int& weakIntRef = weakInt;
    StrongInt sInt{weakIntRef};
    ASSERT_TRUE(sInt.Get() == 3);

    std::string weakString = "Hello";
    StrongString sString{weakString};
    ASSERT_TRUE(sString.Get() == "Hello");
}

TEST(StrongType, Constructor_Move_ValidStrongType)
{
    StrongInt sInt{3};
    ASSERT_TRUE(sInt.Get() == 3);

    StrongString sString{"Hello"};
    ASSERT_TRUE(sString.Get() == "Hello");
}

//TEST(StrongType, Assignement_ByValue_ValidStrongType)
//{
//    int weakInt = 3;
//    StrongInt sInt = weakInt;
//    ASSERT_TRUE(sInt.Get() == 3);
//
//    std::string weakString = "Hello";
//    StrongString sString = weakString;
//    ASSERT_TRUE(sString.Get() == "Hello");
//}

//TEST(StrongType, Assignement_Move_ValidStrongType)
//{
//    StrongInt sInt = 3;
//    ASSERT_TRUE(sInt.Get() == 3);
//
//    StrongString sString = "Hello";
//    ASSERT_TRUE(sString.Get() == "Hello");
//}

TEST(StrongType, Get_ByRef_ValidRefReturned)
{
    StrongInt sInt{3};
    int& aRefOnInt = sInt.Get();
    ASSERT_TRUE(aRefOnInt == 3);

    StrongString sString{"Hello"};
    std::string& aRefOnString = sString.Get();
    ASSERT_TRUE(aRefOnString == "Hello");
}

TEST(StrongType, Get_ByConstRef_ValidConstRefReturned)
{
    StrongInt sInt{3};
    const int& aRefOnInt = sInt.Get();
    ASSERT_TRUE(aRefOnInt == 3);

    StrongString sString{"Hello"};
    const std::string& aRefOnString = sString.Get();
    ASSERT_TRUE(aRefOnString == "Hello");
}
