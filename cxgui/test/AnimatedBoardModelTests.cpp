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

#include <gtest/gtest.h>

#include <cxunit/include/DisableStdStreamsRAII.h>

#include <AnimatedBoardModel.h>
#include <IAnimatedBoardPresenter.h>

namespace
{

bool operator==(const cxgui::Dimensions& p_lhs, const cxgui::Dimensions& p_rhs)
{
    return (p_lhs.m_height.Get() == p_rhs.m_height.Get()) &&
           (p_lhs.m_width.Get() == p_rhs.m_width.Get());
}

bool operator!=(const cxgui::Dimensions& p_lhs, const cxgui::Dimensions& p_rhs)
{
    return !(p_lhs == p_rhs);
}

bool operator==(const cxmath::Position& p_lhs, const cxmath::Position& p_rhs)
{
    return (p_lhs.m_x == p_rhs.m_x) && (p_lhs.m_y == p_rhs.m_y);
}

bool operator!=(const cxmath::Position& p_lhs, const cxmath::Position& p_rhs)
{
    return !(p_lhs == p_rhs);
}

} // namespace

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

TEST(AnimatedBoardModel, /*DISABLED_*/Constructor_ValidInput_DoesNotAssert)
{
    auto presenter = std::make_unique<AnimatedBoardPresenterMock>();
    ASSERT_TRUE(presenter);

    cxunit::DisableStdStreamsRAII streamDisabler;
    const cxgui::AnimatedBoardModel model{*presenter, 3u};
    const std::string streamContents = streamDisabler.GetStdErrContents();

    ASSERT_TRUE(streamContents.empty());
}

//TEST(Status, GetMessage_Success_Asserts)
//{
//    cxunit::DisableStdStreamsRAII streamDisabler;
//
//    const auto status = cxmodel::MakeSuccess();
//    const std::string message = status.GetMessage();
//
//    const std::string streamContents = streamDisabler.GetStdErrContents();
//
//    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
//}

TEST(AnimatedBoardModel, /*DISABLED_*/Update_ValidInput_UpdatesAnimationData)
{
    auto presenter = std::make_unique<AnimatedBoardPresenterMock>();
    ASSERT_TRUE(presenter);

    cxgui::AnimatedBoardModel model{*presenter, 3u};

    // Pre-update values:
    const size_t fpsBefore = model.GetFPS();
    const size_t speedBefore = model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsBefore = model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsBefore = model.GetCellDimensions();
    const double radiusWithoutBorderBefore = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderBefore = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position discPositionBefore = model.GetDiscPosition();
    const double horizontalMarginBefore = model.GetHorizontalMargin();
    const cxmath::Position mirrorDiscPositionBefore = model.GetMirrorDiscPosition();
    const bool mirrorNeededBefore = model.IsMirrorDiscNeeded();
    const double lineWidthBefore = model.GetLineWidth();
    const size_t currentColumnBefore = model.GetCurrentColumn();

    // We update the model:
    model.Update({cxgui::Height{100}, cxgui::Width{150}}, true);

    // Post-update values:
    const size_t fpsAfter = model.GetFPS();
    const size_t speedAfter = model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsAfter = model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsAfter = model.GetCellDimensions();
    const double radiusWithoutBorderAfter = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderAfter = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position discPositionAfter = model.GetDiscPosition();
    const double horizontalMarginAfter = model.GetHorizontalMargin();
    const cxmath::Position mirrorDiscPositionAfter = model.GetMirrorDiscPosition();
    const bool mirrorNeededAfter = model.IsMirrorDiscNeeded();
    const double lineWidthAfter = model.GetLineWidth();
    const size_t currentColumnAfter = model.GetCurrentColumn();

    // Comparing the two:
    ASSERT_TRUE(animatedAreaDimensionsBefore != animatedAreaDimensionsAfter);
    ASSERT_TRUE(cellDimensionsBefore != cellDimensionsAfter);
    ASSERT_TRUE(radiusWithoutBorderBefore != radiusWithoutBorderAfter);
    ASSERT_TRUE(radiusWithBorderBefore != radiusWithBorderAfter);
    ASSERT_TRUE(discPositionBefore != discPositionAfter);
    ASSERT_TRUE(horizontalMarginBefore != horizontalMarginAfter);
    ASSERT_TRUE(mirrorDiscPositionBefore != mirrorDiscPositionAfter);
    ASSERT_TRUE(mirrorNeededBefore != mirrorNeededAfter);
    ASSERT_TRUE(lineWidthBefore != lineWidthAfter);

    ASSERT_FALSE(fpsBefore != fpsAfter);
    ASSERT_FALSE(speedBefore != speedAfter);
    ASSERT_FALSE(currentColumnBefore != currentColumnAfter);
}

TEST(AnimatedBoardModel, /*DISABLED_*/Update_InvalidWidgetHeight_NothingUpdatedAndAsserts)
{
    auto presenter = std::make_unique<AnimatedBoardPresenterMock>();
    ASSERT_TRUE(presenter);

    cxgui::AnimatedBoardModel model{*presenter, 3u};

    // Pre-update values:
    const size_t fpsBefore = model.GetFPS();
    const size_t speedBefore = model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsBefore = model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsBefore = model.GetCellDimensions();
    const double radiusWithoutBorderBefore = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderBefore = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position discPositionBefore = model.GetDiscPosition();
    const double horizontalMarginBefore = model.GetHorizontalMargin();
    const cxmath::Position mirrorDiscPositionBefore = model.GetMirrorDiscPosition();
    const bool mirrorNeededBefore = model.IsMirrorDiscNeeded();
    const double lineWidthBefore = model.GetLineWidth();
    const size_t currentColumnBefore = model.GetCurrentColumn();

    // We update the model:
    constexpr cxgui::Height invalidHeight{-100};

    cxunit::DisableStdStreamsRAII streamDisabler;
    model.Update({invalidHeight, cxgui::Width{150}}, true);

    const size_t fpsAfter = model.GetFPS();
    const size_t speedAfter = model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsAfter = model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsAfter = model.GetCellDimensions();
    const double radiusWithoutBorderAfter = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderAfter = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position discPositionAfter = model.GetDiscPosition();
    const double horizontalMarginAfter = model.GetHorizontalMargin();
    const cxmath::Position mirrorDiscPositionAfter = model.GetMirrorDiscPosition();
    const bool mirrorNeededAfter = model.IsMirrorDiscNeeded();
    const double lineWidthAfter = model.GetLineWidth();
    const size_t currentColumnAfter = model.GetCurrentColumn();

    // Comparing the two:
    ASSERT_TRUE(fpsBefore == fpsAfter);
    ASSERT_TRUE(speedBefore == speedAfter);
    ASSERT_TRUE(animatedAreaDimensionsBefore == animatedAreaDimensionsAfter);
    ASSERT_TRUE(cellDimensionsBefore == cellDimensionsAfter);
    ASSERT_TRUE(radiusWithoutBorderBefore == radiusWithoutBorderAfter);
    ASSERT_TRUE(radiusWithBorderBefore == radiusWithBorderAfter);
    ASSERT_TRUE(discPositionBefore == discPositionAfter);
    ASSERT_TRUE(horizontalMarginBefore == horizontalMarginAfter);
    ASSERT_TRUE(mirrorDiscPositionBefore == mirrorDiscPositionAfter);
    ASSERT_TRUE(mirrorNeededBefore == mirrorNeededAfter);
    ASSERT_TRUE(lineWidthBefore == lineWidthAfter);
    ASSERT_TRUE(currentColumnBefore == currentColumnAfter);

    // There should be an assertion:
    const std::string streamContents = streamDisabler.GetStdErrContents();
    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

TEST(AnimatedBoardModel, /*DISABLED_*/Update_InvalidWidgetWidth_NothingUpdatedAndAsserts)
{
    auto presenter = std::make_unique<AnimatedBoardPresenterMock>();
    ASSERT_TRUE(presenter);

    cxgui::AnimatedBoardModel model{*presenter, 3u};

    // Pre-update values:
    const size_t fpsBefore = model.GetFPS();
    const size_t speedBefore = model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsBefore = model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsBefore = model.GetCellDimensions();
    const double radiusWithoutBorderBefore = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderBefore = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position discPositionBefore = model.GetDiscPosition();
    const double horizontalMarginBefore = model.GetHorizontalMargin();
    const cxmath::Position mirrorDiscPositionBefore = model.GetMirrorDiscPosition();
    const bool mirrorNeededBefore = model.IsMirrorDiscNeeded();
    const double lineWidthBefore = model.GetLineWidth();
    const size_t currentColumnBefore = model.GetCurrentColumn();

    // We update the model:
    constexpr cxgui::Width invalidWidth{-150};

    cxunit::DisableStdStreamsRAII streamDisabler;
    model.Update({cxgui::Height{100}, invalidWidth}, true);

    const size_t fpsAfter = model.GetFPS();
    const size_t speedAfter = model.GetAnimationSpeed();
    const cxgui::Dimensions animatedAreaDimensionsAfter = model.GetAnimatedAreaDimensions();
    const cxgui::Dimensions cellDimensionsAfter = model.GetCellDimensions();
    const double radiusWithoutBorderAfter = model.GetDiscRadius(cxgui::AddLineWidth::NO);
    const double radiusWithBorderAfter = model.GetDiscRadius(cxgui::AddLineWidth::YES);
    const cxmath::Position discPositionAfter = model.GetDiscPosition();
    const double horizontalMarginAfter = model.GetHorizontalMargin();
    const cxmath::Position mirrorDiscPositionAfter = model.GetMirrorDiscPosition();
    const bool mirrorNeededAfter = model.IsMirrorDiscNeeded();
    const double lineWidthAfter = model.GetLineWidth();
    const size_t currentColumnAfter = model.GetCurrentColumn();

    // Comparing the two:
    ASSERT_TRUE(fpsBefore == fpsAfter);
    ASSERT_TRUE(speedBefore == speedAfter);
    ASSERT_TRUE(animatedAreaDimensionsBefore == animatedAreaDimensionsAfter);
    ASSERT_TRUE(cellDimensionsBefore == cellDimensionsAfter);
    ASSERT_TRUE(radiusWithoutBorderBefore == radiusWithoutBorderAfter);
    ASSERT_TRUE(radiusWithBorderBefore == radiusWithBorderAfter);
    ASSERT_TRUE(discPositionBefore == discPositionAfter);
    ASSERT_TRUE(horizontalMarginBefore == horizontalMarginAfter);
    ASSERT_TRUE(mirrorDiscPositionBefore == mirrorDiscPositionAfter);
    ASSERT_TRUE(mirrorNeededBefore == mirrorNeededAfter);
    ASSERT_TRUE(lineWidthBefore == lineWidthAfter);
    ASSERT_TRUE(currentColumnBefore == currentColumnAfter);

    // There should be an assertion:
    const std::string streamContents = streamDisabler.GetStdErrContents();
    ASSERT_TRUE(streamContents.find("Precondition") != std::string::npos);
}

//TEST(AnimatedBoardModel, /*DISABLED_*/Resize_ValidAndDifferentInput_ResizingOccured)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/Resize_InvalidHorizontalRatio_DoesNotResizeAndAsserts)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/Resize_InvalidVerticalRatio_DoesNotResizeAndAsserts)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/AddDiscDisplacement_VerticalDisplacement_DiscMovedVertically)
//{
//    // Check that other dimension is untouched.
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/AddDiscDisplacement_HorizontalDisplacement_DiscMovedHorizontally)
//{
//    // Check that other dimension is untouched.
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/ResetDiscPositions_ValidModel_DiscPositionsReinitialized)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/UpdateCurrentColumn_NewColumIndex_ColumnUpdated)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetFPS_ValidModel_FPSReturned)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetAnimationSpeed_ValidModel_AnimationSpeedReturned)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetAnimatedAreaDimensions)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetCellDimensions)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetDiscRadius_ValidModel_WithoutLineWidth)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetDiscRadius_ValidModel_WithLineWidth)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetDiscPosition_ValidModel_)
//{
//    // Check coverage to make sure all scenarios are tested.
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetHorizontalMargin_ValidModel_MarginReturned)
//{
//    // Test the case where Height == Width (margin is then 0).
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetMirrorDiscPosition_ValidModel_MirrorDiscIsNeeded_ReturnsPosition)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetMirrorDiscPosition_ValidModel_MirrorDiscIsNotNeeded_ReturnsOldPosition)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/IsMirrorDiscNeeded_DiscPositionIsOutsideWidgetToTheLeft_ReturnsTrue)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/IsMirrorDiscNeeded_DiscPositionIsOutsideWidgetToTheRight_ReturnsTrue)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/IsMirrorDiscNeeded_DiscPositionIsInsideWidget_ReturnsFalse)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetLineWidth_ValidModel_LineWidthReturned)
//{
//    ASSERT_TRUE(false);
//}
//
//TEST(AnimatedBoardModel, /*DISABLED_*/GetCurrentColumn_ValidModel_CurrentColumnReturned)
//{
//    ASSERT_TRUE(false);
//}
