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
 * @file Gtkmm3MenuBar.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3MENUBAR_H_B09C49CF_EA28_4DBB_8ED7_BA7E8CEC3CC6
#define GTKMM3MENUBAR_H_B09C49CF_EA28_4DBB_8ED7_BA7E8CEC3CC6

#include <gtkmm/menubar.h>
#include <cxgui/IMenuBar.h>

namespace cxgui
{

/***********************************************************************************************//**
 * @brief Gtkmm 3 implementation of the `cxgui::IMenuBar` interface.
 *
 **************************************************************************************************/
class Gtkmm3MenuBar : public IMenuBar,
                      public Gtk::MenuBar
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

    // cxgui::IMenuBar:
    void Register(IMenu& p_menu) override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

private:

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3MENUBAR_H_B09C49CF_EA28_4DBB_8ED7_BA7E8CEC3CC6
