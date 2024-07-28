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

#include <cxuicmn/IAnimatedBoardModel.h>

class AnimatedBoardModelMock : public cx::ui::cmn::IAnimatedBoardModel
{

public:

    // cx::ui::cmn::IAnimatedBoardModel:
    void Update(const cx::math::Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally) override;
    void Resize(const cx::ui::cmn::ScalingRatios& p_scalingRatios) override;
    void AddChipDisplacement(const cx::math::Height& p_vertical, const cx::math::Width& p_horizontal) override;
    void ResetChipPositions() override;
    void UpdateCurrentColumn(const cx::model::Column& p_newCurrentColumn) override;
    [[nodiscard]] cx::ui::cmn::FPS GetFPS() const override;
    [[nodiscard]] cx::ui::cmn::AnimationSpeed GetAnimationSpeed() const override;
    [[nodiscard]] const cx::math::Dimensions& GetAnimatedAreaDimensions() const override;
    [[nodiscard]] const cx::math::Dimensions& GetCellDimensions() const override;
    [[nodiscard]] cx::math::Radius GetChipRadius() const override;
    [[nodiscard]] const cx::math::Position& GetChipPosition() const override;
    [[nodiscard]] cx::math::Width GetHorizontalMargin() const override;
    [[nodiscard]] const cx::math::Position& GetMirrorChipPosition() const override;
    [[nodiscard]] bool IsMirrorChipNeeded() const override;
    [[nodiscard]] cx::math::Width GetLineWidth(cx::ui::cmn::Feature p_feature) const override;
    [[nodiscard]] const cx::model::Column& GetCurrentColumn() const override;

    // Testing:
    void SetAnimatedAreaDimensions(const cx::math::Dimensions& p_widgetDimensions);
    void SetFPS(const cx::ui::cmn::FPS& p_fps);
    void SetAnimationSpeed(const cx::ui::cmn::AnimationSpeed& p_animationSpeed);
    void SetCurrentColumn(const cx::model::Column& p_currentColumn);
    void SetCellDimensions(const cx::math::Dimensions& p_cellDimensions);

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

    cx::math::Dimensions m_widgetDimensions{cx::math::Height{0.0}, cx::math::Width{0.0}};
    cx::ui::cmn::FPS m_fps{24u};
    cx::ui::cmn::AnimationSpeed m_animationSpeed{3u};
    cx::math::Position m_currentChipPosition;

    cx::math::Dimensions m_cellDimensions{cx::math::Height{0.0}, cx::math::Width{0.0}};
    cx::model::Column m_currentColumn{0u};
};

#endif // ANIMATEDBOARDMODELMOCK_H_FF30200C_A3BA_4A3F_A0C2_292330EF48B3
