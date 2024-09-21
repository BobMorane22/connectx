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
 * @file IAbstractConnectXWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IABSTRACTCONNECTXWIDGETSFACTORY_H_27E986AD_66DF_4324_96AB_AC531266A928
#define IABSTRACTCONNECTXWIDGETSFACTORY_H_27E986AD_66DF_4324_96AB_AC531266A928

#include <memory>

#include <cxmodel/ModelNotificationContext.h>
#include <cxcmnui/ILayout.h>
#include <cxui/IAnimatedBoardModel.h>

namespace cx::cmn::ui
{
    class ILayout;
    class IWindow;
}

namespace cx::ui
{
    class IAboutWindowPresenter;
    class IGameResolutionDialogPresenter;
    class IGameResolutionDialogController;
    class IGameViewController;
    class IGameViewPresenter;
    class IMainWindowController;
    class IMainWindowPresenter;
    class INewGameViewController;
    class INewGameViewPresenter;

    class IAnimatedBoard;
    class IChip;
    class IColorPicker;
    class INewPlayersList;
    class IView;
}

namespace cx::ui
{

/**********************************************************************************************//**
 * @brief Connect X specific widgets abstract factory.
 *
 * Create Connect X specific widgets (i.e. Game board, new players list, windows, etc.) without
 * having to deal with the underlying widgets toolkit.
 *
 *************************************************************************************************/
class IAbstractConnectXWidgetsFactory
{

public:

// ================================================================================================
///@{ @name Windows.
// ================================================================================================

    /******************************************************************************************//**
     * @brief Creates the Connect X main window.
     *
     * The Connect X main window is where everything happens. It is composed of a menu on top,
     * a view on the middle and a status bar at the bottom.
     *
     * Once Connect X is launched, everything happens on the main window and only the view is
     * updated to reflect the application's mode.
     *
     * @warning
     *      There should only be one Connect X main window instance by application.
     *
     * @param p_model
     *      A Connect X compatible model.
     * @param p_controller
     *      A compatible Connect X main window controller.
     * @param p_presenter
     *      A compatible Connect X main window presenter.
     *
     * @post
     *      The returned main window instance is valid.
     *
     * @return
     *      A Connect X main window instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cx::cmn::ui::IWindow> CreateMainWindow(
        cx::model::ModelSubject& p_model,
        IMainWindowController& p_controller,
        IMainWindowPresenter& p_presenter) const = 0;

    /******************************************************************************************//**
     * @brief Creates the Connect X about window.
     *
     * @param p_presenter
     *      An about window presenter.
     *
     * @pre
     *      The about window presenter is valid.
     *
     * @post
     *      The returned about window instance is valid.
     *
     * @return
     *      An about window instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cx::cmn::ui::IWindow> CreateAboutWindow(
        std::unique_ptr<IAboutWindowPresenter> p_presenter) const = 0;

    /******************************************************************************************//**
     * @brief Creates a Connect X game resolution dialog.
     *
     * The resolution dialog's appearance and behavior can be customized through the presenter
     * and the controller.
     *
     * @param p_presenter
     *      A game resolution presenter.
     * @param p_controller
     *      A game resolution controller.
     *
     * @pre
     *      The specified game resolution dialog presenter is valid.
     * @pre
     *      The specified game resolution dialog controller is valid.
     *
     * @post
     *      The returned game resolution dialog instance is valid.
     *
     * @return
     *      A game resolution dialog instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cx::cmn::ui::IWindow> CreateGameResolutionDialog(
        std::unique_ptr<IGameResolutionDialogPresenter> p_presenter,
        std::unique_ptr<IGameResolutionDialogController> p_controller) const = 0;

///@}

// ================================================================================================
///@{ @name Views.
// ================================================================================================

    /*****************************************************************************************//**
     * @brief Creates a view for configuring new games.
     *
     * @param p_presenter
     *      A new game view presenter.
     * @param p_controller
     *      A new game view controller.
     * @param p_parentWindow
     *      The window containing the view.
     * @param p_mainLayout
     *      The main window's top level layout.
     * @param p_viewLeft
     *      The left position of the new game view within the main window's top level layout.
     * @param p_viewTop
     *      The top position of the new game view within the main window's top level layout.
     *
     * @post
     *      The returned new game view instance is valid.
     *
     * @return
     *      A new game view instance.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IView> CreateNewGameView(
        INewGameViewPresenter& p_presenter,
        INewGameViewController& p_controller,
        cx::cmn::ui::IWindow& p_parentWindow,
        cx::cmn::ui::ILayout& p_mainLayout,
        const cx::cmn::ui::ILayout::Column& p_viewLeft,
        const cx::cmn::ui::ILayout::Row& p_viewTop) const = 0;

    /*****************************************************************************************//**
     * @brief Creates a view for playing a Connect X game.
     *
     * @param p_presenter
     *      A game view presenter.
     * @param p_controller
     *      A game view controller.
     * @param p_parentWindow
     *      The window containing the view.
     * @param p_mainLayout
     *      The main window's top level layout.
     * @param p_viewLeft
     *      The left position of the view in the layout within the main window's top level layout.
     * @param p_viewTop
     *      The top position of the view in the layout within the main window's top level layout..
     *
     * @post
     *      The returned game view instance is valid.
     *
     * @return
     *      A game view instance.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IView> CreateGameView(
        IGameViewPresenter& p_presenter,
        IGameViewController& p_controller,
        cx::cmn::ui::IWindow& p_parentWindow,
        cx::cmn::ui::ILayout& p_mainLayout,
        const cx::cmn::ui::ILayout::Column& p_viewLeft,
        const cx::cmn::ui::ILayout::Row& p_viewTop) const = 0;

///@}

// ================================================================================================
///@{ @name New players list.
// ================================================================================================

    /******************************************************************************************//**
     * @brief Creates a Connect X new players list.
     *
     * The new players list is the widgets from which the setup of players which will participate
     * in the next Connect X game is done. It can be customized through a presenter.
     *
     * @param p_presenter
     *      A new game view presenter.
     *
     * @post
     *      The returned new players list instance is valid.
     *
     * @return
     *      A new players list instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<INewPlayersList> CreateNewPlayersList(
        const INewGameViewPresenter& p_presenter) const = 0;

    /*****************************************************************************************//**
     * @brief Creates a color picker.
     *
     * @param p_colors
     *      The colors one can pick from.
     *
     * @pre
     *      The list of colors is not empty.
     *
     * @post
     *      The returned color picker instance is valid.
     *
     * @return
     *      A color picker instance.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IColorPicker> CreateColorPicker(
        const std::vector<cx::model::ChipColor>& p_colors) const = 0;

///@}

// ================================================================================================
///@{ @name Game board
// ================================================================================================

    /*****************************************************************************************//**
     * @brief Creates a game bord for playing a Connect X game.
     *
     * @param p_presenter
     *      A game view presenter.
     * @param p_speed
     *      The number of chip widths travelled by second.
     *
     * @post
     *      The returned game board instance is valid.
     *
     * @return
     *      A game board instance.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IAnimatedBoard> CreateGameBoard(
        const IGameViewPresenter& p_presenter,
        const AnimationSpeed& p_speed) const = 0;

    /******************************************************************************************//**
     * @brief Creates a Connect X chip which can be drawn on the screen.
     *
     * @param p_fillColor
     *     The color filling the center of the chip (inside its border).
     * @param p_backgroundColor
     *     The color around the chip (outside its border).
     * @param p_radius
     *     The chip's diameter (in pixels).
     *
     * @post
     *     The returned chip is valid.
     *
     * @return
     *     A Connect X chip instance.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<IChip> CreateChip(
        const cx::model::ChipColor& p_fillColor,
        const cx::model::ChipColor& p_backgroundColor,
        int p_diameter) const = 0;

///@}

};

} // namespace cx::ui

#endif // IABSTRACTCONNECTXWIDGETSFACTORY_H_27E986AD_66DF_4324_96AB_AC531266A928
