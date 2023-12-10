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
* @file ISpinBox.h
* @date 2023
*
*************************************************************************************************/

#ifndef SPINBOX_H_C1FF0482_BE33_4283_ADB6_3DB5FA8445D7
#define SPINBOX_H_C1FF0482_BE33_4283_ADB6_3DB5FA8445D7

#include <cxstd/StrongType.h>
#include <cxgui/IWidget.h>

namespace cxgui
{

/**********************************************************************************************//**
* @brief Edit box decorated with spin buttons.
*
* @warning
*      Only integer types are supported.
*
*************************************************************************************************/
class ISpinBox : public cxgui::IWidget
{

public:

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override = 0;
    [[nodiscard]] size_t GetHeight() const override = 0;
    void SetEnabled(EnabledState p_enabled) override = 0;
    void SetMargins(const Margins& p_newMarginSizes) override = 0;
    
public:
    
    /******************************************************************************************//**
    * @brief Climb rate for the value in a spin box.
    *
    * When the spin box arrows are hit, the value present in the spinbox is incremented
    * (or decremented) by the climb rate.
    *
    *********************************************************************************************/
    using ClimbRate = cxstd::StrongType<int, struct ClimbRateTag>;

    /******************************************************************************************//**
    * @brief Minimum allowed value in a spin box.
    *
    *********************************************************************************************/
    using Minimum = cxstd::StrongType<int, struct MinumumTag, cxstd::Comparable>;

    /******************************************************************************************//**
    * @brief Maximum allowed value in a spin box.
    *
    *********************************************************************************************/
    using Maximum = cxstd::StrongType<int, struct MaximumTag, cxstd::Comparable>;

    /******************************************************************************************//**
    * @brief Range of values allowed in a spin box.
    *
    *********************************************************************************************/
    struct Range
    {
        /**************************************************************************************//**
        * @brief Constructor.
        *
        * @param p_min
        *      The minimum value allowed for the spin box.
        * @param p_max
        *      The maximum value allowed for the spin box.
        *
        * @pre
        *      The maximum value is strictly greater than the minimum value.
        * @post
        *      The range has a upper limit which is strictly greater than its lower limit.
        *
        *****************************************************************************************/
        Range(const Minimum& p_min, const Maximum& p_max);

        ///< The range lower limit.
        Minimum m_min;

        ///< The range upper limit.
        Maximum m_max;
    };

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     *********************************************************************************************/
    virtual ~ISpinBox() = default;

    /******************************************************************************************//**
     * @brief Get the selected numerical value.
     *
     * @return The selected numerical value.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual int GetValue() const = 0;
};

} // namespace cxgui

#endif // SPINBOX_H_C1FF0482_BE33_4283_ADB6_3DB5FA8445D7
