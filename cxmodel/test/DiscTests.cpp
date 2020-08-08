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
 * @file DiscTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <memory>

#include <gtest/gtest.h>

#include <Disc.h>

TEST(Disc, /*DISABLED_*/Constructor_RedColor_RedColorReturned)
{
    cxmodel::Disc disc{cxmodel::MakeRed()};
    ASSERT_EQ(disc.GetColor(), cxmodel::MakeRed());
}

TEST(Disc, /*DISABLED_*/GetColorAcessor_RedColorInConstructor_RedColorReturned)
{
    cxmodel::Disc disc{cxmodel::MakeRed()};
    ASSERT_EQ(disc.GetColor(), cxmodel::MakeRed());
}

TEST(Disc, /*DISABLED_*/EqualToOperator_TwoSameColor_TrueReturned)
{
    cxmodel::Disc lhs{cxmodel::MakeRed()};
    cxmodel::Disc rhs{cxmodel::MakeRed()};

    ASSERT_TRUE(lhs == rhs);
}

TEST(Disc, /*DISABLED_*/EqualToOperator_TwoDifferentColors_FalseReturned)
{
    cxmodel::Disc lhs{cxmodel::MakeRed()};
    cxmodel::Disc rhs{cxmodel::MakeBlue()};

    ASSERT_FALSE(lhs == rhs);
}

TEST(Disc, /*DISABLED_*/NotEqualToOperator_TwoSameColor_FalseReturned)
{
    cxmodel::Disc lhs{cxmodel::MakeRed()};
    cxmodel::Disc rhs{cxmodel::MakeRed()};

    ASSERT_FALSE(lhs != rhs);
}

TEST(Disc, /*DISABLED_*/NotEqualToOperator_TwoDifferentColors_TrueReturned)
{
    cxmodel::Disc lhs{cxmodel::MakeRed()};
    cxmodel::Disc rhs{cxmodel::MakeBlue()};

    ASSERT_TRUE(lhs != rhs);
}
