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
 * @file NewGameInformation.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxmodel/NewGameInformation.h>

std::size_t cxmodel::NewGameInformation::AddPlayer(const Player& p_newPlayer)
{
    m_playersInformation.push_back(p_newPlayer);

    return m_playersInformation.size();
}

std::vector<cxmodel::Player> cxmodel::NewGameInformation::GetNewPlayers() const
{
    return m_playersInformation;
}

size_t cxmodel::NewGameInformation::GetNbOfNewPlayers() const
{
    return m_playersInformation.size();
}

bool cxmodel::operator==(const cxmodel::NewGameInformation& p_lhs, const cxmodel::NewGameInformation& p_rhs)
{
    bool areEqual = (p_lhs.m_gridHeight == p_rhs.m_gridHeight);

    areEqual &= (p_lhs.m_gridWidth == p_rhs.m_gridWidth);
    areEqual &= (p_lhs.m_gridHeight == p_rhs.m_gridHeight);
    areEqual &= (p_lhs.m_inARowValue == p_rhs.m_inARowValue);

    areEqual &= (p_lhs.GetNbOfNewPlayers() == p_rhs.GetNbOfNewPlayers());

    if(!areEqual)
    {
        return false;
    }

    const auto lhsPlayers = p_lhs.GetNewPlayers();
    const auto rhsPlayers = p_rhs.GetNewPlayers();

    for(size_t i = 0; i < p_lhs.GetNbOfNewPlayers(); ++i)
    {
        areEqual &= (lhsPlayers[i] == rhsPlayers[i]);
    }

    return areEqual;
}

bool cxmodel::operator!=(const cxmodel::NewGameInformation& p_lhs, const cxmodel::NewGameInformation& p_rhs)
{
    return !(p_lhs == p_rhs);
}
