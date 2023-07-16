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
 * @file ILayout.h
 * @date 2023
 *
 *************************************************************************************************/
 #pragma once

class IButton;
class IEditBox;

/**************************************************************************************************
 * Widgets layout.
 *
 *************************************************************************************************/
class ILayout
{

public:

    virtual ~ILayout() = default;

    virtual void Attach(IButton& p_button, int p_left, int p_top) = 0;
    virtual void Attach(IEditBox& p_editBox, int p_left, int p_top) = 0;

};
