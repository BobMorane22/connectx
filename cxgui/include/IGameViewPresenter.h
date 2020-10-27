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

    using ChipColors = std::vector<std::vector<cxmodel::ChipColor>>;

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
     * @brief Active player's chip color accessor.
     *
     * @return The active player's chip color.
     *
     ********************************************************************************************/
    virtual cxmodel::ChipColor GetGameViewActivePlayerChipColor() const = 0;

    /******************************************************************************************//**
     * @brief Next player's chip color accessor.
     *
     * @return The next player's chip color.
     *
     ********************************************************************************************/
    virtual cxmodel::ChipColor GetGameViewNextPlayerChipColor() const = 0;

    /******************************************************************************************//**
     * @brief Active player label text accessor.
     *
     * @return The active player's text label.
     *
     ********************************************************************************************/
    virtual std::string GetGameViewActivePlayerLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Next player label text accessor.
     *
     * @return The next player's text label.
     *
     ********************************************************************************************/
    virtual std::string GetGameViewNextPlayerLabelText() const = 0;

    /******************************************************************************************//**
     * @brief Active player name accessor.
     *
     * @return The active player's name.
     *
     ********************************************************************************************/
    virtual std::string GetGameViewActivePlayerName() const = 0;

    /******************************************************************************************//**
     * @brief Next player name accessor.
     *
     * @return The next player's name.
     *
     ********************************************************************************************/
    virtual std::string GetGameViewNextPlayerName() const = 0;

    /******************************************************************************************//**
     * @brief Board width accessor.
     *
     * @return The board width.
     *
     ********************************************************************************************/
    virtual size_t GetGameViewBoardWidth() const = 0;

    /******************************************************************************************//**
     * @brief Board height accessor.
     *
     * @return The board height.
     *
     ********************************************************************************************/
    virtual size_t GetGameViewBoardHeight() const = 0;

    /******************************************************************************************//**
     * @brief Chip colors accessor.
     *
     * @return The chip colors.
     *
     ********************************************************************************************/
    virtual const ChipColors& GetGameViewChipColors() const = 0;

};

} // namespace cxgui

#endif // IGAMEVIEWPRESENTER_H_564B2260_1CAE_4391_A361_97CAB8D0102D
