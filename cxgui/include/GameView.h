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

#include "Board.h"
#include "Chip.h"
#include "GameKeyHandlerStrategyFactory.h"
#include "IGameViewPresenter.h"
#include "IView.h"

namespace cxgui
{

/*********************************************************************************************//**
 * @brief View for playing the game.
 *
 ************************************************************************************************/
class GameView : public IView
{

public:

    GameView(IGameViewPresenter& p_presenter,
             Gtk::Grid& p_mainLayout,
             int p_viewLeft,
             int p_viewTop);

    void Activate() override;

private:

    void SetLayout();
    void PopulateWidgets();
    void ConfigureWidgets();

    bool OnKeyPressed(GdkEventKey* p_event);

    IGameViewPresenter& m_presenter;

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

    std::unique_ptr<cxgui::Board> m_board;

    // Keys:
    cxgui::GameKeyHandlerStrategyFactory m_keyEventStrategyFactory;
};

} // namespace cxgui

#endif // GAMEVIEW_H_AA8C282C_9CC4_45F4_BE91_C8840160BA1B
