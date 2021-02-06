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
#include <cxmodel/include/IConnectXGameActions.h>
#include <cxmodel/include/IConnectXGameInformation.h>
#include <cxmodel/include/IVersioning.h>
#include <cxmodel/include/GameResolutionStrategyFactory.h>

#include <About.h>
#include <AboutWindowPresenter.h>
#include <GameResolutionDialog.h>
#include <GameResolutionDialogController.h>
#include <GameResolutionDialogPresenterFactory.h>
#include <GameView.h>
#include <IMainWindowController.h>
#include <IMainWindowPresenter.h>
#include <MainWindow.h>
#include <NewGameView.h>
#include <StatusBar.h>
#include <StatusBarPresenter.h>
#include <GameResolutionDialogController.h>

cxgui::MainWindow::MainWindow(Gtk::Application& p_gtkApplication,
                              cxmodel::Subject& p_model,
                              cxgui::IMainWindowController& p_controller,
                              cxgui::IMainWindowPresenter& p_presenter)
 : m_gtkApplication{p_gtkApplication}
 , m_model{p_model}
 , m_controller{p_controller}
 , m_presenter{p_presenter}
 , m_viewLeft{0}
 , m_viewTop{1}
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

    m_newGameView = std::make_unique<NewGameView>(m_presenter, m_controller, m_mainLayout, m_viewLeft, m_viewTop);
    m_newGameView->Activate();

    RegisterStatusBar();
}

void cxgui::MainWindow::ConfigureLayouts()
{
    // Nothing to do...
}

void cxgui::MainWindow::ConfigureWidgets()
{
    m_gameMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::GAME));
    m_newGameMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::NEW_GAME));
    m_reinitializeMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::REINITIALIZE_GAME));
    m_undoMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::UNDO));
    m_redoMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::REDO));
    m_helpMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::HELP));
    m_aboutMenuItem.set_label(m_presenter.GetMenuLabel(MenuItem::ABOUT));

    m_model.Attach(m_statusbarPresenter.get());
    m_statusbarPresenter->Attach(m_statusbar.get());
}

void cxgui::MainWindow::ConfigureSignalHandlers()
{
    m_newGameMenuItem.signal_activate().connect([this](){OnNewGame();});
    m_reinitializeMenuItem.signal_activate().connect([this](){OnReinitializeCurrentGame();});
    m_undoMenuItem.signal_activate().connect([this]{OnUndo();});
    m_redoMenuItem.signal_activate().connect([this]{OnRedo();});
    m_quitMenuItem.signal_activate().connect([this](){m_window.close();});
    m_aboutMenuItem.signal_activate().connect([this](){OnCreateAboutWindow();});
}

int cxgui::MainWindow::Show()
{
    m_window.show_all();
    return m_gtkApplication.run(m_window);
}

void cxgui::MainWindow::Update(cxmodel::NotificationContext p_context, cxmodel::Subject* p_subject)
{
    if(PRECONDITION(p_subject))
    {
        switch(p_context)
        {
            case cxmodel::NotificationContext::CHIP_DROPPED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cxmodel::NotificationContext::CREATE_NEW_GAME:
            {
                UpdateCreateNewGame();
                break;
            }
            case cxmodel::NotificationContext::UNDO_CHIP_DROPPED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cxmodel::NotificationContext::GAME_WON:
            {
                UpdateGameWon(p_context);
                break;
            }
            case cxmodel::NotificationContext::GAME_TIED:
            {
                UpdateGameTied(p_context);
                break;
            }
            case cxmodel::NotificationContext::GAME_ENDED:
            {
                UpdateGameEnded();
                break;
            }
            case cxmodel::NotificationContext::GAME_REINITIALIZED:
            {
                UpdateGameReinitialized(p_context);
                break;
            }
            default:
                ASSERT_ERROR_MSG("Unsupported notification context.");
        }
    }

    UpdateMenuItems();
}

void cxgui::MainWindow::UpdateCreateNewGame()
{
    DeactivateNewGameView();
    ActivateGameView();
}

void cxgui::MainWindow::UpdateChipDropped(cxmodel::NotificationContext p_context)
{
    if(ASSERT(m_gameView))
    {
        m_gameView->Update(p_context);
    }
}

void cxgui::MainWindow::UpdateGameWon(cxmodel::NotificationContext p_context)
{
    m_gameView->Update(p_context);
    CreateGameResolutionWindow(p_context);
}

void cxgui::MainWindow::UpdateGameTied(cxmodel::NotificationContext p_context)
{
    m_gameView->Update(p_context);
    CreateGameResolutionWindow(p_context);
}

void cxgui::MainWindow::UpdateGameEnded()
{
    DeactivateGameView();
    ActivateNewGameView();
}

void cxgui::MainWindow::UpdateGameReinitialized(cxmodel::NotificationContext p_context)
{
    m_gameView->Update(p_context); 
}

void cxgui::MainWindow::UpdateMenuItems()
{
    m_newGameMenuItem.set_sensitive(m_presenter.IsNewGamePossible());
    m_reinitializeMenuItem.set_sensitive(m_presenter.IsCurrentGameReinitializationPossible());
    m_undoMenuItem.set_sensitive(m_presenter.IsUndoPossible());
    m_redoMenuItem.set_sensitive(m_presenter.IsRedoPossible());
}

void cxgui::MainWindow::RegisterMenuBar()
{
    // Adding accelerators:
    auto acceleratorGroup = Gtk::AccelGroup::create();
    m_window.add_accel_group(acceleratorGroup);

    m_undoMenuItem.add_accelerator("activate",
                                   acceleratorGroup,
                                   GDK_KEY_z,
                                   Gdk::ModifierType::CONTROL_MASK,
                                   Gtk::ACCEL_VISIBLE);

    m_redoMenuItem.add_accelerator("activate",
                                   acceleratorGroup,
                                   GDK_KEY_y,
                                   Gdk::ModifierType::CONTROL_MASK,
                                   Gtk::ACCEL_VISIBLE);

    m_menubar.append(m_gameMenuItem);
    m_menubar.append(m_helpMenuItem);
    m_gameMenuItem.set_submenu(m_gameMenu);
    m_gameMenu.append(m_newGameMenuItem);
    m_gameMenu.append(m_reinitializeMenuItem);
    m_gameMenu.append(m_undoMenuItem);
    m_gameMenu.append(m_redoMenuItem);
    m_gameMenu.append(m_quitMenuItem);
    m_helpMenuItem.set_submenu(m_helpMenu);
    m_helpMenu.append(m_aboutMenuItem);

    m_newGameMenuItem.set_sensitive(m_presenter.IsNewGamePossible());
    m_reinitializeMenuItem.set_sensitive(m_presenter.IsCurrentGameReinitializationPossible());
    m_undoMenuItem.set_sensitive(m_presenter.IsUndoPossible());
    m_redoMenuItem.set_sensitive(m_presenter.IsRedoPossible());
}

void cxgui::MainWindow::RegisterStatusBar()
{
    m_statusbarPresenter = std::make_unique<StatusBarPresenter>();
    std::unique_ptr<StatusBar> concreteStatusBar = std::make_unique<StatusBar>(*m_statusbarPresenter);

    m_mainLayout.attach(concreteStatusBar->GetGtkStatusBar(), 0, m_viewTop + 1, 2, 1);

    m_statusbar = std::move(concreteStatusBar);

    POSTCONDITION(m_statusbarPresenter);
    POSTCONDITION(m_statusbar);
}

void cxgui::MainWindow::OnCreateAboutWindow()
{
    if(!m_about)
    {
        cxmodel::IVersioning* versionModel = dynamic_cast<cxmodel::IVersioning*>(&m_model);
        IF_CONDITION_NOT_MET_DO(versionModel, return;);

        std::unique_ptr<IAboutWindowPresenter> aboutPresenter = std::make_unique<AboutWindowPresenter>(*versionModel);
        IF_CONDITION_NOT_MET_DO(aboutPresenter, return;);

        {
            auto aboutWindow = std::make_unique<About>(std::move(aboutPresenter));
            aboutWindow->Init();

            m_about = std::move(aboutWindow);
        }
    }

    m_about->Show();
}

void cxgui::MainWindow::OnNewGame()
{
    m_controller.OnNewGame();
}

void cxgui::MainWindow::OnReinitializeCurrentGame()
{
   m_controller.OnReinitializeCurrentGame();
}

void cxgui::MainWindow::OnUndo()
{
    m_controller.OnUndo();
}

void cxgui::MainWindow::OnRedo()
{
    m_controller.OnRedo();
}

void cxgui::MainWindow::CreateGameResolutionWindow(cxmodel::NotificationContext p_context)
{

    cxmodel::GameResolution resolutionType;
    if(p_context == cxmodel::NotificationContext::GAME_WON)
    {
        resolutionType = cxmodel::GameResolution::WIN;
    }
    else if(p_context == cxmodel::NotificationContext::GAME_TIED)
    {
        resolutionType = cxmodel::GameResolution::TIE;
    }
    else
    {
        ASSERT_ERROR_MSG("Unhandled context.");
        return;
    }

    if(!m_gameResolution)
    {
        cxmodel::IConnectXGameInformation* gameInformationModel = dynamic_cast<cxmodel::IConnectXGameInformation*>(&m_model);
        IF_CONDITION_NOT_MET_DO(gameInformationModel, return;);

        auto gameResolutionPresenter = GameResolutionDialogPresenterFactory::Make(*gameInformationModel, resolutionType);
        IF_CONDITION_NOT_MET_DO(gameResolutionPresenter, return;);

        cxmodel::IConnectXGameActions* gameActionsModel = dynamic_cast<cxmodel::IConnectXGameActions*>(&m_model);
        IF_CONDITION_NOT_MET_DO(gameActionsModel, return;);

        std::unique_ptr<IGameResolutionDialogController> gameResolutionController = std::make_unique<GameResolutionDialogController>(*gameActionsModel);
        IF_CONDITION_NOT_MET_DO(gameResolutionController, return;);

        {
            auto gameResolutionWindow = std::make_unique<GameResolutionDialog>(std::move(gameResolutionPresenter), std::move(gameResolutionController));
            gameResolutionWindow->Init();

            m_gameResolution = std::move(gameResolutionWindow);
        }
    }

    m_gameResolution->Show();
}

void cxgui::MainWindow::ActivateNewGameView()
{
    if(!m_newGameView)
    {
        m_newGameView = std::make_unique<NewGameView>(m_presenter, m_controller, m_mainLayout, m_viewLeft, m_viewTop);
    }

    m_newGameView->Activate();
    m_window.show_all();
}

void cxgui::MainWindow::DeactivateNewGameView()
{
    IF_CONDITION_NOT_MET_DO(m_newGameView, return;);

    m_newGameView->DeActivate();

    m_gameResolution.reset();
}

void cxgui::MainWindow::ActivateGameView()
{
    if(!m_gameView)
    {
        m_gameView = std::make_unique<GameView>(m_presenter, m_controller, m_mainLayout, m_viewLeft, m_viewTop);
    }

    m_gameView->Activate();
    m_window.show_all();
}

void cxgui::MainWindow::DeactivateGameView()
{
    IF_CONDITION_NOT_MET_DO(m_gameView, return;);

    m_gameView->DeActivate();
    m_gameView.reset();
}
