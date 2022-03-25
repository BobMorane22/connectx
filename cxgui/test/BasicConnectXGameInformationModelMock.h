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
 * @file BasicConnectXGameInformationModelMock.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef BASICCONNECTXGAMEINFORMATIONMODELMOCK_H_F117935F_A182_4F97_B8A8_39B023B42263
#define BASICCONNECTXGAMEINFORMATIONMODELMOCK_H_F117935F_A182_4F97_B8A8_39B023B42263

#include <cxmodel/IConnectXGameInformation.h>
#include <cxunit/NotImplementedException.h>

/*********************************************************************************************//**
 * @brief A basic `IConnectXGameInformation` compatible model mock.
 *
 * Use this as a base to create complete `IConnectXGameInformation` compatible model mocks.
 *
 ************************************************************************************************/
class BasicConnectXGameInformationModelMock : public cxmodel::IConnectXGameInformation
{

public:

    size_t GetCurrentGridHeight() const override {return 6u;}
    size_t GetCurrentGridWidth() const override {return 7u;}
    size_t GetCurrentInARowValue() const override {return 4u;}
    const cxmodel::IPlayer& GetActivePlayer() const override {throw cxunit::NotImplementedException();}
    const cxmodel::IPlayer& GetNextPlayer() const override {throw cxunit::NotImplementedException();}
    const cxmodel::IChip& GetChip(size_t /*p_row*/, size_t /*p_column*/) const override {throw cxunit::NotImplementedException();}
    bool IsWon() const override {return false;}
    bool IsTie() const override {return false;}
};

#endif // BASICCONNECTXGAMEINFORMATIONMODELMOCK_H_F117935F_A182_4F97_B8A8_39B023B42263
