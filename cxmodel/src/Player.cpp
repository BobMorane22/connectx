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
 * @file Player.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxmodel/Disc.h>
#include <cxmodel/Player.h>

cxmodel::Player::Player(const std::string p_name, const cxmodel::ChipColor& p_chipColor)
 : m_name{p_name}
 , m_chip{std::make_unique<cxmodel::Disc>(p_chipColor)}
{
    PRECONDITION(!p_name.empty());

    POSTCONDITION(!m_name.empty());
    POSTCONDITION(m_chip);
}

cxmodel::Player::Player(const Player& p_player)
: m_name{p_player.GetName()}
{
    const cxmodel::IChip& playerChip = p_player.GetChip();
    m_chip = std::make_unique<cxmodel::Disc>(playerChip.GetColor());

    POSTCONDITION(!m_name.empty());
    POSTCONDITION(m_chip);
}

cxmodel::Player& cxmodel::Player::operator=(const cxmodel::Player& p_player)
{
    if(this != &p_player)
    {
        this->m_name = p_player.GetName();

        const cxmodel::IChip& playerChip = p_player.GetChip();
        this->m_chip = std::make_unique<cxmodel::Disc>(playerChip.GetColor());
    }

    POSTCONDITION(!this->m_name.empty());
    POSTCONDITION(this->m_chip);

    return *this;
}

std::string cxmodel::Player::GetName() const
{
    return m_name;
}

const cxmodel::IChip& cxmodel::Player::GetChip() const
{
    return *m_chip;
}

bool cxmodel::operator==(const cxmodel::Player& p_lhs, const cxmodel::Player& p_rhs)
{
    return p_lhs.GetChip() == p_rhs.GetChip();
}

bool cxmodel::operator!=(const cxmodel::Player& p_lhs, const cxmodel::Player& p_rhs)
{
    return !(p_lhs == p_rhs);
}
