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
 * @file MainWindowControllerTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include "MainWindowControllerTestFixture.h"

TEST_F(MainWindowControllerTestFixture, OnIncrementBtnPressed_PressedOnce_IncrementedByOne)
{
    ASSERT_EQ(GetModel().GetCurrentValue(), 0);

    GetController().OnIncrementBtnPressed();

    ASSERT_EQ(GetModel().GetCurrentValue(), 1);
}

TEST_F(MainWindowControllerTestFixture, OnReinitializeBthPressed_CountIsOne_CountIsZero)
{
    GetController().OnIncrementBtnPressed();

    ASSERT_EQ(GetModel().GetCurrentValue(), 1);

    GetController().OnReinitializeBthPressed();

    ASSERT_EQ(GetModel().GetCurrentValue(), 0);
}
