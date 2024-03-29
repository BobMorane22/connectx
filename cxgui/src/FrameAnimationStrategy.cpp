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

#include <cmath>

#include <cxinv/assertion.h>
#include <cxmath/math.h>
#include <cxgui/BoardAnimation.h>
#include <cxmodel/Color.h>
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

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                             cxgui::AnimationInformations<cxmath::Width>& /*p_horizontalAnimationInfo*/) override
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

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    IAnimatedBoardModel& m_animationModel;
    const IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> MoveChipLeftOneColumnFrameAnimationStrategy::MoveChipLeftOneColumnFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                                                                                                                   cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo)
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

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> MoveChipRightOneColumnFrameAnimationStrategy::MoveChipRightOneColumnFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                                                                                                                     cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo)
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

/**************************************************************************************************
 * Move chip right to target strategy.
 *
 *************************************************************************************************/
class MoveChipRightToTargetFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    MoveChipRightToTargetFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                                IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> MoveChipRightToTargetFrameAnimationStrategy::MoveChipRightToTargetFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                                                                                                                   cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo)
{
    // Simulates the drop column computed by the model for the bot...
    const cxmodel::Column target{m_presenter.GetBotTarget()};

    // The animation time is modulated by the number of columns the chip has to travel. The
    // animation time can be as small as 0.5s (1 column to traval) and up to 2s (64 columns
    // to travel).
    const double fps = static_cast<double>(m_animationModel.GetFPS().Get());
    const double timeSlice = 1.5 / 63.0;
    const double totalAnimationTimeInSec = 0.5 + ((target.Get() - 1u) * timeSlice);
    const double totalNbOfFrames = totalAnimationTimeInSec * fps;

    const double oneAnimationWidth = (m_animationModel.GetAnimatedAreaDimensions().m_width.Get() / m_presenter.GetBoardWidth().Get()) * target.Get();

    if(p_horizontalAnimationInfo.m_currentDisplacement.Get() >= oneAnimationWidth || std::abs(p_horizontalAnimationInfo.m_currentDisplacement.Get() - oneAnimationWidth) <= 1e-6)
    {
        // End animation:
        p_horizontalAnimationInfo.Reset();
        m_animationModel.UpdateCurrentColumn(target);
        m_presenter.Sync();

        return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_TO_TARGET;
    }
    else
    {
        // Since the added delta can be significant (the animation is pretty wide), there are
        // times where the last delta added makes the displacement increase significantly more
        // than the computed animation width. Visually, this translated into a misaligned chip
        // on the board. To address this, we make an adjustement on the last delta to make
        // sure it does not exceed the computed animation width.
        cxmath::Width delta{oneAnimationWidth / totalNbOfFrames};
        if(p_horizontalAnimationInfo.m_currentDisplacement.Get() + delta.Get() > oneAnimationWidth)
        {
            delta -= p_horizontalAnimationInfo.m_currentDisplacement + delta - cxmath::Width{oneAnimationWidth};
        }

        m_animationModel.AddChipDisplacement(cxmath::Height{0.0}, delta);
        p_horizontalAnimationInfo.m_currentDisplacement += delta;
    }

    return std::nullopt;
}

/**************************************************************************************************
 * Drop chip strategy.
 *
 *************************************************************************************************/
class DropChipFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    DropChipFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                   IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    cxmodel::Row GetDropPosition(const cxmodel::Column& p_column) const;

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

cxmodel::Row DropChipFrameAnimationStrategy::GetDropPosition(const cxmodel::Column& p_column) const
{
    cxmodel::Row dropRow{0u};
    const IGameViewPresenter::ChipColors& chipColors = m_presenter.GetBoardChipColors();

    for(int row = m_presenter.GetBoardHeight().Get() - 1; row >= 0; --row)
    {
        if(chipColors[row][p_column.Get()] == cxmodel::MakeTransparent())
        {
            dropRow = cxmodel::Row{static_cast<size_t>(row)};
            break;
        }
    }

    return dropRow;
}

std::optional<cxgui::BoardAnimationNotificationContext> DropChipFrameAnimationStrategy::DropChipFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                                                                                         cxgui::AnimationInformations<cxmath::Width>& /*p_horizontalAnimationInfo*/)
{
    const double cellHeight = m_animationModel.GetCellDimensions().m_height.Get();
    const double oneAnimationHeight = (GetDropPosition(m_animationModel.GetCurrentColumn()) + cxmodel::Row{1}).Get() * cellHeight;

    const double fps = static_cast<double>(m_animationModel.GetFPS().Get());
    const double nbFrames = p_verticalAnimationInfo.m_nbOfRenderedFrames;
    const double t = nbFrames / fps; // In seconds.

    // For a free falling object, starting with no acceleration, we can compute the displacement
    // at time t using the following formula:
    //
    //                                    d(t) = -½gt².
    //
    // In our case, we need the absolute value of this computation because the y values go
    // increasing from top to bottom in Gtkmm. Furthermore, we multiply this value by 8
    // otherwise the animation is too slow and the game play feels awkward. In the end, we
    // compute the following below:
    //
    //                                    d(t) = |4gt²|
    //
    // to get a smooth gravity animation when dropping a chip:
    const cxmath::Height delta{4 * cxmath::g<double> * t * t};

    if(p_verticalAnimationInfo.m_currentDisplacement.Get() >= oneAnimationHeight || std::abs(p_verticalAnimationInfo.m_currentDisplacement.Get() - oneAnimationHeight) <= 1e-6)
    {
        // End animation:
        p_verticalAnimationInfo.Reset();

        // Reinitialize chip:
        m_animationModel.ResetChipPositions();
        m_animationModel.UpdateCurrentColumn(cxmodel::Column{0u});

        m_presenter.Sync();

        return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP;
    }
    else
    {
        m_animationModel.AddChipDisplacement(delta, cxmath::Width{0.0});
        p_verticalAnimationInfo.m_currentDisplacement += delta;
        p_verticalAnimationInfo.m_nbOfRenderedFrames += 1u;;
    }

    return std::nullopt;
}

/**************************************************************************************************
 * Undo drop chip strategy.
 *
 *************************************************************************************************/
class UndoDropChipFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    UndoDropChipFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                       IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    cxmodel::Row GetDropPosition(const cxmodel::Column& p_column) const;

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> UndoDropChipFrameAnimationStrategy::UndoDropChipFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                                                                                                 cxgui::AnimationInformations<cxmath::Width>& /*p_horizontalAnimationInfo*/)
{
    // Reinitialize chip:
    m_animationModel.ResetChipPositions();
    m_animationModel.UpdateCurrentColumn(cxmodel::Column{0u});
    
    m_presenter.Sync();
    
    return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_UNDO_DROP_CHIP;
}

/**************************************************************************************************
 * Redo drop chip strategy.
 *
 *************************************************************************************************/
class RedoDropChipFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    RedoDropChipFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                       IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    cxmodel::Row GetDropPosition(const cxmodel::Column& p_column) const;

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> RedoDropChipFrameAnimationStrategy::RedoDropChipFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                                                                                                 cxgui::AnimationInformations<cxmath::Width>& /*p_horizontalAnimationInfo*/)
{
    // Reinitialize chip:
    m_animationModel.ResetChipPositions();
    m_animationModel.UpdateCurrentColumn(cxmodel::Column{0u});
    
    m_presenter.Sync();
    
    return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REDO_DROP_CHIP;
}

/**************************************************************************************************
 * Reinitialize strategy.
 *
 *************************************************************************************************/
class ReinitializeFrameAnimationStrategy : public IFrameAnimationStrategy
{

public:

    ReinitializeFrameAnimationStrategy(IAnimatedBoardModel& p_animationModel,
                                       IAnimatedBoardPresenter& p_presenter)
    : m_animationModel{p_animationModel}
    , m_presenter{p_presenter}
    {
    }

    std::optional<cxgui::BoardAnimationNotificationContext> PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& p_verticalAnimationInfo,
                                                                             cxgui::AnimationInformations<cxmath::Width>& p_horizontalAnimationInfo) override;

private:

    cxmodel::Row GetDropPosition(const cxmodel::Column& p_column) const;

    IAnimatedBoardModel& m_animationModel;
    IAnimatedBoardPresenter& m_presenter;
};

std::optional<cxgui::BoardAnimationNotificationContext> ReinitializeFrameAnimationStrategy::ReinitializeFrameAnimationStrategy::PerformAnimation(cxgui::AnimationInformations<cxmath::Height>& /*p_verticalAnimationInfo*/,
                                                                                                                                                 cxgui::AnimationInformations<cxmath::Width>& /*p_horizontalAnimationInfo*/)
{
    // Reinitialize chip:
    m_animationModel.ResetChipPositions();
    m_animationModel.UpdateCurrentColumn(cxmodel::Column{0u});
    
    m_presenter.Sync();
    
    return cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REINITIALIZE_BOARD;
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

        case cxgui::BoardAnimation::MOVE_CHIP_RIGHT_TO_TARGET:
            return std::make_unique<MoveChipRightToTargetFrameAnimationStrategy>(p_animationModel, p_presenter);

        case cxgui::BoardAnimation::DROP_CHIP:
            return std::make_unique<DropChipFrameAnimationStrategy>(p_animationModel, p_presenter);

        case cxgui::BoardAnimation::UNDO_DROP_CHIP:
            return std::make_unique<UndoDropChipFrameAnimationStrategy>(p_animationModel, p_presenter);

        case cxgui::BoardAnimation::REDO_DROP_CHIP:
            return std::make_unique<RedoDropChipFrameAnimationStrategy>(p_animationModel, p_presenter);

        case cxgui::BoardAnimation::REINITIALIZE:
            return std::make_unique<ReinitializeFrameAnimationStrategy>(p_animationModel, p_presenter);

        default:
            return std::make_unique<NoFrameAnimationStrategy>();
    }

    return std::make_unique<NoFrameAnimationStrategy>();
}
