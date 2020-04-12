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
 : m_gtkApplication{p_gtkApplication}
 , m_model{p_model}
 , m_controller{p_controller}
 , m_presenter{p_presenter}
{
}

void cxgui::MainWindow::ConfigureWindow()
{
    m_window.set_title(m_presenter.GetWindowTitle());
    m_window.set_position(Gtk::WIN_POS_CENTER);
}

void cxgui::MainWindow::RegisterLayouts()
{
    // Nothing to do...
}

void cxgui::MainWindow::RegisterWidgets()
{
    RegisterMenuBar();

    m_mainLayout.attach(m_menubar, 0, 0, 2, 1);
    m_mainLayout.attach_next_to(m_undoButton, m_menubar, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout.attach_next_to(m_redoButton, m_undoButton, Gtk::PositionType::POS_RIGHT, 1, 1);
    m_mainLayout.attach_next_to(m_counterLabel, m_undoButton, Gtk::PositionType::POS_BOTTOM, 2, 1);
    m_mainLayout.attach_next_to(m_incrementButton, m_counterLabel, Gtk::PositionType::POS_BOTTOM, 1, 1);
    m_mainLayout.attach_next_to(m_reinitButton, m_incrementButton, Gtk::PositionType::POS_RIGHT, 1, 1);

    RegisterStatusBar();
}

void cxgui::MainWindow::ConfigureLayouts()
{
    // Nothing to do...
}

void cxgui::MainWindow::ConfigureWidgets()
{
    m_gameMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::GAME));
    m_helpMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::HELP));
    m_reinitMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::REINITIALIZE));
    m_aboutMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::ABOUT));

    m_reinitMenuItem.set_sensitive(m_presenter.IsReinitializeBtnEnabled());

    m_counterLabel.set_text(std::to_string(m_presenter.GetCounterValue()));
    m_incrementButton.set_label(m_presenter.GetIncrementBtnLabel());
    m_reinitButton.set_label(m_presenter.GetReinitializeBtnLabel());

    m_counterLabel.set_margin_top(10);
    m_counterLabel.set_margin_bottom(10);

    m_model.Attach(m_statusbarPresenter.get());
    m_statusbarPresenter->Attach(m_statusbar.get());
}

void cxgui::MainWindow::ConfigureSignalHandlers()
{
    m_reinitButton.set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_undoButton.signal_clicked().connect([&controller = m_controller](){controller.OnUndoBtnPressed();});
    m_redoButton.signal_clicked().connect([&controller = m_controller](){controller.OnRedoBtnPressed();});
    m_incrementButton.signal_clicked().connect([&controller = m_controller](){controller.OnIncrementBtnPressed();});
    m_reinitButton.signal_clicked().connect([this, &controller = m_controller](){controller.OnReinitializeBtnPressed();});
    m_quitMenuItem.signal_activate().connect([this](){m_window.close();});
    m_reinitMenuItem.signal_activate().connect([this](){m_controller.OnReinitializeBtnPressed();});
    m_aboutMenuItem.signal_activate().connect([this](){CreateAboutWindow();});
}

int cxgui::MainWindow::Show()
{
    m_window.show_all();
    return m_gtkApplication.run(m_window);
}

void cxgui::MainWindow::Update(cxmodel::NotificationContext, cxmodel::Subject*)
{
    m_reinitButton.set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_reinitMenuItem.set_sensitive(m_presenter.IsReinitializeBtnEnabled());
    m_counterLabel.set_text(std::to_string(m_presenter.GetCounterValue()));
}

void cxgui::MainWindow::RegisterMenuBar()
{
    m_menubar.append(m_gameMenuItem);
    m_menubar.append(m_helpMenuItem);
    m_gameMenuItem.set_submenu(m_gameMenu);
    m_gameMenu.append(m_reinitMenuItem);
    m_gameMenu.append(m_quitMenuItem);
    m_helpMenuItem.set_submenu(m_helpMenu);
    m_helpMenu.append(m_aboutMenuItem);
}

void cxgui::MainWindow::RegisterStatusBar()
{
    m_statusbarPresenter = std::make_unique<StatusBarPresenter>();
    std::unique_ptr<StatusBar> concreteStatusBar = std::make_unique<StatusBar>(*m_statusbarPresenter);

    m_mainLayout.attach_next_to(concreteStatusBar->GetGtkStatusBar(), m_incrementButton, Gtk::PositionType::POS_BOTTOM, 2, 1);

    m_statusbar = std::move(concreteStatusBar);

    POSTCONDITION(m_statusbarPresenter != nullptr);
    POSTCONDITION(m_statusbar != nullptr);
}

void cxgui::MainWindow::CreateAboutWindow()
{
    if(!m_about)
    {
        std::unique_ptr<IAboutWindowPresenter> aboutPresenter = std::make_unique<AboutWindowPresenter>();
        m_model.Attach(aboutPresenter.get());

        {
            auto aboutWindow = std::make_unique<About>(std::move(aboutPresenter));
            aboutWindow->Init();

            m_about = std::move(aboutWindow);
        }

        m_controller.OnAboutMenuPressed();
    }

    m_about->Show();
}
