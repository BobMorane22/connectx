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
 * @file StatusBar.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef STATUSBAR_H_DDBD40E5_28B4_47C2_8550_C0F49082EFBF
#define STATUSBAR_H_DDBD40E5_28B4_47C2_8550_C0F49082EFBF

#include <gtkmm/statusbar.h>

#include "IStatusBar.h"
#include "IStatusBarPresenter.h"

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Main window status bar.
 *
 *************************************************************************************************/
class StatusBar : public IStatusBar
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      A status bar presenter.
     *
     *********************************************************************************************/
    StatusBar(IStatusBarPresenter& p_presenter);

    // cxgui::IStatusBar:
    ~StatusBar() override;
    void SetLastUserActionStatus(const std::string& p_lastUserActionDescription) override;

    /******************************************************************************************//**
     * @brief Get the underlying Gtkmm status bar instance.
     *
     * @return
     *      The underlying Gtkmm status bar instance.
     *
     *********************************************************************************************/
    Gtk::Statusbar& GetGtkStatusBar();

private:

    virtual void Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject) override;

    IStatusBarPresenter& m_presenter;
    Gtk::Statusbar m_statusbar;

};

} // namespace cxgui

#endif // STATUSBAR_H_DDBD40E5_28B4_47C2_8550_C0F49082EFBF
