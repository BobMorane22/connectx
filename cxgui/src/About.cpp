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

#include <About.h>
#include <IAboutWindowPresenter.h>

cxgui::About::About(std::unique_ptr<IAboutWindowPresenter>&& p_presenter)
 : Window()
 , m_presenter{std::move(p_presenter)}
{
    POSTCONDITION(m_presenter);

    m_window.set_title(m_presenter->GetWindowTitle());

    m_name.set_label("<b><big>" + m_presenter->GetApplicationName() + "</big></b>");
    m_version.set_label(m_presenter->GetVersionNumber());
    m_description.set_label(m_presenter->GetApplicationDescription());
    m_license.set_label(m_presenter->GetLicenseDescription());
    m_copyright.set_label(m_presenter->GetCopyrightNotice());
    m_close.set_label(m_presenter->GetCloseText());
}

void cxgui::About::Update(cxmodel::NotificationContext /*p_context*/, cxmodel::Subject* /*p_subject*/)
{
    // Nothing to do...
}

void cxgui::About::ConfigureWindow()
{
    m_window.set_title(m_presenter->GetWindowTitle());
    m_window.set_position(Gtk::WIN_POS_CENTER);
    m_window.set_resizable(false);
}

void cxgui::About::RegisterLayouts()
{
    // Nothing to do.
}

void cxgui::About::RegisterWidgets()
{
    m_mainLayout.attach(m_name, 0, 0, 1, 2);
    m_mainLayout.attach_next_to(m_version, m_name, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout.attach_next_to(m_description, m_version, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout.attach_next_to(m_license, m_description, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout.attach_next_to(m_copyright, m_license, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout.attach_next_to(m_close, m_copyright, Gtk::PositionType::POS_BOTTOM, 1, 1);
}

void cxgui::About::ConfigureLayouts()
{
    // Nothing to do.
}

void cxgui::About::ConfigureWidgets()
{
    m_name.set_use_markup(true);
    m_name.set_margin_bottom(15);

    m_description.set_margin_top(5);
    m_description.set_margin_left(5);
    m_description.set_margin_right(5);
    m_description.set_margin_bottom(5);

    m_copyright.set_margin_bottom(5);
}

void cxgui::About::ConfigureSignalHandlers()
{
    m_close.signal_clicked().connect([this](){m_window.close();});
}
