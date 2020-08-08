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
 * @file Disc.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef DISC_H_E4E3699A_35A5_4050_AAE7_C91C2C38DCEF
#define DISC_H_E4E3699A_35A5_4050_AAE7_C91C2C38DCEF

#include "IChip.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Disc chips.
 *
 * They are the classic Connect 4 disc shaped, mono colored chips.
 *
 ************************************************************************************************/
class Disc : public cxmodel::IChip
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     ********************************************************************************************/
    Disc(const ChipColor p_color);

    // IChip:
    ChipColor GetColor() const override;

private:

    ChipColor m_color;
};

/******************************************************************************************//**
 * @brief Equal-to operator.
 *
 * @param p_lhs The left hand side disc.
 * @param p_rhs The right hand side disc.
 *
 * @return `true` if the disc are considered equal, `false` otherwise.
 *
 ********************************************************************************************/
bool operator==(const Disc& p_lhs, const Disc& p_rhs);

/******************************************************************************************//**
 * @brief Not-equal-to operator.
 *
 * @param p_lhs The left hand side disc.
 * @param p_rhs The right hand side disc.
 *
 * @return `true` if the disc are considered NOT equal, `false` otherwise.
 *
 ********************************************************************************************/
bool operator!=(const Disc& p_lhs, const Disc& p_rhs);

} // namespace cxmodel

#endif // DISC_H_E4E3699A_35A5_4050_AAE7_C91C2C38DCEF
