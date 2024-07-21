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
 * @file VerbosityLevelTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxlog/VerbosityLevel.h>

TEST(VerbosityLevel, /*DISABLED_*/LessThanOperator_IsLessThan_ReturnsTrue)
{
    ASSERT_TRUE(cx::log::VerbosityLevel::NONE    < cx::log::VerbosityLevel::FATAL);
    ASSERT_TRUE(cx::log::VerbosityLevel::FATAL   < cx::log::VerbosityLevel::ERROR);
    ASSERT_TRUE(cx::log::VerbosityLevel::ERROR   < cx::log::VerbosityLevel::WARNING);
    ASSERT_TRUE(cx::log::VerbosityLevel::WARNING < cx::log::VerbosityLevel::INFO);
    ASSERT_TRUE(cx::log::VerbosityLevel::INFO    < cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOperator_IsEqualTo_ReturnsFalse)
{
    ASSERT_FALSE(cx::log::VerbosityLevel::NONE    < cx::log::VerbosityLevel::NONE);
    ASSERT_FALSE(cx::log::VerbosityLevel::FATAL   < cx::log::VerbosityLevel::FATAL);
    ASSERT_FALSE(cx::log::VerbosityLevel::ERROR   < cx::log::VerbosityLevel::ERROR);
    ASSERT_FALSE(cx::log::VerbosityLevel::WARNING < cx::log::VerbosityLevel::WARNING);
    ASSERT_FALSE(cx::log::VerbosityLevel::INFO    < cx::log::VerbosityLevel::INFO);
    ASSERT_FALSE(cx::log::VerbosityLevel::DEBUG   < cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOperator_IsGreaterThan_ReturnsFalse)
{
    ASSERT_FALSE(cx::log::VerbosityLevel::DEBUG   < cx::log::VerbosityLevel::INFO);
    ASSERT_FALSE(cx::log::VerbosityLevel::INFO    < cx::log::VerbosityLevel::WARNING);
    ASSERT_FALSE(cx::log::VerbosityLevel::WARNING < cx::log::VerbosityLevel::ERROR);
    ASSERT_FALSE(cx::log::VerbosityLevel::ERROR   < cx::log::VerbosityLevel::FATAL);
    ASSERT_FALSE(cx::log::VerbosityLevel::FATAL   < cx::log::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOrEqualToOperator_IsLessThan_ReturnsTrue)
{
    ASSERT_TRUE(cx::log::VerbosityLevel::NONE    <= cx::log::VerbosityLevel::FATAL);
    ASSERT_TRUE(cx::log::VerbosityLevel::FATAL   <= cx::log::VerbosityLevel::ERROR);
    ASSERT_TRUE(cx::log::VerbosityLevel::ERROR   <= cx::log::VerbosityLevel::WARNING);
    ASSERT_TRUE(cx::log::VerbosityLevel::WARNING <= cx::log::VerbosityLevel::INFO);
    ASSERT_TRUE(cx::log::VerbosityLevel::INFO    <= cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOrEqualToOperator_IsEqualTo_ReturnsTrue)
{
    ASSERT_TRUE(cx::log::VerbosityLevel::NONE    <= cx::log::VerbosityLevel::NONE);
    ASSERT_TRUE(cx::log::VerbosityLevel::FATAL   <= cx::log::VerbosityLevel::FATAL);
    ASSERT_TRUE(cx::log::VerbosityLevel::ERROR   <= cx::log::VerbosityLevel::ERROR);
    ASSERT_TRUE(cx::log::VerbosityLevel::WARNING <= cx::log::VerbosityLevel::WARNING);
    ASSERT_TRUE(cx::log::VerbosityLevel::INFO    <= cx::log::VerbosityLevel::INFO);
    ASSERT_TRUE(cx::log::VerbosityLevel::DEBUG   <= cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOrEqualToOperator_IsGreater_ReturnsFalse)
{
    ASSERT_FALSE(cx::log::VerbosityLevel::DEBUG   <= cx::log::VerbosityLevel::INFO);
    ASSERT_FALSE(cx::log::VerbosityLevel::INFO    <= cx::log::VerbosityLevel::WARNING);
    ASSERT_FALSE(cx::log::VerbosityLevel::WARNING <= cx::log::VerbosityLevel::ERROR);
    ASSERT_FALSE(cx::log::VerbosityLevel::ERROR   <= cx::log::VerbosityLevel::FATAL);
    ASSERT_FALSE(cx::log::VerbosityLevel::FATAL   <= cx::log::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOperator_IsGreaterThan_ReturnsTrue)
{
    ASSERT_TRUE(cx::log::VerbosityLevel::DEBUG   > cx::log::VerbosityLevel::INFO);
    ASSERT_TRUE(cx::log::VerbosityLevel::INFO    > cx::log::VerbosityLevel::WARNING);
    ASSERT_TRUE(cx::log::VerbosityLevel::WARNING > cx::log::VerbosityLevel::ERROR);
    ASSERT_TRUE(cx::log::VerbosityLevel::ERROR   > cx::log::VerbosityLevel::FATAL);
    ASSERT_TRUE(cx::log::VerbosityLevel::FATAL   > cx::log::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOperator_IsEqualTo_ReturnsFalse)
{
    ASSERT_FALSE(cx::log::VerbosityLevel::NONE    > cx::log::VerbosityLevel::NONE);
    ASSERT_FALSE(cx::log::VerbosityLevel::FATAL   > cx::log::VerbosityLevel::FATAL);
    ASSERT_FALSE(cx::log::VerbosityLevel::ERROR   > cx::log::VerbosityLevel::ERROR);
    ASSERT_FALSE(cx::log::VerbosityLevel::WARNING > cx::log::VerbosityLevel::WARNING);
    ASSERT_FALSE(cx::log::VerbosityLevel::INFO    > cx::log::VerbosityLevel::INFO);
    ASSERT_FALSE(cx::log::VerbosityLevel::DEBUG   > cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOperator_IsLessThan_ReturnsFalse)
{
    ASSERT_FALSE(cx::log::VerbosityLevel::NONE    > cx::log::VerbosityLevel::FATAL);
    ASSERT_FALSE(cx::log::VerbosityLevel::FATAL   > cx::log::VerbosityLevel::ERROR);
    ASSERT_FALSE(cx::log::VerbosityLevel::ERROR   > cx::log::VerbosityLevel::WARNING);
    ASSERT_FALSE(cx::log::VerbosityLevel::WARNING > cx::log::VerbosityLevel::INFO);
    ASSERT_FALSE(cx::log::VerbosityLevel::INFO    > cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOrEqualToOperator_IsGreaterThan_ReturnsTrue)
{
    ASSERT_TRUE(cx::log::VerbosityLevel::DEBUG   >= cx::log::VerbosityLevel::INFO);
    ASSERT_TRUE(cx::log::VerbosityLevel::INFO    >= cx::log::VerbosityLevel::WARNING);
    ASSERT_TRUE(cx::log::VerbosityLevel::WARNING >= cx::log::VerbosityLevel::ERROR);
    ASSERT_TRUE(cx::log::VerbosityLevel::ERROR   >= cx::log::VerbosityLevel::FATAL);
    ASSERT_TRUE(cx::log::VerbosityLevel::FATAL   >= cx::log::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOrEqualToOperator_IsEqualTo_ReturnsTrue)
{
    ASSERT_TRUE(cx::log::VerbosityLevel::NONE    >= cx::log::VerbosityLevel::NONE);
    ASSERT_TRUE(cx::log::VerbosityLevel::FATAL   >= cx::log::VerbosityLevel::FATAL);
    ASSERT_TRUE(cx::log::VerbosityLevel::ERROR   >= cx::log::VerbosityLevel::ERROR);
    ASSERT_TRUE(cx::log::VerbosityLevel::WARNING >= cx::log::VerbosityLevel::WARNING);
    ASSERT_TRUE(cx::log::VerbosityLevel::INFO    >= cx::log::VerbosityLevel::INFO);
    ASSERT_TRUE(cx::log::VerbosityLevel::DEBUG   >= cx::log::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOrEqualToOperator_IsLessThan_ReturnsFalse)
{
    ASSERT_FALSE(cx::log::VerbosityLevel::NONE    >= cx::log::VerbosityLevel::FATAL);
    ASSERT_FALSE(cx::log::VerbosityLevel::FATAL   >= cx::log::VerbosityLevel::ERROR);
    ASSERT_FALSE(cx::log::VerbosityLevel::ERROR   >= cx::log::VerbosityLevel::WARNING);
    ASSERT_FALSE(cx::log::VerbosityLevel::WARNING >= cx::log::VerbosityLevel::INFO);
    ASSERT_FALSE(cx::log::VerbosityLevel::INFO    >= cx::log::VerbosityLevel::DEBUG);
}

