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
 * @file IPlayer.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef IPLAYER_H_551C158B_76C1_424D_B20B_11D25D37A7EB
#define IPLAYER_H_551C158B_76C1_424D_B20B_11D25D37A7EB

#include <memory>
#include <string>

#include <cxmodel/ChipColor.h>

namespace cxmodel
{

class IChip;
class IPlayer;

}

namespace cxmodel
{

/**********************************************************************************************//**
 * Different player types.
 *
 *************************************************************************************************/
enum class PlayerType
{
    HUMAN,
    BOT,
};

/*********************************************************************************************//**
 * @brief This class represent a Connect X player.
 *
 * A player has a name and owns a chip, with which he plays on the board.
 *
 ************************************************************************************************/
class IPlayer
{

public:

    virtual ~IPlayer() = default;

    /******************************************************************************************//**
     * @brief Get the player's name.
     *
     * @return The player's name.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::string GetName() const = 0;

    /******************************************************************************************//**
     * @brief Get the player's chip.
     *
     * @return The player's chip.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual const IChip& GetChip() const = 0;

    /******************************************************************************************//**
     * @brief Indicates if the player is managed by Connect X.
     *
     * @return `true` if the player is managed by Connect X, `false` otherwise.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual bool IsManaged() const = 0;
};

/**********************************************************************************************//**
 * Factory for creating players.
 *
 * @param p_name
 *      The name of the player.
 * @param p_chipColor
 *      The chip color associated with the player.
 * @param p_type
 *      The type of player.
 *
 * @pre The name must not be empty.
 * @pre The chip color must not be transparent.
 * @post A valid player is created.
 *
 * @return The player. If creation failed (for example, if preconditions are not met), an
 *         null player object is returned.
 *
 *************************************************************************************************/
[[nodiscard]] std::unique_ptr<cxmodel::IPlayer> CreatePlayer(const std::string& p_name,
                                                             const ChipColor& p_chipColor,
                                                             PlayerType p_type);

/**********************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs The left hand side player.
 * @param p_rhs The right hand side player.
 *
 * @return `true` if the player share the same disc, `false`otherwise. Note that two different
 *         players can share the same name.
 *
 *************************************************************************************************/
bool operator==(const IPlayer& p_lhs, const IPlayer& p_rhs);

/**********************************************************************************************//**
 * @brief Not-equal-to operator.
 *
 * @param p_lhs The left hand side player.
 * @param p_rhs The right hand side player.
 *
 * @return `true` if the player DO NOT share the same disc, `false`otherwise.
 *
 ************************************************************************************************/
bool operator!=(const IPlayer& p_lhs, const IPlayer& p_rhs);

} // namespace cxmodel

#endif // IPLAYER_H_551C158B_76C1_424D_B20B_11D25D37A7EB
