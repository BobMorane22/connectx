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
 * @file GameView.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <iostream>

#include <gtkmm/window.h>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/IChip.h>
#include <cxmodel/include/ModelNotificationContext.h>

#include "BoardAnimation.h"
#include "common.h"
#include "DiscChip.h"
#include "GameView.h"

cxgui::GameView::GameView(IGameViewPresenter& p_presenter,
                          IGameViewController& p_controller,
                          Gtk::Grid& p_mainLayout,
                          int p_viewLeft,
                          int p_viewTop)
: m_presenter{p_presenter}
, m_controller{p_controller}
, m_mainLayout{p_mainLayout}
, m_viewLeft{p_viewLeft}
, m_viewTop{p_viewTop}
, m_activePlayerChip{std::make_unique<cxgui::DiscChip>(cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), cxgui::DEFAULT_CHIP_SIZE / 4)}
, m_nextPlayerChip{std::make_unique<cxgui::DiscChip>(cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), cxgui::DEFAULT_CHIP_SIZE / 4)}
, m_board{std::make_unique<cxgui::Board>(m_presenter, m_controller)}
{
    PRECONDITION(m_activePlayerChip);
    PRECONDITION(m_nextPlayerChip);

    SetLayout();
    PopulateWidgets();
    ConfigureWidgets();

    // Get a reference to the parent window:
    m_parent = dynamic_cast<Gtk::Window*>(m_mainLayout.get_parent());

    POSTCONDITION(m_parent);
}

void cxgui::GameView::Activate()
{
    // Override default signal handler to catch keyboard events:
    if(ASSERT(m_parent))
    {
        m_parent->add_events(Gdk::KEY_PRESS_MASK);
        m_keysPressedConnection = m_parent->signal_key_press_event().connect([this](GdkEventKey* p_event){return OnKeyPressed(p_event);}, false);
    }

    auto* currentViewLayout = m_mainLayout.get_child_at(m_viewLeft, m_viewTop);

    if(!currentViewLayout)
    {
        ASSERT_ERROR_MSG("Current view should be valid.");
        return;
    }

    // Remove previous view layout:
    m_mainLayout.remove(*currentViewLayout);

    // Add new view layout:
    m_mainLayout.attach(m_viewLayout, m_viewLeft, m_viewTop, 2, 1);
}

void cxgui::GameView::DeActivate()
{
    if(ASSERT(m_parent))
    {
        // Unset key press events:
        m_parent->add_events(m_parent->get_events() & ~Gdk::KEY_PRESS_MASK);

        // Disconnect signal handler:
        m_keysPressedConnection.disconnect();
    }
}

void cxgui::GameView::Update(cxmodel::ModelNotificationContext p_context)
{
    switch(p_context)
    {
        case cxmodel::ModelNotificationContext::CHIP_DROPPED:
        {
            UpdateChipDropped();
            break;
        }
        case cxmodel::ModelNotificationContext::CHIP_MOVED_LEFT:
        {
            UpdateChipMovedLeft();
            break;
        }
        case cxmodel::ModelNotificationContext::CHIP_MOVED_RIGHT:
        {
            UpdateChipMovedRight();
            break;
        }
        case cxmodel::ModelNotificationContext::GAME_WON:
        case cxmodel::ModelNotificationContext::GAME_TIED:
        {
            UpdateGameResolved();
            break;
        }
        case cxmodel::ModelNotificationContext::GAME_REINITIALIZED:
        {
            UpdateGameReinitialized();
            break;
        }
        case cxmodel::ModelNotificationContext::UNDO_CHIP_DROPPED:
        {
            UpdateChipDropped();
            break;
        }
        default:
            break;
    }
}

void cxgui::GameView::SetLayout()
{
    constexpr int TOTAL_WIDTH = 2;

    // Main view layout:
    m_viewLayout.attach(m_title, 0, 0, TOTAL_WIDTH, 1);
    m_viewLayout.attach(m_playersInfoLayout, 0, 1, TOTAL_WIDTH, 1);

    if(ASSERT(m_board))
    {
        m_viewLayout.attach(*m_board, 0, 4, TOTAL_WIDTH, 1);
    }

    // Players info layout:
    m_playersInfoLayout.attach(m_activePlayerLabel, 0, 0, 1, 1);
    m_playersInfoLayout.attach(m_activePlayerName, 1, 0, 1, 1);
    if(ASSERT(m_activePlayerChip))
    {
        m_playersInfoLayout.attach(*m_activePlayerChip, 2, 0, 1, 1);
    }

    m_playersInfoLayout.attach(m_nextPlayerLabel, 0, 1, 1, 1);
    m_playersInfoLayout.attach(m_nextPlayerName, 1, 1, 1, 1);
    if(ASSERT(m_nextPlayerChip))
    {
        m_playersInfoLayout.attach(*m_nextPlayerChip, 2, 1, 1, 1);
    }
}

void cxgui::GameView::PopulateWidgets()
{
    m_title.set_text(m_presenter.GetGameViewTitle());

    m_activePlayerLabel.set_text(m_presenter.GetGameViewActivePlayerLabelText());
    m_activePlayerName.set_text(m_presenter.GetGameViewActivePlayerName());
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());

    m_nextPlayerLabel.set_text(m_presenter.GetGameViewNextPlayerLabelText());
    m_nextPlayerName.set_text(m_presenter.GetGameViewNextPlayerName());
    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
}

void cxgui::GameView::ConfigureWidgets()
{
    // Window margin:
    m_mainLayout.set_margin_left(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_right(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_top(DIALOG_SIDE_MARGIN);
    m_mainLayout.set_margin_bottom(DIALOG_SIDE_MARGIN);

    // View title:
    m_title.set_use_markup(true);
    m_title.set_markup("<big><b>" + m_title.get_text() + "</b></big>");
    m_title.set_margin_bottom(TITLE_BOTTOM_MARGIN);

    // Players section:
    m_activePlayerLabel.set_halign(Gtk::Align::ALIGN_START);
    m_activePlayerLabel.set_hexpand(true);
    m_activePlayerLabel.set_markup("<b>" + m_activePlayerLabel.get_text() + "</b>");
    m_activePlayerName.set_halign(Gtk::Align::ALIGN_START);
    m_activePlayerName.set_hexpand(true);
    if(ASSERT(m_activePlayerChip))
    {
        m_activePlayerChip->set_hexpand(true);
        m_activePlayerChip->set_vexpand(false);
        m_activePlayerChip->set_halign(Gtk::Align::ALIGN_START);
    }

    m_nextPlayerLabel.set_halign(Gtk::Align::ALIGN_START);
    m_nextPlayerLabel.set_hexpand(true);
    m_nextPlayerLabel.set_use_markup(true);
    m_nextPlayerLabel.set_markup("<b>" + m_nextPlayerLabel.get_text() + "</b>");
    m_nextPlayerName.set_halign(Gtk::Align::ALIGN_START);
    m_nextPlayerName.set_hexpand(true);
    if(ASSERT(m_nextPlayerChip))
    {
        m_nextPlayerChip->set_hexpand(true);
        m_nextPlayerChip->set_vexpand(false);
        m_nextPlayerChip->set_halign(Gtk::Align::ALIGN_START);
    }

    m_playersInfoLayout.set_margin_bottom(SECTION_BOTTOM_MARGIN);
}

bool cxgui::GameView::OnKeyPressed(GdkEventKey* p_event)
{
    if(!p_event)
    {
        return true; // Do not propagate...
    }

    const auto strategy = m_keyEventStrategyFactory.Create(p_event);

    if(!strategy || !m_board)
    {
        return false;
    }

    return strategy->Handle(m_controller, *m_board);
}

void cxgui::GameView::UpdateChipDropped()
{
    // Active and next players should be updated as well:
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());
    m_activePlayerName.set_text(m_presenter.GetGameViewActivePlayerName());

    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
    m_nextPlayerName.set_text(m_presenter.GetGameViewNextPlayerName());

    if(ASSERT(m_board))
    {
        m_board->PerformChipAnimation(cxgui::BoardAnimation::DROP_CHIP);
    }
}

void cxgui::GameView::UpdateChipMovedLeft()
{
    if(ASSERT(m_board))
    {
        m_board->PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN);
    }
}

void cxgui::GameView::UpdateChipMovedRight()
{
    if(ASSERT(m_board))
    {
        m_board->PerformChipAnimation(cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN);
    }
}

void cxgui::GameView::UpdateGameResolved()
{
    m_board->PerformChipAnimation(cxgui::BoardAnimation::GAME_WON);
}

void cxgui::GameView::UpdateGameReinitialized()
{
    // Active and next players should be updated as well:
    m_activePlayerChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());
    m_activePlayerName.set_text(m_presenter.GetGameViewActivePlayerName());

    m_nextPlayerChip->ChangeColor(m_presenter.GetGameViewNextPlayerChipColor());
    m_nextPlayerName.set_text(m_presenter.GetGameViewNextPlayerName());

    m_board->PerformChipAnimation(cxgui::BoardAnimation::GAME_REINITIALIZED);
}
