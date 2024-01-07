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
 * @file Gtkmm3OnOffSwitch.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef GTKMM3ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8
#define GTKMM3ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8

#include <gtkmm/switch.h>

#include <cxgui/IOnOffSwitch.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief A switch that is either "On" or "Off".
 *
 *************************************************************************************************/
class Gtkmm3OnOffSwitch : public cxgui::IOnOffSwitch,
                          public Gtk::Switch
{

public:

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

    // cxgui::IOnOffSwitch:
    [[nodiscard]] OnOffState GetState() const override;
    void SetState(OnOffState p_newState) override;
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnStateChanged() override;

};

} // namespace cxgui

#endif // GTKMM3ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8
