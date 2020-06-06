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
 * @file NewGameInformationTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <NewGameInformation.h>

namespace
{
cxmodel::NewGameInformation MakeNewGameInformation(size_t p_gridHeight,
                                                   size_t p_gridWidth,
                                                   size_t p_inARowValue,
                                                   const cxmodel::PlayersInformation& p_playersInfo)
{
    cxmodel::NewGameInformation info;
    info.m_gridHeight = p_gridHeight;
    info.m_gridWidth = p_gridWidth;
    info.m_inARowValue = p_inARowValue;

    for(const auto& playerInfo : p_playersInfo)
    {
        info.AddPlayer(playerInfo);
    }

    return info;
}

} // namespace

TEST(PlayerInformation, /*DISABLED_*/OperatorEqual_TwoSamePlayerInformations_ReturnsTrue)
{
    const cxmodel::PlayerInformation info1{"John Doe", "Red"};
    const cxmodel::PlayerInformation info2{"John Doe", "Red"};

    ASSERT_TRUE(info1 == info2);
}

TEST(PlayerInformation, /*DISABLED_*/OperatorEqual_TwoDifferentNames_ReturnsFalse)
{
    const cxmodel::PlayerInformation info1{"John Doe", "Red"};
    const cxmodel::PlayerInformation info2{"Jane Doe", "Red"};

    ASSERT_FALSE(info1 == info2);
}

TEST(PlayerInformation, /*DISABLED_*/OperatorEqual_TwoDifferentDiscColors_ReturnsFalse)
{
    const cxmodel::PlayerInformation info1{"John Doe", "Red"};
    const cxmodel::PlayerInformation info2{"John Doe", "Blue"};

    ASSERT_FALSE(info1 == info2);
}

TEST(PlayerInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformations_ReturnsFalse)
{
    const cxmodel::PlayerInformation info1{"John Doe", "Red"};
    const cxmodel::PlayerInformation info2{"John Doe", "Red"};

    ASSERT_FALSE(info1 != info2);
}

TEST(PlayerInformation, /*DISABLED_*/OperatorNotEqual_TwoDifferentNames_ReturnsTrue)
{
    const cxmodel::PlayerInformation info1{"John Doe", "Red"};
    const cxmodel::PlayerInformation info2{"Jane Doe", "Red"};

    ASSERT_TRUE(info1 != info2);
}

TEST(PlayerInformation, /*DISABLED_*/OperatorNotEqual_TwoDifferentDiscColors_ReturnsFalse)
{
    const cxmodel::PlayerInformation info1{"John Doe", "Red"};
    const cxmodel::PlayerInformation info2{"John Doe", "Blue"};

    ASSERT_TRUE(info1 != info2);
}

TEST(NewGameInformation, /*DISABLED_*/AddAPlayer_OnePlayer_ReturnsOne)
{
    const cxmodel::PlayerInformation playerInfo{"John Doe", "Red"};

    cxmodel::NewGameInformation gameInfo;
    gameInfo.AddPlayer(playerInfo);

    ASSERT_EQ(gameInfo.GetNbOfPlayers(), 1);
}

TEST(NewGameInformation, /*DISABLED_*/AddPlayer_TwoPlayers_ReturnsTwo)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    cxmodel::NewGameInformation gameInfo;
    gameInfo.AddPlayer(playerInfo1);
    gameInfo.AddPlayer(playerInfo2);

    ASSERT_EQ(gameInfo.GetNbOfPlayers(), 2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_TwoSameInformations_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});

    ASSERT_TRUE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_TwoSameInformationsButOrderDiffer_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {playerInfo2, playerInfo1});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentGridHeight_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(7, 7, 4, {playerInfo1, playerInfo2});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentGridWidth_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 8, 4, {playerInfo1, playerInfo2});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentInARowValue_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 5, {playerInfo1, playerInfo2});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentPlayersInformations_ReturnsFalse)
{
    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {{"Player1", "Red"}, {"Player2", "Blue"}});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {{"Player3", "Yellow"}, {"Player4", "Green"}});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformations_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});

    ASSERT_FALSE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentGridHeight_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(7, 7, 4, {playerInfo1, playerInfo2});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentGridWidth_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 8, 4, {playerInfo1, playerInfo2});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentInARowValue_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 5, {playerInfo1, playerInfo2});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentPlayersInformations_ReturnsTrue)
{
    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {{"Player1", "Red"}, {"Player2", "Blue"}});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {{"Player3", "Yellow"}, {"Player4", "Green"}});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformationsButOrderDiffer_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {playerInfo1, playerInfo2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {playerInfo2, playerInfo1});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}
