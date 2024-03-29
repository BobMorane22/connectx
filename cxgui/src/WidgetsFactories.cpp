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
 * @file WidgetsFactories.cpp
 * @date 2024
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/IAbstractWidgetsFactory.h>
#include <cxgui/IAbstractConnectXWidgetsFactory.h>
#include <cxgui/WidgetsFactories.h>

cxgui::WidgetsFactories::WidgetsFactories(
    std::unique_ptr<IAbstractWidgetsFactory> p_stdFactory,
    std::unique_ptr<IAbstractConnectXWidgetsFactory> p_connectxFactory)
{
    PRECONDITION(p_stdFactory != nullptr);
    PRECONDITION(p_connectxFactory != nullptr);

    m_stdFactory = std::move(p_stdFactory);
    m_connectxFactory = std::move(p_connectxFactory);

    POSTCONDITION(m_stdFactory != nullptr);
    POSTCONDITION(m_connectxFactory != nullptr);

    INVARIANT(m_stdFactory != nullptr);
    INVARIANT(m_connectxFactory != nullptr);
}

const cxgui::IAbstractWidgetsFactory& cxgui::WidgetsFactories::GetStandardWidgetsFactory() const
{
    INVARIANT(m_stdFactory != nullptr);

    return *m_stdFactory;
}

const cxgui::IAbstractConnectXWidgetsFactory& cxgui::WidgetsFactories::GetConnectXWidgetsFactory() const
{
    INVARIANT(m_connectxFactory != nullptr);

    return *m_connectxFactory;
}
