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


#include <cxui/IAnimatedBoard.h> // Can't forward declare because of gui specific subject/observer.  #include <cxui/IView.h>
#include <cxcmnui/ISignal.h>
#include <cxui/IView.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>

namespace cx::cmn::ui
{
    enum class EventPropagation;
    class ILabel;
    class ILayout;
    class IWindow;
}

namespace cx::ui
{
    class IChip;
    class IGameViewController;
    class IGameViewPresenter;
    class WidgetsFactories;
}

namespace cx::cmn::ui
{

/*********************************************************************************************//**
 * @brief Gtkmm3 implementation of the view for playing the game.
 *
 ************************************************************************************************/
class Gtkmm3GameView : public cx::ui::IView,
                       private cx::ui::IBoardAnimationObserver,
                       private cx::ui::IUserActionObserver,
                       private cx::ui::BoardAnimationSubject
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_widgetsFactories
     *      Factories to instantiate widgets.
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
    Gtkmm3GameView(
        cx::ui::WidgetsFactories& p_widgetsFactories,
        cx::ui::IGameViewPresenter& p_presenter,
        cx::ui::IGameViewController& p_controller,
        cx::cmn::ui::IWindow& p_parentWindow,
        cx::cmn::ui::ILayout& p_mainLayout,
        const cx::model::Column& p_viewLeft,
        const cx::model::Row& p_viewTop);

    /*****************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    ~Gtkmm3GameView() override;
    
    // cx::ui::IView:
    void Activate() override;
    void DeActivate() override;
    void Update(cx::model::ModelNotificationContext p_context) override;

    // cx::cmn::ui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;
    void SetTooltip(const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<ISignal<EventPropagation, KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    // cx::ui::IBoardAnimationObserver:
    void Update(cx::ui::BoardAnimationNotificationContext p_context, cx::ui::BoardAnimationSubject* p_subject) override;

    // cx::ui::IUserActionObserver:
    void Update(cx::ui::UserAction p_context, cx::ui::UserActionSubject* p_subject) override;

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    EventPropagation OnKeyPressed(KeyboardKeyPressedEvent p_event);
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

    cx::ui::WidgetsFactories& m_widgetsFactories;

    cx::ui::IGameViewPresenter& m_presenter;
    cx::ui::IGameViewController& m_controller;

    IWindow& m_parentWindow;                  // The window containing the view in its main layout.

    cx::cmn::ui::ILayout& m_mainLayout;

    const cx::model::Column m_viewLeft;
    const cx::model::Row m_viewTop;

    std::unique_ptr<ILayout> m_viewLayout;

    bool m_areKeyboardEventsAccepted = false;  // Indicates if the window accepts keyboard events or not.

    // Controls:
    std::unique_ptr<ILabel> m_title;

    std::unique_ptr<ILayout> m_playersInfoLayout;

    std::unique_ptr<ILabel> m_activePlayerLabel;
    std::unique_ptr<ILabel> m_activePlayerName;
    std::unique_ptr<cx::ui::IChip> m_activePlayerChip;

    std::unique_ptr<ILabel> m_nextPlayerLabel;
    std::unique_ptr<ILabel> m_nextPlayerName;
    std::unique_ptr<cx::ui::IChip> m_nextPlayerChip;

    std::unique_ptr<cx::ui::IAnimatedBoard> m_board;

    // Connections:
    std::unique_ptr<IConnection> m_keysPressedConnection;
};

} // namespace cx::cmn::ui

#endif // GTKMM3GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B
