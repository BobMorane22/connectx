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
 * @file IAnimatedBoardModelTests.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxgui/IAnimatedBoardModel.h>

#include "AnimatedBoardModelMock.h"

namespace
{

AnimatedBoardModelMock CreateMock()
{
    AnimatedBoardModelMock model;
    model.SetAnimatedAreaDimensions({cxmath::Height{70.0}, cxmath::Width{70.0}});
    model.SetCellDimensions({cxmath::Height{10.0}, cxmath::Width{10.0}});

    return model;
}

} // namespace

TEST(IAnimatedBoardModel, /*DISABLED_*/ComputeColumnFromPosition_ValidPositionOnColumn_ReturnsColumn)
{
    const AnimatedBoardModelMock model = CreateMock();

    //                    |   |   |   |   |   |   |   |
    //                    |   |   |   |   |   |   |   |
    //    Position (x) :  00  10  20  30  40  50  60  70
    //    Column       :    0   1   2   3   4   5   6

    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {1.0, 0.0}) == cxmodel::Column{0u});
    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {12.0, 10.0}) == cxmodel::Column{1u});
    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {23.0, 20.0}) == cxmodel::Column{2u});
    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {34.0, 30.0}) == cxmodel::Column{3u});
    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {45.0, 40.0}) == cxmodel::Column{4u});
    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {56.0, 50.0}) == cxmodel::Column{5u});
    ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {67.0, 60.0}) == cxmodel::Column{6u});
}

TEST(IAnimatedBoardModel, /*DISABLED_*/ComputeColumnFromPosition_InvalidPositions_ReturnsColumn0)
{
    const AnimatedBoardModelMock model = CreateMock();

    // x-coordinate below 0:
    {
        cxunit::DisableStdStreamsRAII redirector;
        ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {-1.0, 1.0})  == cxmodel::Column{0u});
        ASSERT_PRECONDITION_FAILED(redirector);
    }

    // y-coordinate below 0:
    {
        cxunit::DisableStdStreamsRAII redirector;
        ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {1.0, -1.0})  == cxmodel::Column{0u});
        ASSERT_PRECONDITION_FAILED(redirector);
    }

    // x-coordinate outside board:
    {
        cxunit::DisableStdStreamsRAII redirector;
        ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {71.0, 1.0})  == cxmodel::Column{0u});
        ASSERT_PRECONDITION_FAILED(redirector);
    }

    // y-coordinate outside board:
    {
        cxunit::DisableStdStreamsRAII redirector;
        ASSERT_TRUE(cxgui::ComputeColumnFromPosition(model, {1.0, 71.0})  == cxmodel::Column{0u});
        ASSERT_PRECONDITION_FAILED(redirector);
    }
}

TEST(IAnimatedBoardModel, /*DISABLED_*/ComputeChipPositionFromColumn_ValidColumn_PositionReturned)
{
    const AnimatedBoardModelMock model = CreateMock();

    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{0u}) == cxmath::Position(5.0, 0.0));
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{1u}) == cxmath::Position(15.0, 0.0));
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{2u}) == cxmath::Position(25.0, 0.0));
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{3u}) == cxmath::Position(35.0, 0.0));
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{4u}) == cxmath::Position(45.0, 0.0));
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{5u}) == cxmath::Position(55.0, 0.0));
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{6u}) == cxmath::Position(65.0, 0.0));
}

TEST(IAnimatedBoardModel, /*DISABLED_*/ComputeChipPositionFromColumn_ColumnOutsideBoard_PositionReturnedAndPreconditionFails)
{
    const AnimatedBoardModelMock model = CreateMock();

    cxunit::DisableStdStreamsRAII redirector;
    ASSERT_TRUE(cxgui::ComputeChipPositionFromColumn(model, cxmodel::Column{7u}) == cxmath::Position(75.0, 0.0));
    ASSERT_PRECONDITION_FAILED(redirector);
    ASSERT_POSTCONDITION_FAILED(redirector);
}
