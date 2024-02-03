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
 * @file IButton.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IBUTTON_H_1C2926A8_3089_41A9_A788_6E72D152DB1D
#define IBUTTON_H_1C2926A8_3089_41A9_A788_6E72D152DB1D

#include <cxgui/ISignal.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief A clickable button.
 *
 *************************************************************************************************/
class IButton : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IButton() = default;

    /******************************************************************************************//**
     * @brief Get the signal for when the button is clicked by the user.
     *
     * @return A signal to connect to for when the button is clicked.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<ISignal<void>> OnClicked() = 0;

};

} // namespace cxgui

#endif // IBUTTON_H_1C2926A8_3089_41A9_A788_6E72D152DB1D
