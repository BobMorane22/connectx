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
 * @file algorithmTests.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <vector>

#include <gtest/gtest.h>

#include <cxstd/algorithm.h>

namespace
{

class Unsortable final
{

public:

    // Allowed:
    [[nodiscard]] static Unsortable A(){return Unsortable{'A'};}
    [[nodiscard]] static Unsortable B(){return Unsortable{'B'};}
    [[nodiscard]] static Unsortable C(){return Unsortable{'C'};}
    [[nodiscard]] static Unsortable D(){return Unsortable{'D'};}
    [[nodiscard]] static Unsortable E(){return Unsortable{'E'};}
    [[nodiscard]] static Unsortable F(){return Unsortable{'F'};}

    Unsortable(const Unsortable& p_rhs) = default;

    [[nodiscard]] bool operator==(const Unsortable& p_rhs) const
    {
        return m_char == p_rhs.m_char;
    }

    // Restricted:
    Unsortable& operator=(const Unsortable& p_rhs) = delete;
    bool operator!=(const Unsortable& p_rhs) = delete;
    bool operator<(const Unsortable& p_rhs) = delete;
    bool operator<=(const Unsortable& p_rhs) = delete;
    bool operator>(const Unsortable& p_rhs) = delete;
    bool operator>=(const Unsortable& p_rhs) = delete;

private:

    Unsortable(char p_char)
    : m_char(p_char)
    {}

    char m_char;
};

bool operator!=(const Unsortable& p_lhs, const Unsortable& p_rhs) = delete;
bool operator<(const Unsortable& p_lhs, const Unsortable& p_rhs) = delete;
bool operator<=(const Unsortable& p_lhs, const Unsortable& p_rhs) = delete;
bool operator>(const Unsortable& p_lhs, const Unsortable& p_rhs) = delete;
bool operator>=(const Unsortable& p_lhs, const Unsortable& p_rhs) = delete;

} // namespace

TEST(Algorithm, ComputeStrictDifference_LhsAndRhsEmpty_ReturnsEmpty)
{
    const std::vector<Unsortable> lhs, rhs;
    ASSERT_TRUE(lhs.empty());
    ASSERT_TRUE(rhs.empty());

    const std::vector<Unsortable> result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result.empty());
}

TEST(Algorithm, ComputeStrictDifference_LhsEmptyButRhsNotEmpty_ReturnsEmpty)
{
    const std::vector<Unsortable> lhs;
    ASSERT_TRUE(lhs.empty());

    const std::vector<Unsortable> rhs{Unsortable::A()};
    ASSERT_TRUE(!rhs.empty());

    const std::vector<Unsortable> result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result.empty());
}

TEST(Algorithm, ComputeStrictDifference_LhsNotEmptyButRhsEmpty_ReturnsLhs)
{
    const std::vector<Unsortable> lhs{Unsortable::A()};
    ASSERT_TRUE(!lhs.empty());

    const std::vector<Unsortable> rhs;
    ASSERT_TRUE(rhs.empty());

    const std::vector<Unsortable> result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == lhs);
}

TEST(Algorithm, ComputeStrictDifference_LhsAndRhsMutuallyExclusive_ReturnsLhs)
{
    const std::vector<Unsortable> lhs{Unsortable::A()};
    ASSERT_TRUE(!lhs.empty());

    const std::vector<Unsortable> rhs{Unsortable::B()};
    ASSERT_TRUE(!rhs.empty());

    const std::vector<Unsortable> result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == lhs);
}

TEST(Algorithm, ComputeStrictDifference_LhsAndRhsNotMutuallyExclusiveSorted_ReturnsDifference)
{
    const std::vector<Unsortable> lhs
    {
        Unsortable::A(),
        Unsortable::B(),
        Unsortable::B(),
        Unsortable::C(),
        Unsortable::D(),
        Unsortable::E(),
        Unsortable::E(),
    };
    ASSERT_TRUE(!lhs.empty());

    const std::vector<Unsortable> rhs
    {
        Unsortable::B(),
        Unsortable::D(),
        Unsortable::F(),
    }; 
    ASSERT_TRUE(!rhs.empty());

    const std::vector<Unsortable> expected
    {
        Unsortable::A(),
        Unsortable::C(),
        Unsortable::E(),
        Unsortable::E(),
    };
    ASSERT_TRUE(!expected.empty());

    const std::vector<Unsortable> result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == expected);
}

TEST(Algorithm, ComputeStrictDifference_LhsAndRhsNotMutuallyExclusiveUnsorted_ReturnsDifference)
{
    const std::vector<Unsortable> lhs
    {
        Unsortable::E(),
        Unsortable::B(),
        Unsortable::D(),
        Unsortable::C(),
        Unsortable::A(),
        Unsortable::E(),
        Unsortable::B(),
    };
    ASSERT_TRUE(!lhs.empty());

    const std::vector<Unsortable> rhs
    {
        Unsortable::F(),
        Unsortable::B(),
        Unsortable::D(),
    }; 
    ASSERT_TRUE(!rhs.empty());

    const std::vector<Unsortable> expected
    {
        Unsortable::E(),
        Unsortable::C(),
        Unsortable::A(),
        Unsortable::E(),
    };
    ASSERT_TRUE(!expected.empty());

    const std::vector<Unsortable> result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == expected);
}
