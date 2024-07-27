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
 * @file Gtkmm3MainWindow.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <string>

#include <cxinv/assertion.h>
#include <cxmodel/common.h>
#include <cxmodel/IConnectXGameActions.h>
#include <cxmodel/IConnectXGameInformation.h>
#include <cxmodel/IVersioning.h>
#include <cxmodel/GameResolutionStrategyFactory.h>
#include <cxuicmn/AboutWindowPresenter.h>
#include <cxuicmn/EnabledState.h>
#include <cxuicmn/GameResolutionDialogController.h>
#include <cxuicmn/GameResolutionDialogPresenterFactory.h>
#include <cxuicmn/Gtkmm3MainWindow.h>
#include <cxuicmn/IAbstractWidgetsFactory.h>
#include <cxuicmn/IAbstractConnectXWidgetsFactory.h>
#include <cxuicmn/IAnimatedBoardPresenter.h>
#include <cxuicmn/IButton.h>
#include <cxuicmn/ILabel.h>
#include <cxuicmn/ILayout.h>
#include <cxuicmn/INewPlayersList.h>
#include <cxuicmn/IMainWindowController.h>
#include <cxuicmn/IMainWindowPresenter.h>
#include <cxuicmn/IMenu.h>
#include <cxuicmn/IMenuBar.h>
#include <cxuicmn/IMenuItem.h>
#include <cxuicmn/ISpinBox.h>
#include <cxuicmn/IStatusBar.h>
#include <cxuicmn/IView.h>
#include <cxuicmn/KeyboardShortcut.h>
#include <cxuicmn/StatusBarPresenter.h>
#include <cxuicmn/StdActionIcon.h>
#include <cxuicmn/WidgetsFactories.h>
#include <cxuicmn/widgetUtilities.h>

cx::cmn::ui::Gtkmm3MainWindow::Gtkmm3MainWindow(
    Gtk::Application& p_gtkApplication,
    cx::model::ModelSubject& p_model,
    cx::cmn::ui::IMainWindowController& p_controller,
    cx::cmn::ui::IMainWindowPresenter& p_presenter,
    cx::cmn::ui::WidgetsFactories& p_widgetsFactories)
 : cx::cmn::ui::Gtkmm3Window{p_widgetsFactories}
 , m_gtkApplication{p_gtkApplication}
 , m_model{p_model}
 , m_controller{p_controller}
 , m_presenter{p_presenter}
 , m_widgetsFactories{p_widgetsFactories}
 , m_viewLeft{0}
 , m_viewTop{1}
{
    // Nothing to do.
}

cx::cmn::ui::Gtkmm3MainWindow::~Gtkmm3MainWindow()
{
    // We unregister the current view from the main layout. If the view is
    // reset before the layout has had time to unregister it, we get a dangling
    // reference to it in the layout.
    cx::cmn::ui::IWidget* currentViewLayout = m_mainLayout->GetWidgetAtPosition(m_viewTop, m_viewLeft);
    if(INL_ASSERT(currentViewLayout))
    {
        m_mainLayout->Unregister(*currentViewLayout);
    }
}

void cx::cmn::ui::Gtkmm3MainWindow::InitializeWidgets()
{
    const cx::cmn::ui::IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();

    m_menuBar = standardWidgetsFactory.CreateMenuBar();
    m_gameMenu = standardWidgetsFactory.CreateMenu(m_presenter.GetMenuLabel(MenuItem::GAME));
    m_helpMenu = standardWidgetsFactory.CreateMenu(m_presenter.GetMenuLabel(MenuItem::HELP));
    m_newGameMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::NEW_GAME));
    m_reinitializeMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::REINITIALIZE_GAME));
    m_undoMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::UNDO), cx::cmn::ui::FreeDesktop::StdActionIcon::EDIT_UNDO);
    m_redoMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::REDO), cx::cmn::ui::FreeDesktop::StdActionIcon::EDIT_REDO);
    m_quitMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::QUIT), cx::cmn::ui::FreeDesktop::StdActionIcon::APPLICATION_EXIT);
    m_contentsMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::CONTENTS), cx::cmn::ui::FreeDesktop::StdActionIcon::HELP_CONTENTS);
    m_aboutMenuItem = standardWidgetsFactory.CreateMenuItem(m_presenter.GetMenuLabel(MenuItem::ABOUT), cx::cmn::ui::FreeDesktop::StdActionIcon::HELP_ABOUT);
}

void cx::cmn::ui::Gtkmm3MainWindow::ConfigureWindow()
{
    set_title(m_presenter.GetWindowTitle());
    set_position(Gtk::WIN_POS_CENTER);
}

void cx::cmn::ui::Gtkmm3MainWindow::RegisterLayouts()
{
    // Nothing to do...
}

void cx::cmn::ui::Gtkmm3MainWindow::RegisterWidgets()
{
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    m_mainLayout->Register(*m_menuBar, {cx::model::Row{0u}, cx::cmn::ui::ILayout::RowSpan{1u}}, {cx::model::Column{0u}, cx::cmn::ui::ILayout::ColumnSpan{2u}});

    RegisterMenuBar();

    const IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();
    m_newGameView = connectXWidgetsFactory.CreateNewGameView(
        m_presenter,
        m_controller,
        *this,
        *m_mainLayout,
        m_viewLeft,
        m_viewTop);
    IF_PRECONDITION_NOT_MET_DO(m_newGameView, return;);

    m_newGameView->Activate();

    RegisterStatusBar();
}

void cx::cmn::ui::Gtkmm3MainWindow::ConfigureLayouts()
{
    // Nothing to do...
}

void cx::cmn::ui::Gtkmm3MainWindow::ConfigureWidgets()
{
    m_model.Attach(m_statusBarPresenter.get());
    m_statusBarPresenter->Attach(m_statusBar.get());
}

void cx::cmn::ui::Gtkmm3MainWindow::ConfigureSignalHandlers()
{
    m_newGameMenuItem->OnTriggered()->Connect([this](){OnNewGame();});
    m_reinitializeMenuItem->OnTriggered()->Connect([this](){OnReinitializeCurrentGame();});
    m_undoMenuItem->OnTriggered()->Connect([this]{OnUndo();});
    m_redoMenuItem->OnTriggered()->Connect([this]{OnRedo();});
    m_quitMenuItem->OnTriggered()->Connect([this](){close();});
    m_contentsMenuItem->OnTriggered()->Connect([this](){OnHelpContentsRequested();});
    m_aboutMenuItem->OnTriggered()->Connect([this](){OnCreateAboutWindow();});
}

int cx::cmn::ui::Gtkmm3MainWindow::Show()
{
    show_all();
    return m_gtkApplication.run(*this);
}

void cx::cmn::ui::Gtkmm3MainWindow::Update(cx::model::ModelNotificationContext p_context, cx::model::ModelSubject* p_subject)
{
    if(INL_PRECONDITION(p_subject))
    {
        switch(p_context)
        {
            case cx::model::ModelNotificationContext::CHIP_DROPPED:
            case cx::model::ModelNotificationContext::CHIP_DROPPED_FAILED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cx::model::ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN:
            case cx::model::ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN:
            {
                UpdateChipMoved(p_context);
                break;
            }
            case cx::model::ModelNotificationContext::CREATE_NEW_GAME:
            {
                UpdateCreateNewGame();
                break;
            }
            case cx::model::ModelNotificationContext::UNDO_CHIP_DROPPED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cx::model::ModelNotificationContext::REDO_CHIP_DROPPED:
            {
                UpdateChipDropped(p_context);
                break;
            }
            case cx::model::ModelNotificationContext::GAME_WON:
            {
                UpdateGameWon(p_context);
                break;
            }
            case cx::model::ModelNotificationContext::GAME_TIED:
            {
                UpdateGameTied(p_context);
                break;
            }
            case cx::model::ModelNotificationContext::GAME_ENDED:
            {
                UpdateGameEnded();
                break;
            }
            case cx::model::ModelNotificationContext::GAME_REINITIALIZED:
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

void cx::cmn::ui::Gtkmm3MainWindow::UpdateCreateNewGame()
{
    DeactivateNewGameView();
    ActivateGameView();
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateChipDropped(cx::model::ModelNotificationContext p_context)
{
    if(INL_ASSERT(m_gameView))
    {
        m_gameView->Update(p_context);
    }
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateChipMoved(cx::model::ModelNotificationContext p_context)
{
    if(INL_ASSERT(m_gameView))
    {
        m_gameView->Update(p_context);
    }
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateGameWon(cx::model::ModelNotificationContext p_context)
{
    m_gameView->Update(p_context);
    CreateGameResolutionWindow(p_context);
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateGameTied(cx::model::ModelNotificationContext p_context)
{
    m_gameView->Update(p_context);
    CreateGameResolutionWindow(p_context);
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateGameEnded()
{
    DeactivateGameView();
    ActivateNewGameView();
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateGameReinitialized(cx::model::ModelNotificationContext p_context)
{
    m_gameView->Update(p_context); 
}

void cx::cmn::ui::Gtkmm3MainWindow::UpdateMenuItems(cx::model::ModelNotificationContext p_context)
{
    EnabledStateUpdate(*m_newGameMenuItem,      m_presenter.IsNewGamePossible());
    EnabledStateUpdate(*m_reinitializeMenuItem, m_presenter.IsCurrentGameReinitializationPossible());
    EnabledStateUpdate(*m_undoMenuItem,         p_context == cx::model::ModelNotificationContext::CHIP_DROPPED || m_presenter.IsUndoPossible());
    EnabledStateUpdate(*m_redoMenuItem,         m_presenter.IsRedoPossible());
}

void cx::cmn::ui::Gtkmm3MainWindow::RegisterMenuBar()
{
    // Keyboard shortcuts:
    m_undoMenuItem->RegisterKeyboardShortcut({cx::cmn::ui::Key::CTRL + cx::cmn::ui::Key::Z});
    m_redoMenuItem->RegisterKeyboardShortcut({cx::cmn::ui::Key::CTRL + cx::cmn::ui::Key::Y});
    m_quitMenuItem->RegisterKeyboardShortcut({cx::cmn::ui::Key::CTRL + cx::cmn::ui::Key::Q});
    m_contentsMenuItem->RegisterKeyboardShortcut({cx::cmn::ui::Key::F1});

    // Game menu:
    m_gameMenu->Register(*m_newGameMenuItem);
    m_gameMenu->Register(*m_reinitializeMenuItem);
    m_gameMenu->Register(*m_undoMenuItem);
    m_gameMenu->Register(*m_redoMenuItem);
    m_gameMenu->Register(*m_quitMenuItem);

    // Help menu:
    m_helpMenu->Register(*m_contentsMenuItem);
    m_helpMenu->Register(*m_aboutMenuItem);

    // Registering everything in the menuBar:
    m_menuBar->Register(*m_gameMenu);
    m_menuBar->Register(*m_helpMenu);

    // Enabling menu items according to the application state:
    EnabledStateUpdate(*m_newGameMenuItem,      m_presenter.IsNewGamePossible());
    EnabledStateUpdate(*m_reinitializeMenuItem, m_presenter.IsCurrentGameReinitializationPossible());
    EnabledStateUpdate(*m_undoMenuItem,         m_presenter.IsUndoPossible());
    EnabledStateUpdate(*m_redoMenuItem,         m_presenter.IsRedoPossible());
}

void cx::cmn::ui::Gtkmm3MainWindow::RegisterStatusBar()
{
    const IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();

    m_statusBarPresenter = std::make_unique<StatusBarPresenter>();
    IF_CONDITION_NOT_MET_DO(m_statusBarPresenter, return;);
    m_statusBar = standardWidgetsFactory.CreateStatusBar(*m_statusBarPresenter);
    IF_CONDITION_NOT_MET_DO(m_statusBar, return;);

    m_mainLayout->Register(
        *m_statusBar,
        {m_viewTop + cx::model::Row{1u},cx::cmn::ui::ILayout::RowSpan{1u}},
        {cx::model::Column{0u}, cx::cmn::ui::ILayout::ColumnSpan{2u}}
    );

    POSTCONDITION(m_statusBarPresenter);
    POSTCONDITION(m_statusBar);
}

void cx::cmn::ui::Gtkmm3MainWindow::OnHelpContentsRequested()
{
    const guint32 timestamp = gtk_get_current_event_time();
    GError* error = nullptr;

    // Trigger the Gnome help system:
    Gtk::Window* window = dynamic_cast<Gtk::Window*>(this);
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

void cx::cmn::ui::Gtkmm3MainWindow::OnCreateAboutWindow()
{
    if(!m_aboutWindow)
    {
        cx::model::IVersioning* versionModel = dynamic_cast<cx::model::IVersioning*>(&m_model);
        IF_CONDITION_NOT_MET_DO(versionModel, return;);

        std::unique_ptr<IAboutWindowPresenter> aboutPresenter = std::make_unique<AboutWindowPresenter>(*versionModel);
        IF_CONDITION_NOT_MET_DO(aboutPresenter, return;);

        {
            const IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();
            m_aboutWindow = connectXWidgetsFactory.CreateAboutWindow(std::move(aboutPresenter));
            IF_CONDITION_NOT_MET_DO(m_aboutWindow, return;);
        }
    }

    const int result = m_aboutWindow->Show();
    IF_CONDITION_NOT_MET_DO(result == EXIT_SUCCESS, return;);
}

void cx::cmn::ui::Gtkmm3MainWindow::OnNewGame()
{
    m_controller.OnNewGame();
}

void cx::cmn::ui::Gtkmm3MainWindow::OnReinitializeCurrentGame()
{
   m_controller.OnReinitializeCurrentGame();
}

void cx::cmn::ui::Gtkmm3MainWindow::OnUndo()
{
    m_controller.OnUndo();
}

void cx::cmn::ui::Gtkmm3MainWindow::OnRedo()
{
    m_controller.OnRedo();
}

void cx::cmn::ui::Gtkmm3MainWindow::CreateGameResolutionWindow(cx::model::ModelNotificationContext p_context)
{

    cx::model::GameResolution resolutionType;
    if(p_context == cx::model::ModelNotificationContext::GAME_WON)
    {
        resolutionType = cx::model::GameResolution::WIN;
    }
    else if(p_context == cx::model::ModelNotificationContext::GAME_TIED)
    {
        resolutionType = cx::model::GameResolution::TIE;
    }
    else
    {
        ASSERT_ERROR_MSG("Unhandled context.");
        return;
    }

    if(!m_gameResolution)
    {
        cx::model::IConnectXGameInformation* gameInformationModel = dynamic_cast<cx::model::IConnectXGameInformation*>(&m_model);
        IF_CONDITION_NOT_MET_DO(gameInformationModel, return;);

        auto gameResolutionPresenter = GameResolutionDialogPresenterFactory::Make(*gameInformationModel, resolutionType);
        IF_CONDITION_NOT_MET_DO(gameResolutionPresenter, return;);

        cx::model::IConnectXGameActions* gameActionsModel = dynamic_cast<cx::model::IConnectXGameActions*>(&m_model);
        IF_CONDITION_NOT_MET_DO(gameActionsModel, return;);

        std::unique_ptr<IGameResolutionDialogController> gameResolutionController = std::make_unique<GameResolutionDialogController>(*gameActionsModel);
        IF_CONDITION_NOT_MET_DO(gameResolutionController, return;);

        const IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();
        m_gameResolution = connectXWidgetsFactory.CreateGameResolutionDialog(
            std::move(gameResolutionPresenter),
            std::move(gameResolutionController));
        IF_CONDITION_NOT_MET_DO(m_gameResolution, return;);
    }

    const int result = m_gameResolution->Show();
    IF_CONDITION_NOT_MET_DO(result == EXIT_SUCCESS, return;);
}

void cx::cmn::ui::Gtkmm3MainWindow::ActivateNewGameView()
{
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    if(!m_newGameView)
    {
        const IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();
        m_newGameView = connectXWidgetsFactory.CreateNewGameView(
            m_presenter,
            m_controller,
            *this,
            *m_mainLayout,
            m_viewLeft,
            m_viewTop);
        IF_PRECONDITION_NOT_MET_DO(m_newGameView, return;);
    }

    m_newGameView->Activate();
    resize(1, 1);
    show_all();
}

void cx::cmn::ui::Gtkmm3MainWindow::DeactivateNewGameView()
{
    IF_CONDITION_NOT_MET_DO(m_newGameView, return;);

    m_newGameView->DeActivate();

    m_gameResolution.reset();
}

void cx::cmn::ui::Gtkmm3MainWindow::ActivateGameView()
{
    IF_CONDITION_NOT_MET_DO(m_mainLayout, return;);

    if(!m_gameView)
    {
        const IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();
        m_gameView = connectXWidgetsFactory.CreateGameView(
            m_presenter,
            m_controller,
            *this,
            *m_mainLayout,
            m_viewLeft,
            m_viewTop);
        IF_CONDITION_NOT_MET_DO(m_gameView, return;);
    }

    m_gameView->Activate();
    resize(1, 1);
    show_all();
}

void cx::cmn::ui::Gtkmm3MainWindow::DeactivateGameView()
{
    IF_CONDITION_NOT_MET_DO(m_gameView, return;);

    m_gameView->DeActivate();
    m_gameView.reset();
}
