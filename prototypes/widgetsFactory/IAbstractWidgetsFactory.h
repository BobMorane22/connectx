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
 * @file IAbstractWidgetsFactory.h
 * @date 2023
 *
 *************************************************************************************************/
#pragma once

#include <memory>

class IButton;
class IEditBox;
class ILayout;


/**************************************************************************************************
 * Available widget toolkit backend.
 *
 *************************************************************************************************/
enum class Backend
{
    GTKMM3,
};

/**************************************************************************************************
 * Abstract widgets factory.
 *
 *************************************************************************************************/
class IAbstractWidgetsFactory
{

public:

    virtual ~IAbstractWidgetsFactory() = default;

    virtual std::unique_ptr<IButton>  CreateButton() const = 0;
    virtual std::unique_ptr<IEditBox> CreateEditBox() const = 0;
    virtual std::unique_ptr<ILayout>  CreateLayout() const = 0;

};


/**************************************************************************************************
 * Creates the appropriate widget factory according to a specified backend.
 *
 *************************************************************************************************/
std::unique_ptr<IAbstractWidgetsFactory> CreateAbstractWidgetsFactory(Backend p_backend);
