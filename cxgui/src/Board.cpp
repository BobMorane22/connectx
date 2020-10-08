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
#include <cxmodel/include/Disc.h>

#include <Board.h>
#include <DiscChip.h>
#include <IGameViewController.h>
#include <IGameViewPresenter.h>

constexpr bool FULLY_HANDLED = true;
constexpr bool PROPAGATE = false;

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

    if(!ASSERT(chip != nullptr))
    {
        return;
    }

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
    Chip* currentChip = GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);

    if(!ASSERT(currentChip != nullptr))
    {
        return;
    }

    currentChip->ChangeColor(cxmodel::MakeTransparent());

    m_currentDiscPosition = 0u;
    Chip* startChip = GetChip(m_nextDiscAreaLayout, m_currentDiscPosition, 0);

    if(!ASSERT(startChip != nullptr))
    {
        return;
    }

    startChip->ChangeColor(m_presenter.GetGameViewActivePlayerChipColor());

    // Refresh board area:
    const cxgui::IGameViewPresenter::ChipColors& chipColors = m_presenter.GetGameViewChipColors();

    for(size_t row = 0u; row < m_presenter.GetGameViewBoardHeight(); ++row)
    {
        for(size_t column = 0u; column < m_presenter.GetGameViewBoardWidth(); ++column)
        {
            Chip* chip = GetChip(m_boardLayout, column, row);

            if(!ASSERT(chip != nullptr))
            {
                return;
            }

            chip->ChangeColor(chipColors[row][column]);
        }
    }
}

cxgui::Chip* cxgui::Board::GetChip(Gtk::Grid& p_discArea, int p_left, int p_top)
{
    Widget* child = p_discArea.get_child_at(p_left, p_top);

    if(!ASSERT(child != nullptr))
    {
        return nullptr;
    }

    Chip* chip = dynamic_cast<Chip*>(child);

    if(!ASSERT(chip != nullptr))
    {
        return nullptr;
    }

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
