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
 * @file BasicConnectXLimitsModelMock.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef BASICCONNECTXLIMITSMODELMOCK_H_FCA3D94F_8883_4D02_B82F_0CB27F9AF498
#define BASICCONNECTXLIMITSMODELMOCK_H_FCA3D94F_8883_4D02_B82F_0CB27F9AF498

#include <cxmodel/IConnectXLimits.h>

/*********************************************************************************************//**
 * @brief A basic `IConnectXLimits` compatible model mock.
 *
 * Use this as a base to create complete `IConnectXLimits.h` compatible model mocks.
 *
 ************************************************************************************************/
class BasicConnectXLimitsModelMock : public cxmodel::IConnectXLimits
{

public:

    size_t GetMinimumGridHeight() const override {return 6u;}
    size_t GetMinimumGridWidth() const override {return 7u;}
    size_t GetMinimumInARowValue() const override {return 4u;}
    size_t GetMaximumGridHeight() const override {return 64u;}
    size_t GetMaximumGridWidth() const override {return 64u;}
    size_t GetMaximumInARowValue() const override {return 8u;}
    size_t GetMinimumNumberOfPlayers() const override {return 2u;}
    size_t GetMaximumNumberOfPlayers() const override {return 10u;}

};

#endif // BASICCONNECTXLIMITSMODELMOCK_H_FCA3D94F_8883_4D02_B82F_0CB27F9AF498
