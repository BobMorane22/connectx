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
 * @file GameResolutionDialog.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <common.h>
#include <GameResolutionDialog.h>
#include <IGameResolutionDialogController.h>
#include <IGameResolutionDialogPresenter.h>

cxgui::GameResolutionDialog::GameResolutionDialog(std::unique_ptr<IGameResolutionDialogPresenter> p_presenter,
                                                  std::unique_ptr<IGameResolutionDialogController> p_controller)
: m_presenter{std::move(p_presenter)}
, m_controller{std::move(p_controller)}
{
    POSTCONDITION(m_presenter);
    POSTCONDITION(m_controller);
}

void cxgui::GameResolutionDialog::Update(cxmodel::NotificationContext /*p_context*/, cxmodel::Subject* /*p_subject*/)
{
    // Nothing to do...
}

void cxgui::GameResolutionDialog::ConfigureWindow()
{
    // We do now want the user to simply close the window by pressing the
    // 'X' button.
    m_window.set_deletable(false);
    m_window.set_modal(true);
}

void cxgui::GameResolutionDialog::RegisterLayouts()
{
    // Nothing to do...
}

void cxgui::GameResolutionDialog::RegisterWidgets()
{
    m_mainLayout.attach(m_title, 0, 0, 1, 1);
    m_mainLayout.attach(m_message, 0, 1, 1, 1);
    m_mainLayout.attach(m_startNewGame, 0, 2, 1, 1);
}

void cxgui::GameResolutionDialog::ConfigureLayouts()
{
    m_mainLayout.set_margin_bottom(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_top(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_left(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_right(DIALOG_SIDE_MARGIN);
}

void cxgui::GameResolutionDialog::ConfigureWidgets()
{
    // Populate widgets:
    m_title.set_text(m_presenter->GetTitle());
    m_message.set_text(m_presenter->GetResolutionMessage());
    m_startNewGame.set_label(m_presenter->GetStartNewGameButtonText());

    // Window title:
    m_title.set_use_markup(true);
    m_title.set_markup("<big><b>" + m_title.get_text() + "</b></big>");
    m_title.set_margin_bottom(TITLE_BOTTOM_MARGIN);
    m_title.set_halign(Gtk::Align::ALIGN_CENTER);
    m_title.set_hexpand(true);

    // Win resolution message:
    m_message.set_halign(Gtk::Align::ALIGN_CENTER);
    m_message.set_margin_bottom(CONTROL_BOTTOM_MARGIN);

    // Button:
    m_startNewGame.set_halign(Gtk::Align::ALIGN_FILL);
    m_startNewGame.set_hexpand_set(true);
    m_startNewGame.set_hexpand(true);
    m_startNewGame.set_margin_bottom(CONTROL_BOTTOM_MARGIN);
}

void cxgui::GameResolutionDialog::ConfigureSignalHandlers()
{
    m_startNewGame.signal_clicked().connect([this]()
                                            {
                                                IF_CONDITION_NOT_MET_DO(m_controller, return;);
                                                m_controller->OnNewGameRequested();

                                                m_window.close();
                                            });
}
