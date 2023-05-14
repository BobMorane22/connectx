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
