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
 * @file FrameAnimationStrategy.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/BoardAnimation.h>
#include <cxgui/BoardAnimationNotificationContext.h>
#include <cxgui/FrameAnimationStrategy.h>
#include <cxgui/IAnimatedBoardModel.h>
#include <cxgui/IAnimatedBoardPresenter.h>

using namespace cxgui;

namespace
{

/**************************************************************************************************
 * No frame animation strategy.
 *
 * This is the default strategy to avoid returning nullptr on cases where the animation is
 * not known. This strategy should never be used in practice.
 *
 *************************************************************************************************/
class NoFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    NoFrameAnimationStrategy()
    {
        ASSERT_ERROR_MSG("Unknown frame animation strategy");
    }

    std::optional<BoardAnimationNotificationContext> PerformAnimation([[maybe_unused]] AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo,
                                                                      [[maybe_unused]] AnimationInformations<cxmath::Height>& p_verticalAnimationInfo) override
    {
        return std::nullopt;
    }
};

/**************************************************************************************************
 * Move chip left one column strategy.
 *
 *************************************************************************************************/
class MoveChipLeftOneColumnFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    MoveChipLeftOneColumnFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                                const IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<BoardAnimationNotificationContext> PerformAnimation(AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo,
                                                                      AnimationInformations<cxmath::Height>& p_verticalAnimationInfo) override;

private:

    IAnimatedBoardModel& m_animationModel;
    const IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> MoveChipLeftOneColumnFrameAnimationStrategy::MoveChipLeftOneColumnFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo,
                                                                                                                                                                   [[maybe_unused]] cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo)
{
    const double fps = static_cast<double>(m_animationModel.GetFPS().Get());
    const double speed = static_cast<double>(m_animationModel.GetAnimationSpeed().Get());
    const double nbFramesPerChip = fps / speed;

    const double oneAnimationWidth = m_animationModel.GetAnimatedAreaDimensions().m_width.Get() / m_presenter.GetBoardWidth().Get();
    const cxmath::Width delta{oneAnimationWidth / nbFramesPerChip};

    if(p_horizontalAnimationInfo.m_currentDisplacement.Get() >= oneAnimationWidth || std::abs(p_horizontalAnimationInfo.m_currentDisplacement.Get() - oneAnimationWidth) <= 1e-6)
    {
        if(m_animationModel.GetCurrentColumn() <= cxmodel::Column{0u})
        {
            const cxmodel::Column currentColumn{m_presenter.GetBoardWidth().Get() - 1u};
            m_animationModel.UpdateCurrentColumn(currentColumn);
        }
        else
        {
            m_animationModel.UpdateCurrentColumn(m_animationModel.GetCurrentColumn() - cxmodel::Column{1u});
        }

        // End animation:
        p_horizontalAnimationInfo.Reset();
        return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN;
    }
    else
    {
        m_animationModel.AddChipDisplacement(cxmath::Height{0.0}, -delta);
        p_horizontalAnimationInfo.m_currentDisplacement += delta;
    }

    return std::nullopt;
}

/**************************************************************************************************
 * Move chip right one column strategy.
 *
 *************************************************************************************************/
class MoveChipRightOneColumnFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    MoveChipRightOneColumnFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                                 IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<BoardAnimationNotificationContext> PerformAnimation(AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo,
                                                                      AnimationInformations<cxmath::Height>& p_verticalAnimationInfo) override;

private:

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> MoveChipRightOneColumnFrameAnimationStrategy::MoveChipRightOneColumnFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo,
                                                                                                                                                                    [[maybe_unused]] cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo)
{
    const double fps = static_cast<double>(m_animationModel.GetFPS().Get());
    const double speed = static_cast<double>(m_animationModel.GetAnimationSpeed().Get());
    const double nbFramesPerChip = fps / speed;

    const double oneAnimationWidth = m_animationModel.GetAnimatedAreaDimensions().m_width.Get() / m_presenter.GetBoardWidth().Get();
    const cxmath::Width delta{oneAnimationWidth / nbFramesPerChip};

    if(p_horizontalAnimationInfo.m_currentDisplacement.Get() >= oneAnimationWidth || std::abs(p_horizontalAnimationInfo.m_currentDisplacement.Get() - oneAnimationWidth) <= 1e-6)
    {
        if(m_animationModel.GetCurrentColumn() >= cxmodel::Column{m_presenter.GetBoardWidth().Get() - 1u})
        {
            m_animationModel.UpdateCurrentColumn(cxmodel::Column{0u});
        }
        else
        {
            m_animationModel.UpdateCurrentColumn(m_animationModel.GetCurrentColumn() + cxmodel::Column{1u});
        }

        // End animation:
        p_horizontalAnimationInfo.Reset();
        m_presenter.Sync();
        return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN;
    }
    else
    {
        m_animationModel.AddChipDisplacement(cxmath::Height{0.0}, delta);
        p_horizontalAnimationInfo.m_currentDisplacement += delta;
    }

    return std::nullopt;
}

} // unamed namespace


/**************************************************************************************************
 * Factory method.
 *
 *************************************************************************************************/
std::unique_ptr<IFrameAnimationStrategy> cxgui::CreateFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                                                             IAnimatedBoardPresenter& p_presenter,
                                                                             const BoardAnimation p_animation)
{
    switch(p_animation)
    {
        case cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN:
            return std::make_unique<MoveChipLeftOneColumnFrameAnimationStrategy>(p_animationModel, p_presenter);

        case cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN:
            return std::make_unique<MoveChipRightOneColumnFrameAnimationStrategy>(p_animationModel, p_presenter);

        default:
            return std::make_unique<NoFrameAnimationStrategy>();
    }

    return std::make_unique<NoFrameAnimationStrategy>();
}
