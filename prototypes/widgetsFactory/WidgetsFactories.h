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
 * @file WidgetsFactories.h
 * @date 2023
 *
 *************************************************************************************************/
#pragma once

#include <memory>

#include "IAbstractWidgetsFactory.h"
#include "IConnectXAbstractWidgetsFactory.h"

class WidgetsFactories
{

public:

    WidgetsFactories(std::unique_ptr<IAbstractWidgetsFactory> p_toolkitFactory,
                    std::unique_ptr<IConnectXAbstractWidgetsFactory> p_connectXSpecificFactory)
    : m_toolkitFactory{std::move(p_toolkitFactory)}
    , m_connectXSpecificFactory{std::move(p_connectXSpecificFactory)}
    {}

    IAbstractWidgetsFactory* operator->() const
    {
        return m_toolkitFactory.get();
    }

    IConnectXAbstractWidgetsFactory* GetConnectXSpecific() const
    {
        return m_connectXSpecificFactory.get();
    }

private:

    std::unique_ptr<IAbstractWidgetsFactory>         m_toolkitFactory;
    std::unique_ptr<IConnectXAbstractWidgetsFactory> m_connectXSpecificFactory;
};
