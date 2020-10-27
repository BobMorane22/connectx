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
 * @file NewGamePresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "MainWindowPresenterTestFixture.h"

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetTitle_NewGamePresenter_TitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewTitle(), "New Game");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetGameSectionTitle_NewGamePresenter_GameSectionTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewGameSectionTitle(), "Game");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNewGameViewInARowLabelText_NewGamePresenter_NewGameViewTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewInARowLabelText(), "In a row:");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNewGameGridSectionTitle_NewGamePresenter_GridSectionTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewBoardSectionTitle(), "Board");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetWidthLabelText_NewGamePresenter_WidthLabelTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewWidthLabelText(), "Width:");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetHeightLabelText_NewGamePresenter_HeightLabelTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewHeightLabelText(), "Height:");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetPlayersSectionTitle_NewGamePresenter_PlayersSectionTitleReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewPlayersSectionTitle(), "Players");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNameColumnHeaderText_NewGamePresenter_NameColumnHeaderTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewNameColumnHeaderText(), "Name");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDiscColumnHeaderText_NewGamePresenter_DiscColumnHeaderTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewDiscColumnHeaderText(), "Disc");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNewGameViewRemovePlayerButtonText_NewGamePresenter_ButtonTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewRemovePlayerButtonText(), "Remove player");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/CanRemoveAnotherPlayer_TooFewPlayers_ReturnsFalse)
{
    ASSERT_FALSE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(2u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/CanRemoveAnotherPlayer_EnoughPlayers_ReturnsTrue)
{
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(3u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(4u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(5u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(6u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(7u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(8u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(9u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanRemoveAnotherPlayer(10u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNewGameViewAddPlayerButtonText_NewGamePresenter_ButtonTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewAddPlayerButtonText(), "Add player");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/CanAddAnotherPlayer_TooManyPlayers_ReturnsFalse)
{
    ASSERT_FALSE(GetNewGameViewPresenter().CanAddAnotherPlayer(10u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/CanAddAnotherPlayer_EnoughPlayers_ReturnsTrue)
{
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(2u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(3u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(4u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(5u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(6u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(7u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(8u));
    ASSERT_TRUE(GetNewGameViewPresenter().CanAddAnotherPlayer(9u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetStartButtonText_NewGamePresenter_StartButtonTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewStartButtonText(), "Start");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMinInARowValue_NewGamePresenter_MinValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewMinInARowValue(), GetLimitsModel().GetMinimumInARowValue());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMaxInARowValue_NewGamePresenter_MaxValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewMaxInARowValue(), GetLimitsModel().GetMaximumInARowValue());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMinBoardWidthValue_NewGamePresenter_MinValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewMinBoardWidthValue(), GetLimitsModel().GetMinimumGridWidth());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMaxBoardWidthValue_NewGamePresenter_MaxValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewMaxBoardWidthValue(), GetLimitsModel().GetMaximumGridWidth());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMinBoardHeightValue_NewGamePresenter_MinValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewMinBoardHeightValue(), GetLimitsModel().GetMinimumGridHeight());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetMaxBoardHeightValue_NewGamePresenter_MaxValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewMaxBoardHeightValue(), GetLimitsModel().GetMaximumGridHeight());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNumericalValuesExpectedMessage_NewGamePresenter_MessageReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNumericalValuesExpectedMessage(), "Enter numerical values for in-a-row and board size values.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetNumericalValuesOutOfRangeMessage_NewGamePresenter_MessageReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNumericalValuesOutOfRangeMessage(), "Numerical values out of range for in-a-row or board size values.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetInARowInvalidInputMessage_NewGamePresenter_MessageReturned)
{
    auto& presenter = GetNewGameViewPresenter();

    std::ostringstream oss;
    oss << "The in-a-row value should be between "
        << presenter.GetNewGameViewMinInARowValue()
        << " and "
        << presenter.GetNewGameViewMaxInARowValue()
        << " inclusively.";

    ASSERT_EQ(presenter.GetInARowInvalidInputMessage(), oss.str());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetBoardDimensionsInvalidInputMessage_InvalidHeight_InvalidHeightMessageReturned)
{
    auto& presenter = GetNewGameViewPresenter();

    std::ostringstream oss;
    oss << "The board height value should be between "
        << presenter.GetNewGameViewMinBoardHeightValue()
        << " and "
        << presenter.GetNewGameViewMaxBoardHeightValue()
        << " inclusively.";

    presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue() + 1u, presenter.GetNewGameViewMaxBoardWidthValue() + 1);
    ASSERT_EQ(presenter.GetBoardDimensionsInvalidInputMessage(), oss.str());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetBoardDimensionsInvalidInputMessage_InvalidWidth_InvalidWidthMessageReturned)
{
    auto& presenter = GetNewGameViewPresenter();

    std::ostringstream oss;
    oss << "The board width value should be between "
        << presenter.GetNewGameViewMinBoardWidthValue()
        << " and "
        << presenter.GetNewGameViewMaxBoardWidthValue()
        << " inclusively.";

    presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue(), presenter.GetNewGameViewMaxBoardWidthValue() + 1);
    ASSERT_EQ(presenter.GetBoardDimensionsInvalidInputMessage(), oss.str());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetPlayersInformationInvalidInputMessage_AllInputValidAndDifferent_EmptyMessageReturned)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "Jane Doe",
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    auto& presenter = GetNewGameViewPresenter();
    presenter.ArePlayersInformationValid(playerNames, chipColors);

    ASSERT_EQ(presenter.GetPlayersInformationInvalidInputMessage(), "");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetPlayersInformationInvalidInputMessage_TwoIdenticalNamesButDifferentColors_EmptyMessageReturned)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "John Doe",
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    auto& presenter = GetNewGameViewPresenter();
    presenter.ArePlayersInformationValid(playerNames, chipColors);

    ASSERT_EQ(presenter.GetPlayersInformationInvalidInputMessage(), "");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetPlayersInformationInvalidInputMessage_AnEmptyName_InvalidPlayerMessageReturned)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        std::string(),
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    auto& presenter = GetNewGameViewPresenter();
    presenter.ArePlayersInformationValid(playerNames, chipColors);

    ASSERT_EQ(presenter.GetPlayersInformationInvalidInputMessage(), "Player names cannot be empty.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetPlayersInformationInvalidInputMessage_TwoIdenticalChipColors_InvalidChipColorsMessageReturned)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "Jane Doe",
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeRed(),
        cxmodel::MakeYellow()
    };

    auto& presenter = GetNewGameViewPresenter();
    presenter.ArePlayersInformationValid(playerNames, chipColors);

    ASSERT_EQ(presenter.GetPlayersInformationInvalidInputMessage(), "Discs must have different colors.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsInARowValueValid_InValidRange_ReturnsTrue)
{
    ASSERT_TRUE(GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMinInARowValue()));
    ASSERT_TRUE(GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMaxInARowValue()));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsInARowValueValid_BelowRange_ReturnsFalse)
{
    ASSERT_FALSE(GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMinInARowValue() - 1u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsInARowValueValid_OverRange_ReturnsFalse)
{
    ASSERT_FALSE(GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMaxInARowValue() + 1u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_BothHeightAndWidthInRange_ReturnsTrue)
{
    auto& presenter = GetNewGameViewPresenter();

    ASSERT_TRUE(presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMinBoardHeightValue(),
                                                  presenter.GetNewGameViewMinBoardWidthValue()));

    ASSERT_TRUE(presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue(),
                                                  presenter.GetNewGameViewMaxBoardWidthValue()));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_HeightBelowRange_ReturnsFalse)
{
    auto& presenter = GetNewGameViewPresenter();

    ASSERT_FALSE(presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMinBoardHeightValue() - 1u,
                                                   presenter.GetNewGameViewMaxBoardWidthValue()));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_HeightOverRange_ReturnsFalse)
{
    auto& presenter = GetNewGameViewPresenter();

    ASSERT_FALSE(presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue() + 1u,
                                                   presenter.GetNewGameViewMaxBoardWidthValue()));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_WidthBelowRange_ReturnsFalse)
{
    auto& presenter = GetNewGameViewPresenter();

    ASSERT_FALSE(presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMinBoardWidthValue(),
                                                   presenter.GetNewGameViewMaxBoardWidthValue() - 1u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_WidthOverRange_ReturnsFalse)
{
    auto& presenter = GetNewGameViewPresenter();

    ASSERT_FALSE(presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardWidthValue(),
                                                   presenter.GetNewGameViewMaxBoardWidthValue() + 1u));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayersInformationValid_NonEmptyPlayerNamesAndAllDifferentChipColors_ReturnsTrue)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "Jane Doe",
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    ASSERT_TRUE(GetNewGameViewPresenter().ArePlayersInformationValid(playerNames, chipColors));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayersInformationValid_AllSamePlayerNamesAndAllDifferentChipColors_ReturnsTrue)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "John Doe",
        "John Doe"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    ASSERT_TRUE(GetNewGameViewPresenter().ArePlayersInformationValid(playerNames, chipColors));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayersInformationValid_AnEmptyPlayerNameAndAllDifferentChipColors_ReturnsFalse)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "",
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    ASSERT_FALSE(GetNewGameViewPresenter().ArePlayersInformationValid(playerNames, chipColors));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayersInformationValid_NonEmptyPlayerNamesAndTwoSameChipColors_ReturnsFalse)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "Jane Doe",
        "Igor Lopez"
    };

    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeRed(),
        cxmodel::MakeYellow()
    };

    ASSERT_FALSE(GetNewGameViewPresenter().ArePlayersInformationValid(playerNames, chipColors));
}
