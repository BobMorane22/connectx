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
 * @file IAnimatedBoardPresenter.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef IANIMATEDBOARDPRESENTER_H_A2048E6E_9B10_4BE6_93E7_CD07D492BE33
#define IANIMATEDBOARDPRESENTER_H_A2048E6E_9B10_4BE6_93E7_CD07D492BE33

#include <cxgui/include/IGameViewPresenter.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Interface for animated board presenters.
 * 
 *************************************************************************************************/
class IAnimatedBoardPresenter
{

public:

    /******************************************************************************************//**
     * @brief Updates the cached values.
     * 
     * Immediately after a call to this, the presenter should be in sync with the model.
     *
     *********************************************************************************************/
    virtual void Sync() = 0;

    /******************************************************************************************//**
     * @brief Retreive the cached board height.
     *
     * @return The cached board height.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetBoardHeight() const = 0;

    /******************************************************************************************//**
     * @brief Retreive the cached board width.
     *
     * @return The cached board width.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual size_t GetBoardWidth() const = 0;

    /******************************************************************************************//**
     * @brief Retreive the cached active player chip color.
     * 
     * @return The cached active player chip color.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual cxmodel::ChipColor GetActivePlayerChipColor() const = 0;

    /******************************************************************************************//**
     * @brief Retreive the cached board chip colors.
     * 
     * @return The cached board chip colors.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const IGameViewPresenter::ChipColors& GetBoardChipColors() const = 0;

};

} // namespace cxgui

#endif // IANIMATEDBOARDPRESENTER_H_A2048E6E_9B10_4BE6_93E7_CD07D492BE33
