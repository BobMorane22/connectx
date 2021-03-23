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
 * @file TwoPlayersGameResolutionStrategyTestFixture.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef TWOPLAYERSGAMERESOLUTIONSTRATEGYTESTFIXTURE_H_B6F0D29A_94C6_4A5E_9AEF_1A2607962AF4
#define TWOPLAYERSGAMERESOLUTIONSTRATEGYTESTFIXTURE_H_B6F0D29A_94C6_4A5E_9AEF_1A2607962AF4

#include "GameResolutionStrategyTestFixture.h"

/*************************************************************************************************
 * @brief Game resolution strategy test fixture for two players game.
 *
 ************************************************************************************************/
class TwoPlayersGameResolutionStrategyTestFixture : public GameResolutionStrategyTestFixture
{

public:

    [[nodiscard]] std::vector<cxmodel::Player> CreatePlayersList() const override
    {
        return {
            {"First player", cxmodel::MakeBlue()},
            {"Second player", cxmodel::MakeRed()}
        };
    }

};

#endif // TWOPLAYERSGAMERESOLUTIONSTRATEGYTESTFIXTURE_H_B6F0D29A_94C6_4A5E_9AEF_1A2607962AF4
