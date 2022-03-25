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

#include <cxmodel/NewGameInformation.h>

namespace
{

struct PlayerCreationInfo
{
    PlayerCreationInfo(const std::string& p_name, const cxmodel::ChipColor p_chipColor)
    : m_name{p_name}
    , m_chipColor{p_chipColor}
    {
    }

    std::string m_name;
    cxmodel::ChipColor m_chipColor;
};

cxmodel::NewGameInformation MakeNewGameInformation(size_t p_gridHeight,
                                                   size_t p_gridWidth,
                                                   size_t p_inARowValue,
                                                   const std::vector<PlayerCreationInfo>& p_playersCreationInfo)
{
    cxmodel::NewGameInformation info;
    info.m_gridHeight = p_gridHeight;
    info.m_gridWidth = p_gridWidth;
    info.m_inARowValue = p_inARowValue;

    for(const auto& playerCreationInfo : p_playersCreationInfo)
    {
        info.m_players.push_back(cxmodel::CreatePlayer(playerCreationInfo.m_name, playerCreationInfo.m_chipColor, cxmodel::PlayerType::HUMAN));
    }

    return info;
}

} // namespace

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_TwoSameInformations_ReturnsTrue)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {player1, player2});

    ASSERT_TRUE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_TwoSameInformationsButOrderDiffer_ReturnsFalse)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {player2, player1});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentGridHeight_ReturnsFalse)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(7, 7, 4, {player1, player2});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentGridWidth_ReturnsFalse)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 8, 4, {player1, player2});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentInARowValue_ReturnsFalse)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 5, {player1, player2});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorEqual_DifferentPlayers_ReturnsFalse)
{
    const PlayerCreationInfo player1{"Player1", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Player2", cxmodel::MakeBlue()};
    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});

    const PlayerCreationInfo player3{"Player3", cxmodel::MakeYellow()};
    const PlayerCreationInfo player4{"Player4", cxmodel::MakeGreen()};
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {player3, player4});

    ASSERT_FALSE(gameInfo1 == gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformations_ReturnsFalse)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {player1, player2});

    ASSERT_FALSE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentGridHeight_ReturnsTrue)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(7, 7, 4, {player1, player2});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentGridWidth_ReturnsTrue)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 8, 4, {player1, player2});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentInARowValue_ReturnsTrue)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 5, {player1, player2});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_DifferentPlayersInformations_ReturnsTrue)
{
    const PlayerCreationInfo player1{"Player1", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Player2", cxmodel::MakeBlue()};
    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});

    const PlayerCreationInfo player3{"Player3", cxmodel::MakeYellow()};
    const PlayerCreationInfo player4{"Player4", cxmodel::MakeGreen()};
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {player3, player4});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}

TEST(NewGameInformation, /*DISABLED_*/OperatorNotEqual_TwoSameInformationsButOrderDiffer_ReturnsTrue)
{
    const PlayerCreationInfo player1{"John Doe", cxmodel::MakeRed()};
    const PlayerCreationInfo player2{"Jane Doe", cxmodel::MakeBlue()};

    const cxmodel::NewGameInformation gameInfo1 = MakeNewGameInformation(6, 7, 4, {player1, player2});
    const cxmodel::NewGameInformation gameInfo2 = MakeNewGameInformation(6, 7, 4, {player2, player1});

    ASSERT_TRUE(gameInfo1 != gameInfo2);
}
