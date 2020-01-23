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

#include <cxgui/test/ModelMockController.h>
#include "MainWindowControllerTestFixture.h"

TEST_F(MainWindowControllerTestFixture, OnIncrementBtnPressed_PressedOnce_IncrementCalledOnModel)
{
    GetController().OnIncrementBtnPressed();

    ModelMockController& model = static_cast<ModelMockController&>(GetModel());

    ASSERT_TRUE(model.GetIncremented());
}

TEST_F(MainWindowControllerTestFixture, OnReinitializeBtnPressed_PressedOnce_ReinitializeCalledOnModel)
{
    GetController().OnReinitializeBtnPressed();

    ModelMockController& model = static_cast<ModelMockController&>(GetModel());

    ASSERT_TRUE(model.GetReinitialized());
}

TEST_F(MainWindowControllerTestFixture, OnUndoBtnPressed_PressedOnce_UndoCalledOnModel)
{
    GetController().OnUndoBtnPressed();

    ModelMockController& model = static_cast<ModelMockController&>(GetModel());

    ASSERT_TRUE(model.GetUndoed());
}

TEST_F(MainWindowControllerTestFixture, OnRedoBtnPressed_PressedOnce_UndoCalledOnModel)
{
    GetController().OnRedoBtnPressed();

    ModelMockController& model = static_cast<ModelMockController&>(GetModel());

    ASSERT_TRUE(model.GetRedoed());
}
