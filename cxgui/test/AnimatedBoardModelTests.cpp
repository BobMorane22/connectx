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

using ModelOperations = std::function<void(cxgui::IAnimatedBoardModel&)>;
using NotSynced = unsigned int;

NotSynced Validate(cxgui::IAnimatedBoardModel& p_model, const ModelOperations& p_operations)
{
    // Pre-operation(s) values:
    const cxgui::FPS fpsBefore                            = p_model.GetFPS();
    const cxgui::AnimationSpeed speedBefore               = p_model.GetAnimationSpeed();
    const cxmath::Dimensions animatedAreaDimensionsBefore = p_model.GetAnimatedAreaDimensions();
    const cxmath::Dimensions cellDimensionsBefore         = p_model.GetCellDimensions();
    const cxmath::Radius chipRadiusBefore                 = p_model.GetChipRadius();
    const cxmath::Position chipPositionBefore             = p_model.GetChipPosition();
    const cxmath::Width horizontalMarginBefore            = p_model.GetHorizontalMargin();
    const cxmath::Position mirrorChipPositionBefore       = p_model.GetMirrorChipPosition();
    const bool mirrorNeededBefore                         = p_model.IsMirrorChipNeeded();
    const cxmath::Width cellLineWidthBefore               = p_model.GetLineWidth(cxgui::Feature::CELL);
    const cxmath::Width chipLineWidthBefore               = p_model.GetLineWidth(cxgui::Feature::CHIP);
    const cxmodel::Column currentColumnBefore             = p_model.GetCurrentColumn();

    // Operation(s) performed on the model:
    EXPECT_TRUE(p_operations);
    p_operations(p_model);

    // Post-operation(s) values:
    const cxgui::FPS fpsAfter                            = p_model.GetFPS();
    const cxgui::AnimationSpeed speedAfter               = p_model.GetAnimationSpeed();
    const cxmath::Dimensions animatedAreaDimensionsAfter = p_model.GetAnimatedAreaDimensions();
    const cxmath::Dimensions cellDimensionsAfter         = p_model.GetCellDimensions();
    const cxmath::Radius chipRadiusAfter                 = p_model.GetChipRadius();
    const cxmath::Position chipPositionAfter             = p_model.GetChipPosition();
    const cxmath::Width horizontalMarginAfter            = p_model.GetHorizontalMargin();
    const cxmath::Position mirrorChipPositionAfter       = p_model.GetMirrorChipPosition();
    const bool mirrorNeededAfter                         = p_model.IsMirrorChipNeeded();
    const cxmath::Width cellLineWidthAfter               = p_model.GetLineWidth(cxgui::Feature::CELL);
    const cxmath::Width chipLineWidthAfter               = p_model.GetLineWidth(cxgui::Feature::CHIP);
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
void PrintType<cxmath::Position>(std::ostream& p_stream, const cxmath::Position& p_value)
{
    p_stream << "("  << p_value.m_x << ", " << p_value.m_y << ")";
}

template<>
void PrintType<cxmath::Radius>(std::ostream& p_stream, const cxmath::Radius& p_value)
{
    p_stream << std::to_string(p_value.Get());
}

// Mocks:
class AnimatedBoardPresenterMock : public cxgui::IAnimatedBoardPresenter
{

public:

    // cxgui::IAnimatedBoardPresenter:
    void Sync() override {FAIL();}
    [[nodiscard]] cxmodel::Height GetBoardHeight() const override {return cxmodel::Height{6u};}
    [[nodiscard]] cxmodel::Width GetBoardWidth() const override {return cxmodel::Width{7u};}
    [[nodiscard]] cxgui::Color GetGameViewBoardColor() const override {return cxgui::Color{8481u, 8481u, 51143u};}
    [[nodiscard]] cxgui::Color GetGameViewColumnHighlightColor() const override {return cxgui::Color{19660u, 19660u, 19660u, 32767u};}
    [[nodiscard]] cxmodel::ChipColor GetActivePlayerChipColor() const override {return cxmodel::MakeRed();}
    [[nodiscard]] const cxgui::IGameViewPresenter::ChipColors& GetBoardChipColors() const override {return m_chipColors;}
    [[nodiscard]] cxmodel::Column GetBotTarget() const {return cxmodel::Column{5u};}

    // Configuration:

private:

    cxgui::IGameViewPresenter::ChipColors m_chipColors;

};

class AnimationModelTestFixture : public ::testing::Test
{

public:

    AnimationModelTestFixture()
    {
        m_presenter = std::make_unique<AnimatedBoardPresenterMock>();
        EXPECT_TRUE(m_presenter);

        m_model = std::make_unique<cxgui::AnimatedBoardModel>(*m_presenter, cxgui::AnimationSpeed{3u});
        EXPECT_TRUE(m_model);
    }

    cxgui::IAnimatedBoardModel& GetModel()
    {
        EXPECT_TRUE(m_model);
        return *m_model;
    }

private:

    std::unique_ptr<cxgui::IAnimatedBoardPresenter> m_presenter;
    std::unique_ptr<cxgui::IAnimatedBoardModel> m_model;

};

} // namespace

ADD_STREAM_REDIRECTORS(AnimationModelTestFixture);

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Constructor_ValidInput_DoesNotAssert)
{
    auto presenter = std::make_unique<AnimatedBoardPresenterMock>();
    ASSERT_TRUE(presenter);

    cxunit::DisableStdStreamsRAII streamDisabler;
    const cxgui::AnimatedBoardModel model{*presenter, cxgui::AnimationSpeed{3u}};
    const std::string streamContents = streamDisabler.GetStdErrContents();

    ASSERT_TRUE(streamContents.empty());
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Update_ValidInput_UpdatesAnimationData)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);
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
    cxgui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cxmath::Height{-100}, cxmath::Width{150}}, true);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Update_InvalidWidgetWidth_NothingUpdatedAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cxmath::Height{100}, cxmath::Width{-150}}, true);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Resize_ValidAndHorizontal_ResizingOccured)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);
    model.AddChipDisplacement(cxmath::Height{1.0}, cxmath::Width{1.0});
    const cxmath::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      const cxgui::ScalingRatios ratios{cxgui::HorizontalScalingRatio{2.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cxmath::Position chipPositionAfter = model.GetChipPosition();

    ASSERT_TRUE(cxmath::AreLogicallyEqual(2.0 * chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Resize_ValidAndVertical_ResizingOccured)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);
    model.AddChipDisplacement(cxmath::Height{1.0}, cxmath::Width{1.0});
    const cxmath::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      const cxgui::ScalingRatios ratios{cxgui::VerticalScalingRatio{3.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cxmath::Position chipPositionAfter = model.GetChipPosition();

    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(3.0 * chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Resize_InvalidHorizontalRatio_DoesNotResizeAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      const cxgui::ScalingRatios ratios{cxgui::HorizontalScalingRatio{-1.0}, cxgui::VerticalScalingRatio{2.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Resize_InvalidVerticalRatio_DoesNotResizeAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      const cxgui::ScalingRatios ratios{cxgui::HorizontalScalingRatio{1.0}, cxgui::VerticalScalingRatio{-2.0}};
                                      p_model.Resize(ratios);
                                  });

    ASSERT_TRUE(whatChanged == NONE);
    ASSERT_PRECONDITION_FAILED(*this);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/AddChipDisplacement_HorizontalDisplacement_ChipMovedHorizontally)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.AddChipDisplacement(cxmath::Height{0.0}, cxmath::Width{1.0});
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cxmath::Position chipPositionAfter = model.GetChipPosition();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_x + 1.0, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/AddChipDisplacement_VerticalDisplacement_ChipMovedVertically)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Position chipPositionBefore = model.GetChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.AddChipDisplacement(cxmath::Height{1.0}, cxmath::Width{0.0});
                                  });

    ASSERT_TRUE(whatChanged == CHIP_POSITION);

    const cxmath::Position chipPositionAfter = model.GetChipPosition();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_y + 1.0, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/ResetChipPositions_ValidModel_ChipPositionsReinitialized)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);
    model.AddChipDisplacement(cxmath::Height{1.0}, cxmath::Width{1.0});

    const cxmath::Position chipPositionBefore = model.GetChipPosition();
    const cxmath::Position mirrorChipPositionBefore = model.GetMirrorChipPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.ResetChipPositions();
                                  });

    ASSERT_TRUE(whatChanged == (CHIP_POSITION | MIRROR_CHIP_POSITION));

    const cxmath::Position chipPositionAfter = model.GetChipPosition();
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));

    const cxmath::Radius chipRadius = model.GetChipRadius();
    const cxmath::Width cellMargin = model.GetHorizontalMargin();
    ASSERT_TRUE(chipPositionAfter.m_x == cellMargin.Get() + chipRadius.Get());
    ASSERT_TRUE(chipPositionAfter.m_y == 0.0);

    const cxmath::Position mirrorChipPositionAfter = model.GetMirrorChipPosition();
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(mirrorChipPositionBefore.m_x, mirrorChipPositionAfter.m_x));
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(mirrorChipPositionBefore.m_y, mirrorChipPositionAfter.m_y));

    ASSERT_TRUE(mirrorChipPositionAfter.m_x == cellMargin.Get() + chipRadius.Get());
    ASSERT_TRUE(mirrorChipPositionAfter.m_y == 0.0);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/UpdateCurrentColumn_NewColumIndex_ColumnUpdated)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmodel::Column currentColumnBefore = model.GetCurrentColumn();
    ASSERT_TRUE(currentColumnBefore == cxmodel::Column{0u});

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.UpdateCurrentColumn(cxmodel::Column{3u});
                                  });

    ASSERT_TRUE(whatChanged == CURRENT_COLUMN);

    const cxmodel::Column currentColumnAfter = model.GetCurrentColumn();
    ASSERT_TRUE(currentColumnAfter == cxmodel::Column{3u});
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetFPS_ValidModel_FPSReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    ASSERT_TRUE(model.GetFPS() == cxgui::FPS{24u});
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetAnimationSpeed_ValidModel_AnimationSpeedReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    ASSERT_TRUE(model.GetAnimationSpeed() == cxgui::AnimationSpeed{3u});
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetAnimatedAreaDimensions)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Dimensions areaDimensionsBeforeUpdate = model.GetAnimatedAreaDimensions();
    ASSERT_TRUE((areaDimensionsBeforeUpdate == cxmath::Dimensions{cxmath::Height{0}, cxmath::Width{0}}));

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Dimensions areaDimensions = model.GetAnimatedAreaDimensions();
    ASSERT_TRUE((areaDimensions == cxmath::Dimensions{cxmath::Height{100}, cxmath::Width{150}}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetCellDimensions_ValidModel_CellDimensionsReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Dimensions cellDimensionsBeforeUpdate = model.GetCellDimensions();
    ASSERT_TRUE((cellDimensionsBeforeUpdate == cxmath::Dimensions{cxmath::Height{0}, cxmath::Width{0}}));

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Dimensions cellDimensionsAfterUpdate = model.GetCellDimensions();
    ASSERT_TRUE((cellDimensionsAfterUpdate == cxmath::Dimensions{cxmath::Height{100.0 / 7.0}, cxmath::Width{150.0 / 7.0}}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipRadius_ValidModel_ChipRadiusReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Radius chipRadiusBeforeUpdate = model.GetChipRadius();
    ASSERT_TRUE(chipRadiusBeforeUpdate == cxmath::Radius{0.0});

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Radius chipRadiusAfterUpdate = model.GetChipRadius();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipRadiusAfterUpdate.Get(), 7.1428571428571432)) << Debug(chipRadiusAfterUpdate);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheLeftChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip is starting at (0,0) and moving, it's horizontal position is not updated:
    ASSERT_TRUE((chipPosition == cxmath::Position{0.0, 7.1428571428571432})) << Debug(chipPosition);

    // Instead, a mirror chip will be added to represent its complement on the other side of the board:
    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{100.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheLeftChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip is starting at (0,0) and it is not moving, an update will
    // make sure it is completely visible to the user:
    ASSERT_TRUE((chipPosition == cxmath::Position{7.1428571428571432, 7.1428571428571432})) << Debug(chipPosition);

    // Also, in this case, no mirror chip will be added (it is only added to simulate
    // continuity across the board limits as animations are performed):
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheLeftChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cxmath::Height{0.0}, cxmath::Width{-7.1428571428571432});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the left but that it is still moving, 
    // its position is not updated:
    ASSERT_TRUE((chipPosition == cxmath::Position{-7.1428571428571432, 7.1428571428571432})) << Debug(chipPosition);

    // Instead, a mirror chip is added on the other side, fully visible:
    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{92.857142857142861, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheLeftChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cxmath::Height{0.0}, cxmath::Width{-7.1428571428571432});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the left, its position is updated to be
    // at the extreme right side:
    ASSERT_TRUE((chipPosition == cxmath::Position{92.857142857142861, 7.1428571428571432})) << Debug(chipPosition);

    // Since all of it is visible, no mirror chip is needed:
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheRightChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cxmath::Height{0.0}, cxmath::Width{100.0});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // The chip is "clamped" to the right, to make sure all of it is visible:
    ASSERT_TRUE((chipPosition == cxmath::Position{92.857142857142861, 7.1428571428571432})) << Debug(chipPosition);

    // No mirror chip is needed in the case:
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheRightChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cxmath::Height{0.0}, cxmath::Width{100.0});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip position makes it cross over to the right (half the chip is crossing over),
    // and the chip is moving, a mirror chip is added, on the left side of the board to give
    // the user the illusion of a smooth crossing over animation:
    ASSERT_TRUE((chipPosition == cxmath::Position{100.0, 7.1428571428571432})) << Debug(chipPosition);

    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheRightChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement( cxmath::Height{0.0}, cxmath::Width{107.1428571428571432});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the right but that it is still moving, 
    // its position is not updated:
    ASSERT_TRUE((chipPosition == cxmath::Position{107.14285714285714, 7.1428571428571432})) << Debug(chipPosition);

    // Instead, a mirror chip is added on the other side, fully visible:
    ASSERT_TRUE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{7.1428571428571388, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheRightChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddChipDisplacement(cxmath::Height{0.0}, cxmath::Width{107.1428571428571432});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorChipPosition();

    // Since the chip has completely crossed to the right, its position is updated to be
    // at the extreme left side:
    ASSERT_TRUE((chipPosition == cxmath::Position{7.1428571428571432, 7.1428571428571432})) << Debug(chipPosition);

    // Since all of it is visible, no mirror chip is needed:
    ASSERT_FALSE(model.IsMirrorChipNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432})) << Debug(mirrorChipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_HorizontalOffsetTowardsTop_PositionIsFixed)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    // Going out of the board (at top):
    model.AddChipDisplacement(cxmath::Height{1.0}, cxmath::Width{50.0});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();

    // Vertical position is "clamped" to the top of the board to make sure the chip is
    // visible to the user:
    ASSERT_TRUE((chipPosition == cxmath::Position{50.0, 7.1428571428571432})) << Debug(chipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_HorizontalOffsetTowardsBottom_PositionIsFixed)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    // Going out of the board (at bottom, remember to bottom is in the positive y):
    model.AddChipDisplacement(cxmath::Height{151.0}, cxmath::Width{50.0});
    model.Update({cxmath::Height{150}, cxmath::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetChipPosition();

    // Vertical position is "clamped" to the bottom of the board to make sure the chip is
    // visible to the user:
    ASSERT_TRUE((chipPosition == cxmath::Position{50.0, 142.85714285714286})) << Debug(chipPosition);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetHorizontalMargin_ValidModel_MarginReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Width horizontalMarginBeforeUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(horizontalMarginBeforeUpdate == cxmath::Width{0.0});

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Width horizontalMarginAfterUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(horizontalMarginAfterUpdate.Get(), 3.571429)) << Debug(horizontalMarginAfterUpdate);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetHorizontalMargin_ValidModelWidthEqualsHeight_ZeroMarginReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Width horizontalMarginBeforeUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(horizontalMarginBeforeUpdate == cxmath::Width{0.0});

    model.Update({cxmath::Height{150}, cxmath::Width{150}}, true);

    const cxmath::Width horizontalMarginAfterUpdate = model.GetHorizontalMargin();

    // There is no margin since both dimensions are the same!
    ASSERT_TRUE(horizontalMarginAfterUpdate.Get() == 0.0) << Debug(horizontalMarginAfterUpdate);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetCellLineWidth_ValidModel_CellLineWidthReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Width lineWidthBeforeUpdate = model.GetLineWidth(cxgui::Feature::CELL);
    ASSERT_TRUE(lineWidthBeforeUpdate == cxmath::Width{0.0});

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Width lineWidthAfterUpdate = model.GetLineWidth(cxgui::Feature::CELL);
    ASSERT_TRUE(cxmath::AreLogicallyEqual(lineWidthAfterUpdate.Get(), 0.5));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipLineWidth_ValidModel_ChipLineWidthReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxmath::Width lineWidthBeforeUpdate = model.GetLineWidth(cxgui::Feature::CHIP);
    ASSERT_TRUE(lineWidthBeforeUpdate == cxmath::Width{0.0});

    model.Update({cxmath::Height{100}, cxmath::Width{150}}, true);

    const cxmath::Width lineWidthAfterUpdate = model.GetLineWidth(cxgui::Feature::CHIP);
    ASSERT_TRUE(cxmath::AreLogicallyEqual(lineWidthAfterUpdate.Get(), 0.035714285714285719));
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/GetUnknownLineWidth_ValidModel_ZeroReturnedAndAssert)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxgui::Feature invalid = static_cast<cxgui::Feature>(-1);

    const cxmath::Width invalidLineWidth = model.GetLineWidth(invalid);
    ASSERT_TRUE(invalidLineWidth == cxmath::Width{0.0});

    ASSERT_ASSERTION_FAILED(*this);
}
