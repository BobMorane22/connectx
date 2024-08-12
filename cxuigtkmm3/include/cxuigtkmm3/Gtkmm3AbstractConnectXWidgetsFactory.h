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
 * @file Gtkmm3AbstractConnectXWidgetsFactory.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05
#define GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05

#include <gtkmm/application.h>

#include <cxui/IAbstractConnectXWidgetsFactory.h>

namespace cx::cmn::ui
{
    class IAbstractWidgetsFactory;
}

namespace cx::ui
{
    class IAboutWindowPresenter;
    class IGameResolutionDialogPresenter;
    class IGameResolutionDialogController;
    class WidgetsFactories;
}

namespace cx::cmn::ui
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
class Gtkmm3AbstractConnectXWidgetsFactory final : public cx::ui::IAbstractConnectXWidgetsFactory
{

public:

   /******************************************************************************************//**
    * @brief Constructor.
    *
    * @param p_stdWidgetsFactory
    *      A standard widgets factory. Useful for reusing standard widgets in Connect X specific
    *      widgets, which makes porting easier.
    *
    * @param p_gtkApplication
    *      The `Gtk::Application` instance representing the current application the factory
    *      is used for. Without it, widgets cannot be rendered on the screen.
    *
    * @pre
    *      The `Gtk::Application` instance given as an argument is valid.
    *
    *********************************************************************************************/
    explicit Gtkmm3AbstractConnectXWidgetsFactory(Glib::RefPtr<Gtk::Application> p_gtkApplication);

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
    void RegisterStandardWidgetsFactory(IAbstractWidgetsFactory& p_stdAbstractWidgetsFactory);

    // cx::ui::IAbstractConnectXWidgetsFactory:
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
        const cx::model::Column& p_viewLeft,
        const cx::model::Row& p_viewTop) const override;
    [[nodiscard]] virtual std::unique_ptr<cx::ui::IView> CreateGameView(
    cx::ui::IGameViewPresenter& p_presenter,
    cx::ui::IGameViewController& p_controller,
    cx::cmn::ui::IWindow& p_parentWindow,
    cx::cmn::ui::ILayout& p_mainLayout,
    const cx::model::Column& p_viewLeft,
    const cx::model::Row& p_viewTop) const override;
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

} // namespace cx::cmn::ui

#endif // GTKMM3ABSTRACTCONNECTXWIDGETSFACTORY_H_B3944DEE_5157_44D5_91D7_B238464FDD05
