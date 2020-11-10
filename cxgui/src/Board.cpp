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

#include <Board.h>
#include <DiscChip.h>
#include <IGameViewController.h>
#include <IGameViewPresenter.h>

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

    pack1(m_nextDiscAreaLayout, true, false);
    pack2(m_boardLayout, true, false);
}

void cxgui::Board::DropChip()
{
    Chip* chip = GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);
    IF_CONDITION_NOT_MET_DO(chip, return;);

    m_controller.OnDown(chip->GetColor(), m_currentDiscPosition);
}

void cxgui::Board::MoveLeft()
{
    Move(Side::Left);
}

void cxgui::Board::MoveRight()
{
    Move(Side::Right);
}

void cxgui::Board::Update()
{
    MoveCurrentDiscAtFirstRow();
    RefreshBoardArea();
}

cxgui::Chip* cxgui::Board::GetChip(Gtk::Grid& p_discArea, int p_left, int p_top)
{
    Widget* child = p_discArea.get_child_at(p_left, p_top);
    IF_CONDITION_NOT_MET_DO(child, return nullptr;);

    Chip* chip = dynamic_cast<Chip*>(child);
    IF_CONDITION_NOT_MET_DO(child, return nullptr;);

    return chip;
}

void cxgui::Board::Move(Side p_side)
{
    ChangeCurrentDisc(cxmodel::MakeTransparent());
    UpdateNextDiscPosition(p_side);
    ChangeCurrentDisc(m_presenter.GetGameViewActivePlayerChipColor());
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

    m_currentDiscPosition = 0u;
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
