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

#include <iostream>

#include <cxinv/include/assertion.h>

#include <Board.h>
#include <DiscChip.h>
#include <IGameViewPresenter.h>

constexpr bool FULLY_HANDLED = true;
constexpr bool PROPAGATE = false;

cxgui::Board::Board(const IGameViewPresenter& p_presenter)
: m_presenter{p_presenter}
, m_nextDiscPosition{0u}
{
    set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    InitializeNextDiscArea(m_presenter.GetGameViewBoardWidth());
    InitializeBoard(m_presenter.GetGameViewBoardHeight(), m_presenter.GetGameViewBoardWidth());

    pack1(m_nextDiscAreaLayout, true, false);
    pack2(m_boardLayout, true, false);
}

void cxgui::Board::DropChip()
{
    std::cout << "Drop!" << std::endl;
}

void cxgui::Board::MoveLeft()
{
    Move(Side::Left);
}

void cxgui::Board::MoveRight()
{
    Move(Side::Right);
}

void cxgui::Board::Move(Side p_side)
{
    ChangeCurrentDisc(cxmodel::MakeTransparent());
    UpdateNextDiscPosition(p_side);
    ChangeCurrentDisc(m_presenter.GetGameViewActivePlayerChipColor());
}

void cxgui::Board::ChangeCurrentDisc(const cxmodel::ChipColor& p_newColor)
{
    Widget* child = m_nextDiscAreaLayout.get_child_at(m_nextDiscPosition, 0);

    if(!ASSERT(child != nullptr))
    {
        return;
    }

    Chip* chip = dynamic_cast<Chip*>(child);

    if(!ASSERT(chip != nullptr))
    {
        return;
    }

    chip->ChangeColor(p_newColor);
}

void cxgui::Board::UpdateNextDiscPosition(Side p_side)
{
    if(p_side == Side::Left)
    {
        if(m_nextDiscPosition > 0)
        {
            --m_nextDiscPosition;
        }
        else
        {
            m_nextDiscPosition = m_presenter.GetGameViewBoardWidth() - 1;
        }
    }
    else
    {
        if(m_nextDiscPosition < m_presenter.GetGameViewBoardWidth() - 1)
        {
            ++m_nextDiscPosition;
        }
        else
        {
            m_nextDiscPosition = 0u;
        }
    }
}

void cxgui::Board::InitializeNextDiscArea(size_t p_width)
{
    m_nextDiscAreaLayout.set_row_homogeneous(true);
    m_nextDiscAreaLayout.set_column_homogeneous(true);

    Chip* activePlayerChip = Gtk::manage(new DiscChip{m_presenter.GetGameViewActivePlayerChipColor(), cxmodel::MakeTransparent()});

    activePlayerChip->set_vexpand(true);
    activePlayerChip->set_hexpand(true);

    m_nextDiscAreaLayout.attach(*activePlayerChip, 0, 0, 1, 1);

    for(size_t i = 1; i < p_width; ++i)
    {
        Chip* noChip = Gtk::manage(new DiscChip{cxmodel::MakeTransparent(), cxmodel::MakeTransparent()});
        noChip->set_vexpand(true);
        noChip->set_hexpand(true);

        m_nextDiscAreaLayout.attach(*noChip, i, 0, 1, 1);
    }
}

void cxgui::Board::InitializeBoard(size_t p_height, size_t p_width)
{
    m_boardLayout.set_row_homogeneous(true);
    m_boardLayout.set_column_homogeneous(true);

    for(size_t i = 0; i < p_height; ++i)
    {
        for(size_t j = 0; j < p_width; ++j)
        {
            Chip* noChip = Gtk::manage(new DiscChip{cxmodel::MakeTransparent(), cxmodel::MakeBlue()});
            noChip->set_vexpand(true);
            noChip->set_hexpand(true);

            m_boardLayout.attach(*noChip, j, i, 1, 1);
        }
    }
}
