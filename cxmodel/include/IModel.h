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
 * @file IModel.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IMODEL_H_CC50381B_15B7_4586_A5F6_5F244A4289BA
#define IMODEL_H_CC50381B_15B7_4586_A5F6_5F244A4289BA

#include <string>

#include "GameInformation.h"
#include "Subject.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for a Connect X compatible model.
 *
 * Inherit from this to create a compatible Connect X model class.
 *
 ************************************************************************************************/
class IModel : public Subject
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IModel() = default;

    /******************************************************************************************//**
     * @brief Get the model name.
     *
     ********************************************************************************************/
    virtual std::string GetName() const = 0;

    /******************************************************************************************//**
     * @brief Get the model version number, formatted as a string.
     *
     ********************************************************************************************/
    virtual std::string GetVersionNumber() const = 0;

    /******************************************************************************************//**
     * @brief Creates a new game.
     *
     * @param p_gameInformation The necessary information to create a game.
     *
     ********************************************************************************************/
    virtual void CreateNewGame(const GameInformation& p_gameInformation) = 0;

    /******************************************************************************************//**
     * @brief Get the current game information.
     *
     * @return The current game information.
     *
     ********************************************************************************************/
    virtual GameInformation GetGameInformation() const = 0;

    /******************************************************************************************//**
     * @brief Undo the last action, if possible.
     *
     * If some undoeable actions were done, the last one will be undoed.
     *
     * @note An action that is undoed must put the model back at the same state is was before
     *       the action was ever done.
     *
     ********************************************************************************************/
    virtual void Undo() = 0;

    /******************************************************************************************//**
     * @brief Redo the last action, if possible.
     *
     * If some redoable actions were undoed, the last one that was undoed will be redoed.
     * Otherwise, nothing happens.
     *
     * @note An action that is redoed must put the model back at the same state it was before
     *       the action was undoed.
     *
     ********************************************************************************************/
    virtual void Redo() = 0;

    /******************************************************************************************//**
     * @brief Sends an update to every observers with the SIGNAL notification context.
     *
     * Use this to update observers that are not triggered from any user action.
     *
     ********************************************************************************************/
    virtual void Signal() = 0;

};

} // namespace cxmodel

#endif // IMODEL_H_CC50381B_15B7_4586_A5F6_5F244A4289BA
