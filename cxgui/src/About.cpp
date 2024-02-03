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

#include <cxgui/About.h>
#include <cxgui/Gtkmm3Button.h>
#include <cxgui/IAboutWindowPresenter.h>

cxgui::About::About(std::unique_ptr<IAboutWindowPresenter>&& p_presenter)
 : Window()
 , m_presenter{std::move(p_presenter)}
{
    POSTCONDITION(m_presenter);

    m_window.set_title(m_presenter->GetWindowTitle());

    m_name.set_label("<b><big>" + m_presenter->GetApplicationName() + "</big></b>");
    m_version.set_label(m_presenter->GetVersionNumber());
    m_description.set_label(m_presenter->GetApplicationDescription());
    m_website.set_markup(m_presenter->GetWebsiteLinkContents());
    m_license.set_label(m_presenter->GetLicenseDescription());
    m_copyright.set_label(m_presenter->GetCopyrightNotice());

    m_close = CreateWidget<Gtkmm3Button>(m_presenter->GetCloseText());
    ASSERT(m_close);
}

void cxgui::About::Update(cxmodel::ModelNotificationContext /*p_context*/, cxmodel::ModelSubject* /*p_subject*/)
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
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    constexpr cxmodel::Row row0{0u};
    constexpr cxmodel::Row row1{1u};
    constexpr cxmodel::Row row2{2u};
    constexpr cxmodel::Row row3{3u};
    constexpr cxmodel::Row row4{4u};
    constexpr cxmodel::Row row5{5u};
    constexpr cxmodel::Row row6{6u};
    constexpr cxgui::ILayout::RowSpan rowSpan1{1u};

    constexpr cxmodel::Column column0{0u};
    constexpr cxgui::ILayout::ColumnSpan columnSpan1{1u};
    
    m_mainLayout->Register(m_name,        {row0, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(m_version,     {row1, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(m_description, {row2, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(m_website,     {row3, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(m_license,     {row4, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(m_copyright,   {row5, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_close,      {row6, rowSpan1}, {column0, columnSpan1});
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
    m_description.set_margin_start(5);
    m_description.set_margin_end(5);
    m_description.set_margin_bottom(5);

    m_copyright.set_margin_bottom(5);
}

void cxgui::About::ConfigureSignalHandlers()
{
    m_close->OnClicked()->Connect([this](){m_window.close();});
}
