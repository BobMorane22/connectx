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

// Refactorings to complete:
//
//  1. Add a templated AreLogicallyEqual version. Consider using ULPs instead
//     of an hardcoded threshold. When done, define it for every usage of
//     ASSERT_DOUBLE_EQ in this file.
//
//  2. Trouver un moyen afin que ce genre de code:
//
//      ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
//
//     puisse être réécrit sans redondance, comme ceci:
//
//      ASSERT_TRUE((GetModel().GetChipPosition() == {0.0, 0.0});
//

#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include <cxunit/StdStreamRedirector.h>
#include <cxgui/BoardAnimation.h>
#include <cxgui/BoardAnimationNotificationContext.h>
#include <cxgui/FrameAnimationStrategy.h>
#include <cxgui/IAnimatedBoardPresenter.h>

class FrameAnimationTestFixture : public ::testing::Test
{

public:

    FrameAnimationTestFixture();

    // Animation model:
    cxgui::IAnimatedBoardModel& GetModel();

    void SetAnimatedAreaDimensionsOnModel(const cxmath::Dimensions& p_widgetDimensions);
    void SetFPSOnModel(const cxgui::FPS& p_fps);
    void SetAnimationSpeedOnModel(const cxgui::AnimationSpeed& p_animationSpeed);
    void SetCurrentColumnOnModel(const cxmodel::Column& p_currentColumn);

    [[nodiscard]] bool WasUpdateCalledOnModel() const {return m_model->WasUpdateCalled();}
    [[nodiscard]] bool WasResizeCalledOnModel() const {return m_model->WasResizeCalled();}
    [[nodiscard]] bool WasAddChipDisplacementCalledOnModel() const {return m_model->WasAddChipDisplacementCalled();}
    [[nodiscard]] bool WasResetChipPositionsCalledOnModel() const {return m_model->WasResetChipPositionsCalled();}
    [[nodiscard]] bool WasUpdateCurrentColumnCalledOnModel() const {return m_model->WasUpdateCurrentColumnCalled();}

    // Presenter:
    cxgui::IAnimatedBoardPresenter& GetPresenter();

    void SetBoardDimensionsOnPresenter(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns);

    [[nodiscard]] bool WasSyncCalledOnPresenter() const {return m_presenter->WasSyncCalled();}

    // Helpers:
    using BothAnimationInformations = std::pair<cxgui::AnimationInformations<cxmath::Height>, cxgui::AnimationInformations<cxmath::Width>>;

    BothAnimationInformations MakeAnimationInformations(const cxmath::Height& p_verticalCurrentDisplacement, const cxmath::Width& p_horizontalCurrentDisplacement);
    void ConfigureModelAndPresenter(const cxmodel::Height& p_boardHeight, const cxmodel::Width& p_boardWidth, const cxmodel::Column& p_currantColumn);

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
        void SetAnimatedAreaDimensions(const cxmath::Dimensions& p_widgetDimensions);
        void SetFPS(const cxgui::FPS& p_fps);
        void SetAnimationSpeed(const cxgui::AnimationSpeed& p_animationSpeed);

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

        cxmath::Dimensions m_dimension{cxmath::Height{0.0}, cxmath::Width{0.0}};
        cxmodel::Column m_currentColumn{0u};
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
        void SetBoardDimensions(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns);

        [[nodiscard]] bool WasSyncCalled() const {return m_syncCalled;}

    private:

        bool m_syncCalled = false;

        cxmodel::Height m_boardHeight{6u};
        cxmodel::Width m_boardWidth{7u};

        cxgui::IGameViewPresenter::ChipColors m_chipColors;
    };

    std::unique_ptr<AnimatedBoardModelMock> m_model;
    std::unique_ptr<AnimatedBoardPresenterMock> m_presenter;

};

ADD_STREAM_REDIRECTORS(FrameAnimationTestFixture);

void FrameAnimationTestFixture::AnimatedBoardModelMock::Update(const cxmath::Dimensions& /*p_widgetDimensions*/, bool /*p_isChipMovingHorizontally*/)
{
    m_updateCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::Resize(const cxgui::ScalingRatios& /*p_scalingRatios*/)
{
    m_resizeCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::AddChipDisplacement(const cxmath::Height& p_vertical, const cxmath::Width& p_horizontal)
{
    m_addChipDisplacementCalled = true;

    m_currentChipPosition.m_x += p_horizontal.Get();
    m_currentChipPosition.m_y += p_vertical.Get();
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::ResetChipPositions()
{
    m_resetChipPositionsCalled = true;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::UpdateCurrentColumn(const cxmodel::Column& p_newCurrentColumn)
{
    m_updateCurrentColumnCalled = true;

    m_currentColumn = p_newCurrentColumn;
}

cxgui::FPS FrameAnimationTestFixture::AnimatedBoardModelMock::GetFPS() const
{
    return m_fps;
}

cxgui::AnimationSpeed FrameAnimationTestFixture::AnimatedBoardModelMock::GetAnimationSpeed() const
{
    return m_animationSpeed;
}

const cxmath::Dimensions& FrameAnimationTestFixture::AnimatedBoardModelMock::GetAnimatedAreaDimensions() const
{
    return m_widgetDimensions;
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
    return m_currentChipPosition;
}

cxmath::Width FrameAnimationTestFixture::AnimatedBoardModelMock::GetHorizontalMargin() const
{
    return cxmath::Width{0.0};
}

const cxmath::Position& FrameAnimationTestFixture::AnimatedBoardModelMock::GetMirrorChipPosition() const
{
    return m_currentChipPosition;
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
    return m_currentColumn;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::SetAnimatedAreaDimensions(const cxmath::Dimensions& p_widgetDimensions)
{
    m_widgetDimensions = p_widgetDimensions;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::SetFPS(const cxgui::FPS& p_fps)
{
    m_fps = p_fps;
}

void FrameAnimationTestFixture::AnimatedBoardModelMock::SetAnimationSpeed(const cxgui::AnimationSpeed& p_animationSpeed)
{
    m_animationSpeed = p_animationSpeed;
}

void FrameAnimationTestFixture::AnimatedBoardPresenterMock::Sync()
{
    m_syncCalled = true;
}

cxmodel::Height FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetBoardHeight() const
{
    return m_boardHeight;
}

cxmodel::Width FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetBoardWidth() const
{
    return m_boardWidth;
}

cxmodel::ChipColor FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetActivePlayerChipColor() const
{
    return cxmodel::MakeTransparent();
}

const cxgui::IGameViewPresenter::ChipColors& FrameAnimationTestFixture::AnimatedBoardPresenterMock::GetBoardChipColors() const
{
    return m_chipColors;
}

void FrameAnimationTestFixture::AnimatedBoardPresenterMock::SetBoardDimensions(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns)
{
    m_boardHeight = p_nbRows;
    m_boardWidth = p_nbColumns;
}

FrameAnimationTestFixture::FrameAnimationTestFixture()
{
    m_model = std::make_unique<AnimatedBoardModelMock>();
    EXPECT_TRUE(m_model);

    m_presenter = std::make_unique<AnimatedBoardPresenterMock>();
    EXPECT_TRUE(m_presenter);
}

cxgui::IAnimatedBoardModel& FrameAnimationTestFixture::GetModel()
{
    EXPECT_TRUE(m_model);
    return *m_model;
}

void FrameAnimationTestFixture::SetAnimatedAreaDimensionsOnModel(const cxmath::Dimensions& p_widgetDimensions)
{
    m_model->SetAnimatedAreaDimensions(p_widgetDimensions);
}

void FrameAnimationTestFixture::SetFPSOnModel(const cxgui::FPS& p_fps)
{
    m_model->SetFPS(p_fps);
}

void FrameAnimationTestFixture::SetAnimationSpeedOnModel(const cxgui::AnimationSpeed& p_animationSpeed)
{
    m_model->SetAnimationSpeed(p_animationSpeed);
}

void FrameAnimationTestFixture::SetCurrentColumnOnModel(const cxmodel::Column& p_currentColumn)
{
    m_model->UpdateCurrentColumn(p_currentColumn);
}

cxgui::IAnimatedBoardPresenter& FrameAnimationTestFixture::GetPresenter()
{
    EXPECT_TRUE(m_presenter);
    return *m_presenter;
}

void FrameAnimationTestFixture::SetBoardDimensionsOnPresenter(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns)
{
    m_presenter->SetBoardDimensions(p_nbRows, p_nbColumns);
}

FrameAnimationTestFixture::BothAnimationInformations FrameAnimationTestFixture::MakeAnimationInformations(const cxmath::Height& p_verticalCurrentDisplacement, const cxmath::Width& p_horizontalCurrentDisplacement)
{
    cxgui::AnimationInformations<cxmath::Height> heightInfo;
    heightInfo.m_currentDisplacement = p_verticalCurrentDisplacement;

    cxgui::AnimationInformations<cxmath::Width> widthInfo;
    widthInfo.m_currentDisplacement = p_horizontalCurrentDisplacement;

    return {heightInfo, widthInfo};
}

void FrameAnimationTestFixture::ConfigureModelAndPresenter(const cxmodel::Height& p_boardHeight, const cxmodel::Width& p_boardWidth, const cxmodel::Column& p_currentColumn)
{
    SetFPSOnModel(cxgui::FPS{24u});
    SetAnimationSpeedOnModel(cxgui::AnimationSpeed{3u});

    SetCurrentColumnOnModel(p_currentColumn);

    SetBoardDimensionsOnPresenter(p_boardHeight, p_boardWidth);

    const double widgetHeight = (p_boardHeight.Get() + 1u) * 10.0;
    const double widgetWidth = (p_boardWidth.Get()) * 10.0;
    SetAnimatedAreaDimensionsOnModel({cxmath::Height{widgetHeight}, cxmath::Width{widgetWidth}});
}

/**************************************************************************************************
 * Unit tests for the factory method.
 *
 *************************************************************************************************/
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_ValidBoardAnimations_StrategyCreated)
{
    std::unique_ptr<cxgui::IFrameAnimationStrategy> strategy;

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::DROP_CHIP);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::UNDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::REDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::REINITIALIZE);
    ASSERT_TRUE(strategy);

    // No strategy:
    cxunit::DisableStdStreamsRAII streamDisabler;
    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::GAME_REINITIALIZED);
    ASSERT_TRUE(strategy);

    strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), cxgui::BoardAnimation::GAME_WON);
    ASSERT_TRUE(strategy);
}

TEST_F(FrameAnimationTestFixtureStdErrStreamRedirector, /*DISABLED_*/CreateFrameAnimationStrategy_InvalidBoardAnimations_ValidNullObjectReturnedAndAsserts)
{
    constexpr cxgui::BoardAnimation invalidBoardAnimation = static_cast<cxgui::BoardAnimation>(-1);
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), invalidBoardAnimation);

    ASSERT_ASSERTION_FAILED(*this);
    ASSERT_TRUE(strategy);
}

/**************************************************************************************************
 * Unit tests for the "Move chip left one column" strategy.
 *
 *************************************************************************************************/
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveLeftOneColumnAnimationStart_AnimationInfoUpdated)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(widthInfo.m_currentDisplacement.Get() == 0.0);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == std::nullopt);

    // We check the column was not updated, since the animation is not completed:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});

    // We check the chip location has been updated appropriately:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, -1.25);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check how the width animation information was updated:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 1.25);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveLeftOneColumnAnimationStart_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == std::nullopt);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_TRUE(WasAddChipDisplacementCalledOnModel());
    ASSERT_FALSE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_FALSE(WasSyncCalledOnPresenter());
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveLeftOneColumnAnimationEnd_AnimationInfoUpdatedAndNotificationReturned)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(widthInfo.m_currentDisplacement.Get() == 10.0);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN);

    // We check the column was updated:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{3u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check the width animation information was reset:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveLeftOneColumnAnimationEnd_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_FALSE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_FALSE(WasSyncCalledOnPresenter());
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveLeftOneColumnAnimationEndFarLeft_AnimationInfoUpdatedAndNotificationReturned)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{0u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{0u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(widthInfo.m_currentDisplacement.Get() == 10.0);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN);

    // We check the column was updated:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{6u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check the width animation information was reset:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveLeftOneColumnAnimationEndFarLeft_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{0u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_LEFT_ONE_COLUMN);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_FALSE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_FALSE(WasSyncCalledOnPresenter());
}


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
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_RedoDropChip_AnimationInfoUpdated)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::REDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unusedH, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, unusedH);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REDO_DROP_CHIP);

    // We check the column was reset:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{0u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_RedoDropChip_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::REDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unusedH, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, unusedH);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REDO_DROP_CHIP);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_TRUE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_TRUE(WasSyncCalledOnPresenter());
}

/**************************************************************************************************
 * Unit tests for the "Reinitialize" strategy.
 *
 *************************************************************************************************/
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_Resize_AnimationInfoUpdated)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::REINITIALIZE);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unusedH, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, unusedH);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REINITIALIZE_BOARD);

    // We check the column was reset:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{0u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_Reinitialize_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::REINITIALIZE);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unusedH, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, unusedH);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_REINITIALIZE_BOARD);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_TRUE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_TRUE(WasSyncCalledOnPresenter());
}
