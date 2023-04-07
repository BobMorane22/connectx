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

#include <deque>
#include <list>
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
    Unsortable(Unsortable&& p_rhs) = default;
    Unsortable& operator=(const Unsortable& p_rhs) = default;
    Unsortable& operator=(Unsortable&& p_rhs) = default;

    [[nodiscard]] bool operator==(const Unsortable& p_rhs) const
    {
        return m_char == p_rhs.m_char;
    }

    // Restricted:
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

/*************************************************************************************************
 *                            cxstd::ComputeStricDifference
 ************************************************************************************************/
namespace
{

template<typename T>
class ComputeStrictDifferenceFixture : public testing::Test {};

using ComputeStrictDifferenceTypes = ::testing::Types<
    std::deque<Unsortable>,
    std::list<Unsortable>,
    std::vector<Unsortable>
>;

TYPED_TEST_SUITE(ComputeStrictDifferenceFixture, ComputeStrictDifferenceTypes);

} // namespace

TYPED_TEST(ComputeStrictDifferenceFixture, ComputeStrictDifference_LhsAndRhsEmpty_ReturnsEmpty)
{
    using Container = TypeParam;

    Container lhs, rhs;

    ASSERT_TRUE(lhs.empty());
    ASSERT_TRUE(rhs.empty());

    const Container result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result.empty());
}

TYPED_TEST(ComputeStrictDifferenceFixture, ComputeStrictDifference_LhsEmptyButRhsNotEmpty_ReturnsEmpty)
{
    using Container = TypeParam;

    const Container lhs;
    ASSERT_TRUE(lhs.empty());

    const Container rhs{Unsortable::A()};
    ASSERT_TRUE(!rhs.empty());

    const Container result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result.empty());
}

TYPED_TEST(ComputeStrictDifferenceFixture, ComputeStrictDifference_LhsNotEmptyButRhsEmpty_ReturnsLhs)
{
    using Container = TypeParam;

    const Container lhs{Unsortable::A()};
    ASSERT_TRUE(!lhs.empty());

    const Container rhs;
    ASSERT_TRUE(rhs.empty());

    const Container result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == lhs);
}

TYPED_TEST(ComputeStrictDifferenceFixture, ComputeStrictDifference_LhsAndRhsMutuallyExclusive_ReturnsLhs)
{
    using Container = TypeParam;

    const Container lhs{Unsortable::A()};
    ASSERT_TRUE(!lhs.empty());

    const Container rhs{Unsortable::B()};
    ASSERT_TRUE(!rhs.empty());

    const Container result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == lhs);
}

TYPED_TEST(ComputeStrictDifferenceFixture, ComputeStrictDifference_LhsAndRhsNotMutuallyExclusiveSorted_ReturnsDifference)
{
    using Container = TypeParam;

    const Container lhs
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

    const Container rhs
    {
        Unsortable::B(),
        Unsortable::D(),
        Unsortable::F(),
    }; 
    ASSERT_TRUE(!rhs.empty());

    const Container expected
    {
        Unsortable::A(),
        Unsortable::C(),
        Unsortable::E(),
        Unsortable::E(),
    };
    ASSERT_TRUE(!expected.empty());

    const Container result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == expected);
}

TYPED_TEST(ComputeStrictDifferenceFixture, ComputeStrictDifference_LhsAndRhsNotMutuallyExclusiveUnsorted_ReturnsDifference)
{
    using Container = TypeParam;

    const Container lhs
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

    const Container rhs
    {
        Unsortable::F(),
        Unsortable::B(),
        Unsortable::D(),
    }; 
    ASSERT_TRUE(!rhs.empty());

    const Container expected
    {
        Unsortable::E(),
        Unsortable::C(),
        Unsortable::A(),
        Unsortable::E(),
    };
    ASSERT_TRUE(!expected.empty());

    const Container result = cxstd::ComputeStrictDifference(lhs, rhs);
    ASSERT_TRUE(result == expected);
}

/*************************************************************************************************
 *                                    cxstd::Unique
 ************************************************************************************************/
namespace
{

template<typename T>
class UniqueFixture : public testing::Test {};

using UniqueTypes = ::testing::Types<
    std::deque<Unsortable>,
    std::list<Unsortable>,
    std::vector<Unsortable>
>;

TYPED_TEST_SUITE(UniqueFixture, UniqueTypes);

} // namespace

TYPED_TEST(UniqueFixture, Unique_EmptyCollection_DoesNothing)
{
    using Container = TypeParam;

    Container collection;
    ASSERT_TRUE(collection.empty());

    cxstd::Unique(collection);
    ASSERT_TRUE(collection.empty());
}

TYPED_TEST(UniqueFixture, Unique_CollectionWithNoDuplicates_DoesNothing)
{
    using Container = TypeParam;

    Container collection
    {
        Unsortable::A(),
        Unsortable::B(),
        Unsortable::C(),
    };
    ASSERT_TRUE(!collection.empty());

    const Container expected = collection;

    cxstd::Unique(collection);
    ASSERT_TRUE(collection == expected);
}

TYPED_TEST(UniqueFixture, Unique_CollectionWithSortedDuplicates_DuplicatesRemoved)
{
    using Container = TypeParam;

    Container collection
    {
        Unsortable::A(),
        Unsortable::B(),
        Unsortable::B(),
        Unsortable::C(),
        Unsortable::D(),
        Unsortable::E(),
        Unsortable::E(),
        Unsortable::E(),
    };
    ASSERT_TRUE(!collection.empty());

    const Container expected
    {
        Unsortable::A(),
        Unsortable::B(),
        Unsortable::C(),
        Unsortable::D(),
        Unsortable::E(),
    };

    cxstd::Unique(collection);
    ASSERT_TRUE(collection == expected);
}

TYPED_TEST(UniqueFixture, Unique_CollectionWithUnsortedDuplicates_DuplicatesRemoved)
{
    using Container = TypeParam;

    Container collection
    {
        Unsortable::E(),
        Unsortable::B(),
        Unsortable::D(),
        Unsortable::C(),
        Unsortable::A(),
        Unsortable::E(),
        Unsortable::E(),
        Unsortable::B(),
    };
    ASSERT_TRUE(!collection.empty());

    const Container expected
    {
        Unsortable::E(),
        Unsortable::B(),
        Unsortable::D(),
        Unsortable::C(),
        Unsortable::A(),
    };

    cxstd::Unique(collection);
    ASSERT_TRUE(collection == expected);
}
