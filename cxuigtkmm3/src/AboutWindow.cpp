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
 * @file AboutWindow.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxui/IAboutWindowPresenter.h>
#include <cxui/IAbstractConnectXWidgetsFactory.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IButton.h>
#include <cxcmnui/ILabel.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/Margins.h>
#include <cxui/WidgetsFactories.h>

#include "AboutWindow.h"

cx::ui::gtkmm3::AboutWindow::AboutWindow(
    cx::ui::WidgetsFactories& p_widgetsFactories,
    std::unique_ptr<cx::ui::IAboutWindowPresenter> p_presenter)
 : cx::cmn::ui::gtkmm3::Window(p_widgetsFactories.GetStandardWidgetsFactory())
 , m_widgetsFactories{p_widgetsFactories}
{
    PRECONDITION(p_presenter);
    m_presenter = std::move(p_presenter);
    POSTCONDITION(m_presenter);
}

void cx::ui::gtkmm3::AboutWindow::Update(cx::model::ModelNotificationContext /*p_context*/, cx::model::ModelSubject* /*p_subject*/)
{
    // Nothing to do...
}

void cx::ui::gtkmm3::AboutWindow::InitializeWidgets()
{
    const cx::cmn::ui::IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();

    m_name = standardWidgetsFactory.CreateLabel();
    m_version = standardWidgetsFactory.CreateLabel();
    m_description = standardWidgetsFactory.CreateLabel();
    m_website = standardWidgetsFactory.CreateLabel();
    m_license = standardWidgetsFactory.CreateLabel();
    m_copyright = standardWidgetsFactory.CreateLabel();
    m_close = standardWidgetsFactory.CreateButton();

    POSTCONDITION(m_name);
    POSTCONDITION(m_version);
    POSTCONDITION(m_description);
    POSTCONDITION(m_website);
    POSTCONDITION(m_license);
    POSTCONDITION(m_copyright);
    POSTCONDITION(m_close);
}

void cx::ui::gtkmm3::AboutWindow::ConfigureWindow()
{
    set_title(m_presenter->GetWindowTitle());
    set_position(Gtk::WIN_POS_CENTER);
    set_resizable(false);
}

void cx::ui::gtkmm3::AboutWindow::RegisterLayouts()
{
    // Nothing to do.
}

void cx::ui::gtkmm3::AboutWindow::RegisterWidgets()
{
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    constexpr cx::model::Row row0{0u};
    constexpr cx::model::Row row1{1u};
    constexpr cx::model::Row row2{2u};
    constexpr cx::model::Row row3{3u};
    constexpr cx::model::Row row4{4u};
    constexpr cx::model::Row row5{5u};
    constexpr cx::model::Row row6{6u};
    constexpr cx::cmn::ui::ILayout::RowSpan rowSpan1{1u};

    constexpr cx::model::Column column0{0u};
    constexpr cx::cmn::ui::ILayout::ColumnSpan columnSpan1{1u};
    
    m_mainLayout->Register(*m_name,        {row0, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_version,     {row1, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_description, {row2, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_website,     {row3, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_license,     {row4, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_copyright,   {row5, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_close,       {row6, rowSpan1}, {column0, columnSpan1});
}

void cx::ui::gtkmm3::AboutWindow::ConfigureLayouts()
{
    // Nothing to do.
}

void cx::ui::gtkmm3::AboutWindow::ConfigureWidgets()
{
    using namespace cx::cmn::ui;

    set_title(m_presenter->GetWindowTitle());

    m_name->SetMargins({TopMargin{0}, BottomMargin{15}, LeftMargin{0}, RightMargin{0}});
    m_description->SetMargins({TopMargin{5}, BottomMargin{5}, LeftMargin{5}, RightMargin{5}});
    m_copyright->SetMargins({TopMargin{0}, BottomMargin{5}, LeftMargin{0}, RightMargin{0}});

    m_name->UpdateContents("<b><big>" + m_presenter->GetApplicationName() + "</big></b>");
    m_version->UpdateContents(m_presenter->GetVersionNumber());
    m_description->UpdateContents(m_presenter->GetApplicationDescription());
    m_website->UpdateContents(m_presenter->GetWebsiteLinkContents());
    m_license->UpdateContents(m_presenter->GetLicenseDescription());
    m_copyright->UpdateContents(m_presenter->GetCopyrightNotice());

    m_close->UpdateContents(m_presenter->GetCloseText());
}

void cx::ui::gtkmm3::AboutWindow::ConfigureSignalHandlers()
{
    m_close->OnClicked()->Connect([this](){close();});
}
