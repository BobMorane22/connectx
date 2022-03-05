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
 * @file AnimatedBoardModelMock.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ANIMATEDBOARDMODELMOCK_H_FF30200C_A3BA_4A3F_A0C2_292330EF48B3
#define ANIMATEDBOARDMODELMOCK_H_FF30200C_A3BA_4A3F_A0C2_292330EF48B3

#include <cxgui/IAnimatedBoardModel.h>

class AnimatedBoardModelMock : public cxgui::IAnimatedBoardModel
{

public:

    // cxgui::IAnimatedBoardModel:
    void Update(const cxmath::Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally) override;
    void Resize(const cxgui::ScalingRatios& p_scalingRatios) override;
    void AddChipDisplacement(const cxmath::Height& p_vertical, const cxmath::Width& p_horizontal) override;
    void ResetChipPositions() override;
    void UpdateCurrentColumn(const cxmodel::Column& p_newCurrentColumn) override;
    [[nodiscard]] cxgui::FPS GetFPS() const override;
    [[nodiscard]] cxgui::AnimationSpeed GetAnimationSpeed() const override;
    [[nodiscard]] const cxmath::Dimensions& GetAnimatedAreaDimensions() const override;
    [[nodiscard]] const cxmath::Dimensions& GetCellDimensions() const override;
    [[nodiscard]] cxmath::Radius GetChipRadius() const override;
    [[nodiscard]] const cxmath::Position& GetChipPosition() const override;
    [[nodiscard]] cxmath::Width GetHorizontalMargin() const override;
    [[nodiscard]] const cxmath::Position& GetMirrorChipPosition() const override;
    [[nodiscard]] bool IsMirrorChipNeeded() const override;
    [[nodiscard]] cxmath::Width GetLineWidth(cxgui::Feature p_feature) const override;
    [[nodiscard]] const cxmodel::Column& GetCurrentColumn() const override;

    // Testing:
    void SetAnimatedAreaDimensions(const cxmath::Dimensions& p_widgetDimensions);
    void SetFPS(const cxgui::FPS& p_fps);
    void SetAnimationSpeed(const cxgui::AnimationSpeed& p_animationSpeed);
    void SetCurrentColumn(const cxmodel::Column& p_currentColumn);
    void SetCellDimensions(const cxmath::Dimensions& p_cellDimensions);

    [[nodiscard]] bool WasUpdateCalled() const {return m_updateCalled;}
    [[nodiscard]] bool WasResizeCalled() const {return m_resizeCalled;}
    [[nodiscard]] bool WasAddChipDisplacementCalled() const {return m_addChipDisplacementCalled;}
    [[nodiscard]] bool WasResetChipPositionsCalled() const {return m_resetChipPositionsCalled;}
    [[nodiscard]] bool WasUpdateCurrentColumnCalled() const {return m_updateCurrentColumnCalled;}

private:

    bool m_updateCalled = false;
    bool m_resizeCalled = false;
    bool m_addChipDisplacementCalled = false;
    bool m_resetChipPositionsCalled = false;
    bool m_updateCurrentColumnCalled = false;

    cxmath::Dimensions m_widgetDimensions{cxmath::Height{0.0}, cxmath::Width{0.0}};
    cxgui::FPS m_fps{24u};
    cxgui::AnimationSpeed m_animationSpeed{3u};
    cxmath::Position m_currentChipPosition;

    cxmath::Dimensions m_cellDimensions{cxmath::Height{0.0}, cxmath::Width{0.0}};
    cxmodel::Column m_currentColumn{0u};
};

#endif // ANIMATEDBOARDMODELMOCK_H_FF30200C_A3BA_4A3F_A0C2_292330EF48B3
