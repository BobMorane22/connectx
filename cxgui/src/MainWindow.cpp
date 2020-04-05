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

#include <gtkmm/application.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/stock.h>

#include <cxinv/include/assertion.h>

#include <About.h>
#include <AboutWindowPresenter.h>
#include <IMainWindowController.h>
#include <IMainWindowPresenter.h>
#include <MainWindow.h>
#include <StatusBar.h>
#include <StatusBarPresenter.h>

cxgui::MainWindow::MainWindow(Gtk::Application& p_gtkApplication,
                              cxmodel::Subject& p_model,
                              cxgui::IMainWindowController& p_controller,
                              cxgui::IMainWindowPresenter& p_presenter)
 : m_controller{p_controller}
 , m_presenter{p_presenter}
 , m_gtkApplication{p_gtkApplication}
{
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
    m_reinitButton->signal_clicked().connect([this, &controller = m_controller](){controller.OnReinitializeBtnPressed();});

    m_mainWindow = std::make_unique<Gtk::ApplicationWindow>();
    m_mainWindow->set_title(m_presenter.GetWindowTitle());

    m_counterLabel->set_margin_top(10);
    m_counterLabel->set_margin_bottom(10);

    CreateMenuBar(p_model);

    m_mainLayout->attach(*m_menubar, 0, 0, 2, 1);
    m_mainLayout->attach_next_to(*m_undoButton, *m_menubar, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout->attach_next_to(*m_redoButton, *m_undoButton, Gtk::PositionType::POS_RIGHT, 1, 1);
    m_mainLayout->attach_next_to(*m_counterLabel, *m_undoButton, Gtk::PositionType::POS_BOTTOM, 2, 1);
    m_mainLayout->attach_next_to(*m_incrementButton, *m_counterLabel, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout->attach_next_to(*m_reinitButton, *m_incrementButton, Gtk::PositionType::POS_RIGHT, 1, 1);

    CreateStatusBar(p_model);

    m_mainWindow->add(*m_mainLayout);

    POSTCONDITION(bool(m_statusbarPresenter));
    POSTCONDITION(m_mainWindow != nullptr);
    POSTCONDITION(m_mainLayout != nullptr);
    POSTCONDITION(m_undoButton != nullptr);
    POSTCONDITION(m_redoButton != nullptr);
    POSTCONDITION(m_counterLabel != nullptr);
    POSTCONDITION(m_incrementButton != nullptr);
    POSTCONDITION(m_reinitButton != nullptr);
    POSTCONDITION(m_statusbar != nullptr);

    CheckInvariants();
}

int cxgui::MainWindow::Show()
{
    m_mainWindow->show_all();
    return m_gtkApplication.run(*m_mainWindow);
}

void cxgui::MainWindow::Update(cxmodel::NotificationContext, cxmodel::Subject*)
{
    m_reinitButton->set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_reinitMenuItem->set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_counterLabel->set_text(std::to_string(m_presenter.GetCounterValue()));

    CheckInvariants();
}

void cxgui::MainWindow::CreateMenuBar(cxmodel::Subject& p_model)
{
    m_menubar = std::make_unique<Gtk::MenuBar>();
    m_gameMenuItem = std::make_unique<Gtk::MenuItem>();
    m_gameMenu = std::make_unique<Gtk::Menu>();
    m_reinitMenuItem = std::make_unique<Gtk::MenuItem>();
    m_quitMenuItem = std::make_unique<Gtk::ImageMenuItem>(Gtk::Stock::QUIT);
    m_helpMenuItem = std::make_unique<Gtk::MenuItem>();
    m_helpMenu = std::make_unique<Gtk::Menu>();
    m_aboutMenuItem = std::make_unique<Gtk::ImageMenuItem>(Gtk::Stock::ABOUT);

    m_menubar->append(*m_gameMenuItem);
    m_menubar->append(*m_helpMenuItem);
    m_gameMenuItem->set_submenu(*m_gameMenu);
    m_gameMenu->append(*m_reinitMenuItem);
    m_gameMenu->append(*m_quitMenuItem);
    m_helpMenuItem->set_submenu(*m_helpMenu);
    m_helpMenu->append(*m_aboutMenuItem);

    m_gameMenuItem->set_label(m_presenter.GetMenuLabel(MenuItem::GAME));
    m_helpMenuItem->set_label(m_presenter.GetMenuLabel(MenuItem::HELP));
    m_reinitMenuItem->set_label(m_presenter.GetMenuLabel(MenuItem::REINITIALIZE));
    m_aboutMenuItem->set_label(m_presenter.GetMenuLabel(MenuItem::ABOUT));

    m_reinitMenuItem->set_sensitive(m_presenter.IsReinitializeBtnEnabled());

    m_quitMenuItem->signal_activate().connect([this](){m_mainWindow->close();});
    m_reinitMenuItem->signal_activate().connect([this](){m_controller.OnReinitializeBtnPressed();});
    m_aboutMenuItem->signal_activate().connect([this, &p_model](){CreateAboutWindow(p_model);});

    POSTCONDITION(m_menubar != nullptr);
    POSTCONDITION(m_gameMenuItem != nullptr);
    POSTCONDITION(m_gameMenu != nullptr);
    POSTCONDITION(m_reinitMenuItem != nullptr);
    POSTCONDITION(m_quitMenuItem != nullptr);
    POSTCONDITION(m_helpMenuItem != nullptr);
    POSTCONDITION(m_helpMenu != nullptr);
    POSTCONDITION(m_aboutMenuItem != nullptr);
}

void cxgui::MainWindow::CreateStatusBar(cxmodel::Subject& p_model)
{
    m_statusbarPresenter = std::make_unique<StatusBarPresenter>();
    std::unique_ptr<StatusBar> concreteStatusBar = std::make_unique<StatusBar>(*m_statusbarPresenter);

    m_mainLayout->attach_next_to(concreteStatusBar->GetGtkStatusBar(), *m_incrementButton, Gtk::PositionType::POS_BOTTOM, 2, 1);

    p_model.Attach(m_statusbarPresenter.get());
    m_statusbar = std::move(concreteStatusBar);
    m_statusbarPresenter->Attach(m_statusbar.get());

    POSTCONDITION(m_statusbarPresenter != nullptr);
    POSTCONDITION(m_statusbar != nullptr);

    CheckInvariants();
}

void cxgui::MainWindow::CreateAboutWindow(cxmodel::Subject& p_model)
{
    if(!m_about)
    {
        std::unique_ptr<IAboutWindowPresenter> aboutPresenter = std::make_unique<AboutWindowPresenter>();
        p_model.Attach(aboutPresenter.get());

        m_about = std::make_unique<About>(std::move(aboutPresenter));

        m_controller.OnAboutMenuPressed();
    }

    m_about->Show();
}

void cxgui::MainWindow::CheckInvariants()
{
    INVARIANT(bool(m_statusbarPresenter));
    INVARIANT(m_mainWindow != nullptr);
    INVARIANT(m_mainLayout != nullptr);
    INVARIANT(m_undoButton != nullptr);
    INVARIANT(m_redoButton != nullptr);
    INVARIANT(m_counterLabel != nullptr);
    INVARIANT(m_incrementButton != nullptr);
    INVARIANT(m_reinitButton != nullptr);
    INVARIANT(m_statusbar != nullptr);
    INVARIANT(m_menubar != nullptr);
    INVARIANT(m_gameMenuItem != nullptr);
    INVARIANT(m_gameMenu != nullptr);
    INVARIANT(m_reinitMenuItem != nullptr);
    INVARIANT(m_quitMenuItem != nullptr);
}
