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
 * @file IAnimatedBoardModel.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <cmath>

#include <cxinv/assertion.h>
#include <cxgui/IAnimatedBoardModel.h>

cxmodel::Column cxgui::ComputeColumnFromPosition(const cxgui::IAnimatedBoardModel& p_model, const cxmath::Position& p_position)
{
    IF_PRECONDITION_NOT_MET_DO(p_position.m_x >= 0.0 && p_position.m_y >= 0.0, return cxmodel::Column{0u};);

    const cxmath::Dimensions& boardDimensions = p_model.GetAnimatedAreaDimensions();
    IF_PRECONDITION_NOT_MET_DO(p_position.m_x <= boardDimensions.m_width.Get(), return cxmodel::Column{0u};);
    IF_PRECONDITION_NOT_MET_DO(p_position.m_y <= boardDimensions.m_height.Get(), return cxmodel::Column{0u};);

    const cxmath::Dimensions& cellDimensions = p_model.GetCellDimensions();    
    const double cellWidth = cellDimensions.m_width.Get();
    const double truncated = std::trunc(p_position.m_x / cellWidth);
    const cxmodel::Column column{static_cast<size_t>(truncated)};

    return column;
}

cxmath::Position cxgui::ComputeChipPositionFromColumn(const cxgui::IAnimatedBoardModel& p_model, const cxmodel::Column& p_column)
{
    const cxmath::Dimensions& cellDimensions = p_model.GetCellDimensions();    
    const double cellWidth = cellDimensions.m_width.Get();

    PRECONDITION((p_column.Get() + 1u) * cellWidth <= p_model.GetAnimatedAreaDimensions().m_width.Get());

    const double targetChipHorizontalPosition = (p_column.Get() * cellWidth) + cellWidth/2.0;
    const double currentChipVerticalPosition = p_model.GetChipPosition().m_y;
    const cxmath::Position positionFromColumn{targetChipHorizontalPosition, currentChipVerticalPosition};

    POSTCONDITION(positionFromColumn.m_x >= 0.0 && positionFromColumn.m_y >= 0.0);
    POSTCONDITION(positionFromColumn.m_x <= p_model.GetAnimatedAreaDimensions().m_width.Get());
    POSTCONDITION(positionFromColumn.m_y <= p_model.GetAnimatedAreaDimensions().m_height.Get());

    return positionFromColumn;
}
