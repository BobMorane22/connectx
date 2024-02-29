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
 * @file Gtkmm3Dialog.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3DIALOG_H_0BE19F00_7BE5_40DA_B880_C87F635AABE8
#define GTKMM3DIALOG_H_0BE19F00_7BE5_40DA_B880_C87F635AABE8

#include <gtkmm/messagedialog.h>

#include <cxmodel/ModelNotificationContext.h>
#include <cxgui/IWindow.h>

namespace cxgui
{
    enum class DialogRole;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 dialog implementation.
 *
 * Unlike Gtkmm, this implementation shares the `IWindow::Show` method. Typical Gtkmm
 * implementations use the `Gtk::Dialog::run` method (but also inherit from `Gtk::Window::show`)
 * which adds confusion.
 *
 *************************************************************************************************/
class Gtkmm3Dialog : public IWindow,
                     public Gtk::MessageDialog
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_parent
     *      The window over which the dialog will appear.
     * @param p_role
     *      The dialog's role. In other words, the type of communication the dialog going to
     *      be used, as far as the user is concerned.
     * @param p_message
     *      The message to display to the user. 
     *
     * @pre
     *      The message should not be empty.
     *
     **********************************************************************************************/
    Gtkmm3Dialog(IWindow& p_parent, DialogRole p_role, const std::string& p_message);

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

    // cxgui::IWindow:
    [[nodiscard]] virtual int Show() override;
    void ShrinkToContents(IWindow::Orientation p_orientation) override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    // cxmodel::IModelObserver:
    void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;

    std::unique_ptr<IWidget> m_delegate;

};

} // namespace cxgui

#endif // GTKMM3DIALOG_H_0BE19F00_7BE5_40DA_B880_C87F635AABE8
