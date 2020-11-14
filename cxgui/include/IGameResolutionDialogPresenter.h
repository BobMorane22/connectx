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
 * @file IGameResolutionDialogPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMERESOLUTIONDIALOGPRESENTER_H_3EBAACE1_3C59_4BB0_B395_9DD85C080FB7
#define IGAMERESOLUTIONDIALOGPRESENTER_H_3EBAACE1_3C59_4BB0_B395_9DD85C080FB7

#include <string>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for game resolution window presenters.
 *
 ************************************************************************************************/
class IGameResolutionDialogPresenter
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IGameResolutionDialogPresenter() = default;

    /******************************************************************************************//**
     * @brief Retrieves the game resolution message.
     *
     * @return The game resolution message (or an empty string if the game has not been resolved).
     *
     ********************************************************************************************/
    virtual std::string GetResolutionMessage() const = 0;
};

} // namespace cxgui

#endif // IGAMERESOLUTIONDIALOGPRESENTER_H_3EBAACE1_3C59_4BB0_B395_9DD85C080FB7
