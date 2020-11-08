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
 * @file GameResolutionStrategyTestFixture.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <Disc.h>

#include "GameResolutionStrategyTestFixture.h"

void GameResolutionStrategyTestFixture::DropChip(size_t p_column,
                                                    const cxmodel::IChip& p_chip,
                                                    cxmodel::IBoard& p_board,
                                                    std::vector<cxmodel::IBoard::Position>& p_takenPositions)
{
    cxmodel::IBoard::Position position;
    ASSERT_TRUE(p_board.DropChip(p_column, p_chip, position));

    p_takenPositions.push_back(position);
}

std::vector<cxmodel::Player> GameResolutionStrategyTestFixture::MakeTwoPlayersList()
{
    const std::vector<cxmodel::Player> twoPlayersList
    {
        {"First player", cxmodel::MakeBlue()},
        {"Second player", cxmodel::MakeRed()}
    };

    EXPECT_EQ(twoPlayersList.size(), 2u);

    return twoPlayersList;
}

std::vector<cxmodel::Player> GameResolutionStrategyTestFixture::MakeThreePlayersList()
{
    auto threePlayersList = MakeTwoPlayersList();

    const cxmodel::Player third{"Third player", cxmodel::MakeYellow()};
    threePlayersList.push_back(third);

    EXPECT_EQ(threePlayersList.size(), 3u);

    return threePlayersList;
}

cxmodel::Board GameResolutionStrategyTestFixture::MakeClassicBoard() const
{
    return cxmodel::Board(6u, 7u, m_model);
}

cxmodel::Board GameResolutionStrategyTestFixture::Make9By9Board() const
{
    return cxmodel::Board(9u, 9u, m_model);
}

cxmodel::Board GameResolutionStrategyTestFixture::Make6By10Board() const
{
    return cxmodel::Board(6u, 10u, m_model);
}

cxmodel::Board GameResolutionStrategyTestFixture::Make8By9Board() const
{
    return cxmodel::Board(8u, 9u, m_model);
}
