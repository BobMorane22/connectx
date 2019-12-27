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
 * @file ModelTests.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <Model.h>

TEST(Model, Constructor_NoOtherAction_CurrentValueIs0)
{
    cxmodel::Model concreteModel;
    cxmodel::IModel& model = concreteModel;

    ASSERT_EQ(model.GetCurrentValue(), 0);
}

TEST(Model, GetCurrentValue_AfterIncrement_CurrentValueIsNot0)
{
    cxmodel::Model concreteModel;
    cxmodel::IModel& model = concreteModel;

    model.Increment();

    ASSERT_NE(model.GetCurrentValue(), 0);
}

TEST(Model, Increment_InitialValueIs0_CurrentValueIs1)
{
    cxmodel::Model concreteModel;
    cxmodel::IModel& model = concreteModel;

    model.Increment();

    ASSERT_EQ(model.GetCurrentValue(), 1);
}

TEST(Model, Reinitialize_InitialValueIs0_CurrentValueIs0)
{
    cxmodel::Model concreteModel;
    cxmodel::IModel& model = concreteModel;

    model.Increment();

    ASSERT_EQ(model.GetCurrentValue(), 1);

    model.Reinitialize();

    ASSERT_EQ(model.GetCurrentValue(), 0);
}
