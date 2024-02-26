/**************************************************************************************************
 *  This file is part of Connect X.
 *
 *  Connect X is free software: you can redistribute it and/or modify *  it under the terms of the GNU General Public License as published by
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
 * @file IWidget.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef IWIDGET_H_845C70A7_65F2_4B7C_8446_A11ED3BC31E8
#define IWIDGET_H_845C70A7_65F2_4B7C_8446_A11ED3BC31E8

#include <cstddef>
#include <memory>
#include <string>

namespace cxgui
{

    enum class EnabledState;
    struct Margins;

}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Interface aggrating services common to all widgets.
 *
 *************************************************************************************************/
class IWidget
{

public:

///@{ @name Construction & destruction

    /**********************************************************************************************//**
     * @brief Destructor.
     *
     *************************************************************************************************/
    virtual ~IWidget() = default;

///@}

///@{ @name Accessors

    /**********************************************************************************************//**
     * @brief Gets the widget's width (in device independant pixels).
     *
     * @return The widget's width (in device independant pixels).
     *
     *************************************************************************************************/
    [[nodiscard]] virtual size_t GetWidth() const = 0;

    /**********************************************************************************************//**
     * @brief Gets the widget's height (in device independant pixels).
     *
     * @return The widget's height (in device independant pixels).
     *
     *************************************************************************************************/
    [[nodiscard]] virtual size_t GetHeight() const = 0;

///@}

///@{ @name Mutators

    /**********************************************************************************************//**
     * @brief Indicates if the widget is sensible to direct user operations.
     *
     * A widget that is disabled is not directly modifiable by the user. For example, mouse or
     * keyboard events will have no effect on it. The only way to modify a disabled widget is
     * indirectly, through modifying another widget which would trigger a reaction on the disabled
     * widget (typicaly example is a label). A widget that is enabled will repond to user events.
     *
     * @param p_enabled The new enabled or disabled state of the widget.
     *
     *************************************************************************************************/
    virtual void SetEnabled(EnabledState p_enabled) = 0;

    /******************************************************************************************//**
     * @brief Changes the margin sizes for the widget.
     *
     * @param p_newMarginSizes
     *      The new margin sizes.
     *
     *********************************************************************************************/
    virtual void SetMargins(const Margins& p_newMarginSizes) = 0;

    /******************************************************************************************//**
     * @brief Sets a tooltip.
     *
     * @param p_tooltipContents
     *      The text to appear inside the tooltip.
     *
     *********************************************************************************************/
    virtual void SetTooltip(const std::string& p_tooltipContents) = 0;

///@}

};

} // namespace cxgui

#endif // IWIDGET_H_845C70A7_65F2_4B7C_8446_A11ED3BC31E8
