/**************************************************************************************************
 *  This file is part of Connect X.
 *
 *  Connect X is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.  *
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
 * @file Gtkmm3GameView.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B
#define GTKMM3GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B

#include <cxgui/IAnimatedBoard.h>
#include <cxgui/GameViewKeyHandlerStrategyFactory.h>
#include <cxgui/IView.h>

namespace cxgui
{
    class IChip;
    class IGameViewController;
    class IGameViewPresenter;
    class ILabel;
    class ILayout;
    class IWindow;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Gtkmm3 implementation of the view for playing the game.
 *
 ************************************************************************************************/
class Gtkmm3GameView : public IView,
                       private cxgui::IBoardAnimationObserver,
                       private cxgui::IUserActionObserver,
                       private cxgui::BoardAnimationSubject
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter
     *      The game view presenter.
     * @param p_controller
     *      The game view controller.
     * @param p_parentWindow
     *      The window containing the view in its main layout.
     * @param p_mainLayout
     *      The main window's top level layout (in which to insert the Game view).
     * @param p_viewLeft
     *      The left position of the view in the layout.
     * @param p_viewTop
     *      The top position of the view in the layout.
     *
     ********************************************************************************************/
    Gtkmm3GameView(IGameViewPresenter& p_presenter,
                   IGameViewController& p_controller,
                   IWindow& p_parentWindow,
                   cxgui::ILayout& p_mainLayout,
                   const cxmodel::Column& p_viewLeft,
                   const cxmodel::Row& p_viewTop);

    /*****************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    ~Gtkmm3GameView() override;
    
    // cxgui::IView:
    void Activate() override;
    void DeActivate() override;
    void Update(cxmodel::ModelNotificationContext p_context) override;

    // IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents)override;

private:

    // cxgui::IBoardAnimationObserver:
    void Update(cxgui::BoardAnimationNotificationContext p_context, cxgui::BoardAnimationSubject* p_subject) override;

    // cxgui::IUserActionObserver:
    void Update(cxgui::UserAction p_context, cxgui::UserActionSubject* p_subject) override;

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    bool OnKeyPressed(GdkEventKey* p_event);
    void EnableKeyHandlers();
    void DisableKeyHandlers();

    void UpdateChipDropped();
    void UpdateChipDroppedFailed();
    void UpdateUndoChipDropped();
    void UpdateRedoChipDropped();
    void UpdateChipMovedLeftOneColumn();
    void UpdateChipMovedRightOneColumn();
    void UpdateChipMovedRightToTarget();
    void UpdateGameResolved();
    void UpdateGameReinitialized();

    void SyncPlayers();

private:

    IGameViewPresenter& m_presenter;
    IGameViewController& m_controller;

    // The window containing the view in its main layout.
    IWindow& m_parentWindow;

    cxgui::ILayout& m_mainLayout;

    const cxmodel::Column m_viewLeft;
    const cxmodel::Row m_viewTop;

    std::unique_ptr<ILayout> m_viewLayout;

    // Controls:
    std::unique_ptr<ILabel> m_title;

    std::unique_ptr<ILayout> m_playersInfoLayout;

    std::unique_ptr<ILabel> m_activePlayerLabel;
    std::unique_ptr<ILabel> m_activePlayerName;
    std::unique_ptr<cxgui::IChip> m_activePlayerChip;

    std::unique_ptr<ILabel> m_nextPlayerLabel;
    std::unique_ptr<ILabel> m_nextPlayerName;
    std::unique_ptr<cxgui::IChip> m_nextPlayerChip;

    std::unique_ptr<cxgui::IAnimatedBoard> m_board;

    // Connexions.
    sigc::connection m_keysPressedConnection;
};

} // namespace cxgui

#endif // GTKMM3GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B
