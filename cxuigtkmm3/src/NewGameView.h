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
 * @file NewGameView.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
#define GTKMM3NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF

#include <optional>

#include <cxcmn/Status.h>
#include <cxcmnui/ILayout.h>
#include <cxui/IView.h>

namespace cx::model
{
    class NewGameInformation;
}

namespace cx::ui
{
    class WidgetsFactories;
    class INewGameViewController;
    class INewGameViewPresenter;
    class INewPlayersList;
}

namespace cx::cmn::ui
{
    class IButton;
    class ILabel;
    class ILayout;
    class ISpinBox;
    class IWindow;
}

namespace cx::ui::gtkmm3
{

/*********************************************************************************************//**
 * @brief Gtkmm 3 implementation of the view for creating new games.
 *
 ************************************************************************************************/
class NewGameView : public cx::ui::IView
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_widgetsFactories
     *      Factories to instantiate widgets.
     * @param p_presenter
     *      A main window presenter (new game view).
     * @param p_controller
     *      A main window controller (new game view).
     * @param p_parentWindow
     *      The window containing the view.
     * @param p_mainLayout
     *      The main window's top level layout.
     * @param p_viewLeft
     *      The left position of the new game view within the main window's top level layout.
     * @param p_viewTop
     *      The top position of the new game view within the main window's top level layout.
     *
     ********************************************************************************************/
    NewGameView(
       cx::ui::WidgetsFactories& p_widgetsFactories,
       cx::ui::INewGameViewPresenter& p_presenter,
       cx::ui::INewGameViewController& p_controller,
       cx::cmn::ui::IWindow& p_parentWindow,
       cx::cmn::ui::ILayout& p_mainLayout,
       const cx::cmn::ui::ILayout::Column& p_viewLeft,
       const cx::cmn::ui::ILayout::Row& p_viewTop);

    // cx::ui::IView:
    void Activate() override;
    void DeActivate() override;
    void Update(cx::model::ModelNotificationContext p_context) override;

    // IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(cx::cmn::ui::EnabledState p_enabled) override;
    void SetMargins(const cx::cmn::ui::Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    void OnStart();
    void OnAddPlayer();
    void OnRemovePlayer();
    void OnNewGameParameterUpdated();

    [[nodiscard]] cx::cmn::Status ExtractGameInformation(cx::model::NewGameInformation& p_gameInformation) const;

private:

    cx::ui::WidgetsFactories& m_widgetsFactories;

    cx::ui::INewGameViewPresenter& m_presenter;
    cx::ui::INewGameViewController& m_controller;

    cx::cmn::ui::IWindow& m_parentWindow;

    cx::cmn::ui::ILayout& m_mainLayout;

    const cx::cmn::ui::ILayout::Column m_viewLeft;
    const cx::cmn::ui::ILayout::Row m_viewTop;

    std::unique_ptr<cx::cmn::ui::ILayout> m_viewLayout;

    // Controls:
    std::unique_ptr<cx::cmn::ui::ILabel> m_title;

    std::unique_ptr<cx::cmn::ui::ILabel> m_gameSectionTitle;
    std::unique_ptr<cx::cmn::ui::ILabel> m_inARowLabel;
    std::unique_ptr<cx::cmn::ui::ISpinBox> m_inARowSpinBox;

    std::unique_ptr<cx::cmn::ui::ILabel> m_gridSectionTitle;
    std::unique_ptr<cx::cmn::ui::ILabel> m_gridWidthLabel;
    std::unique_ptr<cx::cmn::ui::ISpinBox> m_boardWidthSpinBox;
    std::unique_ptr<cx::cmn::ui::ILabel> m_gridHeightLabel;
    std::unique_ptr<cx::cmn::ui::ISpinBox> m_boardHeightSpinBox;

    std::unique_ptr<cx::cmn::ui::ILabel> m_playersSectionTitle;
    std::unique_ptr<cx::ui::INewPlayersList> m_playersList;

    std::unique_ptr<cx::cmn::ui::IButton> m_removePlayerButton;
    std::unique_ptr<cx::cmn::ui::IButton> m_addPlayerButton;
    std::unique_ptr<cx::cmn::ui::IButton> m_startButton;

};

} // namespace cx::ui::gtkmm3

#endif // GTKMM3NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
