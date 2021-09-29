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
 * @file GameView.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B
#define GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B

#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include "AnimatedBoard.h"
#include "Chip.h"
#include "GameKeyHandlerStrategyFactory.h"
#include "IBoardAnimator.h"
#include "IGameViewController.h"
#include "IGameViewPresenter.h"
#include "IView.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief View for playing the game.
 *
 ************************************************************************************************/
class GameView : public IView,
                 public cxgui::IBoardAnimationObserver,
                 public cxgui::BoardAnimationSubject
{

public:

    GameView(IGameViewPresenter& p_presenter,
             IGameViewController& p_controller,
             Gtk::Grid& p_mainLayout,
             int p_viewLeft,
             int p_viewTop);

    void Update(cxgui::BoardAnimationNotificationContext p_context, cxgui::BoardAnimationSubject* p_subject) override;

    // IView:
    void Activate() override;
    void DeActivate() override;
    void Update(cxmodel::ModelNotificationContext p_context) override;

private:

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    bool OnKeyPressed(GdkEventKey* p_event);

    void UpdateChipDropped();
    void UpdateChipMovedLeft();
    void UpdateChipMovedRight();
    void UpdateGameResolved();
    void UpdateGameReinitialized();

    IGameViewPresenter& m_presenter;
    IGameViewController& m_controller;

    Gtk::Grid& m_mainLayout;

    const int m_viewLeft;
    const int m_viewTop;

    Gtk::Grid m_viewLayout;

    // Parent window:
    Gtk::Window* m_parent;

    // Controls:
    Gtk::Label m_title;

    Gtk::Grid m_playersInfoLayout;

    Gtk::Label m_activePlayerLabel;
    Gtk::Label m_activePlayerName;
    std::unique_ptr<cxgui::Chip> m_activePlayerChip;

    Gtk::Label m_nextPlayerLabel;
    Gtk::Label m_nextPlayerName;
    std::unique_ptr<cxgui::Chip> m_nextPlayerChip;

    std::unique_ptr<cxgui::AnimatedBoard> m_board;

    // Keys:
    cxgui::GameKeyHandlerStrategyFactory m_keyEventStrategyFactory;

    // Signals:
    sigc::connection m_keysPressedConnection;
};

} // namespace cxgui

#endif // GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B
