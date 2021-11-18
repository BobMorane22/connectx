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

namespace cxgui
{

class IAnimatedBoardPresenter;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Concrete animated board model.
 *
 *************************************************************************************************/
class AnimatedBoardModel : public cxgui::IAnimatedBoardModel
{

public:

    AnimatedBoardModel(const cxgui::IAnimatedBoardPresenter& p_presenter, size_t p_animationSpeed);

    void Update(const Dimensions& p_widgetDimensions, bool p_isChipMovingHorizontally) override;
    void Resize(double p_horizontalRatio, double p_verticalRatio) override;
    void AddChipDisplacement(double p_horizontal, double p_vertical) override;
    void ResetChipPositions() override;
    void UpdateCurrentColumn(size_t p_newCurrentColumn) override;

    [[nodiscard]] size_t GetFPS() const override;
    [[nodiscard]] size_t GetAnimationSpeed() const override;
    [[nodiscard]] const Dimensions& GetAnimatedAreaDimensions() const override;
    [[nodiscard]] const Dimensions& GetCellDimensions() const override;
    [[nodiscard]] double GetChipRadius() const override;
    [[nodiscard]] const cxmath::Position& GetChipPosition() const override;
    [[nodiscard]] double GetHorizontalMargin() const override;
    [[nodiscard]] const cxmath::Position& GetMirrorChipPosition() const override;
    [[nodiscard]] bool IsMirrorChipNeeded() const override;
    [[nodiscard]] double GetLineWidth(Feature p_feature) const override;
    [[nodiscard]] size_t GetCurrentColumn() const override;

private:

    template<BoardAnimation A>
    [[nodiscard]] bool ComputeChipPosition(double p_windowWidth, double p_halfChipSize, double p_horizontalMargin);
    [[nodiscard]] bool ComputeChipLeftPosition(double p_windowWidth, double p_halfChipSize, double p_horizontalMargin);
    [[nodiscard]] bool ComputeChipRightPosition(double p_windowWidth, double p_halfChipSize, double p_horizontalMargin);
    void ComputeChipVerticalPosition(const double p_halfChipSize, double p_height);

    const cxgui::IAnimatedBoardPresenter& m_presenter;

    size_t m_animationSpeed; // Units: chips/sec

    Dimensions m_widgetDimensions{Height{0}, Width{0}};
    Dimensions m_cellDimensions{Height{0}, Width{0}};

    double m_chipRadius = 0.0;

    bool m_isChipMovingHorizontally = false;
    cxmath::Position m_chipPosition{0.0, 0.0};
    cxmath::Position m_mirrorChipPosition{0.0, 0.0};
    bool m_isMirrorChipNeeded = false;

    double m_horizontalMargin = 0.0;

    double m_chipLineWidth = 0.0;
    double m_cellLineWidth = 0.0;

    size_t m_currentColumn = 0u;
};

} // namespace cxgui

#endif // ANIMATEDBOARDMODEL_H_71B2242B_9840_4520_818A_DC44B21E2307
