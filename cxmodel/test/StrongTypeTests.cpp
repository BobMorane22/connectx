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

TEST(StrongType, /*DISABLED_*/Constructor_ByValue_ValidStrongType)
{
    int weakInt = 3;
    StrongInt sInt{weakInt};
    ASSERT_TRUE(sInt.Get() == 3);

    std::string weakString = "Hello";
    StrongString sString{weakString};
    ASSERT_TRUE(sString.Get() == "Hello");
}

TEST(StrongType, /*DISABLED_*/Constructor_ByRef_ValidStrongType)
{
    int weakInt = 3;
    int& weakIntRef = weakInt;
    StrongInt sInt{weakIntRef};
    ASSERT_TRUE(sInt.Get() == 3);

    std::string weakString = "Hello";
    StrongString sString{weakString};
    ASSERT_TRUE(sString.Get() == "Hello");
}

TEST(StrongType, /*DISABLED_*/Constructor_Move_ValidStrongType)
{
    StrongInt sInt{3};
    ASSERT_TRUE(sInt.Get() == 3);

    StrongString sString{"Hello"};
    ASSERT_TRUE(sString.Get() == "Hello");
}

//TEST(StrongType, /*DISABLED_*/Assignement_ByValue_ValidStrongType)
//{
//    int weakInt = 3;
//    StrongInt sInt = weakInt;
//    ASSERT_TRUE(sInt.Get() == 3);
//
//    std::string weakString = "Hello";
//    StrongString sString = weakString;
//    ASSERT_TRUE(sString.Get() == "Hello");
//}

//TEST(StrongType, /*DISABLED_*/Assignement_Move_ValidStrongType)
//{
//    StrongInt sInt = 3;
//    ASSERT_TRUE(sInt.Get() == 3);
//
//    StrongString sString = "Hello";
//    ASSERT_TRUE(sString.Get() == "Hello");
//}

TEST(StrongType, /*DISABLED_*/Get_ByRef_ValidRefReturned)
{
    StrongInt sInt{3};
    int& aRefOnInt = sInt.Get();
    ASSERT_TRUE(aRefOnInt == 3);

    StrongString sString{"Hello"};
    std::string& aRefOnString = sString.Get();
    ASSERT_TRUE(aRefOnString == "Hello");
}

TEST(StrongType, /*DISABLED_*/Get_ByConstRef_ValidConstRefReturned)
{
    StrongInt sInt{3};
    const int& aRefOnInt = sInt.Get();
    ASSERT_TRUE(aRefOnInt == 3);

    StrongString sString{"Hello"};
    const std::string& aRefOnString = sString.Get();
    ASSERT_TRUE(aRefOnString == "Hello");
}

namespace
{

using ECInt = cxstd::StrongType<int, struct IntTag, cxstd::EqualityComparable>;

} // namespace

TEST(EqualityComparable, OperatorEquals_TwoEqualUnderlying_ReturnsTrue)
{
    constexpr int same = 1;
    constexpr ECInt lhs{same};
    constexpr ECInt rhs{same};

    // Underlying equality:
    ASSERT_TRUE(lhs.Get() == rhs.Get());

    // Strong type equality:
    ASSERT_TRUE(lhs == rhs);
}

TEST(EqualityComparable, OperatorEquals_TwoDifferentUnderlying_ReturnsFalse)
{
    constexpr ECInt lhs{1};
    constexpr ECInt rhs{2};

    // Underlying inequality:
    ASSERT_TRUE(lhs.Get() != rhs.Get());

    // Strong type inequality:
    ASSERT_TRUE(lhs != rhs);
}

namespace
{

using AInt = cxstd::StrongType<int, struct IntTag, cxstd::Addable>;

} // namespace

TEST(Addable, OperatorPlus_OnePlusTwo_ReturnsThree)
{
    constexpr AInt lhs{1};
    constexpr AInt rhs{2};

    constexpr AInt sum = lhs + rhs;

    ASSERT_TRUE(sum.Get() == 3);
}

TEST(Addable, OperatorMinus_OneMinusTwo_ReturnsMinusOne)
{
    constexpr AInt lhs{1};
    constexpr AInt rhs{2};

    constexpr AInt difference = lhs - rhs;

    ASSERT_TRUE(difference.Get() == -1);
}

TEST(Addable, OperatorIncrementPlus_OnePlusTwo_ReturnsThree)
{
    AInt lhs{1};
    constexpr AInt rhs{2};

    lhs += rhs;

    ASSERT_TRUE(lhs.Get() == 3);
}

TEST(Addable, OperatorIncrementPlus_Chaining_ReturnsResult)
{
    AInt lhs{1};
    constexpr AInt rhs{2};

    (lhs += rhs) += rhs;

    ASSERT_TRUE(lhs.Get() == 5);
}

TEST(Addable, OperatorIncrementMinus_OneMinusTwo_ReturnsMinusOne)
{
    AInt lhs{1};
    constexpr AInt rhs{2};

    lhs -= rhs;

    ASSERT_TRUE(lhs.Get() == -1);
}

TEST(Addable, OperatorIncrementMinus_Chaining_ReturnsResult)
{
    AInt lhs{1};
    constexpr AInt rhs{2};

    (lhs -= rhs) -= rhs;

    ASSERT_TRUE(lhs.Get() == -3);
}

namespace
{

using CInt = cxstd::StrongType<int, struct IntTag, cxstd::EqualityComparable, cxstd::Comparable>;

} // namespace

TEST(Comparable, OperatorLessThan_IsLessThen_ReturnsTrue)
{
    constexpr CInt lhs{1};
    constexpr CInt rhs{2};

    // Underlying type:
    ASSERT_TRUE(lhs.Get() < rhs.Get());

    // Strong type equivalent:
    ASSERT_TRUE(lhs < rhs);
}

TEST(Comparable, OperatorLessThan_AreEqual_ReturnsFalse)
{
    constexpr int same = 1;
    constexpr CInt lhs{same};
    constexpr CInt rhs{same};

    // Underlying type:
    ASSERT_FALSE(lhs.Get() < rhs.Get());

    // Strong type equivalent:
    ASSERT_FALSE(lhs < rhs);
}

TEST(Comparable, OperatorLessThan_NotLessThan_ReturnsFalse)
{
    constexpr CInt lhs{2};
    constexpr CInt rhs{1};

    // Underlying type:
    ASSERT_FALSE(lhs.Get() < rhs.Get());

    // Strong type equivalent:
    ASSERT_FALSE(lhs < rhs);
}

TEST(Comparable, OperatorGreaterThan_IsGreaterThen_ReturnsTrue)
{
    constexpr CInt lhs{2};
    constexpr CInt rhs{1};

    // Underlying type:
    ASSERT_TRUE(lhs.Get() > rhs.Get());

    // Strong type equivalent:
    ASSERT_TRUE(lhs > rhs);
}

TEST(Comparable, OperatorGreaterThan_AreEqual_ReturnsFalse)
{
    constexpr int same = 1;
    constexpr CInt lhs{same};
    constexpr CInt rhs{same};

    // Underlying type:
    ASSERT_FALSE(lhs.Get() > rhs.Get());

    // Strong type equivalent:
    ASSERT_FALSE(lhs > rhs);
}

TEST(Comparable, OperatorGreaterThan_NotGreaterThan_ReturnsFalse)
{
    constexpr CInt lhs{1};
    constexpr CInt rhs{2};

    // Underlying type:
    ASSERT_FALSE(lhs.Get() > rhs.Get());

    // Strong type equivalent:
    ASSERT_FALSE(lhs > rhs);
}

TEST(Comparable, OperatorLessThanOrEqual_IsLessThen_ReturnsTrue)
{
    constexpr CInt lhs{1};
    constexpr CInt rhs{2};

    // Underlying type:
    ASSERT_TRUE(lhs.Get() <= rhs.Get());

    // Strong type equivalent:
    ASSERT_TRUE(lhs <= rhs);
}

TEST(Comparable, OperatorLessThanOrEqual_AreEqual_ReturnsTrue)
{
    constexpr int same = 1;
    constexpr CInt lhs{same};
    constexpr CInt rhs{same};

    // Underlying type:
    ASSERT_TRUE(lhs.Get() <= rhs.Get());

    // Strong type equivalent:
    ASSERT_TRUE(lhs <= rhs);
}

TEST(Comparable, OperatorLessThanOrEqual_NotLessThan_ReturnsFalse)
{
    constexpr CInt lhs{2};
    constexpr CInt rhs{1};

    // Underlying type:
    ASSERT_FALSE(lhs.Get() <= rhs.Get());

    // Strong type equivalent:
    ASSERT_FALSE(lhs <= rhs);
}

TEST(Comparable, OperatorGreaterThanOrEqual_IsGreaterThen_ReturnsTrue)
{
    constexpr CInt lhs{2};
    constexpr CInt rhs{1};

    // Underlying type:
    ASSERT_TRUE(lhs.Get() >= rhs.Get());

    // Strong type equivalent:
    ASSERT_TRUE(lhs >= rhs);
}

TEST(Comparable, OperatorGreaterThanOrEqual_AreEqual_ReturnsTrue)
{
    constexpr int same = 1;
    constexpr CInt lhs{same};
    constexpr CInt rhs{same};

    // Underlying type:
    ASSERT_TRUE(lhs.Get() >= rhs.Get());

    // Strong type equivalent:
    ASSERT_TRUE(lhs >= rhs);
}

TEST(Comparable, OperatorGreaterThanOrEqual_NotGreaterThan_ReturnsFalse)
{
    constexpr CInt lhs{1};
    constexpr CInt rhs{2};

    // Underlying type:
    ASSERT_FALSE(lhs.Get() >= rhs.Get());

    // Strong type equivalent:
    ASSERT_FALSE(lhs >= rhs);
}
