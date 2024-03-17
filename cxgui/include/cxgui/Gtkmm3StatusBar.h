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
 * @file Gtkmm3StatusBar.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3STATUSBAR_H_DDBD40E5_28B4_47C2_8550_C0F49082EFBF
#define GTKMM3STATUSBAR_H_DDBD40E5_28B4_47C2_8550_C0F49082EFBF

#include <gtkmm/statusbar.h>

#include "IStatusBar.h"
#include "IStatusBarPresenter.h"

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Main window status bar.
 *
 *************************************************************************************************/
class Gtkmm3StatusBar : public IStatusBar,
                        public Gtk::Statusbar
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      A status bar presenter.
     *
     *********************************************************************************************/
    explicit Gtkmm3StatusBar(IStatusBarPresenter& p_presenter);

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

    // cxgui::IStatusBar:
    void SetLastUserActionStatus(const std::string& p_lastUserActionDescription) override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;

private:

    virtual void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;

private:

    std::unique_ptr<IWidget> m_delegate;

    IStatusBarPresenter& m_presenter;

};

} // namespace cxgui

#endif // GTKMM3STATUSBAR_H_DDBD40E5_28B4_47C2_8550_C0F49082EFBF
