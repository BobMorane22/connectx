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
 * @file ModelMockPresenter.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef MODELMOCKPRESENTER_H_A4A9F6D9_7463_47D5_A25A_00880ACB678C
#define MODELMOCKPRESENTER_H_A4A9F6D9_7463_47D5_A25A_00880ACB678C

#include <cxmodel/include/IModel.h>

class ModelMockPresenter : public cxmodel::IModel
{

public:

    virtual unsigned int GetCurrentValue() const override;

    virtual void Increment() override;
    virtual void Reinitialize() override;

    virtual void Undo() override;
    virtual void Redo() override;


private:

    unsigned int m_currentValue;

};

#endif // MODELMOCK_H_A4A9F6D9_7463_47D5_A25A_00880ACB678C
