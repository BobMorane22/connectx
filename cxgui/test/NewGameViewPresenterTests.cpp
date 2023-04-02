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
 * @file NewGameViewPresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "MainWindowPresenterTestFixture.h"
#include "NewGameViewPresenterMock.h"

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

TEST_F(MainWindowPresenterTestFixture, /*DISABLED*/GetIsManagedColumnHeaderText_NewGamePresenter_IsManagedColumnTextReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetNewGameViewIsManagedColumnHeaderText(), "Bot");
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

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultInARowValue_NewGamePresenter_DefaultValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultInARowValue(), 4u);
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultBoardHeightValue_NewGamePresenter_DefaultValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultBoardHeightValue(), 6u);
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultBoardWidthValue_NewGamePresenter_DefaultValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultBoardWidthValue(), 7u);
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultPlayerName_NewGamePresenter_DefaultValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(1u), "-- Player 1 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(2u), "-- Player 2 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(3u), "-- Player 3 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(4u), "-- Player 4 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(5u), "-- Player 5 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(6u), "-- Player 6 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(7u), "-- Player 7 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(8u), "-- Player 8 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(9u), "-- Player 9 --");
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerName(10u), "-- Player 10 --");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultChipColor_NewGamePresenter_DefaultValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(1u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(2u), cxmodel::MakeGreen());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(3u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(4u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(5u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(6u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(7u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(8u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(9u), cxmodel::MakeRed());
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultChipColor(10u), cxmodel::MakeRed());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultChipColors_NewGamePresenter_DefaultValueReturned)
{
    const auto defaults = GetNewGameViewPresenter().GetDefaultChipColors();

    ASSERT_TRUE(defaults.size() == 10u);
    ASSERT_TRUE(defaults[0] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::RED));
    ASSERT_TRUE(defaults[1] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::GREEN));
    ASSERT_TRUE(defaults[2] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::YELLOW));
    ASSERT_TRUE(defaults[3] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::AQUA));
    ASSERT_TRUE(defaults[4] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::FUSCHIA));
    ASSERT_TRUE(defaults[5] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::GRAY));
    ASSERT_TRUE(defaults[6] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::LIME));
    ASSERT_TRUE(defaults[7] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::MAROON));
    ASSERT_TRUE(defaults[8] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::OLIVE));
    ASSERT_TRUE(defaults[9] == cxmodel::ChipColor::MakePredefined(cxmodel::ChipColor::Predefined::TEAL));
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/GetDefaultPlayerType_NewGamePresenter_DefaultValueReturned)
{
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(1u), cxmodel::PlayerType::HUMAN);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(2u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(3u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(4u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(5u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(6u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(7u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(8u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(9u), cxmodel::PlayerType::BOT);
    ASSERT_EQ(GetNewGameViewPresenter().GetDefaultPlayerType(10u), cxmodel::PlayerType::BOT);
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

    const auto status = GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMinInARowValue() - 1u);

    ASSERT_EQ(status.GetMessage(), oss.str());
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

    const auto status = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue() + 1u,
                                                          presenter.GetNewGameViewMaxBoardWidthValue() + 1);

    ASSERT_EQ(status.GetMessage(), oss.str());
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

    const auto status = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue(),
                                                          presenter.GetNewGameViewMaxBoardWidthValue() + 1);

    ASSERT_EQ(status.GetMessage(), oss.str());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsInARowValueValid_InValidRange_ReturnsSuccess)
{
    const auto statusMin = GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMinInARowValue());
    ASSERT_TRUE(statusMin.IsSuccess());

    const auto statusMax = GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMaxInARowValue());
    ASSERT_TRUE(statusMax.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsInARowValueValid_BelowRange_ReturnsError)
{
    const auto status = GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMinInARowValue() - 1u);
    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsInARowValueValid_OverRange_ReturnsError)
{
    const auto status = GetNewGameViewPresenter().IsInARowValueValid(GetNewGameViewPresenter().GetNewGameViewMaxInARowValue() + 1u);
    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_BothHeightAndWidthInRange_ReturnsSuccess)
{
    auto& presenter = GetNewGameViewPresenter();

    const auto statusMin = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMinBoardHeightValue(),
                                                             presenter.GetNewGameViewMinBoardWidthValue());
    ASSERT_TRUE(statusMin.IsSuccess());

    const auto statusMax = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue(),
                                                             presenter.GetNewGameViewMaxBoardWidthValue());
    ASSERT_TRUE(statusMax.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_HeightBelowRange_ReturnsError)
{
    auto& presenter = GetNewGameViewPresenter();
    const auto status = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMinBoardHeightValue() - 1u,
                                                          presenter.GetNewGameViewMaxBoardWidthValue());

    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_HeightOverRange_ReturnsError)
{
    auto& presenter = GetNewGameViewPresenter();
    const auto status = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardHeightValue() + 1u,
                                                          presenter.GetNewGameViewMaxBoardWidthValue());

    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_WidthBelowRange_ReturnsError)
{
    auto& presenter = GetNewGameViewPresenter();
    const auto status = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMinBoardWidthValue(),
                                                          presenter.GetNewGameViewMaxBoardWidthValue() - 1u);

    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/AreBoardDimensionsValid_WidthOverRange_ReturnsError)
{
    auto& presenter = GetNewGameViewPresenter();
    const auto status = presenter.AreBoardDimensionsValid(presenter.GetNewGameViewMaxBoardWidthValue(),
                                                          presenter.GetNewGameViewMaxBoardWidthValue() + 1u);

    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerNamesValid_NonEmptyAndDifferentPlayerNames_ReturnsSuccess)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "Jane Doe",
        "Igor Lopez"
    };

    const auto status = GetNewGameViewPresenter().ArePlayerNamesValid(playerNames);
    ASSERT_TRUE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerNamesValid_AllSamePlayerNames_ReturnsSuccess)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "John Doe",
        "John Doe"
    };

    const auto status = GetNewGameViewPresenter().ArePlayerNamesValid(playerNames);
    ASSERT_TRUE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerNamesValid_AnEmptyPlayerName_ReturnsError)
{
    const std::vector<std::string> playerNames
    {
        "John Doe",
        "",
        "Igor Lopez"
    };

    const auto status = GetNewGameViewPresenter().ArePlayerNamesValid(playerNames);
    ASSERT_FALSE(status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "Player names cannot be empty.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerChipColorsValid_AllDifferentColors_ReturnsSuccess)
{
    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeBlue(),
        cxmodel::MakeYellow()
    };

    const auto status = GetNewGameViewPresenter().ArePlayerChipColorsValid(chipColors);
    ASSERT_TRUE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerChipColorsValid_TwoSameColors_ReturnsError)
{
    const std::vector<cxmodel::ChipColor> chipColors
    {
        cxmodel::MakeRed(),
        cxmodel::MakeYellow(),
        cxmodel::MakeYellow()
    };

    const auto status = GetNewGameViewPresenter().ArePlayerChipColorsValid(chipColors);
    ASSERT_FALSE(status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "Discs must have different colors.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerTypesValid_AllHumans_ReturnsSuccess)
{
    const std::vector<cxmodel::PlayerType> playerTypes
    {
        cxmodel::PlayerType::HUMAN,
        cxmodel::PlayerType::HUMAN,
        cxmodel::PlayerType::HUMAN
    };

    const auto status = GetNewGameViewPresenter().ArePlayerTypesValid(playerTypes);
    ASSERT_TRUE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerTypesValid_OneHuman_ReturnsSuccess)
{
    const std::vector<cxmodel::PlayerType> playerTypes
    {
        cxmodel::PlayerType::BOT,
        cxmodel::PlayerType::HUMAN,
        cxmodel::PlayerType::BOT
    };

    const auto status = GetNewGameViewPresenter().ArePlayerTypesValid(playerTypes);
    ASSERT_TRUE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/ArePlayerTypesValid_NoHuman_ReturnsError)
{
    const std::vector<cxmodel::PlayerType> playerTypes
    {
        cxmodel::PlayerType::BOT,
        cxmodel::PlayerType::BOT,
        cxmodel::PlayerType::BOT
    };

    const auto status = GetNewGameViewPresenter().ArePlayerTypesValid(playerTypes);
    ASSERT_FALSE(status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "At least one player must not be a bot.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGameWinnable_TooManyPlayersForTheBoard_ReturnsError)
{
    const size_t inARowValue = 7u; // Too large...
    const size_t nbOfPlayers = 7u; // and too many. Does not fit the board.
    const size_t boardHeight = 6u;
    const size_t boardWidth  = 7u;

    const auto status = GetNewGameViewPresenter().IsNewGameWinnable(inARowValue, nbOfPlayers, boardHeight, boardWidth);
    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGameWinnable_InARowValueTooBig_ReturnsError)
{
    const size_t inARowValue = 8u; // Too large.
    const size_t nbOfPlayers = 2u;
    const size_t boardHeight = 6u;
    const size_t boardWidth  = 7u;

    const auto status = GetNewGameViewPresenter().IsNewGameWinnable(inARowValue, nbOfPlayers, boardHeight, boardWidth);
    ASSERT_FALSE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGameWinnable_JustEnoughPlayersForTheBoardAndInARowFits_ReturnsSuccess)
{
    const size_t inARowValue = 7u;
    const size_t nbOfPlayers = 6u; // Just enough
    const size_t boardHeight = 6u;
    const size_t boardWidth  = 7u;

    const auto status = GetNewGameViewPresenter().IsNewGameWinnable(inARowValue, nbOfPlayers, boardHeight, boardWidth);
    ASSERT_TRUE(status.IsSuccess());
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGameWinnable_TooManyPlayersForTheBoard_TooManyPlayersOrInnapropriateInARowMessageReturned)
{
    const size_t inARowValue = 7u; // Too large...
    const size_t nbOfPlayers = 7u; // and too many. Does not fit the board.
    const size_t boardHeight = 6u;
    const size_t boardWidth  = 7u;

    const auto status = GetNewGameViewPresenter().IsNewGameWinnable(inARowValue, nbOfPlayers, boardHeight, boardWidth);
    ASSERT_EQ(status.GetMessage(), "There is not enough room on the board. Adjust the number of players or the in-a-row value.");
}

TEST_F(MainWindowPresenterTestFixture, /*DISABLED_*/IsNewGameWinnable_InARowValueTooBig_InvalidInARowMessageReturned)
{
    const size_t inARowValue = 8u; // Too large.
    const size_t nbOfPlayers = 2u;
    const size_t boardHeight = 6u;
    const size_t boardWidth  = 7u;

    const auto status = GetNewGameViewPresenter().IsNewGameWinnable(inARowValue, nbOfPlayers, boardHeight, boardWidth);
    ASSERT_EQ(status.GetMessage(), "The in-a-row value does not fit on the board.");
}

namespace
{

class NewGameViewPresenterValidateMock : public NewGameViewPresenterMock
{

public:

    NewGameViewPresenterValidateMock(
        const cxmodel::Status& p_inARowStatus,
        const cxmodel::Status& p_boardDimensionsStatus,
        const cxmodel::Status& p_playerNamesStatus,
        const cxmodel::Status& p_playerChipColorsStatus,
        const cxmodel::Status& p_playerTypesStatus,
        const cxmodel::Status& p_newGameWinnableStatus)
    : m_inARowStatus{p_inARowStatus}
    , m_boardDimensionsStatus{p_boardDimensionsStatus}
    , m_playerNamesStatus{p_playerNamesStatus}
    , m_playerChipColorsStatus{p_playerChipColorsStatus}
    , m_playerTypesStatus{p_playerTypesStatus}
    , m_newGameWinnableStatus{p_newGameWinnableStatus}
    {}

    [[nodiscard]] cxmodel::Status IsInARowValueValid(size_t /*p_inARowValue*/) const override {return m_inARowStatus;}
    [[nodiscard]] cxmodel::Status AreBoardDimensionsValid(size_t /*p_boardHeight*/, size_t /*p_boardWidth*/) const override {return m_boardDimensionsStatus;}
    [[nodiscard]] cxmodel::Status ArePlayerNamesValid(const std::vector<std::string>& /*p_playerNames*/) const override {return m_playerNamesStatus;}
    [[nodiscard]] cxmodel::Status ArePlayerChipColorsValid(const std::vector<cxmodel::ChipColor>& /*p_playerChipColors*/) const override {return m_playerChipColorsStatus;}
    [[nodiscard]] cxmodel::Status ArePlayerTypesValid(const std::vector<cxmodel::PlayerType>& /*p_playerTypes*/) const override {return m_playerTypesStatus;}
    [[nodiscard]] cxmodel::Status IsNewGameWinnable(size_t /*p_inARowValue*/, size_t /*p_nbOfPlayers*/, size_t /*p_boardHeight*/, size_t /*p_boardWidth*/) const override {return m_newGameWinnableStatus;}

private:

    cxmodel::Status m_inARowStatus;
    cxmodel::Status m_boardDimensionsStatus;
    cxmodel::Status m_playerNamesStatus;
    cxmodel::Status m_playerChipColorsStatus;
    cxmodel::Status m_playerTypesStatus;
    cxmodel::Status m_newGameWinnableStatus;
};

// We don't really care about the game information contents, except that we
// need at least one player to get coverage in the `for` loops inside the
// `cxgui::Validate` logic. The tests do not depend on the contents of
// the new game information, but rather on the presenter validations.
[[nodiscard]] cxmodel::NewGameInformation NewGameInformationCreate()
{
    cxmodel::NewGameInformation info;

    info.m_players.push_back(cxmodel::CreatePlayer("Will Ferrell", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN));
    info.m_players.push_back(cxmodel::CreatePlayer("RoboCop", cxmodel::MakeBlue(), cxmodel::PlayerType::BOT));

    return info;
}

} // namespace

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_ValidNewGame_ReturnsSuccess)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess());

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(status.IsSuccess());
}

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_InvalidInARowValue_ReturnsError)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeError("In-a-row invalid"),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess());

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(!status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "In-a-row invalid");
}

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_InvalidBoardDimensions_ReturnsError)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeSuccess(),
                                                     cxmodel::MakeError("Board dimensions invalid"),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess());

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(!status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "Board dimensions invalid");
}

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_InvalidPlayerNames_ReturnsError)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeError("Player names invalid"),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess());

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(!status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "Player names invalid");
}

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_InvalidPlayerChipColors_ReturnsError)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeError("Player chip colors invalid"),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess());

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(!status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "Player chip colors invalid");
}

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_InvalidPlayerTypes_ReturnsError)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeError("Player types invalid"),
                                                     cxmodel::MakeSuccess());

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(!status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "Player types invalid");
}

TEST(INewGameViewPresenter, /*DISABLED_*/Validate_UnwinableGame_ReturnsError)
{
    const NewGameViewPresenterValidateMock presenter(cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeSuccess(),
                                                     cxmodel::MakeError("New game not winnable"));

    const cxmodel::Status status = cxgui::Validate(NewGameInformationCreate(), presenter);

    ASSERT_TRUE(!status.IsSuccess());
    ASSERT_TRUE(status.GetMessage() == "New game not winnable");
}
