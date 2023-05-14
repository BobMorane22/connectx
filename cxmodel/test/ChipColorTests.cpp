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
    using namespace cxmodel;

    const cxmodel::ChipColor expectedRed{65535u, 0u, 0u};
    const cxmodel::ChipColor result = cxmodel::MakeFromHSLA(0.0, 1.0, 0.5, 1.0);

    ASSERT_EQ(expectedRed, result);
}

TEST(ChipColor, /*DISABLED_*/ComputeHSL_RGBRedColor_HSLComputed)
{
    const cxmodel::ChipColor red{65535u, 0u, 0u};

    const double hue = cxmodel::ComputeHue(red);
    ASSERT_EQ(0.0, hue);

    const double saturation = cxmodel::ComputeSaturation(red);
    ASSERT_EQ(1.0, saturation);

    const double luminosity = cxmodel::ComputeLuminosity(red);
    ASSERT_EQ(0.5, luminosity);
}

TEST(ChipColor, /*DISABLED_*/ComputeHSL_RGBRandomColor_HSLComputed)
{
    constexpr unsigned short MAX = std::numeric_limits<unsigned short>::max();
    constexpr unsigned short HALF = (MAX >> 1);
    constexpr unsigned short QUARTER = (HALF >> 1);

    const cxmodel::ChipColor random{HALF, QUARTER, HALF};

    const double hue = cxmodel::ComputeHue(random);
    ASSERT_NEAR(0.833333, hue, 1e-6);

    const double saturation = cxmodel::ComputeSaturation(random);
    ASSERT_NEAR(0.333347, saturation, 1e-6);

    const double luminosity = cxmodel::ComputeLuminosity(random);
    ASSERT_NEAR(0.374990, luminosity, 1e-6);
}

TEST(ChipColor, /*DISABLED*/ColorFactories_RunTime_ColorsReturned)
{
    ASSERT_TRUE(cxmodel::MakeTransparent() == cxmodel::ChipColor(0u, 0u, 0u, 0u));
    ASSERT_TRUE(cxmodel::MakeRed() == cxmodel::ChipColor(63222u, 6425u, 13878u));
    ASSERT_TRUE(cxmodel::MakeBlue() == cxmodel::ChipColor(7453u, 34695u, 65535u));
    ASSERT_TRUE(cxmodel::MakeYellow() == cxmodel::ChipColor(64764u, 54507u, 9252u));
    ASSERT_TRUE(cxmodel::MakeGreen() == cxmodel::ChipColor(1028u, 56797u, 5911u));
    ASSERT_TRUE(cxmodel::MakePink() == cxmodel::ChipColor(62194u, 29041u, 62194u));
    ASSERT_TRUE(cxmodel::MakeOrange() == cxmodel::ChipColor(64764u, 29041u, 3855u));
    ASSERT_TRUE(cxmodel::MakeAqua() == cxmodel::ChipColor(16191u, 61166u, 58339u));
    ASSERT_TRUE(cxmodel::MakeBlack() == cxmodel::ChipColor(10280u, 7967u, 8481u));
    ASSERT_TRUE(cxmodel::MakeLilac() == cxmodel::ChipColor(31611u, 15163u, 65535u));
    ASSERT_TRUE(cxmodel::MakeSalmon() == cxmodel::ChipColor(65535u, 41377u, 33410u));
}

TEST(ChipColor, /*DISABLED*/ColorFactories_CompileTime_ColorsReturned)
{
    static_assert(cxmodel::MakeTransparent() == cxmodel::ChipColor{0u, 0u, 0u, 0u});
    static_assert(cxmodel::MakeRed() == cxmodel::ChipColor{63222u, 6425u, 13878u});
    static_assert(cxmodel::MakeBlue() == cxmodel::ChipColor{7453u, 34695u, 65535u});
    static_assert(cxmodel::MakeYellow() == cxmodel::ChipColor{64764u, 54507u, 9252u});
    static_assert(cxmodel::MakeGreen() == cxmodel::ChipColor{1028u, 56797u, 5911u});
    static_assert(cxmodel::MakePink() == cxmodel::ChipColor{62194u, 29041u, 62194u});
    static_assert(cxmodel::MakeOrange() == cxmodel::ChipColor{64764u, 29041u, 3855u});
    static_assert(cxmodel::MakeAqua() == cxmodel::ChipColor{16191u, 61166u, 58339u});
    static_assert(cxmodel::MakeBlack() == cxmodel::ChipColor{10280u, 7967u, 8481u});
    static_assert(cxmodel::MakeLilac() == cxmodel::ChipColor{31611u, 15163u, 65535u});
    static_assert(cxmodel::MakeSalmon() == cxmodel::ChipColor{65535u, 41377u, 33410u});
}
