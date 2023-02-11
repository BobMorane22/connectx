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
 * @file AnimatedBoardModelMock.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include "AnimatedBoardModelMock.h"

void AnimatedBoardModelMock::Update(const cxmath::Dimensions& /*p_widgetDimensions*/, bool /*p_isChipMovingHorizontally*/)
{
    m_updateCalled = true;
}

void AnimatedBoardModelMock::Resize(const cxgui::ScalingRatios& /*p_scalingRatios*/)
{
    m_resizeCalled = true;
}

void AnimatedBoardModelMock::AddChipDisplacement(const cxmath::Height& p_vertical, const cxmath::Width& p_horizontal)
{
    m_addChipDisplacementCalled = true;

    m_currentChipPosition.m_x += p_horizontal.Get();
    m_currentChipPosition.m_y += p_vertical.Get();
}

void AnimatedBoardModelMock::ResetChipPositions()
{
    m_resetChipPositionsCalled = true;
}

void AnimatedBoardModelMock::UpdateCurrentColumn(const cxmodel::Column& p_newCurrentColumn)
{
    m_updateCurrentColumnCalled = true;

    m_currentColumn = p_newCurrentColumn;
}

cxgui::FPS AnimatedBoardModelMock::GetFPS() const
{
    return m_fps;
}

cxgui::AnimationSpeed AnimatedBoardModelMock::GetAnimationSpeed() const
{
    return m_animationSpeed;
}

const cxmath::Dimensions& AnimatedBoardModelMock::GetAnimatedAreaDimensions() const
{
    return m_widgetDimensions;
}

const cxmath::Dimensions& AnimatedBoardModelMock::GetCellDimensions() const
{
    return m_cellDimensions;
}

cxmath::Radius AnimatedBoardModelMock::GetChipRadius() const
{
    return cxmath::Radius{0.0};
}

const cxmath::Position& AnimatedBoardModelMock::GetChipPosition() const
{
    return m_currentChipPosition;
}

cxmath::Width AnimatedBoardModelMock::GetHorizontalMargin() const
{
    return cxmath::Width{0.0};
}

const cxmath::Position& AnimatedBoardModelMock::GetMirrorChipPosition() const
{
    return m_currentChipPosition;
}

bool AnimatedBoardModelMock::IsMirrorChipNeeded() const
{
    return false;
}

cxmath::Width AnimatedBoardModelMock::GetLineWidth(cxgui::Feature /*p_feature*/) const
{
    return cxmath::Width{0.0};
}

const cxmodel::Column& AnimatedBoardModelMock::GetCurrentColumn() const
{
    return m_currentColumn;
}

void AnimatedBoardModelMock::SetAnimatedAreaDimensions(const cxmath::Dimensions& p_widgetDimensions)
{
    m_widgetDimensions = p_widgetDimensions;
}

void AnimatedBoardModelMock::SetFPS(const cxgui::FPS& p_fps)
{
    m_fps = p_fps;
}

void AnimatedBoardModelMock::SetAnimationSpeed(const cxgui::AnimationSpeed& p_animationSpeed)
{
    m_animationSpeed = p_animationSpeed;
}

void AnimatedBoardModelMock::SetCurrentColumn(const cxmodel::Column& p_currentColumn)
{
    m_currentColumn = p_currentColumn;
}

void AnimatedBoardModelMock::SetCellDimensions(const cxmath::Dimensions& p_cellDimensions)
{
    m_cellDimensions = p_cellDimensions;
}
