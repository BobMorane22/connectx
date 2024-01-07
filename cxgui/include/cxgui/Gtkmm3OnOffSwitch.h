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

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<IWidget> p_delegate);

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

    // cxgui::IOnOffSwitch:
    [[nodiscard]] OnOffState GetState() const override;
    void SetState(OnOffState p_newState) override;
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnStateChanged() override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3ONOFFSWITCH_H_3F9ABCFC_7442_44F5_8C96_A15828BC28B8
