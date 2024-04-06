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
/**********************************************************************************************//** * @file GameResolutionDialog.cpp
 * @file Gtkmm3GameResolutionDialog.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <cxgui/common.h>
#include <cxgui/Gtkmm3GameResolutionDialog.h>
#include <cxgui/IAbstractConnectXWidgetsFactory.h>
#include <cxgui/IAbstractWidgetsFactory.h>
#include <cxgui/IButton.h>
#include <cxgui/IGameResolutionDialogController.h>
#include <cxgui/IGameResolutionDialogPresenter.h>
#include <cxgui/ILabel.h>
#include <cxgui/Margins.h>
#include <cxgui/WidgetsFactories.h>

cxgui::Gtkmm3GameResolutionDialog::Gtkmm3GameResolutionDialog(
    cxgui::WidgetsFactories& p_widgetsFactories,
    std::unique_ptr<IGameResolutionDialogPresenter> p_presenter,
    std::unique_ptr<IGameResolutionDialogController> p_controller)
: m_presenter{std::move(p_presenter)}
, m_controller{std::move(p_controller)}
, m_widgetsFactories{p_widgetsFactories}
{
    POSTCONDITION(m_presenter);
    POSTCONDITION(m_controller);
}

void cxgui::Gtkmm3GameResolutionDialog::Update(cxmodel::ModelNotificationContext /*p_context*/, cxmodel::ModelSubject* /*p_subject*/)
{
    // Nothing to do...
}

void cxgui::Gtkmm3GameResolutionDialog::InitializeWidgets()
{
    const IAbstractWidgetsFactory& stdWidgetsFactory =  m_widgetsFactories.GetStandardWidgetsFactory();

    m_title = stdWidgetsFactory.CreateLabel();
    m_message = stdWidgetsFactory.CreateLabel();
    m_startNewGame = stdWidgetsFactory.CreateButton();

    POSTCONDITION(m_title);
    POSTCONDITION(m_message);
    POSTCONDITION(m_startNewGame);
}

void cxgui::Gtkmm3GameResolutionDialog::ConfigureWindow()
{
    // We do now want the user to simply close the window by pressing the 'X' button.
    set_deletable(false);
    set_modal(true);
}

void cxgui::Gtkmm3GameResolutionDialog::RegisterLayouts()
{
    // Nothing to do...
}

void cxgui::Gtkmm3GameResolutionDialog::RegisterWidgets()
{
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    constexpr cxmodel::Row row0{0u};
    constexpr cxmodel::Row row1{1u};
    constexpr cxmodel::Row row2{2u};
    constexpr cxgui::ILayout::RowSpan rowSpan1{1u};

    constexpr cxmodel::Column column0{0u};
    constexpr cxgui::ILayout::ColumnSpan columnSpan1{1u};

    m_mainLayout->Register(*m_title,        {row0, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_message,      {row1, rowSpan1}, {column0, columnSpan1});
    m_mainLayout->Register(*m_startNewGame, {row2, rowSpan1}, {column0, columnSpan1});
}

void cxgui::Gtkmm3GameResolutionDialog::ConfigureLayouts()
{
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);
    
    m_mainLayout->SetMargins({ TopMargin{DIALOG_SIDE_MARGIN}, BottomMargin{DIALOG_SIDE_MARGIN}, LeftMargin{DIALOG_SIDE_MARGIN}, RightMargin{DIALOG_SIDE_MARGIN}});
}

void cxgui::Gtkmm3GameResolutionDialog::ConfigureWidgets()
{
    // Populate widgets:
    m_title->UpdateContents(m_presenter->GetTitle());
    m_message->UpdateContents(m_presenter->GetResolutionMessage());
    m_startNewGame->UpdateContents(m_presenter->GetStartNewGameButtonText());

    // Window title:
    m_title->UpdateContents("<big><b>" + m_title->GetContents() + "</b></big>");
    m_title->SetMargins({TopMargin{0}, BottomMargin{TITLE_BOTTOM_MARGIN}, LeftMargin{0}, RightMargin{0}});

    // Win resolution message:
    m_message->SetMargins({TopMargin{0}, BottomMargin{CONTROL_BOTTOM_MARGIN}, LeftMargin{0}, RightMargin{0}});
}

void cxgui::Gtkmm3GameResolutionDialog::ConfigureSignalHandlers()
{
    m_startNewGame->OnClicked()->Connect(
        [this]()
        {
            IF_CONDITION_NOT_MET_DO(m_controller, return;);
            m_controller->OnNewGameRequested();

            close();
        });
}
