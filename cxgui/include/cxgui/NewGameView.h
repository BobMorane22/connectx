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

#ifndef NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
#define NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF

#include <optional>

#include <cxmodel/Status.h>
#include <cxgui/Gtkmm3Window.h>
#include <cxgui/IView.h>

namespace cxmodel
{
    class NewGameInformation;
}

namespace cxgui
{
    class IButton;
    class ILabel;
    class ILayout;
    class INewGameViewController;
    class INewGameViewPresenter;
    class INewPlayersList;
    class ISpinBox;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief View for creating new games.
 *
 ************************************************************************************************/
class NewGameView : public cxgui::IView
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
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
    NewGameView(INewGameViewPresenter& p_presenter,
                INewGameViewController& p_controller,
                IWindow& p_parentWindow,
                cxgui::ILayout& p_mainLayout,
                const cxmodel::Column& p_viewLeft,
                const cxmodel::Row& p_viewTop);

    // IView:
    void Activate() override;
    void DeActivate() override;
    void Update(cxmodel::ModelNotificationContext p_context) override;

private:

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    void OnStart();
    void OnAddPlayer();
    void OnRemovePlayer();
    void OnNewGameParameterUpdated();

    [[nodiscard]] cxmodel::Status ExtractGameInformation(cxmodel::NewGameInformation& p_gameInformation) const;

    INewGameViewPresenter& m_presenter;
    INewGameViewController& m_controller;

    IWindow& m_parentWindow;

    cxgui::ILayout& m_mainLayout;

    const cxmodel::Column m_viewLeft;
    const cxmodel::Row m_viewTop;

    std::unique_ptr<ILayout> m_viewLayout;

    // Controls:
    std::unique_ptr<ILabel> m_title;

    std::unique_ptr<ILabel> m_gameSectionTitle;
    std::unique_ptr<ILabel> m_inARowLabel;
    std::unique_ptr<ISpinBox> m_inARowSpinBox;

    std::unique_ptr<ILabel> m_gridSectionTitle;
    std::unique_ptr<ILabel> m_gridWidthLabel;
    std::unique_ptr<ISpinBox> m_boardWidthSpinBox;
    std::unique_ptr<ILabel> m_gridHeightLabel;
    std::unique_ptr<ISpinBox> m_boardHeightSpinBox;

    std::unique_ptr<ILabel> m_playersSectionTitle;
    std::unique_ptr<INewPlayersList> m_playersList;

    std::unique_ptr<IButton> m_removePlayerButton;
    std::unique_ptr<IButton> m_addPlayerButton;
    std::unique_ptr<IButton> m_startButton;

};

} // namespace cxgui

#endif // NEWGAMEVIEW_H_C5E65447_64C6_4DFE_B0F7_E6E9DB14BEAF
