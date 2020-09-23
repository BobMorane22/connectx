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
 * @file IGameViewPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef IGAMEVIEWPRESENTER_H_564B2260_1CAE_4391_A361_97CAB8D0102D
#define IGAMEVIEWPRESENTER_H_564B2260_1CAE_4391_A361_97CAB8D0102D

#include <string>

#include <cxmodel/include/ChipColor.h>

namespace cxgui
{

/*********************************************************************************************//**
 * @brief Presenter for the 'Game' view.
 *
 ************************************************************************************************/
class IGameViewPresenter
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     ********************************************************************************************/
    virtual ~IGameViewPresenter() = default;

    /******************************************************************************************//**
     * @brief Game view title accessor.
     *
     * @return The game view title.
     *
     ********************************************************************************************/
    virtual std::string GetGameViewTitle() const = 0;

    /******************************************************************************************//**
     * @brief Game view message accessor.
     *
     * @return The game view message.
     *
     * The game view message is a string message that presents the new game information. It is
     * a temporary accessor used to make sure the model connection is working before developing
     * the view further.
     *
     ********************************************************************************************/
    virtual std::string GetGameViewMessage() const = 0;

    /******************************************************************************************//**
     * @brief Active player's chip color accessor.
     *
     * @return The active player's chip color.
     *
     ********************************************************************************************/
    virtual cxmodel::ChipColor GetActivePlayerChipColor() const = 0;

    /******************************************************************************************//**
     * @brief Next player's chip color accessor.
     *
     * @return The next player's chip color.
     *
     ********************************************************************************************/
    virtual cxmodel::ChipColor GetNextPlayerChipColor() const = 0;

    /******************************************************************************************//**
     * @brief Active player label text accessor.
     *
     * @return The active player's text label.
     *
     ********************************************************************************************/
    virtual std::string GetActivePlayerLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Next player label text accessor.
     *
     * @return The next player's text label.
     *
     ********************************************************************************************/
    virtual std::string GetNextPlayerLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Active player name accessor.
     *
     * @return The active player's name.
     *
     ********************************************************************************************/
    virtual std::string GetActivePlayerName() const = 0;

    /******************************************************************************************//**
     * @brief Next player name accessor.
     *
     * @return The next player's name.
     *
     ********************************************************************************************/
    virtual std::string GetNextPlayerName() const = 0;

};

} // namespace cxgui

#endif // IGAMEVIEWPRESENTER_H_564B2260_1CAE_4391_A361_97CAB8D0102D
