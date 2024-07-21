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
 * @file AnimatedBoardModelTests.cpp
 * @date 2021
 *
 *************************************************************************************************/

#include <functional>
#include <limits>

#include <gtest/gtest.h>

#include <cxunit/StdStreamRedirector.h>
#include <cxmath/math.h>
#include <cxgui/AnimatedBoardModel.h>
#include <cxgui/IAnimatedBoardPresenter.h>

namespace
{

constexpr bool CHIP_IS_MOVING_HORIZONTALLY = true;
constexpr bool CHIP_IS_NOT_MOVING_HORIZONTALLY = false;

// Represents model elements that are not synched:
constexpr unsigned int NONE                 = 0x00;

constexpr unsigned int FPS                  = 0x01 << 0;
constexpr unsigned int SPEED                = 0x01 << 1;
constexpr unsigned int AREA_DIMENSIONS      = 0x01 << 2;
constexpr unsigned int CELL_DIMENSIONS      = 0x01 << 3;
constexpr unsigned int CHIP_RADIUS          = 0x01 << 5;
constexpr unsigned int CHIP_POSITION        = 0x01 << 6;
constexpr unsigned int HORIZONTAL_MARGIN    = 0x01 << 7;
constexpr unsigned int MIRROR_CHIP_POSITION = 0x01 << 8;
constexpr unsigned int IS_MIRROR_NEEDED     = 0x01 << 9;
constexpr unsigned int CELL_LINE_WIDTH      = 0x01 << 10;
constexpr unsigned int CHIP_LINE_WIDTH      = 0x01 << 10;
constexpr unsigned int CURRENT_COLUMN       = 0x01 << 11;

using ModelOperations = std::function<void(cx::gui::IAnimatedBoardModel&)>;
using NotSynced = unsigned int;

NotSynced Validate(cx::gui::IAnimatedBoardModel& p_model, const ModelOperations& p_operations)
{
    // Pre-operation(s) values:
    const cx::gui::FPS fpsBefore                            = p_model.GetFPS();
    const cx::gui::AnimationSpeed speedBefore               = p_model.GetAnimationSpeed();
    const cx::math::Dimensions animatedAreaDimensionsBefore = p_model.GetAnimatedAreaDimensions();
    const cx::math::Dimensions cellDimensionsBefore         = p_model.GetCellDimensions();
    const cx::math::Radius chipRadiusBefore                 = p_model.GetChipRadius();
    const cx::math::Position chipPositionBefore             = p_model.GetChipPosition();
    const cx::math::Width horizontalMarginBefore            = p_model.GetHorizontalMargin();
    const cx::math::Position mirrorChipPositionBefore       = p_model.GetMirrorChipPosition();
    const bool mirrorNeededBefore                         = p_model.IsMirrorChipNeeded();
    const cx::math::Width cellLineWidthBefore               = p_model.GetLineWidth(cx::gui::Feature::CELL);
    const cx::math::Width chipLineWidthBefore               = p_model.GetLineWidth(cx::gui::Feature::CHIP);
    const cxmodel::Column currentColumnBefore             = p_model.GetCurrentColumn();

    // Operation(s) performed on the model:
    EXPECT_TRUE(p_operations);
    p_operations(p_model);

    // Post-operation(s) values:
    const cx::gui::FPS fpsAfter                            = p_model.GetFPS();
    const cx::gui::AnimationSpeed speedAfter               = p_model.GetAnimationSpeed();
    const cx::math::Dimensions animatedAreaDimensionsAfter = p_model.GetAnimatedAreaDimensions();
    const cx::math::Dimensions cellDimensionsAfter         = p_model.GetCellDimensions();
    const cx::math::Radius chipRadiusAfter                 = p_model.GetChipRadius();
    const cx::math::Position chipPositionAfter             = p_model.GetChipPosition();
    const cx::math::Width horizontalMarginAfter            = p_model.GetHorizontalMargin();
    const cx::math::Position mirrorChipPositionAfter       = p_model.GetMirrorChipPosition();
    const bool mirrorNeededAfter                         = p_model.IsMirrorChipNeeded();
    const cx::math::Width cellLineWidthAfter               = p_model.GetLineWidth(cx::gui::Feature::CELL);
    const cx::math::Width chipLineWidthAfter               = p_model.GetLineWidth(cx::gui::Feature::CHIP);
    const cxmodel::Column currentColumnAfter             = p_model.GetCurrentColumn();

    // Comparing the two:
    NotSynced syncResult = NONE;

    if(fpsBefore != fpsAfter)                                        syncResult |= FPS;
    if(speedBefore != speedAfter)                                    syncResult |= SPEED;
    if(animatedAreaDimensionsBefore != animatedAreaDimensionsAfter)  syncResult |= AREA_DIMENSIONS;
    if(cellDimensionsBefore != cellDimensionsAfter)                  syncResult |= CELL_DIMENSIONS;
    if(chipRadiusBefore != chipRadiusAfter)                          syncResult |= CHIP_RADIUS;
    if(chipPositionBefore != chipPositionAfter)                      syncResult |= CHIP_POSITION;
    if(horizontalMarginBefore != horizontalMarginAfter)              syncResult |= HORIZONTAL_MARGIN;
    if(mirrorChipPositionBefore != mirrorChipPositionAfter)          syncResult |= MIRROR_CHIP_POSITION;
    if(mirrorNeededBefore != mirrorNeededAfter)                      syncResult |= IS_MIRROR_NEEDED;
    if(cellLineWidthBefore != cellLineWidthAfter)                    syncResult |= CELL_LINE_WIDTH;
    if(chipLineWidthBefore != chipLineWidthAfter)                    syncResult |= CHIP_LINE_WIDTH;
    if(currentColumnBefore != currentColumnAfter)                    syncResult |= CURRENT_COLUMN;

    return syncResult;
}

// Printers (used for better readibility in unit test reports):
template<typename T>
void PrintType([[maybe_unused]] std::ostream& p_stream, [[maybe_unused]] const T& p_value)
{
    FAIL() << "Printer not defined for this type";
}

template<typename T>
std::string Debug(const T& p_value)
{
    std::ostringstream ss;
    ss.precision(std::numeric_limits<double>::max_digits10);
    ss << "DEBUG - Actual value : ";
    PrintType(ss, p_value);

    return ss.str();
}

template<>
void PrintType<cx::math::Position>(std::ostream& p_stream, const cx::math::Position& p_value)
{
    p_stream << "("  << p_value.m_x << ", " << p_value.m_y << ")";
}

template<>
void PrintType<cx::math::Radius>(std::ostream& p_stream, const cx::math::Radius& p_value)
{
    p_stream << std::to_string(p_value.Get());
}

// Mocks:
class AnimatedBoardPresenterMock : public cx::gui::IAnimatedBoardPresenter
{

public:

    // cx::gui::IAnimatedBoardPresenter:
    void Sync() override {FAIL();}
    [[nodiscard]] cxmodel::Height GetBoardHeight() const override {return cxmodel::Height{6u};}
    [[nodiscard]] cxmodel::Width GetBoardWidth() const override {return cxmodel::Width{7u};}
    [[nodiscard]] cx::gui::Color GetGameViewBoardColor() const override {return cx::gui::Color{8481u, 8481u, 51143u};}
    [[nodiscard]] cx::gui::Color GetGameViewColumnHighlightColor() const override {return cx::gui::Color{19660u, 19660u, 19660u, 32767u};}
    [[nodiscard]] cxmodel::ChipColor GetActivePlayerChipColor() const override {return cxmodel::MakeRed();}
    [[nodiscard]] const cx::gui::IGameViewPresenter::ChipColors& GetBoardChipColors() const override {return m_chipColors;}
    [[nodiscard]] cxmodel::Column GetBotTarget() const {return cxmodel::Column{5u};}

    // Configuration:

private:

    cx::gui::IGameViewPresenter::ChipColors m_chipColors;

};

class AnimationModelTestFixture : public ::testing::Test
{

public:

    AnimationModelTestFixture()
    {
        m_presenter = std::make_unique<AnimatedBoardPresenterMock>();
        EXPECT_TRUE(m_presenter);

        m_model = std::make_unique<cx::gui::AnimatedBoardModel>(*m_presenter, cx::gui::AnimationSpeed{3u});
        EXPECT_TRUE(m_model);
    }

    cx::gui::IAnimatedBoardModel& GetModel()
    {
        EXPECT_TRUE(m_model);
        return *m_model;
    }

private:

    std::unique_ptr<cx::gui::IAnimatedBoardPresenter> m_presenter;
    std::unique_ptr<cx::gui::IAnimatedBoardModel> m_model;

};

} // namespace

ADD_STREAM_REDIRECTORS(AnimationModelTestFixture);

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Constructor_ValidInput_DoesNotAssert)
{
    auto presenter = std::make_unique<AnimatedBoardPresenterMock>();
    ASSERT_TRUE(presenter);

    cx::unit::DisableStdStreamsRAII streamDisabler;
    const cx::gui::AnimatedBoardModel model{*presenter, cx::gui::AnimationSpeed{3u}};
    const std::string streamContents = streamDisabler.GetStdErrContents();

    ASSERT_TRUE(streamContents.empty());
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Update_ValidInput_UpdatesAnimationData)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);
                                  });

    // Comparing the two:
    ASSERT_TRUE(whatChanged == (AREA_DIMENSIONS      |
                                CELL_DIMENSIONS      |
                                CHIP_RADIUS          |
                                CHIP_POSITION        |
                                HORIZONTAL_MARGIN    |
                                MIRROR_CHIP_POSITION |
                                IS_MIRROR_NEEDED     |
                                CELL_LINE_WIDTH      |
                                CHIP_LINE_WIDTH)
    );
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Update_InvalidWidgetHeight_NothingUpdatedAndAsserts)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cx::math::Height{-100}, cx::math::Width{150}}, true);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Update_InvalidWidgetWidth_NothingUpdatedAndAsserts)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cx::math::Height{100}, cx::math::Width{-150}}, true);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Resize_ValidAndHorizontal_ResizingOccured)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);
    model.AddChipDisplacement(cx::math::Height{1.0}, cx::math::Width{1.0});
    const cx::math::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      const cx::gui::ScalingRatios ratios{cx::gui::HorizontalScalingRatio{2.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cx::math::Position chipPositionAfter = model.GetChipPosition();

    ASSERT_TRUE(cx::math::AreLogicallyEqual(2.0 * chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Resize_ValidAndVertical_ResizingOccured)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);
    model.AddChipDisplacement(cx::math::Height{1.0}, cx::math::Width{1.0});
    const cx::math::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      const cx::gui::ScalingRatios ratios{cx::gui::VerticalScalingRatio{3.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cx::math::Position chipPositionAfter = model.GetChipPosition();

    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cx::math::AreLogicallyEqual(3.0 * chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Resize_InvalidHorizontalRatio_DoesNotResizeAndAsserts)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      const cx::gui::ScalingRatios ratios{cx::gui::HorizontalScalingRatio{-1.0}, cx::gui::VerticalScalingRatio{2.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Resize_InvalidVerticalRatio_DoesNotResizeAndAsserts)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      const cx::gui::ScalingRatios ratios{cx::gui::HorizontalScalingRatio{1.0}, cx::gui::VerticalScalingRatio{-2.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/AddChipDisplacement_HorizontalDisplacement_ChipMovedHorizontally)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.AddChipDisplacement(cx::math::Height{0.0}, cx::math::Width{1.0});
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cx::math::Position chipPositionAfter = model.GetChipPosition();
    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipPositionBefore.m_x + 1.0, chipPositionAfter.m_x));
    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/AddChipDisplacement_VerticalDisplacement_ChipMovedVertically)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.AddChipDisplacement(cx::math::Height{1.0}, cx::math::Width{0.0});
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cx::math::Position chipPositionAfter = model.GetChipPosition();
    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipPositionBefore.m_y + 1.0, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/ResetChipPositions_ValidModel_ChipPositionsReinitialized)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);
    model.AddChipDisplacement(cx::math::Height{1.0}, cx::math::Width{1.0});

    const cx::math::Position chipPositionBefore = model.GetChipPosition();
    const cx::math::Position mirrorChipPositionBefore = model.GetMirrorChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.ResetChipPositions();
                                  });

    ASSERT_TRUE(whatChanged == (CHIP_POSITION | MIRROR_CHIP_POSITION));

    const cx::math::Position chipPositionAfter = model.GetChipPosition();
    ASSERT_TRUE(!cx::math::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(!cx::math::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));

    const cx::math::Radius chipRadius = model.GetChipRadius();
    const cx::math::Width cellMargin = model.GetHorizontalMargin();
    ASSERT_TRUE(chipPositionAfter.m_x == cellMargin.Get() + chipRadius.Get());
    ASSERT_TRUE(chipPositionAfter.m_y == 0.0);

    const cx::math::Position mirrorChipPositionAfter = model.GetMirrorChipPosition();
    ASSERT_TRUE(!cx::math::AreLogicallyEqual(mirrorChipPositionBefore.m_x, mirrorChipPositionAfter.m_x));
    ASSERT_TRUE(!cx::math::AreLogicallyEqual(mirrorChipPositionBefore.m_y, mirrorChipPositionAfter.m_y));

    ASSERT_TRUE(mirrorChipPositionAfter.m_x == cellMargin.Get() + chipRadius.Get());
    ASSERT_TRUE(mirrorChipPositionAfter.m_y == 0.0);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/UpdateCurrentColumn_NewColumIndex_ColumnUpdated)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cxmodel::Column currentColumnBefore = model.GetCurrentColumn();
    ASSERT_TRUE(currentColumnBefore == cxmodel::Column{0u});

    const NotSynced whatChanged = Validate(model,
                                  [](cx::gui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.UpdateCurrentColumn(cxmodel::Column{3u});
                                  });

    ASSERT_TRUE(whatChanged == CURRENT_COLUMN);

    const cxmodel::Column currentColumnAfter = model.GetCurrentColumn();
    ASSERT_TRUE(currentColumnAfter == cxmodel::Column{3u});
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetFPS_ValidModel_FPSReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    ASSERT_TRUE(model.GetFPS() == cx::gui::FPS{24u});
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetAnimationSpeed_ValidModel_AnimationSpeedReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    ASSERT_TRUE(model.GetAnimationSpeed() == cx::gui::AnimationSpeed{3u});
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetAnimatedAreaDimensions)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Dimensions areaDimensionsBeforeUpdate = model.GetAnimatedAreaDimensions();
    ASSERT_TRUE((areaDimensionsBeforeUpdate == cx::math::Dimensions{cx::math::Height{0}, cx::math::Width{0}}));

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Dimensions areaDimensions = model.GetAnimatedAreaDimensions();
    ASSERT_TRUE((areaDimensions == cx::math::Dimensions{cx::math::Height{100}, cx::math::Width{150}}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetCellDimensions_ValidModel_CellDimensionsReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Dimensions cellDimensionsBeforeUpdate = model.GetCellDimensions();
    ASSERT_TRUE((cellDimensionsBeforeUpdate == cx::math::Dimensions{cx::math::Height{0}, cx::math::Width{0}}));

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Dimensions cellDimensionsAfterUpdate = model.GetCellDimensions();
    ASSERT_TRUE((cellDimensionsAfterUpdate == cx::math::Dimensions{cx::math::Height{100.0 / 7.0}, cx::math::Width{150.0 / 7.0}}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipRadius_ValidModel_ChipRadiusReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Radius chipRadiusBeforeUpdate = model.GetChipRadius();
    ASSERT_TRUE(chipRadiusBeforeUpdate == cx::math::Radius{0.0});

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Radius chipRadiusAfterUpdate = model.GetChipRadius();
    ASSERT_TRUE(cx::math::AreLogicallyEqual(chipRadiusAfterUpdate.Get(), 7.1428571428571432)) << Debug(chipRadiusAfterUpdate);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheLeftChipIsMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip is starting at (0,0) and moving, it's horizontal position is not updated:
    ASSERT_TRUE((chipPosition == cx::math::Position{0.0, 7.1428571428571432})) << Debug(chipPosition);

    // Instead, a mirror chip will be added to represent its complement on the other side of the board:
    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{100.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheLeftChipIsNotMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip is starting at (0,0) and it is not moving, an update will
    // make sure it is completely visible to the user:
    ASSERT_TRUE((chipPosition == cx::math::Position{7.1428571428571432, 7.1428571428571432})) << Debug(chipPosition);

    // Also, in this case, no mirror chip will be added (it is only added to simulate
    // continuity across the board limits as animations are performed):
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheLeftChipIsMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cx::math::Height{0.0}, cx::math::Width{-7.1428571428571432});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the left but that it is still moving, 
    // its position is not updated:
    ASSERT_TRUE((chipPosition == cx::math::Position{-7.1428571428571432, 7.1428571428571432})) << Debug(chipPosition);

    // Instead, a mirror chip is added on the other side, fully visible:
    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{92.857142857142861, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheLeftChipIsNotMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cx::math::Height{0.0}, cx::math::Width{-7.1428571428571432});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the left, its position is updated to be
    // at the extreme right side:
    ASSERT_TRUE((chipPosition == cx::math::Position{92.857142857142861, 7.1428571428571432})) << Debug(chipPosition);

    // Since all of it is visible, no mirror chip is needed:
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheRightChipIsNotMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cx::math::Height{0.0}, cx::math::Width{100.0});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // The chip is "clamped" to the right, to make sure all of it is visible:
    ASSERT_TRUE((chipPosition == cx::math::Position{92.857142857142861, 7.1428571428571432})) << Debug(chipPosition);

    // No mirror chip is needed in the case:
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheRightChipIsMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cx::math::Height{0.0}, cx::math::Width{100.0});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip position makes it cross over to the right (half the chip is crossing over),
    // and the chip is moving, a mirror chip is added, on the left side of the board to give
    // the user the illusion of a smooth crossing over animation:
    ASSERT_TRUE((chipPosition == cx::math::Position{100.0, 7.1428571428571432})) << Debug(chipPosition);

    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheRightChipIsMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement( cx::math::Height{0.0}, cx::math::Width{107.1428571428571432});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the right but that it is still moving, 
    // its position is not updated:
    ASSERT_TRUE((chipPosition == cx::math::Position{107.14285714285714, 7.1428571428571432})) << Debug(chipPosition);

    // Instead, a mirror chip is added on the other side, fully visible:
    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{7.1428571428571388, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheRightChipIsNotMoving_ReturnsPosition)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cx::math::Height{0.0}, cx::math::Width{107.1428571428571432});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();
    const cx::math::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the right, its position is updated to be
    // at the extreme left side:
    ASSERT_TRUE((chipPosition == cx::math::Position{7.1428571428571432, 7.1428571428571432})) << Debug(chipPosition);

    // Since all of it is visible, no mirror chip is needed:
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cx::math::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_HorizontalOffsetTowardsTop_PositionIsFixed)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    // Going out of the board (at top):
    model.AddChipDisplacement(cx::math::Height{1.0}, cx::math::Width{50.0});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();

    // Vertical position is "clamped" to the top of the board to make sure the chip is
    // visible to the user:
    ASSERT_TRUE((chipPosition == cx::math::Position{50.0, 7.1428571428571432})) << Debug(chipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_HorizontalOffsetTowardsBottom_PositionIsFixed)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    // Going out of the board (at bottom, remember to bottom is in the positive y):
    model.AddChipDisplacement(cx::math::Height{151.0}, cx::math::Width{50.0});
    model.Update({cx::math::Height{150}, cx::math::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cx::math::Position chipPosition = model.GetChipPosition();

    // Vertical position is "clamped" to the bottom of the board to make sure the chip is
    // visible to the user:
    ASSERT_TRUE((chipPosition == cx::math::Position{50.0, 142.85714285714286})) << Debug(chipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetHorizontalMargin_ValidModel_MarginReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Width horizontalMarginBeforeUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(horizontalMarginBeforeUpdate == cx::math::Width{0.0});

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Width horizontalMarginAfterUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(cx::math::AreLogicallyEqual(horizontalMarginAfterUpdate.Get(), 3.571429)) << Debug(horizontalMarginAfterUpdate);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetHorizontalMargin_ValidModelWidthEqualsHeight_ZeroMarginReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Width horizontalMarginBeforeUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(horizontalMarginBeforeUpdate == cx::math::Width{0.0});

    model.Update({cx::math::Height{150}, cx::math::Width{150}}, true);

    const cx::math::Width horizontalMarginAfterUpdate = model.GetHorizontalMargin();

    // There is no margin since both dimensions are the same!
    ASSERT_TRUE(horizontalMarginAfterUpdate.Get() == 0.0) << Debug(horizontalMarginAfterUpdate);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetCellLineWidth_ValidModel_CellLineWidthReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Width lineWidthBeforeUpdate = model.GetLineWidth(cx::gui::Feature::CELL);
    ASSERT_TRUE(lineWidthBeforeUpdate == cx::math::Width{0.0});

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Width lineWidthAfterUpdate = model.GetLineWidth(cx::gui::Feature::CELL);
    ASSERT_TRUE(cx::math::AreLogicallyEqual(lineWidthAfterUpdate.Get(), 0.5));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipLineWidth_ValidModel_ChipLineWidthReturned)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::math::Width lineWidthBeforeUpdate = model.GetLineWidth(cx::gui::Feature::CHIP);
    ASSERT_TRUE(lineWidthBeforeUpdate == cx::math::Width{0.0});

    model.Update({cx::math::Height{100}, cx::math::Width{150}}, true);

    const cx::math::Width lineWidthAfterUpdate = model.GetLineWidth(cx::gui::Feature::CHIP);
    ASSERT_TRUE(cx::math::AreLogicallyEqual(lineWidthAfterUpdate.Get(), 0.035714285714285719));
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/GetUnknownLineWidth_ValidModel_ZeroReturnedAndAssert)
{
    cx::gui::IAnimatedBoardModel& model = GetModel();

    const cx::gui::Feature invalid = static_cast<cx::gui::Feature>(-1);

    const cx::math::Width invalidLineWidth = model.GetLineWidth(invalid);
    ASSERT_TRUE(invalidLineWidth == cx::math::Width{0.0});

    ASSERT_ASSERTION_FAILED(*this);
}
