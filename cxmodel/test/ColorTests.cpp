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
 * @file ColorTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <Color.h>

namespace
{

template<typename T>
constexpr bool IsColorCompileTimeUsable()
{
    using namespace cxmodel;

    constexpr Color<T> color = Color<T>::MakePredefined(Color<T>::Predefined::AQUA);

    // Unused (compile time check only).
    (void)color;

    return true;
}

static_assert(IsColorCompileTimeUsable< unsigned char >(), "Color can be compile-time evaluated if possible.");
static_assert(IsColorCompileTimeUsable< unsigned short >(), "Color can be compile-time evaluated if possible.");
static_assert(IsColorCompileTimeUsable< unsigned int >(), "Color can be compile-time evaluated if possible.");
static_assert(IsColorCompileTimeUsable< unsigned long int >(), "Color can be compile-time evaluated if possible.");
static_assert(IsColorCompileTimeUsable< unsigned long long int >(), "Color can be compile-time evaluated if possible.");

} // namespace

template<typename T>
class ColorTypedTestFixture : public ::testing::Test
{

public:

    constexpr static cxmodel::Color<T> MakePredefined(typename cxmodel::Color<T>::Predefined p_color )
    {
        return cxmodel::Color<T>::MakePredefined(p_color);
    }

};

using TypesUnderTest = ::testing::Types<unsigned char,
                                        unsigned short,
                                        unsigned int,
                                        unsigned long int,
                                        unsigned long long int>;

TYPED_TEST_CASE(ColorTypedTestFixture, TypesUnderTest);

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/R_ColorRed_MaxReturned)
{
    using namespace cxmodel;

    const Color<TypeParam> color = ColorTypedTestFixture<TypeParam>::MakePredefined(Color< TypeParam >::Predefined::RED);

    ASSERT_EQ(color.R(), std::numeric_limits<TypeParam>::max());
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/G_ColorRed_ZeroReturned)
{
    using namespace cxmodel;

    const Color<TypeParam> color = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::RED);

    ASSERT_EQ(color.G(), 0u);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/B_ColorRed_ZeroReturned)
{
    using namespace cxmodel;

    const Color<TypeParam> color = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::RED);

    ASSERT_EQ(color.B(), 0u);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/A_ColorRed_MaxReturned)
{
    using namespace cxmodel;

    const Color<TypeParam> color = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::RED);

    ASSERT_EQ(color.A(), std::numeric_limits<TypeParam>::max());
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/MakePredefined_AllPredefined_CorrectoColorMade)
{
    using namespace cxmodel;

    const TypeParam MAX = std::numeric_limits<TypeParam>::max();
    const TypeParam MID = (MAX >> 1);

    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::AQUA),    Color<TypeParam>(0, MAX, MAX, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLACK),   Color<TypeParam>(0, 0, 0, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE),    Color<TypeParam>(0, 0, MAX, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::FUSCHIA), Color<TypeParam>(MAX, 0, MAX, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::GRAY),    Color<TypeParam>(MID, MID, MID, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::GREEN),   Color<TypeParam>(0u, MAX, 0u, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::LIME),    Color<TypeParam>(0, MID, 0, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::MAROON),  Color<TypeParam>(MID, 0u, 0u, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::NAVY),    Color<TypeParam>(0u, 0u, MID, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::OLIVE),   Color<TypeParam>(MID, MID, 0u, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::PURPLE),  Color<TypeParam>(MID, 0u, MID, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::RED),     Color<TypeParam>(MAX, 0, 0, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::TEAL),    Color<TypeParam>(0u, MID, MID, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::WHITE),   Color<TypeParam>(MAX, MAX, MAX, MAX));
    ASSERT_EQ(ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::YELLOW),  Color<TypeParam>(MAX, MAX, 0, MAX));
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/EqualityOperator_TwoSameColors_ReturnsTrue)
{
    using namespace cxmodel;

    const Color<TypeParam> lhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);
    const Color<TypeParam> rhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);

    ASSERT_TRUE(lhs == rhs);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/EqualityOperator_TwoDifferentColors_ReturnsTrue)
{
    using namespace cxmodel;

    const Color<TypeParam> lhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);
    const Color<TypeParam> rhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::WHITE);

    ASSERT_FALSE(lhs == rhs);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NonEqualityOperator_TwoSameColors_ReturnsFalse)
{
    using namespace cxmodel;

    const Color<TypeParam> lhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);
    const Color<TypeParam> rhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);

    ASSERT_FALSE(lhs != rhs);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NonEqualityOperator_TwoDifferentColors_ReturnsTrue)
{
    using namespace cxmodel;

    const Color<TypeParam> lhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);
    const Color<TypeParam> rhs = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::WHITE);

    ASSERT_TRUE(lhs != rhs);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedR_NoRed_ReturnsZero)
{
    using namespace cxmodel;

    const Color<TypeParam> noRed = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLACK);
    const double normalizedRed = NormalizedR(noRed);

    ASSERT_EQ(0.0, normalizedRed);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedR_FullRed_ReturnsOne)
{
    using namespace cxmodel;

    const Color<TypeParam> fullRed = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::RED);
    const double normalizedRed = NormalizedR(fullRed);

    ASSERT_EQ(1.0, normalizedRed);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedR_HalfRed_ReturnsOneHalf)
{
    using namespace cxmodel;

    const TypeParam MAX = std::numeric_limits<TypeParam>::max();
    const TypeParam MID = (MAX >> 1);

    const Color<TypeParam> halfRed = Color<TypeParam>(MID, 0, 0, 0);
    const double normalizedRed = NormalizedR(halfRed);

    ASSERT_NEAR(0.5, normalizedRed, 1e-2);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedG_NoGreen_ReturnsZero)
{
    using namespace cxmodel;

    const Color<TypeParam> noGreen = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLACK);
    const double normalizedGreen = NormalizedG(noGreen);

    ASSERT_EQ(0.0, normalizedGreen);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedG_FullGreen_ReturnsOne)
{
    using namespace cxmodel;

    const Color<TypeParam> fullGreen = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::GREEN);
    const double normalizedGreen = NormalizedG(fullGreen);

    ASSERT_EQ(1.0, normalizedGreen);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedG_HalfGreen_ReturnsOneHalf)
{
    using namespace cxmodel;

    const TypeParam MAX = std::numeric_limits<TypeParam>::max();
    const TypeParam MID = (MAX >> 1);

    const Color<TypeParam> halfGreen = Color<TypeParam>(0, MID, 0, 0);
    const double normalizedGreen = NormalizedG(halfGreen);

    ASSERT_NEAR(0.5, normalizedGreen, 1e-2);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedB_NoBlue_ReturnsZero)
{
    using namespace cxmodel;

    const Color<TypeParam> noBlue = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLACK);
    const double normalizedBlue = NormalizedB(noBlue);

    ASSERT_EQ(0.0, normalizedBlue);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedB_FullBlue_ReturnsOne)
{
    using namespace cxmodel;

    const Color<TypeParam> fullBlue = ColorTypedTestFixture<TypeParam>::MakePredefined(Color<TypeParam>::Predefined::BLUE);
    const double normalizedBlue = NormalizedB(fullBlue);

    ASSERT_EQ(1.0, normalizedBlue);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedB_HalfBlue_ReturnsOneHalf)
{
    using namespace cxmodel;

    const TypeParam MAX = std::numeric_limits<TypeParam>::max();
    const TypeParam MID = (MAX >> 1);

    const Color<TypeParam> halfBlue = Color<TypeParam>(0, 0, MID, 0);
    const double normalizedBlue = NormalizedB(halfBlue);

    ASSERT_NEAR(0.5, normalizedBlue, 1e-2);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedA_NoAlpha_ReturnsZero)
{
    using namespace cxmodel;

    const Color<TypeParam> noAlpha = Color<TypeParam>(0, 0, 0, 0);
    const double normalizedAlpha = NormalizedA(noAlpha);

    ASSERT_EQ(0.0, normalizedAlpha);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedA_FullAlpha_ReturnsOne)
{
    using namespace cxmodel;

    const TypeParam MAX = std::numeric_limits<TypeParam>::max();
    const Color<TypeParam> fullAlpha = Color<TypeParam>(0, 0, 0, MAX);
    const double normalizedAlpha = NormalizedA(fullAlpha);

    ASSERT_EQ(1.0, normalizedAlpha);
}

TYPED_TEST(ColorTypedTestFixture, /*DISABLED_*/NormalizedA_HalfAlpha_ReturnsOneHalf)
{
    using namespace cxmodel;

    const TypeParam MAX = std::numeric_limits<TypeParam>::max();
    const TypeParam MID = (MAX >> 1);

    const Color<TypeParam> halfAlpha = Color<TypeParam>(0, 0, 0, MID);
    const double normalizedAlpha = NormalizedA(halfAlpha);

    ASSERT_NEAR(0.5, normalizedAlpha, 1e-2);
}
