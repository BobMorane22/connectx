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
 * @file mathTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cmath>
#include <math.h>

TEST(math, /*DISABLED_*/Pi_Constant_ReturnsConstant)
{
    ASSERT_NEAR(cxmath::pi<long double>, std::acos(-1), 1e-12);
    ASSERT_NEAR(cxmath::pi<double>, std::acos(-1), 1e-9);
    ASSERT_NEAR(cxmath::pi<float>, std::acos(-1), 1e-6);
    ASSERT_EQ(cxmath::pi<int>, 3);
}
