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
 * @file Gtkmm3AbstractConnectXWidgetsFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/Gtkmm3AboutWindow.h>
#include <cxgui/Gtkmm3AbstractConnectXWidgetsFactory.h>
#include <cxgui/Gtkmm3MainWindow.h>
#include <cxgui/IButton.h>
#include <cxgui/ILabel.h>
#include <cxgui/IMainWindowController.h>
#include <cxgui/IMainWindowPresenter.h>
#include <cxgui/WidgetsFactories.h>

cxgui::Gtkmm3AbstractConnectXWidgetsFactory::Gtkmm3AbstractConnectXWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
    InvariantsCheck();
}

void cxgui::Gtkmm3AbstractConnectXWidgetsFactory::RegisterStandardWidgetsFactory(IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory)
{
    m_widgetsFactories = std::make_unique<WidgetsFactories>(p_stdAbstractWidgetsFactory, *this);

    POSTCONDITION(m_widgetsFactories);
    InvariantsCheck();
}

std::unique_ptr<cxgui::IWindow> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateMainWindow(
    cxmodel::ModelSubject& p_model,
    IMainWindowController& p_controller,
    IMainWindowPresenter& p_presenter) const
{
    IF_PRECONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto mainWindow = cxgui::CreateWidget<cxgui::Gtkmm3MainWindow>(
        *(m_gtkApplication.get()),
        p_model,
        p_controller,
        p_presenter);

    IF_CONDITION_NOT_MET_DO(mainWindow, return nullptr;);

    mainWindow->RegisterWidgetsFactories(m_widgetsFactories.get());
    mainWindow->Init();

    POSTCONDITION(mainWindow);
    InvariantsCheck();

    return mainWindow;
}

std::unique_ptr<cxgui::IWindow> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateAboutWindow(
        std::unique_ptr<IAboutWindowPresenter> p_presenter) const
{
    IF_PRECONDITION_NOT_MET_DO(p_presenter, return nullptr;);

    auto aboutWindow = CreateWidget<Gtkmm3AboutWindow>(std::move(p_presenter));
    POSTCONDITION(aboutWindow);

    aboutWindow->Init();

    return aboutWindow;
}

void cxgui::Gtkmm3AbstractConnectXWidgetsFactory::InvariantsCheck() const 
{
    INVARIANT(m_gtkApplication);
}
