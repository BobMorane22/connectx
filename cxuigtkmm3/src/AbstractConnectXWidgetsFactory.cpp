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
 * @file AbstractConnectXWidgetsFactory.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxcmnui/IButton.h>
#include <cxcmnui/ILabel.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/ISpinBox.h>
#include <cxui/BoardAnimation.h>
#include <cxui/IAnimatedBoardModel.h>
#include <cxui/IAnimatedBoardPresenter.h>
#include <cxui/IGameResolutionDialogController.h>
#include <cxui/IGameResolutionDialogPresenter.h>
#include <cxui/IGameViewController.h>
#include <cxui/IGameViewPresenter.h>
#include <cxui/IMainWindowController.h>
#include <cxui/IMainWindowPresenter.h>
#include <cxui/INewGameViewController.h>
#include <cxui/INewGameViewPresenter.h>
#include <cxui/INewPlayersList.h>
#include <cxui/WidgetsFactories.h>
#include <cxcmnuigtkmm3/WidgetDelegate.h>
#include <cxuigtkmm3/AboutWindow.h>
#include <cxuigtkmm3/AbstractConnectXWidgetsFactory.h>
#include <cxuigtkmm3/AnimatedBoard.h>
#include <cxuigtkmm3/ColorPicker.h>
#include <cxuigtkmm3/DiscChip.h>
#include <cxuigtkmm3/GameResolutionDialog.h>
#include <cxuigtkmm3/GameView.h>
#include <cxuigtkmm3/MainWindow.h>
#include <cxuigtkmm3/NewGameView.h>
#include <cxuigtkmm3/NewPlayersList.h>

cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::AbstractConnectXWidgetsFactory(
    Glib::RefPtr<Gtk::Application> p_gtkApplication)
{
    PRECONDITION(bool(p_gtkApplication));

    m_gtkApplication = p_gtkApplication;

    POSTCONDITION(bool(m_gtkApplication));
    InvariantsCheck();
}

void cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::RegisterStandardWidgetsFactory(
    cx::cmn::ui::IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory)
{
    m_widgetsFactories = std::make_unique<cx::ui::WidgetsFactories>(
        p_stdAbstractWidgetsFactory,
        *this);

    POSTCONDITION(m_widgetsFactories);
    InvariantsCheck();
}

std::unique_ptr<cx::cmn::ui::IWindow> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateMainWindow(
    cx::model::ModelSubject& p_model,
    cx::ui::IMainWindowController& p_controller,
    cx::ui::IMainWindowPresenter& p_presenter) const
{
    IF_PRECONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto mainWindow = cx::cmn::ui::gtkmm3::CreateWidget<MainWindow>(
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

std::unique_ptr<cx::cmn::ui::IWindow> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateAboutWindow(
    std::unique_ptr<cx::ui::IAboutWindowPresenter> p_presenter) const
{
    IF_PRECONDITION_NOT_MET_DO(p_presenter, return nullptr;);

    auto aboutWindow = cx::cmn::ui::gtkmm3::CreateWidget<AboutWindow>(
        *m_widgetsFactories,
        std::move(p_presenter));
    POSTCONDITION(aboutWindow);

    aboutWindow->Init();

    POSTCONDITION(aboutWindow);
    InvariantsCheck();

    return aboutWindow;
}

std::unique_ptr<cx::cmn::ui::IWindow> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateGameResolutionDialog(
    std::unique_ptr<cx::ui::IGameResolutionDialogPresenter> p_presenter,
    std::unique_ptr<cx::ui::IGameResolutionDialogController> p_controller) const
{
    IF_PRECONDITION_NOT_MET_DO(p_presenter, return nullptr;);
    IF_PRECONDITION_NOT_MET_DO(p_controller, return nullptr;);

    auto gameResolutionDialog = cx::cmn::ui::gtkmm3::CreateWidget<GameResolutionDialog>(
        *m_widgetsFactories,
        std::move(p_presenter),
        std::move(p_controller));
    gameResolutionDialog->Init();

    POSTCONDITION(gameResolutionDialog);
    InvariantsCheck();

    return gameResolutionDialog;
}

std::unique_ptr<cx::ui::IView> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateNewGameView(
    cx::ui::INewGameViewPresenter& p_presenter,
    cx::ui::INewGameViewController& p_controller,
    cx::cmn::ui::IWindow& p_parentWindow,
    cx::cmn::ui::ILayout& p_mainLayout,
    const cx::model::Column& p_viewLeft,
    const cx::model::Row& p_viewTop) const
{
    auto newGameView = std::make_unique<NewGameView>(
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

std::unique_ptr<cx::ui::IView> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateGameView(
    cx::ui::IGameViewPresenter& p_presenter,
    cx::ui::IGameViewController& p_controller,
    cx::cmn::ui::IWindow& p_parentWindow,
    cx::cmn::ui::ILayout& p_mainLayout,
    const cx::model::Column& p_viewLeft,
    const cx::model::Row& p_viewTop) const
{
    auto gameView = std::make_unique<GameView>(
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

std::unique_ptr<cx::ui::INewPlayersList> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateNewPlayersList(
    const cx::ui::INewGameViewPresenter& p_presenter) const
{
    IF_CONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto newPlayersList = cx::cmn::ui::gtkmm3::CreateWidget<NewPlayersList>(p_presenter, *m_widgetsFactories);

    InvariantsCheck();
    POSTCONDITION(newPlayersList);

    return newPlayersList;
}

std::unique_ptr<cx::ui::IColorPicker> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateColorPicker(
    const std::vector<cx::model::ChipColor>& p_colors) const
{
    IF_PRECONDITION_NOT_MET_DO(!p_colors.empty(), return nullptr;);

    auto picker = cx::cmn::ui::gtkmm3::CreateWidget<ColorPicker>(p_colors);
    POSTCONDITION(picker);

    return picker;
}

std::unique_ptr<cx::ui::IAnimatedBoard> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateGameBoard(
    const cx::ui::IGameViewPresenter& p_presenter,
    const cx::ui::AnimationSpeed& p_speed) const
{
    auto animatedBoard = cx::cmn::ui::gtkmm3::CreateWidget<AnimatedBoard>(p_presenter, p_speed);

    InvariantsCheck();
    POSTCONDITION(animatedBoard);

    return animatedBoard;
}

std::unique_ptr<cx::ui::IChip> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateChip(
   const cx::model::ChipColor& p_fillColor,
   const cx::model::ChipColor& p_backgroundColor,
   int p_diameter) const
{
    auto chip = cx::cmn::ui::gtkmm3::CreateWidget<DiscChip>(
        p_fillColor,
        p_backgroundColor,
        p_diameter);

    InvariantsCheck();
    POSTCONDITION(chip);

    return chip;
}

void cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::InvariantsCheck() const 
{
    INVARIANT(m_gtkApplication);
}
