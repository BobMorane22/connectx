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
 * @file IMainWindow.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IMAINWINDOW_H_87FB17B9_ABA6_42D6_8B00_1B898BCD3C94
#define IMAINWINDOW_H_87FB17B9_ABA6_42D6_8B00_1B898BCD3C94

#include <cxmodel/include/IObserver.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for creating a main application window.
 *
 * This interface presents the basic utilities needed to create main application windows.
 *
 ************************************************************************************************/
class IMainWindow : public cxmodel::IObserver
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IMainWindow() = default;

    /******************************************************************************************//**
     * @brief Shows the window on the screen.
     *
     * Shows the window on the screen for a user to see.
     *
     * @return @c EXIT_SUCCESS if the window if the window terminated the application without
     *         errors, @c EXIT_FAILURE otherwise.
     *
     ********************************************************************************************/
    virtual int Show() = 0;

};

} // namespace cxgui

#endif // IMAINWINDOW_H_87FB17B9_ABA6_42D6_8B00_1B898BCD3C94
