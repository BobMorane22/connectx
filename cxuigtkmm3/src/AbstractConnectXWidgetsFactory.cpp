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
#include <cxui/IStatusBar.h>
#include <cxui/WidgetsFactories.h>
#include <cxcmnuigtkmm3/WidgetDelegate.h>
#include <cxuigtkmm3/AbstractConnectXWidgetsFactory.h>

#include "AboutWindow.h"
#include "AnimatedBoard.h"
#include "ColorPicker.h"
#include "DiscChip.h"
#include "GameResolutionDialog.h"
#include "GameView.h"
#include "MainWindow.h"
#include "NewGameView.h"
#include "NewPlayersList.h"
#include "StatusBar.h"

namespace cx::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Abstract widgets factory for Gtkmm 3.24.5.
 *
 * This factory handles the Connect X specific widgets.
 *
 * @invariant
 *       The stored `Gtk::Application` instance is valid.
 *
 *************************************************************************************************/
class AbstractConnectXWidgetsFactory final : public cx::ui::IAbstractConnectXWidgetsFactory
{

public:

   /******************************************************************************************//**
    * @brief Constructor.
    *
    * @param p_gtkApplication
    *      The `Gtk::Application` instance representing the current application the factory
    *      is used for. Without it, widgets cannot be rendered on the screen.
    *
    * @pre
    *      The `Gtk::Application` instance given as an argument is valid.
    *
    *********************************************************************************************/
    explicit AbstractConnectXWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication);

   /******************************************************************************************//**
    * @brief Sets a standard widgets factory.
    *
    * Whenever possible, this factory should be used when creating Connect X specific widgets
    * to avoid multiple maintance point for equivalent widget types.
    *
    * @post
    *      The stored widget factories are valid.
    *
    *********************************************************************************************/
    void RegisterStandardWidgetsFactory(cx::cmn::ui::IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory);

    // cx::ui::IAbstractConnectXWidgetsFactory:
    [[nodiscard]] std::unique_ptr<IStatusBar> CreateStatusBar(
        IStatusBarPresenter& p_presenter,
        cx::model::ModelSubject& p_model) const override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IWindow> CreateMainWindow(cx::model::ModelSubject& p_model,
        cx::ui::IMainWindowController& p_controller,
        cx::ui::IMainWindowPresenter& p_presenter) const override;
    [[nodiscard]] virtual std::unique_ptr<cx::cmn::ui::IWindow> CreateAboutWindow(
        std::unique_ptr<cx::ui::IAboutWindowPresenter> p_presenter) const override;
    [[nodiscard]] virtual std::unique_ptr<cx::cmn::ui::IWindow> CreateGameResolutionDialog(
        std::unique_ptr<cx::ui::IGameResolutionDialogPresenter> p_presenter,
        std::unique_ptr<cx::ui::IGameResolutionDialogController> p_controller) const override;
    [[nodiscard]] virtual std::unique_ptr<cx::ui::IView> CreateNewGameView(
        cx::ui::INewGameViewPresenter& p_presenter,
        cx::ui::INewGameViewController& p_controller,
        cx::cmn::ui::IWindow& p_parentWindow,
        cx::cmn::ui::ILayout& p_mainLayout,
        const cx::cmn::ui::ILayout::Column& p_viewLeft,
        const cx::cmn::ui::ILayout::Row& p_viewTop) const override;
    [[nodiscard]] virtual std::unique_ptr<cx::ui::IView> CreateGameView(
        cx::ui::IGameViewPresenter& p_presenter,
        cx::ui::IGameViewController& p_controller,
        cx::cmn::ui::IWindow& p_parentWindow,
        cx::cmn::ui::ILayout& p_mainLayout,
        const cx::cmn::ui::ILayout::Column& p_viewLeft,
        const cx::cmn::ui::ILayout::Row& p_viewTop) const override;
    [[nodiscard]] std::unique_ptr<cx::ui::INewPlayersList> CreateNewPlayersList(
        const cx::ui::INewGameViewPresenter& p_presenter) const override;
    [[nodiscard]] std::unique_ptr<cx::ui::IColorPicker> CreateColorPicker(
        const std::vector<cx::model::ChipColor>& p_colors) const override;
    [[nodiscard]] std::unique_ptr<cx::ui::IAnimatedBoard> CreateGameBoard(
        const cx::ui::IGameViewPresenter& p_presenter,
        const cx::ui::AnimationSpeed& p_speed) const override;
    [[nodiscard]] std::unique_ptr<cx::ui::IChip> CreateChip(
        const cx::model::ChipColor& p_fillColor,
        const cx::model::ChipColor& p_backgroundColor,
        int p_diameter) const override;

private:

    void InvariantsCheck() const;

private:

    Glib::RefPtr<Gtk::Application> m_gtkApplication;

    std::unique_ptr<cx::ui::WidgetsFactories> m_widgetsFactories;

};

} // namespace cx::ui::gtkmm3

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

std::unique_ptr<cx::ui::IStatusBar> cx::ui::gtkmm3::AbstractConnectXWidgetsFactory::CreateStatusBar(
    IStatusBarPresenter& p_presenter,
    cx::model::ModelSubject& p_model) const
{
    IF_PRECONDITION_NOT_MET_DO(m_widgetsFactories, return nullptr;);

    auto statusBar = cx::cmn::ui::gtkmm3::CreateWidget<StatusBar>(
        p_presenter);
    IF_CONDITION_NOT_MET_DO(statusBar, return nullptr;);

    p_model.Attach(&p_presenter);
    p_presenter.Attach(statusBar.get());

    POSTCONDITION(statusBar);
    InvariantsCheck();

    return statusBar;
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

    p_model.Attach(&p_presenter);
    p_presenter.Attach(mainWindow.get());

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
    const cx::cmn::ui::ILayout::Column& p_viewLeft,
    const cx::cmn::ui::ILayout::Row& p_viewTop) const
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
    const cx::cmn::ui::ILayout::Column& p_viewLeft,
    const cx::cmn::ui::ILayout::Row& p_viewTop) const
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

[[nodiscard]] std::unique_ptr<cx::ui::IAbstractConnectXWidgetsFactory> cx::ui::gtkmm3::CreateFactory(
    Glib::RefPtr<Gtk::Application> p_gtkApplication,
    cx::cmn::ui::IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory)
{
    IF_PRECONDITION_NOT_MET_DO(bool(p_gtkApplication), return nullptr;);

    auto factory = std::make_unique<AbstractConnectXWidgetsFactory>(p_gtkApplication);
    IF_PRECONDITION_NOT_MET_DO(factory, return nullptr;);

    factory->RegisterStandardWidgetsFactory(p_stdAbstractWidgetsFactory);

    POSTCONDITION(factory != nullptr);

    return factory;
}
