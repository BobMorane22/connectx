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

#include <Board.h>
#include <IConnectXLimits.h>
#include <Player.h>

class GameResolutionStrategyTestFixture : public ::testing::Test
{

public:

    void DropChip(size_t p_column,
                  const cxmodel::IChip& p_chip,
                  cxmodel::IBoard& p_board,
                  std::vector<cxmodel::IBoard::Position>& p_takenPositions);

    static std::vector<cxmodel::Player> MakeTwoPlayersList();
    static std::vector<cxmodel::Player> MakeThreePlayersList();

    cxmodel::Board MakeClassicBoard() const;
    cxmodel::Board Make9By9Board() const;
    cxmodel::Board Make6By10Board() const;
    cxmodel::Board Make9By8Board() const;

private:

    class LimitsModelMock : public cxmodel::IConnectXLimits
    {
        size_t GetMinimumGridHeight() const override {return 6u;};
        size_t GetMinimumGridWidth() const override {return 7u;};
        size_t GetMinimumInARowValue() const override {return 3u;};
        size_t GetMaximumGridHeight() const override {return 9u;};
        size_t GetMaximumGridWidth() const override {return 10u;};
        size_t GetMaximumInARowValue() const override {return 7u;};
        size_t GetMinimumNumberOfPlayers() const override {return 2u;};
        size_t GetMaximumNumberOfPlayers() const override {return 3u;};
    };

    const LimitsModelMock m_model;
};

#endif // GAMERESOLUTIONSTRATEGYTESTFIXTURE_H_FC3AC7C1_2CB4_4147_94BC_E245D3FFA0DA
