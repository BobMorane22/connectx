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
 * @file IOnOffSwitch.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef IONOFFSWITCH_H_19A0A6E4_FA1D_4E24_B071_BB06B97181AC
#define IONOFFSWITCH_H_19A0A6E4_FA1D_4E24_B071_BB06B97181AC

#include <cxgui/IWidget.h>

namespace cxgui
{
    enum class OnOffState;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief On/Off switch widget.
 *
 * At any time, the widget can only have one of two states: "On" or "Off". In between states
 * are not possible.
 *
 *************************************************************************************************/
class IOnOffSwitch : public cxgui::IWidget
{

public:

    /**********************************************************************************************//**
     * @brief Default destructor.
     *
     *************************************************************************************************/
    virtual ~IOnOffSwitch() = default;

    /**********************************************************************************************//**
     * @brief Gets the state of the switch.
     *
     * @return The state of the switch (On/Off).
     *
     *************************************************************************************************/
    [[nodiscard]] virtual OnOffState GetState() const = 0;

    /**********************************************************************************************//**
     * @brief Updates the state of the switch.
     *
     * @param p_newState The new state of the switch.
     *
     *************************************************************************************************/
    virtual void SetState(OnOffState p_newState) = 0;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override = 0;
    [[nodiscard]] size_t GetHeight() const override = 0;
    void SetReadOnly(bool p_isReadOnly) override = 0;

};

} // namespace cxgui

#endif // IONOFFSWITCH_H_19A0A6E4_FA1D_4E24_B071_BB06B97181AC
