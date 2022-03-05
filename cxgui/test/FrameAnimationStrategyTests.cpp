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
#include <utility>

#include <cxunit/StdStreamRedirector.h>
#include <cxgui/BoardAnimation.h>
#include <cxgui/BoardAnimationNotificationContext.h>
#include <cxgui/FrameAnimationStrategy.h>
#include <cxgui/IAnimatedBoardPresenter.h>

#include "AnimatedBoardModelMock.h"
#include "AnimatedBoardPresenterMock.h"

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
    void SetCellDimensionsOnModel(const cxmath::Dimensions& p_cellDimensions);

    [[nodiscard]] bool WasUpdateCalledOnModel() const {return m_model->WasUpdateCalled();}
    [[nodiscard]] bool WasResizeCalledOnModel() const {return m_model->WasResizeCalled();}
    [[nodiscard]] bool WasAddChipDisplacementCalledOnModel() const {return m_model->WasAddChipDisplacementCalled();}
    [[nodiscard]] bool WasResetChipPositionsCalledOnModel() const {return m_model->WasResetChipPositionsCalled();}
    [[nodiscard]] bool WasUpdateCurrentColumnCalledOnModel() const {return m_model->WasUpdateCurrentColumnCalled();}

    // Presenter:
    cxgui::IAnimatedBoardPresenter& GetPresenter();

    void SetBoardDimensionsOnPresenter(const cxmodel::Height& p_nbRows, const cxmodel::Width& p_nbColumns);
    void AddChipsToColumnOnPresenter(const cxmodel::Column& p_column, size_t p_nbOfChipsToAdd);

    [[nodiscard]] bool WasSyncCalledOnPresenter() const {return m_presenter->WasSyncCalled();}

    // Helpers:
    using BothAnimationInformations = std::pair<cxgui::AnimationInformations<cxmath::Height>, cxgui::AnimationInformations<cxmath::Width>>;

    BothAnimationInformations MakeAnimationInformations(const cxmath::Height& p_verticalCurrentDisplacement, const cxmath::Width& p_horizontalCurrentDisplacement);
    void ConfigureModelAndPresenter(const cxmodel::Height& p_boardHeight, const cxmodel::Width& p_boardWidth, const cxmodel::Column& p_currantColumn);

private:

    std::unique_ptr<AnimatedBoardModelMock> m_model;
    std::unique_ptr<AnimatedBoardPresenterMock> m_presenter;

};

ADD_STREAM_REDIRECTORS(FrameAnimationTestFixture);

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
    m_model->SetCurrentColumn(p_currentColumn);
}

void FrameAnimationTestFixture::SetCellDimensionsOnModel(const cxmath::Dimensions& p_cellDimensions)
{
    m_model->SetCellDimensions(p_cellDimensions);
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

void FrameAnimationTestFixture::AddChipsToColumnOnPresenter(const cxmodel::Column& p_column, size_t p_nbOfChipsToAdd)
{
    EXPECT_TRUE(p_column.Get() < m_presenter->GetBoardWidth().Get());

    m_presenter->AddChipsToColumn(p_column, p_nbOfChipsToAdd);
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

    const cxmath::Dimensions cellDimensions{cxmath::Height{10.0}, cxmath::Width{10.0}};
    SetCellDimensionsOnModel(cellDimensions);

    const double widgetHeight = (p_boardHeight.Get() + 1u) * cellDimensions.m_height.Get();
    const double widgetWidth = (p_boardWidth.Get()) * cellDimensions.m_width.Get();
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

/**************************************************************************************************
 * Unit tests for the null strategy object.
 *
 *************************************************************************************************/
TEST_F(FrameAnimationTestFixtureStdErrStreamRedirector, /*DISABLED_*/CreateFrameAnimationStrategy_InvalidBoardAnimation_ValidNullObjectReturnedAndAsserts)
{
    constexpr cxgui::BoardAnimation invalidBoardAnimation = static_cast<cxgui::BoardAnimation>(-1);
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), invalidBoardAnimation);

    ASSERT_ASSERTION_FAILED(*this);
    ASSERT_TRUE(strategy);
}

TEST_F(FrameAnimationTestFixtureStdErrStreamRedirector, /*DISABLED_*/CreateFrameAnimationStrategy_InvalidBoardAnimation_NothingUpdated)
{
    // We create the strategy:
    constexpr cxgui::BoardAnimation invalidBoardAnimation = static_cast<cxgui::BoardAnimation>(-1);
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(), GetPresenter(), invalidBoardAnimation);
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

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check how the width animation information was not updated:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 0.0);
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
    ASSERT_FALSE(WasUpdateCurrentColumnCalledOnModel());

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
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveRightOneColumnAnimationStart_AnimationInfoUpdated)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
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
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 1.25);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check how the width animation information was updated:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 1.25);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveRightOneColumnAnimationStart_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
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
    ASSERT_FALSE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_FALSE(WasSyncCalledOnPresenter());
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveRightOneColumnAnimationEnd_AnimationInfoUpdatedAndNotificationReturned)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(widthInfo.m_currentDisplacement.Get() == 10.0);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN);

    // We check the column was updated:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{5u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check the width animation information was reset:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveRightOneColumnAnimationEnd_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_FALSE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_TRUE(WasSyncCalledOnPresenter());
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveRightOneColumnAnimationEndFarLeft_AnimationInfoUpdatedAndNotificationReturned)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{6u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{6u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(widthInfo.m_currentDisplacement.Get() == 10.0);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN);

    // We check the column was updated:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{0u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check the width animation information was reset:
    ASSERT_DOUBLE_EQ(widthInfo.m_currentDisplacement.Get(), 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_MoveRightOneColumnAnimationEndFarLeft_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unused, widthInfo] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{10.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{6u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(widthInfo, unused);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_MOVE_RIGHT_ONE_COLUMN);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_FALSE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_TRUE(WasSyncCalledOnPresenter());
}

/**************************************************************************************************
 * Unit tests for the "Drop chip" strategy.
 *
 *************************************************************************************************/
struct DropChipStartAnimationData
{
    size_t m_nbOfChipsInBoard;
    double m_currentDisplacement;

    DropChipStartAnimationData(size_t p_nbOfChipsInBoard, double p_currentDisplacement)
    : m_nbOfChipsInBoard{p_nbOfChipsInBoard}
    , m_currentDisplacement{p_currentDisplacement}
    {}
};

class FrameAnimationTestFixtureForDropChipStartAnimation : public FrameAnimationTestFixture,
                                                           public testing::WithParamInterface<DropChipStartAnimationData>
{
};

std::vector<DropChipStartAnimationData> MakeDropChipStartAnimationData()
{
    return
        {
            {0u, 7.5},
            {1u, 7.1428571428571432},
            {2u, 6.666666666666667},
            {3u, 7.5},
            {4u, 6.666666666666667},
            {5u, 5.0},
        };
}

INSTANTIATE_TEST_SUITE_P(DropChipStartAnimation,
                         FrameAnimationTestFixtureForDropChipStartAnimation,
                         testing::ValuesIn(MakeDropChipStartAnimationData()));

TEST_P(FrameAnimationTestFixtureForDropChipStartAnimation, /*DISABLED_*/CreateFrameAnimationStrategy_DropChipAnimationStartWithChipsIn_AnimationInfoUpdatedAndNotificationReturned)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [heightInfo, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We add three chips to the board:
    AddChipsToColumnOnPresenter(cxmodel::Column{4u}, GetParam().m_nbOfChipsInBoard);

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(heightInfo.m_currentDisplacement.Get() == 0.0);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, heightInfo);
    ASSERT_TRUE(notification == std::nullopt);

    // We check the column was not updated, since the animation is not completed:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});

    // We check the chip location has been updated appropriately:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, GetParam().m_currentDisplacement);

    // We check how the width animation information was updated:
    ASSERT_DOUBLE_EQ(heightInfo.m_currentDisplacement.Get(), GetParam().m_currentDisplacement);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_DropChipAnimationStart_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [heightInfo, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, heightInfo);
    ASSERT_TRUE(notification == std::nullopt);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_TRUE(WasAddChipDisplacementCalledOnModel());
    ASSERT_FALSE(WasResetChipPositionsCalledOnModel());
    ASSERT_FALSE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_FALSE(WasSyncCalledOnPresenter());
}

struct DropChipEndAnimationData
{
    size_t m_nbOfChipsInBoard;
    double m_animationFullHeight;

    DropChipEndAnimationData(size_t p_nbOfChipsInBoard, double p_animationFullHeight)
    : m_nbOfChipsInBoard{p_nbOfChipsInBoard}
    , m_animationFullHeight{p_animationFullHeight}
    {}
};

class FrameAnimationTestFixtureForDropChipEndAnimation : public FrameAnimationTestFixture,
                                                         public testing::WithParamInterface<DropChipEndAnimationData>
{
};

std::vector<DropChipEndAnimationData> MakeDropChipEndAnimationData()
{
    return
        {
            {0u, 60.0},
            {1u, 50.0},
            {2u, 40.0}, 
            {3u, 30.0},
            {4u, 20.0},
            {5u, 10.0},
        };
}

INSTANTIATE_TEST_SUITE_P(DropChipEndAnimation,
                         FrameAnimationTestFixtureForDropChipEndAnimation,
                         testing::ValuesIn(MakeDropChipEndAnimationData()));


TEST_P(FrameAnimationTestFixtureForDropChipEndAnimation, /*DISABLED_*/CreateFrameAnimationStrategy_DropChipAnimationEnd_AnimationInfoUpdatedAndNotificationReturned)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [heightInfo, unusedW] = MakeAnimationInformations(cxmath::Height{GetParam().m_animationFullHeight}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We add three chips to the board:
    AddChipsToColumnOnPresenter(cxmodel::Column{4u}, GetParam().m_nbOfChipsInBoard);

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));
    ASSERT_TRUE(heightInfo.m_currentDisplacement.Get() == GetParam().m_animationFullHeight);

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, heightInfo);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP);

    // We check the column was not updated, since the animation is not completed:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{0u});

    // We check the chip location has been updated appropriately:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);

    // We check how the width animation information was updated:
    ASSERT_DOUBLE_EQ(heightInfo.m_currentDisplacement.Get(), 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_DropChipAnimationEnd_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [heightInfo, unusedW] = MakeAnimationInformations(cxmath::Height{60.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, heightInfo);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_DROP_CHIP);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_TRUE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_TRUE(WasSyncCalledOnPresenter());
}

/**************************************************************************************************
 * Unit tests for the "Undo drop chip" strategy.
 *
 *************************************************************************************************/
TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_UndoDropChip_AnimationInfoUpdated)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::UNDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unusedH, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{4u});
    ASSERT_TRUE((GetModel().GetChipPosition() == cxmath::Position{0.0, 0.0}));

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, unusedH);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_UNDO_DROP_CHIP);

    // We check the column was reset:
    ASSERT_TRUE(GetModel().GetCurrentColumn() == cxmodel::Column{0u});

    // We check the chip location has not been updated:
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_x, 0.0);
    ASSERT_DOUBLE_EQ(GetModel().GetChipPosition().m_y, 0.0);
}

TEST_F(FrameAnimationTestFixture, /*DISABLED_*/CreateFrameAnimationStrategy_UndoDropChip_AppropriateMethodsCalled)
{
    // We create the strategy:
    auto strategy = cxgui::CreateFrameAnimationStrategy(GetModel(),
                                                        GetPresenter(),
                                                        cxgui::BoardAnimation::UNDO_DROP_CHIP);
    ASSERT_TRUE(strategy);

    // We set up initial conditions:
    auto [unusedH, unusedW] = MakeAnimationInformations(cxmath::Height{0.0}, cxmath::Width{0.0});
    ConfigureModelAndPresenter(cxmodel::Height{6u}, cxmodel::Width{7u}, cxmodel::Column{4u});

    // We run the strategy:
    const auto notification = strategy->PerformAnimation(unusedW, unusedH);
    ASSERT_TRUE(notification == cxgui::BoardAnimationNotificationContext::POST_ANIMATE_UNDO_DROP_CHIP);

    // We check what model and presenter methods were called:
    ASSERT_FALSE(WasUpdateCalledOnModel());
    ASSERT_FALSE(WasResizeCalledOnModel());
    ASSERT_FALSE(WasAddChipDisplacementCalledOnModel());
    ASSERT_TRUE(WasResetChipPositionsCalledOnModel());
    ASSERT_TRUE(WasUpdateCurrentColumnCalledOnModel());

    ASSERT_TRUE(WasSyncCalledOnPresenter());
}

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
