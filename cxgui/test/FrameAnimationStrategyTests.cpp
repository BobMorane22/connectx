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
 * @file FrameAnimationStrategyTests.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <memory>

#include <cxgui/BoardAnimation.h>
#include <cxgui/FrameAnimationStrategy.h>
#include <cxgui/IAnimatedBoardPresenter.h>

class FrameAnimationTestFixture : public ::testing::Test
{

public:

    FrameAnimationTestFixture();

    cxgui::IAnimatedBoardModel& ModelGet();
    cxgui::IAnimatedBoardPresenter& PresenterGet();

private:

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

        cxmath::Dimensions m_dimension{cxmath::Height{0.0}, cxmath::Width{0.0}};
        cxmath::Position m_position;
        cxmodel::Column m_column{0u};
    };

    class AnimatedBoardPresenterMock : public cxgui::IAnimatedBoardPresenter
    {

    public:

        // cxgui::IAnimatedBoardPresenter:
        void Sync() override;
        [[nodiscard]] cxmodel::Height GetBoardHeight() const override;
        [[nodiscard]] cxmodel::Width GetBoardWidth() const override;
        [[nodiscard]] cxmodel::ChipColor GetActivePlayerChipColor() const override;
        [[nodiscard]] const cxgui::IGameViewPresenter::ChipColors& GetBoardChipColors() const override;

        // Testing:
        bool WasSyncCalled() const {return m_syncCalled;}

    private:

        bool m_syncCalled = false;

        cxgui::IGameViewPresenter::ChipColors m_chipColors;
    };

    std::unique_ptr<AnimatedBoardModelMock> m_model;
    std::unique_ptr<AnimatedBoardPresenterMock> m_presenter;

};

void FrameAnimationTestFixture::AnimatedBoardModelMock::Update(const cxmath::Dimensions& /*p_widgetDimensions*/, bool /*p_isChipMovingHorizontally*/)
{
    m_updateCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::Resize(const cxgui::ScalingRatios& /*p_scalingRatios*/)
{
    m_resizeCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::AddChipDisplacement(const cxmath::Height& /*p_vertical*/, const cxmath::Width& /*p_horizontal*/)
{
    m_addChipDisplacementCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::ResetChipPositions()
{
    m_resetChipPositionsCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::UpdateCurrentColumn(const cxmodel::Column& /*p_newCurrentColumn*/)
{
    m_updateCurrentColumnCalled = true;
}

cxgui::FPS FrameAnimationTestFixture::AnimatedBoardModelMock::GetFPS() const
{
    return cxgui::FPS{0};
}

cxgui::AnimationSpeed FrameAnimationTestFixture::AnimatedBoardModelMock::GetAnimationSpeed() const
{
    return cxgui::AnimationSpeed{0u};
}

const cxmath::Dimensions& FrameAnimationTestFixture::AnimatedBoardModelMock::GetAnimatedAreaDimensions() const
{
    return m_dimension;
}

const cxmath::Dimensions& FrameAnimationTestFixture::AnimatedBoardModelMock::GetCellDimensions() const
{
    return m_dimension;
}

cxmath::Radius FrameAnimationTestFixture::AnimatedBoardModelMock::GetChipRadius() const
{
    return cxmath::Radius{0.0};
}

const cxmath::Position& FrameAnimationTestFixture::AnimatedBoardModelMock::GetChipPosition() const
{
    return m_position;
}

cxmath::Width FrameAnimationTestFixture::AnimatedBoardModelMock::GetHorizontalMargin() const
{
    return cxmath::Width{0.0};
}

const cxmath::Position& FrameAnimationTestFixture::AnimatedBoardModelMock::GetMirrorChipPosition() const
{
    return m_position;
}

bool FrameAnimationTestFixture::AnimatedBoardModelMock::IsMirrorChipNeeded() const
{
    return false;
}

cxmath::Width FrameAnimationTestFixture::AnimatedBoardModelMock::GetLineWidth(cxgui::Feature /*p_feature*/) const
{
    return cxmath::Width{0.0};
}

const cxmodel::Column& FrameAnimationTestFixture::AnimatedBoardModelMock::GetCurrentColumn() const
{
    return m_column;
}

void FrameAnimationTestFixture::AnimatedBoardPresenterMock::Sync()
{
    m_syncCalled = true;
}

cxmodel::Height FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetBoardHeight() const
{
    return cxmodel::Height{0u};
}

cxmodel::Width FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetBoardWidth() const
{
    return cxmodel::Width{0u};
}

cxmodel::ChipColor FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetActivePlayerChipColor() const
{
    return cxmodel::MakeTransparent();
}

const cxgui::IGameViewPresenter::ChipColors& FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetBoardChipColors() const
{
    return m_chipColors;
}

FrameAnimationTestFixture::FrameAnimationTestFixture()
{
    m_model = std::make_unique<AnimatedBoardModelMock>();
    EXPECT_TRUE(m_model);

    m_presenter = std::make_unique<AnimatedBoardPresenterMock>();
    EXPECT_TRUE(m_presenter);
}

cxgui::IAnimatedBoardModel& FrameAnimationTestFixture::ModelGet()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

cxgui::IAnimatedBoardPresenter& FrameAnimationTestFixture::PresenterGet()
{
    EXPECT_TRUE(m_presenter);
    return *m_presenter;
}

/**************************************************************************************************
 * Unit tests for the factory method.
 *
 *************************************************************************************************/
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_ValidBoardAnimations_StrategyCreated)
{
    std::unique_ptr<cxgui::IFrameAnimationStrategy> strategy;

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::DROP_CHIP);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::UNDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::REDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::REINITIALIZE);
    ASSERT_TRUE(strategy);

    // No strategy:
    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::GAME_REINITIALIZED);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), cxgui::BoardAnimation::GAME_WON);
    ASSERT_TRUE(strategy);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_InvalidBoardAnimations_ValidNullObjectReturned)
{
    constexpr cxgui::BoardAnimation invalidBoardAnimation = static_cast<cxgui::BoardAnimation>(-1);
    auto strategy = cxgui::CreateFrameAnimationStrategy(ModelGet(), PresenterGet(), invalidBoardAnimation);

    ASSERT_TRUE(strategy);
}

/**************************************************************************************************
 * Unit tests for the "Move chip left one column" strategy.
 *
 *************************************************************************************************/

/**************************************************************************************************
 * Unit tests for the "Move chip right one column" strategy.
 *
 *************************************************************************************************/

/**************************************************************************************************
 * Unit tests for the "Drop chip" strategy.
 *
 *************************************************************************************************/

/**************************************************************************************************
 * Unit tests for the "Undo drop chip" strategy.
 *
 *************************************************************************************************/

/**************************************************************************************************
 * Unit tests for the "Redo drop chip" strategy.
 *
 *************************************************************************************************/

/**************************************************************************************************
 * Unit tests for the "Reinitialize" strategy.
 *
 *************************************************************************************************/
