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
 * @date 2024
 *
 *************************************************************************************************/

#ifndef IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F
#define IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F

#include <memory>

namespace cxgui
{
    class IMenuBar;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Abstract widgets factory.
 *
 * Create standard widgets (i.e. buttons, labels, textboxes, etc.) without dealing with the
 * underlying toolkit.
 *
 *************************************************************************************************/
class IAbstractWidgetsFactory
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IAbstractWidgetsFactory() = default;

    /******************************************************************************************//**
     * @brief Create a menu bar instance.
     *
     * @post
     *      The returned menu bar instance is valid.
     *
     * @return
     *      A menu bar instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual std::unique_ptr<cxgui::IMenuBar> CreateMenuBar() const = 0;

};

} // namespace cxgui

#endif // IABSTRACTWIDGETSFACTORY_H_FE309A25_8E9C_4F60_852F_0ADD5750890F
