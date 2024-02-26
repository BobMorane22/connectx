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

#include <cxinv/assertion.h>
#include <cxmodel/common.h>
#include <cxmodel/IConnectXGameActions.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IVersioning.h>
#include <cxmodel/GameResolutionStrategyFactory.h>
#include <cxgui/About.h>
#include <cxgui/AboutWindowPresenter.h>
#include <cxgui/EnabledState.h>
#include <cxgui/GameResolutionDialog.h>
#include <cxgui/GameResolutionDialogController.h>
#include <cxgui/GameResolutionDialogPresenterFactory.h>
#include <cxgui/GameView.h>
#include <cxgui/Gtkmm3Layout.h>
#include <cxgui/Gtkmm3Menu.h>
#include <cxgui/Gtkmm3MenuBar.h>
#include <cxgui/Gtkmm3MenuItem.h>
#include <cxgui/IAnimatedBoardPresenter.h>
#include <cxgui/ILabel.h>
#include <cxgui/ILayout.h>
#include <cxgui/INewPlayersList.h>
#include <cxgui/IMainWindowController.h>
#include <cxgui/IMainWindowPresenter.h>
#include <cxgui/ISpinBox.h>
#include <cxgui/KeyboardShortcut.h>
#include <cxgui/MainWindow.h>
#include <cxgui/NewGameView.h>
#include <cxgui/StatusBar.h>
#include <cxgui/StatusBarPresenter.h>
#include <cxgui/StdActionIcon.h>

cxgui::MainWindow::MainWindow(Gtk::Application& p_gtkApplication,
                              cxmodel::ModelSubject& p_model,
                              cxgui::IMainWindowController& p_controller,
                              cxgui::IMainWindowPresenter& p_presenter)
 : m_gtkApplication{p_gtkApplication}
 , m_model{p_model}
 , m_controller{p_controller}
 , m_presenter{p_presenter}
 , m_viewLeft{0}
 , m_viewTop{1}
{
    // This should be located elsewhere. For now, I don't have a choice to locate it
    // here because of the pointer nature of the attribute. To be moved when passing
    // to popover menus.
    m_menuBar = CreateWidget<Gtkmm3MenuBar>();
    ASSERT(m_menuBar);

    m_gameMenu = CreateWidget<Gtkmm3Menu>(m_presenter.GetMenuLabel(MenuItem::GAME));
    ASSERT(m_gameMenu);

    m_newGameMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::NEW_GAME));
    ASSERT(m_newGameMenuItem);

    m_reinitializeMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::REINITIALIZE_GAME));
    ASSERT(m_reinitializeMenuItem);

    m_undoMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::UNDO), cxgui::FreeDesktop::StdActionIcon::EDIT_UNDO);
    ASSERT(m_undoMenuItem);

    m_redoMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::REDO), cxgui::FreeDesktop::StdActionIcon::EDIT_REDO);
    ASSERT(m_redoMenuItem);

    m_quitMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::QUIT), cxgui::FreeDesktop::StdActionIcon::APPLICATION_EXIT);
    ASSERT(m_quitMenuItem);

    m_helpMenu = CreateWidget<Gtkmm3Menu>(m_presenter.GetMenuLabel(MenuItem::HELP));
    ASSERT(m_helpMenu);

    m_contentsMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::CONTENTS), cxgui::FreeDesktop::StdActionIcon::HELP_CONTENTS);
    ASSERT(m_contentsMenuItem);

    m_aboutMenuItem = CreateWidget<Gtkmm3MenuItem>(m_presenter.GetMenuLabel(MenuItem::ABOUT), cxgui::FreeDesktop::StdActionIcon::HELP_ABOUT);
    ASSERT(m_aboutMenuItem);
}

cxgui::MainWindow::~MainWindow()
{
    // We unregister the current view from the main layout. If the view is
    // reset before the layout has had time to unregister it, we get a dangling
    // reference to it in the layout.
    cxgui::IWidget* currentViewLayout = m_mainLayout->GetWidgetAtPosition(m_viewTop, m_viewLeft);
    if(INL_ASSERT(currentViewLayout))
    {
        m_mainLayout->Unregister(*currentViewLayout);
    }
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
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    m_mainLayout->Register(*m_menuBar, {cxmodel::Row{0u}, cxgui::ILayout::RowSpan{1u}}, {cxmodel::Column{0u}, cxgui::ILayout::ColumnSpan{2u}});

    RegisterMenuBar();

    m_newGameView = std::make_unique<NewGameView>(m_presenter, m_controller, m_window, *m_mainLayout, m_viewLeft, m_viewTop);
    m_newGameView->Activate();

    RegisterStatusBar();
}

void cxgui::MainWindow::ConfigureLayouts()
{
    // Nothing to do...
}

void cxgui::MainWindow::ConfigureWidgets()
{
    m_model.Attach(m_statusbarPresenter.get());
    m_statusbarPresenter->Attach(m_statusbar.get());
}

void cxgui::MainWindow::ConfigureSignalHandlers()
{
    m_newGameMenuItem->OnTriggered()->Connect([this](){OnNewGame();});
    m_reinitializeMenuItem->OnTriggered()->Connect([this](){OnReinitializeCurrentGame();});
    m_undoMenuItem->OnTriggered()->Connect([this]{OnUndo();});
    m_redoMenuItem->OnTriggered()->Connect([this]{OnRedo();});
    m_quitMenuItem->OnTriggered()->Connect([this](){m_window.close();});
    m_contentsMenuItem->OnTriggered()->Connect([this](){OnHelpContentsRequested();});
    m_aboutMenuItem->OnTriggered()->Connect([this](){OnCreateAboutWindow();});
}

int cxgui::MainWindow::Show()
{
    m_window.show_all();
    return m_gtkApplication.run(m_window);
}

void cxgui::MainWindow::Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject)
{
    if(INL_PRECONDITION(p_subject))
    {
        switch(p_context)
        {
            case cxmodel::ModelNotificationContext::CHIP_DROPPED:
            case cxmodel::ModelNotificationContext::CHIP_DROPPED_FAILED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cxmodel::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN:
            case cxmodel::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN:
            {
                UpdateChipMoved(p_context);
                break;
            }
            case cxmodel::ModelNotificationContext::CREATE_NEW_GAME:
            {
                UpdateCreateNewGame();
                break;
            }
            case cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cxmodel::ModelNotificationContext::REDO_CHIP_DROPPED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cxmodel::ModelNotificationContext::GAME_WON:
            {
                UpdateGameWon(p_context);
                break;
            }
            case cxmodel::ModelNotificationContext::GAME_TIED:
            {
                UpdateGameTied(p_context);
                break;
            }
            case cxmodel::ModelNotificationContext::GAME_ENDED:
            {
                UpdateGameEnded();
                break;
            }
            case cxmodel::ModelNotificationContext::GAME_REINITIALIZED:
            {
                UpdateGameReinitialized(p_context);
                break;
            }
            default:
                ASSERT_ERROR_MSG("Unsupported notification context.");
        }
    }

    UpdateMenuItems(p_context);
}

void cxgui::MainWindow::UpdateCreateNewGame()
{
    DeactivateNewGameView();
    ActivateGameView();
}

void cxgui::MainWindow::UpdateChipDropped(cxmodel::ModelNotificationContext p_context)
{
    if(INL_ASSERT(m_gameView))
    {
        m_gameView->Update(p_context);
    }
}

void cxgui::MainWindow::UpdateChipMoved(cxmodel::ModelNotificationContext p_context)
{
    if(INL_ASSERT(m_gameView))
    {
        m_gameView->Update(p_context);
    }
}

void cxgui::MainWindow::UpdateGameWon(cxmodel::ModelNotificationContext p_context)
{
    m_gameView->Update(p_context);
    CreateGameResolutionWindow(p_context);
}

void cxgui::MainWindow::UpdateGameTied(cxmodel::ModelNotificationContext p_context)
{
    m_gameView->Update(p_context);
    CreateGameResolutionWindow(p_context);
}

void cxgui::MainWindow::UpdateGameEnded()
{
    DeactivateGameView();
    ActivateNewGameView();
}

void cxgui::MainWindow::UpdateGameReinitialized(cxmodel::ModelNotificationContext p_context)
{
    m_gameView->Update(p_context); 
}

void cxgui::MainWindow::UpdateMenuItems(cxmodel::ModelNotificationContext p_context)
{
    m_newGameMenuItem->SetEnabled(cxgui::EnabledState::Disabled);
    if(m_presenter.IsNewGamePossible())
    {
        m_newGameMenuItem->SetEnabled(cxgui::EnabledState::Enabled);
    }

    m_reinitializeMenuItem->SetEnabled(cxgui::EnabledState::Disabled);
    if(m_presenter.IsCurrentGameReinitializationPossible())
    {
        m_reinitializeMenuItem->SetEnabled(cxgui::EnabledState::Enabled);
    }

    m_undoMenuItem->SetEnabled(cxgui::EnabledState::Disabled);
    if(p_context == cxmodel::ModelNotificationContext::CHIP_DROPPED || m_presenter.IsUndoPossible())
    {
        m_undoMenuItem->SetEnabled(cxgui::EnabledState::Enabled);
    }

    m_redoMenuItem->SetEnabled(cxgui::EnabledState::Disabled);
    if(m_presenter.IsRedoPossible())
    {
        m_redoMenuItem->SetEnabled(cxgui::EnabledState::Enabled);
    }
}

void cxgui::MainWindow::RegisterMenuBar()
{
    // Keyboard shortcuts:
    m_undoMenuItem->RegisterKeyboardShortcut({cxgui::Key::CTRL + cxgui::Key::Z});
    m_redoMenuItem->RegisterKeyboardShortcut({cxgui::Key::CTRL + cxgui::Key::Y});
    m_quitMenuItem->RegisterKeyboardShortcut({cxgui::Key::CTRL + cxgui::Key::Q});
    m_contentsMenuItem->RegisterKeyboardShortcut({cxgui::Key::F1});

    // Game menu:
    m_gameMenu->Register(*m_newGameMenuItem);
    m_gameMenu->Register(*m_reinitializeMenuItem);
    m_gameMenu->Register(*m_undoMenuItem);
    m_gameMenu->Register(*m_redoMenuItem);
    m_gameMenu->Register(*m_quitMenuItem);

    // Help menu:
    m_helpMenu->Register(*m_contentsMenuItem);
    m_helpMenu->Register(*m_aboutMenuItem);

    // Registering everythin in the menuBar:
    m_menuBar->Register(*m_gameMenu);
    m_menuBar->Register(*m_helpMenu);
}

void cxgui::MainWindow::RegisterStatusBar()
{
    m_statusbarPresenter = std::make_unique<StatusBarPresenter>();
    std::unique_ptr<StatusBar> concreteStatusBar = std::make_unique<StatusBar>(*m_statusbarPresenter);

    m_mainLayout->Register(
        concreteStatusBar->GetGtkStatusBar(),
        {m_viewTop + cxmodel::Row{1u},cxgui::ILayout::RowSpan{1u}},
        {cxmodel::Column{0u}, cxgui::ILayout::ColumnSpan{2u}});

    m_statusbar = std::move(concreteStatusBar);

    POSTCONDITION(m_statusbarPresenter);
    POSTCONDITION(m_statusbar);
}

void cxgui::MainWindow::OnHelpContentsRequested()
{
    const guint32 timestamp = gtk_get_current_event_time();
    GError* error = nullptr;

    // Trigger the Gnome help system:
    Gtk::Window* window = dynamic_cast<Gtk::Window*>(&m_window);
    IF_CONDITION_NOT_MET_DO(window, return;);

    const bool status = gtk_show_uri_on_window(window->gobj(),
                                               "help:connectx",
                                               timestamp,
                                               &error);

    if(!status)
    {
        ASSERT_ERROR_MSG(error->message);
        return;
    }
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

void cxgui::MainWindow::CreateGameResolutionWindow(cxmodel::ModelNotificationContext p_context)
{

    cxmodel::GameResolution resolutionType;
    if(p_context == cxmodel::ModelNotificationContext::GAME_WON)
    {
        resolutionType = cxmodel::GameResolution::WIN;
    }
    else if(p_context == cxmodel::ModelNotificationContext::GAME_TIED)
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
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    if(!m_newGameView)
    {
        m_newGameView = std::make_unique<NewGameView>(m_presenter, m_controller, m_window, *m_mainLayout, m_viewLeft, m_viewTop);
    }

    m_newGameView->Activate();
    m_window.resize(1, 1);
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
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    if(!m_gameView)
    {
        m_gameView = std::make_unique<GameView>(m_presenter, m_controller, m_window, *m_mainLayout, m_viewLeft, m_viewTop);
        IF_CONDITION_NOT_MET_DO(m_gameView, return;);
    }

    m_gameView->Activate();
    m_window.resize(1, 1);
    m_window.show_all();
}

void cxgui::MainWindow::DeactivateGameView()
{
    IF_CONDITION_NOT_MET_DO(m_gameView, return;);

    m_gameView->DeActivate();
    m_gameView.reset();
}
