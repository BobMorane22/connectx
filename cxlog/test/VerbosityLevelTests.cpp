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

#include <VerbosityLevel.h>

TEST(VerbosityLevel, /*DISABLED_*/LessThanOperator_IsLessThan_ReturnsTrue)
{
    ASSERT_TRUE(cxlog::VerbosityLevel::NONE    < cxlog::VerbosityLevel::FATAL);
    ASSERT_TRUE(cxlog::VerbosityLevel::FATAL   < cxlog::VerbosityLevel::ERROR);
    ASSERT_TRUE(cxlog::VerbosityLevel::ERROR   < cxlog::VerbosityLevel::WARNING);
    ASSERT_TRUE(cxlog::VerbosityLevel::WARNING < cxlog::VerbosityLevel::INFO);
    ASSERT_TRUE(cxlog::VerbosityLevel::INFO    < cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOperator_IsEqualTo_ReturnsFalse)
{
    ASSERT_FALSE(cxlog::VerbosityLevel::NONE    < cxlog::VerbosityLevel::NONE);
    ASSERT_FALSE(cxlog::VerbosityLevel::FATAL   < cxlog::VerbosityLevel::FATAL);
    ASSERT_FALSE(cxlog::VerbosityLevel::ERROR   < cxlog::VerbosityLevel::ERROR);
    ASSERT_FALSE(cxlog::VerbosityLevel::WARNING < cxlog::VerbosityLevel::WARNING);
    ASSERT_FALSE(cxlog::VerbosityLevel::INFO    < cxlog::VerbosityLevel::INFO);
    ASSERT_FALSE(cxlog::VerbosityLevel::DEBUG   < cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOperator_IsGreaterThan_ReturnsFalse)
{
    ASSERT_FALSE(cxlog::VerbosityLevel::DEBUG   < cxlog::VerbosityLevel::INFO);
    ASSERT_FALSE(cxlog::VerbosityLevel::INFO    < cxlog::VerbosityLevel::WARNING);
    ASSERT_FALSE(cxlog::VerbosityLevel::WARNING < cxlog::VerbosityLevel::ERROR);
    ASSERT_FALSE(cxlog::VerbosityLevel::ERROR   < cxlog::VerbosityLevel::FATAL);
    ASSERT_FALSE(cxlog::VerbosityLevel::FATAL   < cxlog::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOrEqualToOperator_IsLessThan_ReturnsTrue)
{
    ASSERT_TRUE(cxlog::VerbosityLevel::NONE    <= cxlog::VerbosityLevel::FATAL);
    ASSERT_TRUE(cxlog::VerbosityLevel::FATAL   <= cxlog::VerbosityLevel::ERROR);
    ASSERT_TRUE(cxlog::VerbosityLevel::ERROR   <= cxlog::VerbosityLevel::WARNING);
    ASSERT_TRUE(cxlog::VerbosityLevel::WARNING <= cxlog::VerbosityLevel::INFO);
    ASSERT_TRUE(cxlog::VerbosityLevel::INFO    <= cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOrEqualToOperator_IsEqualTo_ReturnsTrue)
{
    ASSERT_TRUE(cxlog::VerbosityLevel::NONE    <= cxlog::VerbosityLevel::NONE);
    ASSERT_TRUE(cxlog::VerbosityLevel::FATAL   <= cxlog::VerbosityLevel::FATAL);
    ASSERT_TRUE(cxlog::VerbosityLevel::ERROR   <= cxlog::VerbosityLevel::ERROR);
    ASSERT_TRUE(cxlog::VerbosityLevel::WARNING <= cxlog::VerbosityLevel::WARNING);
    ASSERT_TRUE(cxlog::VerbosityLevel::INFO    <= cxlog::VerbosityLevel::INFO);
    ASSERT_TRUE(cxlog::VerbosityLevel::DEBUG   <= cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/LessThanOrEqualToOperator_IsGreater_ReturnsFalse)
{
    ASSERT_FALSE(cxlog::VerbosityLevel::DEBUG   <= cxlog::VerbosityLevel::INFO);
    ASSERT_FALSE(cxlog::VerbosityLevel::INFO    <= cxlog::VerbosityLevel::WARNING);
    ASSERT_FALSE(cxlog::VerbosityLevel::WARNING <= cxlog::VerbosityLevel::ERROR);
    ASSERT_FALSE(cxlog::VerbosityLevel::ERROR   <= cxlog::VerbosityLevel::FATAL);
    ASSERT_FALSE(cxlog::VerbosityLevel::FATAL   <= cxlog::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOperator_IsGreaterThan_ReturnsTrue)
{
    ASSERT_TRUE(cxlog::VerbosityLevel::DEBUG   > cxlog::VerbosityLevel::INFO);
    ASSERT_TRUE(cxlog::VerbosityLevel::INFO    > cxlog::VerbosityLevel::WARNING);
    ASSERT_TRUE(cxlog::VerbosityLevel::WARNING > cxlog::VerbosityLevel::ERROR);
    ASSERT_TRUE(cxlog::VerbosityLevel::ERROR   > cxlog::VerbosityLevel::FATAL);
    ASSERT_TRUE(cxlog::VerbosityLevel::FATAL   > cxlog::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOperator_IsEqualTo_ReturnsFalse)
{
    ASSERT_FALSE(cxlog::VerbosityLevel::NONE    > cxlog::VerbosityLevel::NONE);
    ASSERT_FALSE(cxlog::VerbosityLevel::FATAL   > cxlog::VerbosityLevel::FATAL);
    ASSERT_FALSE(cxlog::VerbosityLevel::ERROR   > cxlog::VerbosityLevel::ERROR);
    ASSERT_FALSE(cxlog::VerbosityLevel::WARNING > cxlog::VerbosityLevel::WARNING);
    ASSERT_FALSE(cxlog::VerbosityLevel::INFO    > cxlog::VerbosityLevel::INFO);
    ASSERT_FALSE(cxlog::VerbosityLevel::DEBUG   > cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOperator_IsLessThan_ReturnsFalse)
{
    ASSERT_FALSE(cxlog::VerbosityLevel::NONE    > cxlog::VerbosityLevel::FATAL);
    ASSERT_FALSE(cxlog::VerbosityLevel::FATAL   > cxlog::VerbosityLevel::ERROR);
    ASSERT_FALSE(cxlog::VerbosityLevel::ERROR   > cxlog::VerbosityLevel::WARNING);
    ASSERT_FALSE(cxlog::VerbosityLevel::WARNING > cxlog::VerbosityLevel::INFO);
    ASSERT_FALSE(cxlog::VerbosityLevel::INFO    > cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOrEqualToOperator_IsGreaterThan_ReturnsTrue)
{
    ASSERT_TRUE(cxlog::VerbosityLevel::DEBUG   >= cxlog::VerbosityLevel::INFO);
    ASSERT_TRUE(cxlog::VerbosityLevel::INFO    >= cxlog::VerbosityLevel::WARNING);
    ASSERT_TRUE(cxlog::VerbosityLevel::WARNING >= cxlog::VerbosityLevel::ERROR);
    ASSERT_TRUE(cxlog::VerbosityLevel::ERROR   >= cxlog::VerbosityLevel::FATAL);
    ASSERT_TRUE(cxlog::VerbosityLevel::FATAL   >= cxlog::VerbosityLevel::NONE);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOrEqualToOperator_IsEqualTo_ReturnsTrue)
{
    ASSERT_TRUE(cxlog::VerbosityLevel::NONE    >= cxlog::VerbosityLevel::NONE);
    ASSERT_TRUE(cxlog::VerbosityLevel::FATAL   >= cxlog::VerbosityLevel::FATAL);
    ASSERT_TRUE(cxlog::VerbosityLevel::ERROR   >= cxlog::VerbosityLevel::ERROR);
    ASSERT_TRUE(cxlog::VerbosityLevel::WARNING >= cxlog::VerbosityLevel::WARNING);
    ASSERT_TRUE(cxlog::VerbosityLevel::INFO    >= cxlog::VerbosityLevel::INFO);
    ASSERT_TRUE(cxlog::VerbosityLevel::DEBUG   >= cxlog::VerbosityLevel::DEBUG);
}

TEST(VerbosityLevel, /*DISABLED_*/GreaterThanOrEqualToOperator_IsLessThan_ReturnsFalse)
{
    ASSERT_FALSE(cxlog::VerbosityLevel::NONE    >= cxlog::VerbosityLevel::FATAL);
    ASSERT_FALSE(cxlog::VerbosityLevel::FATAL   >= cxlog::VerbosityLevel::ERROR);
    ASSERT_FALSE(cxlog::VerbosityLevel::ERROR   >= cxlog::VerbosityLevel::WARNING);
    ASSERT_FALSE(cxlog::VerbosityLevel::WARNING >= cxlog::VerbosityLevel::INFO);
    ASSERT_FALSE(cxlog::VerbosityLevel::INFO    >= cxlog::VerbosityLevel::DEBUG);
}

