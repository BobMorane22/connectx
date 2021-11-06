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

#include <gtest/gtest.h>

#include <cxunit/include/StdStreamRedirector.h>
#include <cxmath/include/math.h>

#include <AnimatedBoardModel.h>
#include <IAnimatedBoardPresenter.h>

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
constexpr unsigned int DISC_RADIUS_NO_LW    = 0x01 << 4;
constexpr unsigned int DISC_RADIUS_WITH_LW  = 0x01 << 5;
constexpr unsigned int DISC_POSITION        = 0x01 << 6;
constexpr unsigned int HORIZONTAL_MARGIN    = 0x01 << 7;
constexpr unsigned int MIRROR_DISC_POSITION = 0x01 << 8;
constexpr unsigned int IS_MIRROR_NEEDED     = 0x01 << 9;
constexpr unsigned int LINE_WIDTH           = 0x01 << 10;
constexpr unsigned int CURRENT_COLUMN       = 0x01 << 11;

using ModelOperations = std::function<void(cxgui::IAnimatedBoardModel&)>;
using NotSynced = unsigned int;

NotSynced Validate(cxgui::IAnimatedBoardModel& p_model, const ModelOperations& p_operations)
{
    // Pre-operation(s) values:
    const size_t fpsBefore                               = p_model.GetFPS();
    const size_t speedBefore                             = p_model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsBefore = p_model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsBefore         = p_model.GetCellDimensions();
    const double radiusWithoutBorderBefore               = p_model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderBefore                  = p_model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position chipPositionBefore            = p_model.GetDiscPosition();
    const double horizontalMarginBefore                  = p_model.GetHorizontalMargin();
    const cxmath::Position mirrorChipPositionBefore      = p_model.GetMirrorDiscPosition();
    const bool mirrorNeededBefore                        = p_model.IsMirrorDiscNeeded();
    const double lineWidthBefore                         = p_model.GetLineWidth();
    const size_t currentColumnBefore                     = p_model.GetCurrentColumn();

    // Operation(s) performed on the model:
    EXPECT_TRUE(p_operations);
    p_operations(p_model);

    // Post-operation(s) values:
    const size_t fpsAfter                               = p_model.GetFPS();
    const size_t speedAfter                             = p_model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsAfter = p_model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsAfter         = p_model.GetCellDimensions();
    const double radiusWithoutBorderAfter               = p_model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderAfter                  = p_model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position chipPositionAfter            = p_model.GetDiscPosition();
    const double horizontalMarginAfter                  = p_model.GetHorizontalMargin();
    const cxmath::Position mirrorChipPositionAfter      = p_model.GetMirrorDiscPosition();
    const bool mirrorNeededAfter                        = p_model.IsMirrorDiscNeeded();
    const double lineWidthAfter                         = p_model.GetLineWidth();
    const size_t currentColumnAfter                     = p_model.GetCurrentColumn();

    // Comparing the two:
    NotSynced syncResult = NONE;

    if(fpsBefore != fpsAfter)                                        syncResult |= FPS;
    if(speedBefore != speedAfter)                                    syncResult |= SPEED;
    if(animatedAreaDimensionsBefore != animatedAreaDimensionsAfter)  syncResult |= AREA_DIMENSIONS;
    if(cellDimensionsBefore != cellDimensionsAfter)                  syncResult |= CELL_DIMENSIONS;
    if(radiusWithoutBorderBefore != radiusWithoutBorderAfter)        syncResult |= DISC_RADIUS_NO_LW;
    if(radiusWithBorderBefore != radiusWithBorderAfter)              syncResult |= DISC_RADIUS_WITH_LW;
    if(chipPositionBefore != chipPositionAfter)                      syncResult |= DISC_POSITION;
    if(horizontalMarginBefore != horizontalMarginAfter)              syncResult |= HORIZONTAL_MARGIN;
    if(mirrorChipPositionBefore != mirrorChipPositionAfter)          syncResult |= MIRROR_DISC_POSITION;
    if(mirrorNeededBefore != mirrorNeededAfter)                      syncResult |= IS_MIRROR_NEEDED;
    if(lineWidthBefore != lineWidthAfter)                            syncResult |= LINE_WIDTH;
    if(currentColumnBefore != currentColumnAfter)                    syncResult |= CURRENT_COLUMN;

    return syncResult;
}

class AnimatedBoardPresenterMock : public cxgui::IAnimatedBoardPresenter
{

public:

    // cxgui::IAnimatedBoardPresenter:
    void Sync() override {FAIL();}
    [[nodiscard]] size_t GetBoardHeight() const override {return 6u;}
    [[nodiscard]] size_t GetBoardWidth() const override {return 7u;}
    [[nodiscard]] cxmodel::ChipColor GetActivePlayerChipColor() const override {return cxmodel::MakeRed();}
    [[nodiscard]] const cxgui::IGameViewPresenter::ChipColors& GetBoardChipColors() const override {return m_chipColors;}

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

        m_model = std::make_unique<cxgui::AnimatedBoardModel>(*m_presenter, 3u);
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
    const cxgui::AnimatedBoardModel model{*presenter, 3u};
    const std::string streamContents = streamDisabler.GetStdErrContents();

    ASSERT_TRUE(streamContents.empty());
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Update_ValidInput_UpdatesAnimationData)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);
                                  });

    // Comparing the two:
    ASSERT_TRUE(whatChanged == (AREA_DIMENSIONS      |
                                CELL_DIMENSIONS      |
                                DISC_RADIUS_NO_LW    |
                                DISC_RADIUS_WITH_LW  |
                                DISC_POSITION        |
                                HORIZONTAL_MARGIN    |
                                MIRROR_DISC_POSITION |
                                IS_MIRROR_NEEDED     |
                                LINE_WIDTH)
    );
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Update_InvalidWidgetHeight_NothingUpdatedAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cxgui::Height{-100}, cxgui::Width{150}}, true);
                                  });

    ASSERT_TRUE(whatChanged == NONE);

    // There should be an assertion:
    const std::string streamContents = GetStdErrContents();
    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Update_InvalidWidgetWidth_NothingUpdatedAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Update({cxgui::Height{100}, cxgui::Width{-150}}, true);
                                  });

    ASSERT_TRUE(whatChanged == NONE);

    // There should be an assertion:
    const std::string streamContents = GetStdErrContents();
    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Resize_ValidAndHorizontal_ResizingOccured)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);
    model.AddDiscDisplacement(1.0, 1.0);
    const cxmath::Position chipPositionBefore = model.GetDiscPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Resize(2.0, 1.0);
                                  });

    ASSERT_TRUE(whatChanged == DISC_POSITION);

    const cxmath::Position chipPositionAfter = model.GetDiscPosition();

    ASSERT_TRUE(cxmath::AreLogicallyEqual(2.0 * chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/Resize_ValidAndVertical_ResizingOccured)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);
    model.AddDiscDisplacement(1.0, 1.0);
    const cxmath::Position chipPositionBefore = model.GetDiscPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Resize(1.0, 3.0);
                                  });

    ASSERT_TRUE(whatChanged == DISC_POSITION);

    const cxmath::Position chipPositionAfter = model.GetDiscPosition();

    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(3.0 * chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Resize_InvalidHorizontalRatio_DoesNotResizeAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Resize(-1.0, 2.0);
                                  });

    ASSERT_TRUE(whatChanged == NONE);

    // There should be an assertion:
    const std::string streamContents = GetStdErrContents();
    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST_F(AnimationModelTestFixtureStdErrStreamRedirector, /*DISABLED_*/Resize_InvalidVerticalRatio_DoesNotResizeAndAsserts)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.Resize(1.0, -2.0);
                                  });

    ASSERT_TRUE(whatChanged == NONE);

    // There should be an assertion:
    const std::string streamContents = GetStdErrContents();
    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/AddChipDisplacement_HorizontalDisplacement_ChipMovedHorizontally)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const cxmath::Position chipPositionBefore = model.GetDiscPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.AddDiscDisplacement(1.0, 0.0);
                                  });

    ASSERT_TRUE(whatChanged == DISC_POSITION);

    const cxmath::Position chipPositionAfter = model.GetDiscPosition();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_x + 1.0, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/AddChipDisplacement_VerticalDisplacement_ChipMovedVertically)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const cxmath::Position chipPositionBefore = model.GetDiscPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.AddDiscDisplacement(0.0, 1.0);
                                  });

    ASSERT_TRUE(whatChanged == DISC_POSITION);

    const cxmath::Position chipPositionAfter = model.GetDiscPosition();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipPositionBefore.m_y + 1.0, chipPositionAfter.m_y));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/ResetChipPositions_ValidModel_ChipPositionsReinitialized)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);
    model.AddDiscDisplacement(1.0, 1.0);

    const cxmath::Position chipPositionBefore = model.GetDiscPosition();
    const cxmath::Position mirrorChipPositionBefore = model.GetMirrorDiscPosition();

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.ResetDiscPositions();
                                  });

    ASSERT_TRUE(whatChanged == (DISC_POSITION | MIRROR_DISC_POSITION));

    const cxmath::Position chipPositionAfter = model.GetDiscPosition();
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(chipPositionBefore.m_x, chipPositionAfter.m_x));
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(chipPositionBefore.m_y, chipPositionAfter.m_y));

    ASSERT_TRUE(chipPositionAfter.m_x == 0.0);
    ASSERT_TRUE(chipPositionAfter.m_y == 0.0);

    const cxmath::Position mirrorChipPositionAfter = model.GetMirrorDiscPosition();
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(mirrorChipPositionBefore.m_x, mirrorChipPositionAfter.m_x));
    ASSERT_TRUE(!cxmath::AreLogicallyEqual(mirrorChipPositionBefore.m_y, mirrorChipPositionAfter.m_y));

    ASSERT_TRUE(mirrorChipPositionAfter.m_x == 0.0);
    ASSERT_TRUE(mirrorChipPositionAfter.m_y == 0.0);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/UpdateCurrentColumn_NewColumIndex_ColumnUpdated)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const size_t currentColumnBefore = model.GetCurrentColumn();
    ASSERT_TRUE(currentColumnBefore == 0u);

    const NotSynced whatChanged = Validate(model,
                                  [](cxgui::IAnimatedBoardModel& p_model)
                                  {
                                      p_model.UpdateCurrentColumn(3u);
                                  });

    ASSERT_TRUE(whatChanged == CURRENT_COLUMN);

    const size_t currentColumnAfter = model.GetCurrentColumn();
    ASSERT_TRUE(currentColumnAfter == 3u);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetFPS_ValidModel_FPSReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    ASSERT_TRUE(model.GetFPS() == 24u);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetAnimationSpeed_ValidModel_AnimationSpeedReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    ASSERT_TRUE(model.GetAnimationSpeed() == 3u);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetAnimatedAreaDimensions)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxgui::Dimensions areaDimensionsBeforeUpdate = model.GetAnimatedAreaDimensions();
    ASSERT_TRUE((areaDimensionsBeforeUpdate == cxgui::Dimensions{cxgui::Height{0}, cxgui::Width{0}}));

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const cxgui::Dimensions areaDimensions = model.GetAnimatedAreaDimensions();
    ASSERT_TRUE((areaDimensions == cxgui::Dimensions{cxgui::Height{100}, cxgui::Width{150}}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetCellDimensions_ValidModel_CellDimensionsReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const cxgui::Dimensions cellDimensionsBeforeUpdate = model.GetCellDimensions();
    ASSERT_TRUE((cellDimensionsBeforeUpdate == cxgui::Dimensions{cxgui::Height{0}, cxgui::Width{0}}));

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const cxgui::Dimensions cellDimensionsAfterUpdate = model.GetCellDimensions();
    ASSERT_TRUE((cellDimensionsAfterUpdate == cxgui::Dimensions{cxgui::Height{100.0 / 7.0}, cxgui::Width{150.0 / 7.0}}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipRadius_ValidModel_WithoutLineWidth)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const double chipRadiusBeforeUpdate = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    ASSERT_TRUE(chipRadiusBeforeUpdate == 0.0);

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const double chipRadiusAfterUpdate = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipRadiusAfterUpdate, 7.142857));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipRadius_ValidModel_WithLineWidth)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const double chipRadiusBeforeUpdate = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    ASSERT_TRUE(chipRadiusBeforeUpdate == 0.0);

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const double chipRadiusAfterUpdate = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    ASSERT_TRUE(cxmath::AreLogicallyEqual(chipRadiusAfterUpdate, 7.125));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheLeftChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip is starting at (0,0) and moving, it's horizontal position is not updated:
    ASSERT_TRUE((chipPosition == cxmath::Position{0.0, 7.1428571428571432}));

    // Instead, a mirror chip will be added to represent its complement on the other side of the board:
    ASSERT_TRUE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{100.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheLeftChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip is starting at (0,0) and it is not moving, an update will
    // make sure it is completely visible to the user:
    ASSERT_TRUE((chipPosition == cxmath::Position{7.1428571428571432, 7.1428571428571432}));

    // Also, in this case, no mirror chip will be added (it is only added to simulate
    // continuity across the board limits as animations are performed):
    ASSERT_FALSE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheLeftChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddDiscDisplacement(-7.1428571428571432, 0.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip has completely crossed to the left but that it is still moving, 
    // its position is not updated:
    ASSERT_TRUE((chipPosition == cxmath::Position{-7.1428571428571432, 7.1428571428571432}));

    // Instead, a mirror chip is added on the other side, fully visible:
    ASSERT_TRUE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{92.857142857142861, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheLeftChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddDiscDisplacement(-7.1428571428571432, 0.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip has completely crossed to the left, its position is updated to be
    // at the extreme right side:
    ASSERT_TRUE((chipPosition == cxmath::Position{92.857142857142861, 7.1428571428571432}));

    // Since all of it is visible, no mirror chip is needed:
    ASSERT_FALSE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheRightChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddDiscDisplacement(100.0, 0.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // The chip is "clamped" to the right, to make sure all of it is visible:
    ASSERT_TRUE((chipPosition == cxmath::Position{92.857142857142861, 7.1428571428571432}));

    // No mirror chip is needed in the case:
    ASSERT_FALSE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CrossedToTheRightChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddDiscDisplacement(100.0, 0.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip position makes it cross over to the right (half the chip is crossing over),
    // and the chip is moving, a mirror chip is added, on the left side of the board to give
    // the user the illusion of a smooth crossing over animation:
    ASSERT_TRUE((chipPosition == cxmath::Position{100.0, 7.1428571428571432}));

    ASSERT_TRUE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheRightChipIsMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddDiscDisplacement(107.1428571428571432, 0.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip has completely crossed to the right but that it is still moving, 
    // its position is not updated:
    ASSERT_TRUE((chipPosition == cxmath::Position{107.1428571428571432, 7.1428571428571432}));

    // Instead, a mirror chip is added on the other side, fully visible:
    ASSERT_TRUE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{7.1428571428571388, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_CompletelyCrossedToTheRightChipIsNotMoving_ReturnsPosition)
{
    cxgui::IAnimatedBoardModel& model = GetModel();
    model.AddDiscDisplacement(107.1428571428571432, 0.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();
    const cxmath::Position mirrorChipPosition = model.GetMirrorDiscPosition();

    // Since the chip has completely crossed to the right, its position is updated to be
    // at the extreme left side:
    ASSERT_TRUE((chipPosition == cxmath::Position{7.1428571428571432, 7.1428571428571432}));

    // Since all of it is visible, no mirror chip is needed:
    ASSERT_FALSE(model.IsMirrorDiscNeeded());
    ASSERT_TRUE((mirrorChipPosition == cxmath::Position{0.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_HorizontalOffsetTowardsTop_PositionIsFixed)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    // Going out of the board (at top):
    model.AddDiscDisplacement(50.0, 1.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();

    // Vertical position is "clamped" to the top of the board to make sure the chip is
    // visible to the user:
    ASSERT_TRUE((chipPosition == cxmath::Position{50.0, 7.1428571428571432}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetChipPosition_HorizontalOffsetTowardsBottom_PositionIsFixed)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    // Going out of the board (at bottom, remember to bottom is in the positive y):
    model.AddDiscDisplacement(50.0, 151.0);
    model.Update({cxgui::Height{150}, cxgui::Width{100}}, CHIP_IS_NOT_MOVING_HORIZONTALLY);

    const cxmath::Position chipPosition = model.GetDiscPosition();

    // Vertical position is "clamped" to the bottom of the board to make sure the chip is
    // visible to the user:
    ASSERT_TRUE((chipPosition == cxmath::Position{50.0, 142.85714285714286}));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetHorizontalMargin_ValidModel_MarginReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const double horizontalMarginBeforeUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(horizontalMarginBeforeUpdate == 0.0);

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const double horizontalMarginAfterUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(horizontalMarginAfterUpdate, 3.571428));
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetHorizontalMargin_ValidModelWidthEqualsHeight_ZeroMarginReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const double horizontalMarginBeforeUpdate = model.GetHorizontalMargin();
    ASSERT_TRUE(horizontalMarginBeforeUpdate == 0.0);

    model.Update({cxgui::Height{150}, cxgui::Width{150}}, true);

    const double horizontalMarginAfterUpdate = model.GetHorizontalMargin();

    // There is no margin since both dimensions are the same!
    ASSERT_TRUE(horizontalMarginAfterUpdate == 0.0);
}

TEST_F(AnimationModelTestFixture, /*DISABLED_*/GetLineWidth_ValidModel_LineWidthReturned)
{
    cxgui::IAnimatedBoardModel& model = GetModel();

    const double lineWidthBeforeUpdate = model.GetLineWidth();
    ASSERT_TRUE(lineWidthBeforeUpdate == 0.0);

    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    const double lineWidthAfterUpdate = model.GetLineWidth();
    ASSERT_TRUE(cxmath::AreLogicallyEqual(lineWidthAfterUpdate, 0.5));
}
