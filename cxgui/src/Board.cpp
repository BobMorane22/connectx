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
 * @file GameBoard.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>

#include <gdkmm/display.h>

#include <cxinv/include/assertion.h>
#include <cxmodel/include/Disc.h>

#include "Board.h"
#include "BoardAnimation.h"
#include "DiscChip.h"
#include "IGameViewController.h"
#include "IGameViewPresenter.h"

constexpr bool FULLY_HANDLED = true;
constexpr bool PROPAGATE = false;

namespace
{

// Computes the best chip dimension so that the game view, when the board is present with all
// chips drawn, is entirely viewable on the user's screen.
int ComputeMinimumChipSize(const cxgui::Board& p_board, size_t p_nbRows, size_t p_nbColumns)
{
    // Get screen containing the widget:
    const Glib::RefPtr<const Gdk::Screen> screen = p_board.get_screen();
    IF_CONDITION_NOT_MET_DO(bool(screen), return -1;);

    // Get the screen dimensions:
    const int fullScreenHeight = screen->get_height();
    const int fullScreenWidth = screen->get_width();

    // Get minimum screen dimension:
    const int minFullScreenDimension = std::min(fullScreenHeight, fullScreenWidth);

    // First, we check if the chips can use their default size:
    int nbRows = static_cast<int>(p_nbRows);
    int nbColumns = static_cast<int>(p_nbColumns);

    if(nbRows * cxgui::DEFAULT_CHIP_SIZE < (2 * fullScreenHeight) / 3)
    {
        if(nbColumns * cxgui::DEFAULT_CHIP_SIZE < (2 * fullScreenWidth) / 3)
        {
            return cxgui::DEFAULT_CHIP_SIZE;
        }
    }

    // The the biggest board dimension:
    const int maxBoardDimension = std::max(nbRows, nbColumns);

    // From this, the max chip dimension (dimension at which together, chips from the board would fill the
    // entire screen in its smallest dimension) is computed:
    const int maxChipDimension = (minFullScreenDimension / maxBoardDimension);

    // We take two thirds from this value for the board (leaving the remaining to the rest of the
    // game view):
    return (maxChipDimension * 2) / 3;
}

} // namespace

cxgui::Board::Board(const IGameViewPresenter& p_presenter, IGameViewController& p_controller)
: m_presenter{p_presenter}
, m_controller{p_controller}
, m_currentDiscPosition{0u}
{
    set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    InitializeNextDiscArea(m_presenter.GetGameViewBoardWidth());
    InitializeBoard(m_presenter.GetGameViewBoardHeight(), m_presenter.GetGameViewBoardWidth());
    HighlightCurrentColumn();

    pack1(m_nextDiscAreaLayout, true, false);
    pack2(m_boardLayout, true, false);
}

void cxgui::Board::PerformChipAnimation(BoardAnimation p_animation)
{
    switch(p_animation)
    {
        case cxgui::BoardAnimation::GAME_REINITIALIZED:
        {
            MoveCurrentDiscAtFirstRow();
            ClearBoardArea();
            break;
        }
        case cxgui::BoardAnimation::GAME_WON:
        {
            ClearNextDiscArea();
            RefreshBoardArea();
            break;
        }
        case cxgui::BoardAnimation::MOVE_CHIP_LEFT_ONE_COLUMN:
        {
            Move(Side::Left);
            break;
        }
        case cxgui::BoardAnimation::MOVE_CHIP_RIGHT_ONE_COLUMN:
        {
            Move(Side::Right);
            break;
        }
        case cxgui::BoardAnimation::DROP_CHIP:
        {
            MoveCurrentDiscAtFirstRow();
            RefreshBoardArea();
            break;
        }
        case cxgui::BoardAnimation::UNDO_DROP_CHIP:
        {
            MoveCurrentDiscAtFirstRow();
            RefreshBoardArea();
            break;
        }
        default:
        {
            ASSERT_ERROR_MSG("Unknown board animation.");
            return;
        }
    }
}

size_t cxgui::Board::GetCurrentColumn() const
{
    return m_currentDiscPosition;
}

const cxgui::Chip* cxgui::Board::GetCurrentChip() const
{
    return GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);
}

void cxgui::Board::MoveLeft()
{
    Move(Side::Left);
}

void cxgui::Board::MoveRight()
{
    Move(Side::Right);
}

cxgui::Chip* cxgui::Board::GetChip(const Gtk::Grid& p_discArea, int p_left, int p_top)
{
    // Get the const version of this board. This will make sure the const version of this
    // method is called when using this reference (otherwise this method will be called
    // and we will enter infinite recursion):
    const Board& thisBoard = static_cast<const Board&>(*this);

    // Call the const version, but cast away constness:
    return const_cast<Chip*>(thisBoard.GetChip(p_discArea, p_left, p_top));
}

const cxgui::Chip* cxgui::Board::GetChip(const Gtk::Grid& p_discArea, int p_left, int p_top) const
{
    const Widget* child = p_discArea.get_child_at(p_left, p_top);
    IF_CONDITION_NOT_MET_DO(child, return nullptr;);

    const Chip* chip = dynamic_cast<const Chip*>(child);
    IF_CONDITION_NOT_MET_DO(child, return nullptr;);

    return chip;
}

void cxgui::Board::Move(Side p_side)
{
    ChangeCurrentDisc(cxmodel::MakeTransparent());
    UnHighlightCurrentColumn();

    UpdateNextDiscPosition(p_side);

    ChangeCurrentDisc(m_presenter.GetGameViewActivePlayerChipColor());
    HighlightCurrentColumn();
}

void cxgui::Board::ChangeCurrentDisc(const cxmodel::ChipColor& p_newColor)
{
    Chip* chip = GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);
    IF_CONDITION_NOT_MET_DO(chip, return;);

    chip->ChangeColor(p_newColor);
}

void cxgui::Board::UpdateNextDiscPosition(Side p_side)
{
    if(p_side == Side::Left)
    {
        if(m_currentDiscPosition > 0)
        {
            --m_currentDiscPosition;
        }
        else
        {
            m_currentDiscPosition = m_presenter.GetGameViewBoardWidth() - 1;
        }
    }
    else
    {
        if(m_currentDiscPosition < m_presenter.GetGameViewBoardWidth() - 1)
        {
            ++m_currentDiscPosition;
        }
        else
        {
            m_currentDiscPosition = 0u;
        }
    }
}

void cxgui::Board::InitializeNextDiscArea(size_t p_width)
{
    const int chipDimension = ComputeMinimumChipSize(*this, m_presenter.GetGameViewBoardHeight(), m_presenter.GetGameViewBoardWidth());

    m_nextDiscAreaLayout.set_row_homogeneous(true);
    m_nextDiscAreaLayout.set_column_homogeneous(true);

    Chip* activePlayerChip = Gtk::manage(new DiscChip{m_presenter.GetGameViewActivePlayerChipColor(), cxmodel::MakeTransparent(), chipDimension});

    activePlayerChip->set_vexpand(true);
    activePlayerChip->set_hexpand(true);

    m_nextDiscAreaLayout.attach(*activePlayerChip, 0, 0, 1, 1);

    for(size_t i = 1; i < p_width; ++i)
    {
        Chip* noChip = Gtk::manage(new DiscChip{cxmodel::MakeTransparent(), cxmodel::MakeTransparent(), chipDimension});
        noChip->set_vexpand(true);
        noChip->set_hexpand(true);

        m_nextDiscAreaLayout.attach(*noChip, i, 0, 1, 1);
    }
}

void cxgui::Board::InitializeBoard(size_t p_height, size_t p_width)
{
    const int chipDimension = ComputeMinimumChipSize(*this, m_presenter.GetGameViewBoardHeight(), m_presenter.GetGameViewBoardWidth());

    m_boardLayout.set_row_homogeneous(true);
    m_boardLayout.set_column_homogeneous(true);

    for(size_t i = 0; i < p_height; ++i)
    {
        for(size_t j = 0; j < p_width; ++j)
        {
            Chip* noChip = Gtk::manage(new DiscChip{cxmodel::MakeTransparent(), cxmodel::MakeBlue(), chipDimension});
            noChip->set_vexpand(true);
            noChip->set_hexpand(true);

            m_boardLayout.attach(*noChip, j, i, 1, 1);
        }
    }
}

void cxgui::Board::MoveCurrentDiscAtFirstRow()
{
    Chip* currentChip = GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);
    IF_CONDITION_NOT_MET_DO(currentChip, return;);

    currentChip->ChangeColor(cxmodel::MakeTransparent());

    UnHighlightCurrentColumn();
    m_currentDiscPosition = 0u;
    HighlightCurrentColumn();

    Chip* startChip = GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);
    IF_CONDITION_NOT_MET_DO(startChip, return;);

    startChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());
}

void cxgui::Board::RefreshBoardArea()
{
    const cxgui::IGameViewPresenter::ChipColors& chipColors = m_presenter.GetGameViewChipColors();

    for(size_t row = 0u; row < m_presenter.GetGameViewBoardHeight(); ++row)
    {
        for(size_t column = 0u; column < m_presenter.GetGameViewBoardWidth(); ++column)
        {
            Chip* chip = GetChip(m_boardLayout, column, row);
            IF_CONDITION_NOT_MET_DO(chip, return;);

            chip->ChangeColor(chipColors[row][column]);
        }
    }
}

void cxgui::Board::ClearNextDiscArea()
{
    for(size_t column = 0u; column < m_presenter.GetGameViewBoardWidth(); ++column)
    {
        Chip* chip = GetChip(m_nextDiscAreaLayout, column, 0u);
        IF_CONDITION_NOT_MET_DO(chip, return;);

        chip->ChangeColor(cxmodel::MakeTransparent());
    }
}

void cxgui::Board::ClearBoardArea()
{
    for(size_t row = 0u; row < m_presenter.GetGameViewBoardHeight(); ++row)
    {
        for(size_t column = 0u; column < m_presenter.GetGameViewBoardWidth(); ++column)
        {
            Chip* chip = GetChip(m_boardLayout, column, row);
            IF_CONDITION_NOT_MET_DO(chip, return;);

            chip->ChangeColor(cxmodel::MakeTransparent());
        }
    }
}

void cxgui::Board::HighlightCurrentColumn()
{
    for(size_t row = 0u; row < m_presenter.GetGameViewBoardHeight(); ++row)
    {
        for(size_t column = 0u; column < m_presenter.GetGameViewBoardWidth(); ++column)
        {
            if(column == m_currentDiscPosition)
            {
                Chip* chip = GetChip(m_boardLayout, column, row);
                IF_CONDITION_NOT_MET_DO(chip, return;);

                chip->Highlight();
            }
        }
    }
}

void cxgui::Board::UnHighlightCurrentColumn()
{
    for(size_t row = 0u; row < m_presenter.GetGameViewBoardHeight(); ++row)
    {
        for(size_t column = 0u; column < m_presenter.GetGameViewBoardWidth(); ++column)
        {
            if(column == m_currentDiscPosition)
            {
                Chip* chip = GetChip(m_boardLayout, column, row);
                IF_CONDITION_NOT_MET_DO(chip, return;);

                chip->UnHighlight();
            }
        }
    }
}
