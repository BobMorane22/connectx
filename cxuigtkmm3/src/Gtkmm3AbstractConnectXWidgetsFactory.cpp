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
#include <cxui/BoardAnimation.h>
#include <cxuigtkmm3/Gtkmm3AboutWindow.h>
#include <cxuigtkmm3/Gtkmm3AbstractConnectXWidgetsFactory.h>
#include <cxuigtkmm3/Gtkmm3AnimatedBoard.h>
#include <cxuigtkmm3/Gtkmm3ColorPicker.h>
#include <cxuigtkmm3/Gtkmm3DiscChip.h>
#include <cxuigtkmm3/Gtkmm3GameResolutionDialog.h>
#include <cxuigtkmm3/Gtkmm3GameView.h>
#include <cxuigtkmm3/Gtkmm3MainWindow.h>
#include <cxuigtkmm3/Gtkmm3NewGameView.h>
#include <cxuigtkmm3/Gtkmm3NewPlayersList.h>
#include <cxuicmngtkmm3/Gtkmm3WidgetDelegate.h>
#include <cxui/IAnimatedBoardModel.h>
#include <cxui/IAnimatedBoardPresenter.h>
#include <cxuicmn/IButton.h>
#include <cxui/IGameResolutionDialogController.h>
#include <cxui/IGameResolutionDialogPresenter.h>
#include <cxui/IGameViewController.h>
#include <cxui/IGameViewPresenter.h>
#include <cxuicmn/ILabel.h>
#include <cxuicmn/ILayout.h>
#include <cxui/IMainWindowController.h>
#include <cxui/IMainWindowPresenter.h>
#include <cxui/INewGameViewController.h>
#include <cxui/INewGameViewPresenter.h>
#include <cxui/INewPlayersList.h>
#include <cxuicmn/ISpinBox.h>
#include <cxui/WidgetsFactories.h>

cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::Gtkmm3AbstractConnectXWidgetsFactory(
    Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
    InvariantsCheck();
}

void cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::RegisterStandardWidgetsFactory(
    IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory)
{
    m_widgetsFactories = std::make_unique<WidgetsFactories>(
        p_stdAbstractWidgetsFactory,
        *this);

    POSTCONDITION(m_widgetsFactories);
    InvariantsCheck();
}

std::unique_ptr<cx::ui::cmn::IWindow> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateMainWindow(
    cx::model::ModelSubject& p_model,
    IMainWindowController& p_controller,
    IMainWindowPresenter& p_presenter) const
{
    IF_PRECONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto mainWindow = cx::ui::cmn::CreateWidget<Gtkmm3MainWindow>(
        *(m_gtkApplication.get()),
        p_model,
        p_controller,
        p_presenter,
        *m_widgetsFactories);
    IF_CONDITION_NOT_MET_DO(mainWindow, return nullptr;);

    mainWindow->Init();

    POSTCONDITION(mainWindow);
    InvariantsCheck();

    return mainWindow;
}

std::unique_ptr<cx::ui::cmn::IWindow> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateAboutWindow(
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

std::unique_ptr<cx::ui::cmn::IWindow> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateGameResolutionDialog(
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

std::unique_ptr<cx::ui::cmn::IView> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateNewGameView(
    INewGameViewPresenter& p_presenter,
    INewGameViewController& p_controller,
    IWindow& p_parentWindow,
    cx::ui::cmn::ILayout& p_mainLayout,
    const cx::model::Column& p_viewLeft,
    const cx::model::Row& p_viewTop) const
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

std::unique_ptr<cx::ui::cmn::IView> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateGameView(
    IGameViewPresenter& p_presenter,
    IGameViewController& p_controller,
    IWindow& p_parentWindow,
    cx::ui::cmn::ILayout& p_mainLayout,
    const cx::model::Column& p_viewLeft,
    const cx::model::Row& p_viewTop) const
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

std::unique_ptr<cx::ui::cmn::INewPlayersList> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateNewPlayersList(
    const cx::ui::cmn::INewGameViewPresenter& p_presenter) const
{
    IF_CONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto newPlayersList = CreateWidget<Gtkmm3NewPlayersList>(p_presenter, *m_widgetsFactories);

    InvariantsCheck();
    POSTCONDITION(newPlayersList);

    return newPlayersList;
}

std::unique_ptr<cx::ui::cmn::IColorPicker> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateColorPicker(
    const std::vector<cx::model::ChipColor>& p_colors) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_colors.empty(), return nullptr;);

    auto picker = CreateWidget<Gtkmm3ColorPicker>(p_colors);
    POSTCONDITION(picker);

    return picker;
}

std::unique_ptr<cx::ui::cmn::IAnimatedBoard> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateGameBoard(
    const cx::ui::cmn::IGameViewPresenter& p_presenter,
    const cx::ui::cmn::AnimationSpeed& p_speed) const
{
    auto animatedBoard = CreateWidget<Gtkmm3AnimatedBoard>(p_presenter, p_speed);

    InvariantsCheck();
    POSTCONDITION(animatedBoard);

    return animatedBoard;
}

std::unique_ptr<cx::ui::cmn::IChip> cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::CreateChip(
   const cx::model::ChipColor& p_fillColor,
   const cx::model::ChipColor& p_backgroundColor,
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

void cx::ui::cmn::Gtkmm3AbstractConnectXWidgetsFactory::InvariantsCheck() const 
{
    INVARIANT(m_gtkApplication);
}
