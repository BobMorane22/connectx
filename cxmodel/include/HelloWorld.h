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
 * @file HelloWorld.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef HELLOWORLD_H_2BB45F48_E623_451E_9844_93D90D732496
#define HELLOWORLD_H_2BB45F48_E623_451E_9844_93D90D732496

#include <string>

/*********************************************************************************************//**
 * @brief 'Hello World!' formatter.
 *
 * Formats a string containing 'Hello World!'.
 *
 ************************************************************************************************/
class HelloWorld
{

public:

    /******************************************************************************************//**
     * @brief Formats a string containing 'Hello World!'.
     *
     * @return The 'Hello World' string.
     *
     ********************************************************************************************/
    std::string Make() const;

private:

    const std::string m_HELLO_WORLD = "Hello World!";
};

#endif // HELLOWORLD_H_2BB45F48_E623_451E_9844_93D90D732496
