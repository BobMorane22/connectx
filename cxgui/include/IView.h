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
 * @file IView.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IVIEW_H_DADC38E4_6E1F_4DED_A6F9_5D66F1558C89
#define IVIEW_H_DADC38E4_6E1F_4DED_A6F9_5D66F1558C89

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Replaceable window contents.
 *
 * Views are meant to be a part of a window which can get swapped for another view at runtime.
 * With this tool, you can have a window display different content depending on the state of
 * the application. The visible view is the last onw that was activated.
 *
 ************************************************************************************************/
class IView
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IView() = default;

    /******************************************************************************************//**
     * @brief Activate the view.
     *
     * Activating a view means that in the eyes of the containing window, it becomes the new
     * view in place. If the window is refreshed, it is this new view that will be displayed.
     * Note that it is the responsibility of the containing window to refresh itself, the view
     * should not know about the window.
     *
     ********************************************************************************************/
    virtual void Activate() = 0;

    /******************************************************************************************//**
     * @brief Deactivate the view.
     *
     * Deactivating a view means cleaning up all resources and preparing for a clean exit. After
     * this call, the window should have no leftovers from the view and should be ready to
     * switch to another view without conflict.
     *
     ********************************************************************************************/
    virtual void DeActivate() = 0;

};

} // namespace cxgui

#endif // IVIEW_H_DADC38E4_6E1F_4DED_A6F9_5D66F1558C89
