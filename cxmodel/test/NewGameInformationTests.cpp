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

    const size_t gridHeight = 6;
    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;
    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_TRUE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_TwoSameInformationsButOrderDiffer_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;

    // Order differs here:
    gameInfo2.AddPlayer(playerInfo2);
    gameInfo2.AddPlayer(playerInfo1);

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentGridHeight_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = 6;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = 7;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;

    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentGridWidth_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = 7;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = 8;
    gameInfo2.m_inARowValue = inARowValue;
    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentInARowValue_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t gridWidth = 7;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = 4;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = 5;
    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentPlayersInformations_ReturnsFalse)
{
    const size_t gridHeight = 6;
    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer({"Player1", "Red"});
    gameInfo1.AddPlayer({"Player2", "Blue"});

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;
    gameInfo2.AddPlayer({"Player3", "Yellow"});
    gameInfo2.AddPlayer({"Player4", "Green"});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformations_ReturnsFalse)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;
    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_FALSE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentGridHeight_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = 6;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = 7;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;

    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentGridWidth_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = 7;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = 8;
    gameInfo2.m_inARowValue = inARowValue;
    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentInARowValue_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t gridWidth = 7;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = 4;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = 5;
    gameInfo2.AddPlayer(playerInfo1);
    gameInfo2.AddPlayer(playerInfo2);

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentPlayersInformations_ReturnsTrue)
{
    const size_t gridHeight = 6;
    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer({"Player1", "Red"});
    gameInfo1.AddPlayer({"Player2", "Blue"});

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;
    gameInfo2.AddPlayer({"Player3", "Yellow"});
    gameInfo2.AddPlayer({"Player4", "Green"});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformationsButOrderDiffer_ReturnsTrue)
{
    const cxmodel::PlayerInformation playerInfo1{"John Doe", "Red"};
    const cxmodel::PlayerInformation playerInfo2{"Jane Doe", "Blue"};

    const size_t gridHeight = 6;
    const size_t gridWidth = 7;
    const size_t inARowValue = 4;

    cxmodel::NewGameInformation gameInfo1;
    gameInfo1.m_gridHeight = gridHeight;
    gameInfo1.m_gridWidth = gridWidth;
    gameInfo1.m_inARowValue = inARowValue;
    gameInfo1.AddPlayer(playerInfo1);
    gameInfo1.AddPlayer(playerInfo2);

    cxmodel::NewGameInformation gameInfo2;
    gameInfo2.m_gridHeight = gridHeight;
    gameInfo2.m_gridWidth = gridWidth;
    gameInfo2.m_inARowValue = inARowValue;

    // Order differs here:
    gameInfo2.AddPlayer(playerInfo2);
    gameInfo2.AddPlayer(playerInfo1);

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}
