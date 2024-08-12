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
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxui/IAbstractConnectXWidgetsFactory.h>
#include <cxui/WidgetsFactories.h>

cx::ui::WidgetsFactories::WidgetsFactories(
    cx::cmn::ui::IAbstractWidgetsFactory& p_stdFactory,
    IAbstractConnectXWidgetsFactory& p_connectxFactory)
: m_stdFactory{p_stdFactory}
, m_connectxFactory{p_connectxFactory}
{
}

const cx::cmn::ui::IAbstractWidgetsFactory& cx::ui::WidgetsFactories::GetStandardWidgetsFactory() const
{
    return m_stdFactory;
}

const cx::ui::IAbstractConnectXWidgetsFactory& cx::ui::WidgetsFactories::GetConnectXWidgetsFactory() const
{
    return m_connectxFactory;
}
