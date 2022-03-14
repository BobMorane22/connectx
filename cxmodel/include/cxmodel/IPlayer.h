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

#include <string>

namespace cxmodel
{

class IChip;

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

} // namespace cxmodel

#endif // IPLAYER_H_551C158B_76C1_424D_B20B_11D25D37A7EB
