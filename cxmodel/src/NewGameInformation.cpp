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

cxmodel::NewGameInformation::NewGameInformation(NewGameInformation&& p_other)
{
    m_gridHeight = p_other.m_gridHeight;
    m_gridWidth = p_other.m_gridWidth;
    m_inARowValue = p_other.m_inARowValue;

    m_players = std::move(p_other.m_players);
}

cxmodel::NewGameInformation& cxmodel::NewGameInformation::operator=(NewGameInformation&& p_other)
{
    *this = NewGameInformation(std::move(p_other));

    return *this;
}

bool cxmodel::operator==(const cxmodel::NewGameInformation& p_lhs, const cxmodel::NewGameInformation& p_rhs)
{
    bool areEqual = true;

    areEqual &= (p_lhs.m_gridWidth == p_rhs.m_gridWidth);
    areEqual &= (p_lhs.m_gridHeight == p_rhs.m_gridHeight);
    areEqual &= (p_lhs.m_inARowValue == p_rhs.m_inARowValue);

    areEqual &= (p_lhs.m_players.size() == p_rhs.m_players.size());

    if(!areEqual)
    {
        return false;
    }

    const auto lhsPlayers = p_lhs.m_players;
    const auto rhsPlayers = p_rhs.m_players;

    for(size_t i = 0u; i < p_lhs.m_players.size(); ++i)
    {
        areEqual &= (*lhsPlayers[i] == *rhsPlayers[i]);
    }

    return areEqual;
}

bool cxmodel::operator!=(const cxmodel::NewGameInformation& p_lhs, const cxmodel::NewGameInformation& p_rhs)
{
    return !(p_lhs == p_rhs);
}
