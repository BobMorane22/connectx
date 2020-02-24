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
 * @file MainWindow.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <string>

#include <gtkmm/statusbar.h>
#include <gtkmm/stock.h>

#include <cxinv/include/assertion.h>

#include <IMainWindowController.h>
#include <IMainWindowPresenter.h>
#include <MainWindow.h>
#include <StatusBar.h>
#include <StatusBarPresenter.h>

cxgui::MainWindow::MainWindow(int argc,
                              char *argv[],
                              cxmodel::Subject& p_model,
                              cxgui::IMainWindowController& p_controller,
                              cxgui::IMainWindowPresenter& p_presenter)
 : m_controller{p_controller}
 , m_presenter{p_presenter}
{
    PRECONDITION(argc > 0);
    PRECONDITION(argv != nullptr);

    // This call must come first. Otherwise, we call operation on the window without
    // the Gtkmm library being initialized and the application crashes (segmentation
    // fault) when launched.
    InitializeGtkmm(argc, argv);

    m_mainLayout = std::make_unique<Gtk::Grid>();
    m_undoButton = std::make_unique<Gtk::Button>(Gtk::Stock::UNDO);
    m_redoButton = std::make_unique<Gtk::Button>(Gtk::Stock::REDO);
    m_counterLabel = std::make_unique<Gtk::Label>(std::to_string(m_presenter.GetCounterValue()));
    m_incrementButton = std::make_unique<Gtk::Button>(m_presenter.GetIncrementBtnLabel());
    m_reinitButton = std::make_unique<Gtk::Button>(m_presenter.GetReinitializeBtnLabel());

    m_reinitButton->set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_undoButton->signal_clicked().connect([&controller = m_controller](){controller.OnUndoBtnPressed();});
    m_redoButton->signal_clicked().connect([&controller = m_controller](){controller.OnRedoBtnPressed();});
    m_incrementButton->signal_clicked().connect([&controller = m_controller](){controller.OnIncrementBtnPressed();});
    m_reinitButton->signal_clicked().connect([&controller = m_controller](){controller.OnReinitializeBtnPressed();});

    m_mainWindow = std::make_unique<Gtk::ApplicationWindow>();
    m_mainWindow->set_title(m_presenter.GetWindowTitle());

    m_counterLabel->set_margin_top(10);
    m_counterLabel->set_margin_bottom(10);

    m_mainLayout->attach(*m_undoButton, 0, 0, 1, 1);
    m_mainLayout->attach_next_to(*m_redoButton, *m_undoButton, Gtk::PositionType::POS_RIGHT, 1, 1);
    m_mainLayout->attach_next_to(*m_counterLabel, *m_undoButton, Gtk::PositionType::POS_BOTTOM, 2, 1);
    m_mainLayout->attach_next_to(*m_incrementButton, *m_counterLabel, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout->attach_next_to(*m_reinitButton, *m_incrementButton, Gtk::PositionType::POS_RIGHT, 1, 1);

    CreateStatusBar(p_model);

    m_mainWindow->add(*m_mainLayout);

    POSTCONDITION(bool(m_app));
    POSTCONDITION(m_mainWindow != nullptr);
    POSTCONDITION(m_mainLayout != nullptr);
    POSTCONDITION(m_undoButton != nullptr);
    POSTCONDITION(m_redoButton != nullptr);
    POSTCONDITION(m_counterLabel != nullptr);
    POSTCONDITION(m_incrementButton != nullptr);
    POSTCONDITION(m_reinitButton != nullptr);

    CheckInvariants();
}

int cxgui::MainWindow::Show()
{
    m_mainWindow->show_all();
    return m_app->run(*m_mainWindow);
}

void cxgui::MainWindow::InitializeGtkmm(int argc, char *argv[])
{
    m_app = Gtk::Application::create(argc, argv, "bobmorane.connectx");

    POSTCONDITION(bool(m_app));
}

void cxgui::MainWindow::Update(cxmodel::NotificationContext, cxmodel::Subject*)
{
    m_reinitButton->set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_counterLabel->set_text(std::to_string(m_presenter.GetCounterValue()));

    CheckInvariants();
}

void cxgui::MainWindow::CreateStatusBar(cxmodel::Subject& p_model)
{
    m_statusbarPresenter = std::make_unique<StatusBarPresenter>();
    std::unique_ptr<StatusBar> concreteStatusBar = std::make_unique<StatusBar>(*m_statusbarPresenter);

    m_mainLayout->attach_next_to(concreteStatusBar->GetGtkStatusBar(), *m_incrementButton, Gtk::PositionType::POS_BOTTOM, 2, 1);

    p_model.Attach(m_statusbarPresenter.get());
    m_statusbar = std::move(concreteStatusBar);
    m_statusbarPresenter->Attach(m_statusbar.get());
}

void cxgui::MainWindow::CheckInvariants()
{
    INVARIANT(bool(m_app));
    INVARIANT(m_mainWindow != nullptr);
    INVARIANT(m_mainLayout != nullptr);
    INVARIANT(m_undoButton != nullptr);
    INVARIANT(m_redoButton != nullptr);
    INVARIANT(m_counterLabel != nullptr);
    INVARIANT(m_incrementButton != nullptr);
    INVARIANT(m_reinitButton != nullptr);
}
