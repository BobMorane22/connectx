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
 * @file WinGameResolutionStrategyTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <memory>

#include <gtest/gtest.h>

#include <Board.h>
#include <Disc.h>
#include <IConnectXLimits.h>
#include <WinGameResolutionStrategy.h>

class WinGameResolutionStrategyTestFixture : public ::testing::Test
{

public:

    void DropChip(size_t p_column,
                  const cxmodel::IChip& p_chip,
                  cxmodel::IBoard& p_board,
                  std::vector<cxmodel::IBoard::Position>& p_takenPositions)
    {
        cxmodel::IBoard::Position position;
        ASSERT_TRUE(p_board.DropChip(p_column, p_chip, position));

        p_takenPositions.push_back(position);
    }

    static std::vector<cxmodel::Player> MakeTwoPlayersList()
    {
        const std::vector<cxmodel::Player> twoPlayersList
        {
            {"First player", cxmodel::MakeBlue()},
            {"Second player", cxmodel::MakeRed()}
        };

        EXPECT_EQ(twoPlayersList.size(), 2u);

        return twoPlayersList;
    }

    static std::vector<cxmodel::Player> MakeThreePlayersList()
    {
        auto threePlayersList = MakeTwoPlayersList();

        const cxmodel::Player third{"Third player", cxmodel::MakeYellow()};
        threePlayersList.push_back(third);

        EXPECT_EQ(threePlayersList.size(), 3u);

        return threePlayersList;
    }

    cxmodel::Board MakeClassicBoard() const {return cxmodel::Board(6u, 7u, m_model);}
    cxmodel::Board Make9By9Board() const {return cxmodel::Board(9u, 9u, m_model);}
    cxmodel::Board Make6By10Board() const {return cxmodel::Board(6u, 10u, m_model);}

private:

    class LimitsModelMock : public cxmodel::IConnectXLimits
    {
        size_t GetMinimumGridHeight() const override {return 6u;};
        size_t GetMinimumGridWidth() const override {return 7u;};
        size_t GetMinimumInARowValue() const override {return 3u;};
        size_t GetMaximumGridHeight() const override {return 9u;};
        size_t GetMaximumGridWidth() const override {return 10u;};
        size_t GetMaximumInARowValue() const override {return 5u;};
        size_t GetMinimumNumberOfPlayers() const override {return 2u;};
        size_t GetMaximumNumberOfPlayers() const override {return 3u;};
    };

    const LimitsModelMock m_model;
};

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicBoardNoDiscs_ReturnsFalse)
{
    const cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_9By9BoardNoDiscs_ReturnsFalse)
{
    const cxmodel::Board board = Make9By9Board();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardNoDiscs_ReturnsFalse)
{
    const cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalWinBottomLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalNoWinBottomLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalWinBottomLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalNoWinBottomLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalWinBottomRightCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalNoWinBottomRightCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalWinBottomRightCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalNoWinBottomRightCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalWinTopLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalNoWinTopLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalWinTopLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalNoWinTopLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalWinTopRightCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardHorizontalNoWinTopRightCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalWinTopRightCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardHorizontalNoWinTopRightCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalWinBottomLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalNoWinBottomLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalWinBottomLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalNoWinBottomLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalWinBottomRightCorner_ReturnsTrue)
{

    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalNoWinBottomRightCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalWinBottomRightCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalNoWinBottomRightCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalWinTopLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalNoWinTopLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalWinTopLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalNoWinTopLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalWinTopRightCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardVerticalNoWinTopRightCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalWinTopRightCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardVerticalNoWinTopRightCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalUpwardWinBottomLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalUpwardNoWinBottomLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalUpwardWinBottomLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalUpwardNoWinBottomLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalUpwardWinTopRightCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalUpwardNoWinTopRightCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalUpwardWinTopRightCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalUpwardNoWinTopRightCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalDownwardWinBottomRightCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalDownwardNoWinBottomRightCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalDownwardWinBottomRightCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[1].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalDownwardNoWinBottomRightCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(8u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_ClassicGameBoardDiagonalDownwardWinTopLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, DISABLED_Handle_ClassicGameBoardDiagonalDownwardNoWinTopLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = MakeClassicBoard();
    const size_t inARowValue = 4u;
    const std::vector<cxmodel::Player> players = MakeTwoPlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle()); // Fails here (there is a win...)
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(5u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalDownwardWinTopLeftCorner_ReturnsTrue)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[0].GetChip(), board, takenPositions);

    ASSERT_TRUE(strategy.Handle());
}

TEST_F(WinGameResolutionStrategyTestFixture, /*DISABLED_*/Handle_6By10GameBoardDiagonalDownwardNoWinTopLeftCorner_ReturnsFalse)
{
    cxmodel::Board board = Make6By10Board();
    const size_t inARowValue = 5u;
    const std::vector<cxmodel::Player> players = MakeThreePlayersList();
    std::vector<cxmodel::IBoard::Position> takenPositions;
    ASSERT_TRUE(takenPositions.empty());

    cxmodel::WinGameResolutionStrategy strategy{board, inARowValue, players, takenPositions};

    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(4u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(0u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(1u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(8u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(9u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(2u, players[0].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(6u, players[1].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(7u, players[2].GetChip(), board, takenPositions);    ASSERT_FALSE(strategy.Handle());
    DropChip(3u, players[0].GetChip(), board, takenPositions);

    ASSERT_FALSE(strategy.Handle());
}
