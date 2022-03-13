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
 * @file Player.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef PLAYER_H_DAB68678_E251_4176_8E82_D3D8339D47B2
#define PLAYER_H_DAB68678_E251_4176_8E82_D3D8339D47B2

#include <memory>

#include "IChip.h"
#include "IPlayer.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief This class represent a Connect X player.
 *
 ************************************************************************************************/
class Player : public IPlayer
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre The player name is not empty.
     *
     * @param p_name      The player name.
     * @param p_chipColor The player's chip color.
     *
     ********************************************************************************************/
    Player(const std::string& p_name, const ChipColor& p_chipColor);

    /******************************************************************************************//**
     * @brief Copy constructor.
     *
     * @param p_player The player to copy.
     *
     ********************************************************************************************/
    Player(const Player& p_player);

    /******************************************************************************************//**
     * @brief Copy assignment operator.
     *
     * @param p_player The player to copy-assign.
     *
     ********************************************************************************************/
    Player& operator=(const Player& p_player);

    // cxmodel::IPlayer:
    [[nodiscard]] std::string GetName() const override;
    [[nodiscard]] const IChip& GetChip() const override;

private:

    std::string m_name;
    std::unique_ptr<IChip> m_chip;

};

/******************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs The left hand side player.
 * @param p_rhs The right hand side player.
 *
 * @return `true` if the player share the same disc, `false`otherwise. Note that two different
 *         players can share the same name.
 *
 ********************************************************************************************/
bool operator==(const Player& p_lhs, const Player& p_rhs);

/******************************************************************************************//**
 * @brief Not-equal-to operator.
 *
 * @param p_lhs The left hand side player.
 * @param p_rhs The right hand side player.
 *
 * @return `true` if the player DO NOT share the same disc, `false`otherwise.
 *
 ********************************************************************************************/
bool operator!=(const Player& p_lhs, const Player& p_rhs);

} // namespace cxmodel

#endif // PLAYER_H_DAB68678_E251_4176_8E82_D3D8339D47B2
