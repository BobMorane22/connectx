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
 * @file CommandReinitialize.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef COMMANDREINITIALIZE_H_D036C481_8FC6_410B_8B2F_397136AC1038
#define COMMANDREINITIALIZE_H_D036C481_8FC6_410B_8B2F_397136AC1038

#include "ICommand.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Command that reinitializes a value to an initial value.
 *
 ************************************************************************************************/
class CommandReinitialize : public ICommand
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param      p_reinitValue   The value to reinitialize to.
     * @param      p_initialValue  The initial value before anything was done.
     * @param[out] p_value         The actual value that will be reinitialized.
     *
     * Creates a command thats lets a user reinitialize something to a predefined value.
     *
     ********************************************************************************************/
    CommandReinitialize(unsigned int p_reinitValue,
                        unsigned int p_initialValue,
                        unsigned int& p_value);

    /******************************************************************************************//**
     * @brief Reinitializes the value.
     *
     ********************************************************************************************/
    void Execute() override;

    /******************************************************************************************//**
     * @brief Undoes a reinitialization.
     *
     ********************************************************************************************/
    void Undo() override;


private:

    const unsigned int m_reinitValue;
    const unsigned int m_initialValue;
    unsigned int& m_value;
};

} // namespace cxmodel

#endif // COMMANDREINITIALIZE_H_D036C481_8FC6_410B_8B2F_397136AC1038
