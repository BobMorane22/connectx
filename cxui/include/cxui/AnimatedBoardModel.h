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
 * @file AnimatedBoardModel.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef ANIMATEDBOARDMODEL_H_71B2242B_9840_4520_818A_DC44B21E2307
#define ANIMATEDBOARDMODEL_H_71B2242B_9840_4520_818A_DC44B21E2307

#include <algorithm>

#include "BoardAnimation.h"
#include "IAnimatedBoardModel.h"

namespace cx::ui
{

class IAnimatedBoardPresenter;

}

namespace cx::ui
{

/**********************************************************************************************//**
 * @brief Concrete animated board model.
 *
 *************************************************************************************************/
class AnimatedBoardModel : public cx::ui::IAnimatedBoardModel
{

public:

    /**********************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      A game board presenter.
     * @param p_animationSpeed
     *      The animation speed (i.e. the number of chips travelled per second).
     *
     *************************************************************************************************/
    AnimatedBoardModel(const cx::ui::IAnimatedBoardPresenter& p_presenter, const cx::ui::AnimationSpeed& p_animationSpeed);

    void Update(const cx::math::Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally) override;
    void Resize(const cx::ui::cmn::ScalingRatios& p_scalingRatios) override;
    void AddChipDisplacement(const cx::math::Height& p_vertical, const cx::math::Width& p_horizontal) override;
    void ResetChipPositions() override;
    void UpdateCurrentColumn(const cx::model::Column& p_newCurrentColumn) override;

    [[nodiscard]] FPS GetFPS() const override;
    [[nodiscard]] AnimationSpeed GetAnimationSpeed() const override;
    [[nodiscard]] const cx::math::Dimensions& GetAnimatedAreaDimensions() const override;
    [[nodiscard]] const cx::math::Dimensions& GetCellDimensions() const override;
    [[nodiscard]] cx::math::Radius GetChipRadius() const override;
    [[nodiscard]] const cx::math::Position& GetChipPosition() const override;
    [[nodiscard]] cx::math::Width GetHorizontalMargin() const override;
    [[nodiscard]] const cx::math::Position& GetMirrorChipPosition() const override;
    [[nodiscard]] bool IsMirrorChipNeeded() const override;
    [[nodiscard]] cx::math::Width GetLineWidth(Feature p_feature) const override;
    [[nodiscard]] const cx::model::Column& GetCurrentColumn() const override;

private:

    template<BoardAnimation A>
    [[nodiscard]] bool ComputeChipPosition(double p_windowWidth, const cx::math::Radius& p_discRadius, double p_horizontalMargin);
    [[nodiscard]] bool ComputeChipLeftPosition(double p_windowWidth, const cx::math::Radius& p_discRadius, double p_horizontalMargin);
    [[nodiscard]] bool ComputeChipRightPosition(double p_windowWidth, const cx::math::Radius& p_discRadius, double p_horizontalMargin);
    void ComputeChipVerticalPosition(const cx::math::Radius& p_discRadius, double p_height);

    const cx::ui::IAnimatedBoardPresenter& m_presenter;

    cx::ui::AnimationSpeed m_animationSpeed;

    cx::math::Dimensions m_widgetDimensions{cx::math::Height{0.0}, cx::math::Width{0.0}};
    cx::math::Dimensions m_cellDimensions{cx::math::Height{0.0}, cx::math::Width{0.0}};

    cx::math::Radius m_chipRadius{0.0};

    bool m_isChipMovingHorizontally = false;
    cx::math::Position m_chipPosition{0.0, 0.0};
    cx::math::Position m_mirrorChipPosition{0.0, 0.0};
    bool m_isMirrorChipNeeded = false;

    cx::math::Width m_horizontalMargin{0.0};

    cx::math::Width m_chipLineWidth{0.0};
    cx::math::Width m_cellLineWidth{0.0};

    cx::model::Column m_currentColumn{0u};
};

} // namespace cx::ui

#endif // ANIMATEDBOARDMODEL_H_71B2242B_9840_4520_818A_DC44B21E2307
