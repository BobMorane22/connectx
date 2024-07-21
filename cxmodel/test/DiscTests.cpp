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

#include <cxmodel/Disc.h>

TEST(Disc, /*DISABLED_*/Constructor_RedColor_RedColorReturned)
{
    cx::model::Disc disc{cx::model::MakeRed()};
    ASSERT_EQ(disc.GetColor(), cx::model::MakeRed());
}

TEST(Disc, /*DISABLED_*/GetColorAcessor_RedColorInConstructor_RedColorReturned)
{
    cx::model::Disc disc{cx::model::MakeRed()};
    ASSERT_EQ(disc.GetColor(), cx::model::MakeRed());
}

TEST(Disc, /*DISABLED_*/EqualToOperator_TwoSameColor_TrueReturned)
{
    cx::model::Disc lhs{cx::model::MakeRed()};
    cx::model::Disc rhs{cx::model::MakeRed()};

    ASSERT_TRUE(lhs == rhs);
}

TEST(Disc, /*DISABLED_*/EqualToOperator_TwoDifferentColors_FalseReturned)
{
    cx::model::Disc lhs{cx::model::MakeRed()};
    cx::model::Disc rhs{cx::model::MakeBlue()};

    ASSERT_FALSE(lhs == rhs);
}

TEST(Disc, /*DISABLED_*/NotEqualToOperator_TwoSameColor_FalseReturned)
{
    cx::model::Disc lhs{cx::model::MakeRed()};
    cx::model::Disc rhs{cx::model::MakeRed()};

    ASSERT_FALSE(lhs != rhs);
}

TEST(Disc, /*DISABLED_*/NotEqualToOperator_TwoDifferentColors_TrueReturned)
{
    cx::model::Disc lhs{cx::model::MakeRed()};
    cx::model::Disc rhs{cx::model::MakeBlue()};

    ASSERT_TRUE(lhs != rhs);
}
