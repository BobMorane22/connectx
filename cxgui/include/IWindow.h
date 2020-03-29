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
 * @file IWindow.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IWINDOW_H_4807796E_6C76_4D0A_BF7D_81534795BA29
#define IWINDOW_H_4807796E_6C76_4D0A_BF7D_81534795BA29

#include <cxmodel/include/IObserver.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Interface for creating a standard window.
 *
 * This interface presents the basic utilities needed to create windows.
 *
 ************************************************************************************************/
class IWindow : public cxmodel::IObserver
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IWindow() = default;

    /******************************************************************************************//**
     * @brief Shows the window on the screen.
     *
     * Shows the window on the screen for a user to see.
     *
     ********************************************************************************************/
    virtual void Show() = 0;

};

} // namespace cxgui

#endif // IWINDOW_H_4807796E_6C76_4D0A_BF7D_81534795BA29
