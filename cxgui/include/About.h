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
 * @file About.cpp
 * @date 2020
 *
 *************************************************************************************************/

#ifndef ABOUT_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1
#define ABOUT_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1

#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/window.h>

#include "IAboutWindowPresenter.h"
#include "Window.h"

namespace cxgui
{

class About : public Window<Gtk::Window>
{

public:

    About(std::unique_ptr<IAboutWindowPresenter>&& p_presenter);

    void Update(cxmodel::NotificationContext p_context, cxmodel::ModelSubject* p_subject) override;


private:

    void ConfigureWindow() override;
    void RegisterLayouts() override;
    void RegisterWidgets() override;
    void ConfigureLayouts() override;
    void ConfigureWidgets() override;
    void ConfigureSignalHandlers() override;

    std::unique_ptr<IAboutWindowPresenter> m_presenter;

    Gtk::Label m_name;
    Gtk::Label m_version;
    Gtk::Label m_description;
    Gtk::Label m_license;
    Gtk::Label m_copyright;

    Gtk::Button m_close;

};

} // namespace cxgui

#endif // ABOUT_H_396864CD_88A3_43F2_B08B_3F9FEBE89DE1
