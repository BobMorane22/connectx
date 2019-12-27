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
 * @file Model.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC
#define MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC

#include <IModel.h>
#include <Subject.h>

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Connect X model.
 *
 * This class holds the Connect X related business rules.
 *
 ************************************************************************************************/
class Model : public IModel, Subject
{

public:

    Model();

    unsigned int GetCurrentValue() const override;

    void Increment() override;
    void Reinitialize() override;

private:

    static constexpr unsigned int m_INITIAL_VALUE = 0u;

    unsigned int m_currentValue;
};

} // namespace cxmodel

#endif // MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC
