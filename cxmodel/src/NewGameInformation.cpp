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

#include <cxinv/include/assertion.h>

#include <NewGameInformation.h>

bool cxmodel::operator==(const cxmodel::PlayerInformation& p_lhs, const cxmodel::PlayerInformation& p_rhs)
{
    return (p_lhs.m_name == p_rhs.m_name) && (p_lhs.m_discColor == p_rhs.m_discColor);
}

bool cxmodel::operator!=(const cxmodel::PlayerInformation& p_lhs, const cxmodel::PlayerInformation& p_rhs)
{
    return !(p_lhs == p_rhs);
}

std::size_t cxmodel::NewGameInformation::AddPlayer(const PlayerInformation& p_playerInformation)
{
    m_playersInformation.push_back(p_playerInformation);

    return m_playersInformation.size();
}

cxmodel::NewGameInformation::PlayersInformation cxmodel::NewGameInformation::GetPlayersInformation() const
{
    return m_playersInformation;
}

size_t cxmodel::NewGameInformation::GetNbOfPlayers() const
{
    return m_playersInformation.size();
}

bool cxmodel::operator==(const cxmodel::NewGameInformation& p_lhs, const cxmodel::NewGameInformation& p_rhs)
{
    bool areEqual = (p_lhs.m_gridHeight == p_rhs.m_gridHeight);

    areEqual &= (p_lhs.m_gridWidth == p_rhs.m_gridWidth);
    areEqual &= (p_lhs.m_gridHeight == p_rhs.m_gridHeight);
    areEqual &= (p_lhs.m_inARowValue == p_rhs.m_inARowValue);

    areEqual &= (p_lhs.GetNbOfPlayers() == p_rhs.GetNbOfPlayers());

    if(!areEqual)
    {
        return false;
    }

    const auto lhsPlayers = p_lhs.GetPlayersInformation();
    const auto rhsPlayers = p_rhs.GetPlayersInformation();

    for(size_t i = 0; i < p_lhs.GetNbOfPlayers(); ++i)
    {
        areEqual &= (lhsPlayers[i] == rhsPlayers[i]);
    }

    return areEqual;
}

bool cxmodel::operator!=(const cxmodel::NewGameInformation& p_lhs, const cxmodel::NewGameInformation& p_rhs)
{
    return !(p_lhs == p_rhs);
}
