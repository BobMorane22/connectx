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
 * @file ConcreteSubjectlMock.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef CONCRETESUBJECTMOCK_H_8CBA88D3_AEA7_4343_9FDC_B12FCD7E945F
#define CONCRETESUBJECTMOCK_H_8CBA88D3_AEA7_4343_9FDC_B12FCD7E945F

#include <Subject.h>

class ConcreteSubjectMock : public cxmodel::Subject
{

public:

    ConcreteSubjectMock(int p_data);
    ~ConcreteSubjectMock() override = default;

    int GetData() const;
    void IncrementData();

private:

    int m_data;

};

#endif // CONCRETESUBJECTMOCK_H_8CBA88D3_AEA7_4343_9FDC_B12FCD7E945F
