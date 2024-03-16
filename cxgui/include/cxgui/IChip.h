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
 * @file IChip.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef ICHIP_H_77522105_D372_4CF2_9AE7_68B8BD308F44
#define ICHIP_H_77522105_D372_4CF2_9AE7_68B8BD308F44

#include <cxmodel/ChipColor.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Chip for dropping in the Connect X game board.
 *
 * A chip is a piece with which Connect X players can fill the board.
 *
 *************************************************************************************************/
class IChip : public IWidget
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IChip() = default;

    /******************************************************************************************//**
     * @brief Changes the chip's fill color.
     *
     * @param p_newFillColor
     *      The new fill color.
     *
     ********************************************************************************************/
    virtual void ChangeColor(const cxmodel::ChipColor& p_newFillColor) = 0;

    /******************************************************************************************//**
     * @brief Chip color accessor.
     *
     * @return
     *      The chip's color.
     *
     ********************************************************************************************/
    [[nodiscard]] virtual cxmodel::ChipColor GetColor() const = 0;

    /******************************************************************************************//**
     * @brief Highlights the current chip.
     *
     * The chip's background is hilighted.
     *
     ********************************************************************************************/
    virtual void Highlight() = 0;

    /******************************************************************************************//**
     * @brief Removes highlighting from the current chip, if any.
     *
     ********************************************************************************************/
    virtual void UnHighlight() = 0;
};

} // namespace cxgui

#endif // ICHIP_H_77522105_D372_4CF2_9AE7_68B8BD308F44
