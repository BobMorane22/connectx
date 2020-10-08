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
 * @file GameBoard.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GAMEBOARD_H_7597FDE7_7C70_437C_9AF2_432828186B6A
#define GAMEBOARD_H_7597FDE7_7C70_437C_9AF2_432828186B6A

#include <gtkmm/grid.h>
#include <gtkmm/paned.h>

#include <cxmodel/include/ChipColor.h>
#include <cxmodel/include/IChip.h>

namespace cxgui
{
    class Chip;
    class IGameViewController;
    class IGameViewPresenter;
}

namespace cxgui
{

/*********************************************************************************************//**
 * @brief A graphical Connect X game board.
 *
 ************************************************************************************************/
class Board : public Gtk::Paned
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_presenter  The Game View presenter.
     * @param p_controller The Game View controller.
     *
     ********************************************************************************************/
    Board(const IGameViewPresenter& p_presenter, IGameViewController& p_controller);

    /******************************************************************************************//**
     * @brief Drops the chip in the current column.
     *
     ********************************************************************************************/
    void DropChip();

    /******************************************************************************************//**
     * @brief Moves the chip one column left (wraps around if necessary).
     *
     ********************************************************************************************/
    void MoveLeft();

    /******************************************************************************************//**
     * @brief Moves the chip one column right (wraps around if necessary).
     *
     ********************************************************************************************/
    void MoveRight();

    /******************************************************************************************//**
     * @brief Updates the board.
     *
     ********************************************************************************************/
    void Update();

private:

    enum class Side
    {
        Left,
        Right
    };

    Chip* GetChip(Gtk::Grid& p_discArea, int p_left, int p_top);

    void Move(Side p_side);
    void ChangeCurrentDisc(const cxmodel::ChipColor& p_newColor);
    void UpdateNextDiscPosition(Side p_side);

    void InitializeNextDiscArea(size_t p_width);
    void InitializeBoard(size_t p_height, size_t p_width);

    const IGameViewPresenter& m_presenter;
    IGameViewController& m_controller;

    Gtk::Grid m_nextDiscAreaLayout;
    Gtk::Grid m_boardLayout;

    std::size_t m_currentDiscPosition;
};

} // namespace cxgui

#endif // GAMEBOARD_H_7597FDE7_7C70_437C_9AF2_432828186B6A
