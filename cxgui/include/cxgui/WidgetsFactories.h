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
 * @date 2024
 *
 *************************************************************************************************/

#ifndef WIDGETSFACTORIES_H_4652F2EE_88BE_4042_8BF4_67A223339FF7
#define WIDGETSFACTORIES_H_4652F2EE_88BE_4042_8BF4_67A223339FF7

namespace cx::gui
{

class IAbstractWidgetsFactory;
class IAbstractConnectXWidgetsFactory;

}

namespace cx::gui
{

/**********************************************************************************************//**
 * @brief Utility class for holding widgets factories.
 *
 * This is a container for factories. Its reponsibility is to make it possible to use both a
 * standard widgets factory and a Connect X widgets factory from the same source, without
 * coupling them.
 *
 * @invariant Both widgets factories are valid.
 *
 *************************************************************************************************/
class WidgetsFactories final
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_stdFactory
     *      Standard widgets abstract factory.
     *
     * @param p_connectxFactory
     *      Connect X specific widgets abstract factory.
     *
     *********************************************************************************************/
    WidgetsFactories(IAbstractWidgetsFactory& p_stdFactory, IAbstractConnectXWidgetsFactory& p_connectxFactory);

    /******************************************************************************************//**
     * @brief Get the standard widgets factory.
     *
     *********************************************************************************************/
    [[nodiscard]] const IAbstractWidgetsFactory& GetStandardWidgetsFactory() const;

    /******************************************************************************************//**
     * @brief Get the Connect X widgets factory.
     *
     *********************************************************************************************/
    [[nodiscard]] const IAbstractConnectXWidgetsFactory& GetConnectXWidgetsFactory() const;

private:

    IAbstractWidgetsFactory& m_stdFactory;
    IAbstractConnectXWidgetsFactory& m_connectxFactory;
};

} // namespace cx::gui

#endif // WIDGETSFACTORIES_H_4652F2EE_88BE_4042_8BF4_67A223339FF7
