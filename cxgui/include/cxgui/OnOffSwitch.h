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
 * @file OnOffSwitch.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8
#define ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8

#include <gtkmm/switch.h>

#include <cxgui/IOnOffSwitch.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief A switch that is either "On" or "Off".
 *
 *************************************************************************************************/
class OnOffSwitch : public cxgui::IOnOffSwitch
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     *********************************************************************************************/
    OnOffSwitch();

    // cxgui::IOnOffSwitch:
    [[nodiscard]] OnOffState GetState() const override;
    void SetState(OnOffState p_newState) override;
    void StateChangedSignalConnect(const std::function<void()>& p_slot) override;

    // cxgui::IWidget
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;

    /******************************************************************************************//**
     * @brief Get the underlying Gtkmm widget instance.
     *
     * @return The underlying Gtkmm switch implementation.
     *
     *********************************************************************************************/
    [[nodiscard]] Gtk::Switch& GetUnderlying(){return m_underlying;}

private:

    std::function<void()> m_stateChangedSlot = [](){};

    Gtk::Switch m_underlying;

};

} // namespace cxgui

#endif // ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8
