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
 * @file INewGameViewController.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef INEWGAMEVIEWCONTROLLER_H_C4599F8B_25C5_4F7A_9A04_07CE371790CE
#define INEWGAMEVIEWCONTROLLER_H_C4599F8B_25C5_4F7A_9A04_07CE371790CE

#include <cxmodel/NewGameInformation.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Controller for the 'New Game' view.
 *
 ************************************************************************************************/
class INewGameViewController
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~INewGameViewController() = default;

    /******************************************************************************************//**
     * @brief Start control handler.
     *
     * @param The game information used to start the game.
     *
     * Called when the game is started.
     *
     ********************************************************************************************/
    virtual void OnStart(const cxmodel::NewGameInformation p_gameInformation) = 0;

};

} // namespace cxgui

#endif // INEWGAMEVIEWCONTROLLER_H_C4599F8B_25C5_4F7A_9A04_07CE371790CE
