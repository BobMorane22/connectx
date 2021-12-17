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
 * @file GameResolutionStrategyTestFixture.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMERESOLUTIONSTRATEGYTESTFIXTURE_H_FC3AC7C1_2CB4_4147_94BC_E245D3FFA0DA
#define GAMERESOLUTIONSTRATEGYTESTFIXTURE_H_FC3AC7C1_2CB4_4147_94BC_E245D3FFA0DA

#include <gtest/gtest.h>

#include <cxmodel/IConnectXLimits.h>
#include <cxmodel/Player.h>

/*************************************************************************************************
 * @brief Fixture for testing game resolution strategies.
 *
 * Specialize this fixture to create different game scenarios.
 *
 *************************************************************************************************/
class GameResolutionStrategyTestFixture : public ::testing::Test
{

public:

    /*********************************************************************************************
     * @brief Validates a game encoded into an ASCII string.
     *
     * The ascii format for a game is a board is the following:
     *
     *     |  | | | | | | |
     *     |  | | | | | | |
     *     |7w| | | | | | |
     *     |5 |6| | | | | |
     *     |3 |4| | | | | |
     *     |1 |2| | | | | |
     *
     * In which numbers represent the nth move (e.g. 6 means the 6th move) and letters game states.
     * Possible game states are:
     *
     *   - Ongoing : represented by a move number alone.
     *   - Won     : represented by a move number followed by the letter 'w'
     *   - Tied    : represented by a move number followed by the letter 't'
     *
     * For every moved marked as 'Ongoing', the absence of a win and of a tie are validated. In this
     * case, the game is considered not valid if either a win or a tie is detected. For every move
     * marked as 'Won', the absence of a tied is checked as well as the presence of a win. If any one
     * of these conditions is not met, the game is consideted invalid. Finally, for every move marked
     * as 'Tied', the absence of a win and the presence is checked. If any one of these conditions is
     * not met, the game is considered invalid.
     *
     * @param p_playerList  The list of players.
     * @param p_inARowValue The in-a-row value for the game.
     * @param p_asciiGame   The game encoded as an ascii string (see expexted format above).
     *
     * @return `true` if the game is valid, `false` otherwise.
     *
     ************************************************************************************************/
    [[nodiscard]] bool ValidateGame(const std::vector<cxmodel::Player>& p_playerList,
                                    const size_t p_inARowValue,
                                    const std::string& p_asciiGame);

private:

    class LimitsModelMock : public cxmodel::IConnectXLimits
    {

    public:

        size_t GetMinimumGridHeight() const override {return 6u;};
        size_t GetMinimumGridWidth() const override {return 7u;};
        size_t GetMinimumInARowValue() const override {return 3u;};
        size_t GetMaximumGridHeight() const override {return 9u;};
        size_t GetMaximumGridWidth() const override {return 10u;};
        size_t GetMaximumInARowValue() const override {return 7u;};
        size_t GetMinimumNumberOfPlayers() const override {return 2u;};
        size_t GetMaximumNumberOfPlayers() const override {return 7u;};
    };

    const LimitsModelMock m_model;
};

#endif // GAMERESOLUTIONSTRATEGYTESTFIXTURE_H_FC3AC7C1_2CB4_4147_94BC_E245D3FFA0DA
