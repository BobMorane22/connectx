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
 * @file Gtkmm3WidgetsFactory.h
 * @date 2023
 *
 *************************************************************************************************/

#pragma once

#include "IAbstractWidgetsFactory.h"

/**************************************************************************************************
 * Concrete widgets factory with Gtkmm3 as its backend.
 *
 *************************************************************************************************/
class Gtkmm3WidgetsFactory : public IAbstractWidgetsFactory
{

public:

    std::unique_ptr<IButton>  CreateButton() const override;
    std::unique_ptr<IEditBox> CreateEditBox() const override;
    std::unique_ptr<ILayout>  CreateLayout() const override;

};
