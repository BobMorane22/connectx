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
 * @file ChipColorTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxmodel/ChipColor.h>

TEST(ChipColor, /*DISABLED_*/MakeFromHSLA_RedFromHSLA_RedReturned)
{
    using namespace cx::model;

    const cx::model::ChipColor expectedRed{65535u, 0u, 0u};
    const cx::model::ChipColor result = cx::model::MakeFromHSLA(0.0, 1.0, 0.5, 1.0);

    ASSERT_EQ(expectedRed, result);
}

TEST(ChipColor, /*DISABLED_*/ComputeHSL_RGBRedColor_HSLComputed)
{
    const cx::model::ChipColor red{65535u, 0u, 0u};

    const double hue = cx::model::ComputeHue(red);
    ASSERT_EQ(0.0, hue);

    const double saturation = cx::model::ComputeSaturation(red);
    ASSERT_EQ(1.0, saturation);

    const double luminosity = cx::model::ComputeLuminosity(red);
    ASSERT_EQ(0.5, luminosity);
}

TEST(ChipColor, /*DISABLED_*/ComputeHSL_RGBRandomColor_HSLComputed)
{
    constexpr unsigned short MAX = std::numeric_limits<unsigned short>::max();
    constexpr unsigned short HALF = (MAX >> 1);
    constexpr unsigned short QUARTER = (HALF >> 1);

    const cx::model::ChipColor random{HALF, QUARTER, HALF};

    const double hue = cx::model::ComputeHue(random);
    ASSERT_NEAR(0.833333, hue, 1e-6);

    const double saturation = cx::model::ComputeSaturation(random);
    ASSERT_NEAR(0.333347, saturation, 1e-6);

    const double luminosity = cx::model::ComputeLuminosity(random);
    ASSERT_NEAR(0.374990, luminosity, 1e-6);
}

TEST(ChipColor, /*DISABLED*/ColorFactories_RunTime_ColorsReturned)
{
    ASSERT_TRUE(cx::model::MakeTransparent() == cx::model::ChipColor(0u, 0u, 0u, 0u));
    ASSERT_TRUE(cx::model::MakeRed() == cx::model::ChipColor(63222u, 6425u, 13878u));
    ASSERT_TRUE(cx::model::MakeBlue() == cx::model::ChipColor(7453u, 34695u, 65535u));
    ASSERT_TRUE(cx::model::MakeYellow() == cx::model::ChipColor(64764u, 54507u, 9252u));
    ASSERT_TRUE(cx::model::MakeGreen() == cx::model::ChipColor(1028u, 56797u, 5911u));
    ASSERT_TRUE(cx::model::MakePink() == cx::model::ChipColor(62194u, 29041u, 62194u));
    ASSERT_TRUE(cx::model::MakeOrange() == cx::model::ChipColor(64764u, 29041u, 3855u));
    ASSERT_TRUE(cx::model::MakeAqua() == cx::model::ChipColor(16191u, 61166u, 58339u));
    ASSERT_TRUE(cx::model::MakeBlack() == cx::model::ChipColor(10280u, 7967u, 8481u));
    ASSERT_TRUE(cx::model::MakeLilac() == cx::model::ChipColor(31611u, 15163u, 65535u));
    ASSERT_TRUE(cx::model::MakeSalmon() == cx::model::ChipColor(65535u, 41377u, 33410u));
}

TEST(ChipColor, /*DISABLED*/ColorFactories_CompileTime_ColorsReturned)
{
    static_assert(cx::model::MakeTransparent() == cx::model::ChipColor{0u, 0u, 0u, 0u});
    static_assert(cx::model::MakeRed() == cx::model::ChipColor{63222u, 6425u, 13878u});
    static_assert(cx::model::MakeBlue() == cx::model::ChipColor{7453u, 34695u, 65535u});
    static_assert(cx::model::MakeYellow() == cx::model::ChipColor{64764u, 54507u, 9252u});
    static_assert(cx::model::MakeGreen() == cx::model::ChipColor{1028u, 56797u, 5911u});
    static_assert(cx::model::MakePink() == cx::model::ChipColor{62194u, 29041u, 62194u});
    static_assert(cx::model::MakeOrange() == cx::model::ChipColor{64764u, 29041u, 3855u});
    static_assert(cx::model::MakeAqua() == cx::model::ChipColor{16191u, 61166u, 58339u});
    static_assert(cx::model::MakeBlack() == cx::model::ChipColor{10280u, 7967u, 8481u});
    static_assert(cx::model::MakeLilac() == cx::model::ChipColor{31611u, 15163u, 65535u});
    static_assert(cx::model::MakeSalmon() == cx::model::ChipColor{65535u, 41377u, 33410u});
}
