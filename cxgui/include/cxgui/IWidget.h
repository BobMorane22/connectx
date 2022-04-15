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
 * @file IWidget.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef IWIDGET_H_845C70A7_65F2_4B7C_8446_A11ED3BC31E8
#define IWIDGET_H_845C70A7_65F2_4B7C_8446_A11ED3BC31E8

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Interface aggrating services common to all widgets.
 *
 *************************************************************************************************/
class IWidget
{

public:

    ~IWidget() = default;

    [[nodiscard]] virtual size_t GetWidth() const = 0;
    [[nodiscard]] virtual size_t GetHeight() const = 0;

};

} // namespace cxgui

#endif // IWIDGET_H_845C70A7_65F2_4B7C_8446_A11ED3BC31E8
