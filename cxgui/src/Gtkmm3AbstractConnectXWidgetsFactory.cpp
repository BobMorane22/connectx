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
#include <cxgui/BoardAnimation.h>
#include <cxgui/Gtkmm3AboutWindow.h>
#include <cxgui/Gtkmm3AbstractConnectXWidgetsFactory.h>
#include <cxgui/Gtkmm3AnimatedBoard.h>
#include <cxgui/Gtkmm3DiscChip.h>
#include <cxgui/Gtkmm3GameResolutionDialog.h>
#include <cxgui/Gtkmm3GameView.h>
#include <cxgui/Gtkmm3MainWindow.h>
#include <cxgui/Gtkmm3NewGameView.h>
#include <cxgui/Gtkmm3NewPlayersList.h>
#include <cxgui/IAnimatedBoardModel.h>
#include <cxgui/IAnimatedBoardPresenter.h>
#include <cxgui/IButton.h>
#include <cxgui/IGameResolutionDialogController.h>
#include <cxgui/IGameResolutionDialogPresenter.h>
#include <cxgui/IGameViewController.h>
#include <cxgui/IGameViewPresenter.h>
#include <cxgui/ILabel.h>
#include <cxgui/IMainWindowController.h>
#include <cxgui/IMainWindowPresenter.h>
#include <cxgui/INewGameViewController.h>
#include <cxgui/INewGameViewPresenter.h>
#include <cxgui/INewPlayersList.h>
#include <cxgui/ISpinBox.h>
#include <cxgui/WidgetsFactories.h>

cxgui::Gtkmm3AbstractConnectXWidgetsFactory::Gtkmm3AbstractConnectXWidgetsFactory(
    Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
    InvariantsCheck();
}

void cxgui::Gtkmm3AbstractConnectXWidgetsFactory::RegisterStandardWidgetsFactory(
    IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory)
{
    m_widgetsFactories = std::make_unique<WidgetsFactories>(
        p_stdAbstractWidgetsFactory,
        *this);

    POSTCONDITION(m_widgetsFactories);
    InvariantsCheck();
}

std::unique_ptr<cxgui::IWindow> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateMainWindow(
    cxmodel::ModelSubject& p_model,
    IMainWindowController& p_controller,
    IMainWindowPresenter& p_presenter) const
{
    IF_PRECONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto mainWindow = cxgui::CreateWidget<Gtkmm3MainWindow>(
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

    auto aboutWindow = CreateWidget<Gtkmm3AboutWindow>(
        *m_widgetsFactories,
        std::move(p_presenter));
    POSTCONDITION(aboutWindow);

    aboutWindow->Init();

    POSTCONDITION(aboutWindow);
    InvariantsCheck();

    return aboutWindow;
}

std::unique_ptr<cxgui::IWindow> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateGameResolutionDialog(
    std::unique_ptr<IGameResolutionDialogPresenter> p_presenter,
    std::unique_ptr<IGameResolutionDialogController> p_controller) const
{
    IF_PRECONDITION_NOT_MET_DO(p_presenter, return nullptr;);
    IF_PRECONDITION_NOT_MET_DO(p_controller, return nullptr;);

    auto gameResolutionDialog = CreateWidget<Gtkmm3GameResolutionDialog>(
        *m_widgetsFactories,
        std::move(p_presenter),
        std::move(p_controller));
    gameResolutionDialog->Init();

    POSTCONDITION(gameResolutionDialog);
    InvariantsCheck();

    return gameResolutionDialog;
}

std::unique_ptr<cxgui::IView> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateNewGameView(
    INewGameViewPresenter& p_presenter,
    INewGameViewController& p_controller,
    IWindow& p_parentWindow,
    cxgui::ILayout& p_mainLayout,
    const cxmodel::Column& p_viewLeft,
    const cxmodel::Row& p_viewTop) const
{
    auto newGameView = std::make_unique<Gtkmm3NewGameView>(
        *m_widgetsFactories,
        p_presenter,
        p_controller,
        p_parentWindow,
        p_mainLayout,
        p_viewLeft,
        p_viewTop);

    InvariantsCheck();
    POSTCONDITION(newGameView);

    return newGameView;
}

std::unique_ptr<cxgui::IView> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateGameView(
    IGameViewPresenter& p_presenter,
    IGameViewController& p_controller,
    IWindow& p_parentWindow,
    cxgui::ILayout& p_mainLayout,
    const cxmodel::Column& p_viewLeft,
    const cxmodel::Row& p_viewTop) const
{
    auto gameView = std::make_unique<Gtkmm3GameView>(
        *m_widgetsFactories,
        p_presenter,
        p_controller,
        p_parentWindow,
        p_mainLayout,
        p_viewLeft,
        p_viewTop);

    InvariantsCheck();
    POSTCONDITION(gameView);

    return gameView;
}

std::unique_ptr<cxgui::INewPlayersList> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateNewPlayersList(
    const cxgui::INewGameViewPresenter& p_presenter) const
{
    auto newPlayersList = CreateWidget<Gtkmm3NewPlayersList>(p_presenter);

    InvariantsCheck();
    POSTCONDITION(newPlayersList);

    return newPlayersList;
}

std::unique_ptr<cxgui::IAnimatedBoard> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateGameBoard(
    const cxgui::IGameViewPresenter& p_presenter,
    const cxgui::AnimationSpeed& p_speed) const
{
    auto animatedBoard = CreateWidget<Gtkmm3AnimatedBoard>(p_presenter, p_speed);

    InvariantsCheck();
    POSTCONDITION(animatedBoard);

    return animatedBoard;
}

std::unique_ptr<cxgui::IChip> cxgui::Gtkmm3AbstractConnectXWidgetsFactory::CreateChip(
   const cxmodel::ChipColor& p_fillColor,
   const cxmodel::ChipColor& p_backgroundColor,
   int p_diameter) const
{
    auto chip = CreateWidget<Gtkmm3DiscChip>(
        p_fillColor,
        p_backgroundColor,
        p_diameter);

    InvariantsCheck();
    POSTCONDITION(chip);

    return chip;
}

void cxgui::Gtkmm3AbstractConnectXWidgetsFactory::InvariantsCheck() const 
{
    INVARIANT(m_gtkApplication);
}
