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

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Interface for a Connect X compatible model.
 *
 * Inherit from this to create a compatible Connect X model class.
 *
 ************************************************************************************************/
class IModel
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     ********************************************************************************************/
    virtual ~IModel() = default;

    /******************************************************************************************//**
     * @brief Access the current value.
     *
     * @return The current value as stored in the model.
     *
     ********************************************************************************************/
    virtual unsigned int GetCurrentValue() const = 0;

    /******************************************************************************************//**
     * @brief Increments the current value in the model.
     *
     * @post The value in the model is incremented by one.
     *
     * Increments by one the value stored in the model.
     *
     ********************************************************************************************/
    virtual void Increment() = 0;

    /******************************************************************************************//**
     * @brief Reinitialize the value stored in the model to its initial value.
     *
     * @post The value in the model is back to its initial value.
     *
     * At the model creation, an initial value is given to the current value. When this method
     * is called, the current value is reinitialized to this initial value, as if the model had
     * just been created.
     *
     ********************************************************************************************/
    virtual void Reinitialize() = 0;

};

} // namespace cxmodel

#endif // IMODEL_H_CC50381B_15B7_4586_A5F6_5F244A4289BA
