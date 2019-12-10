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
 * @file IMainWindow.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef IMAINWINDOW_H_87FB17B9_ABA6_42D6_8B00_1B898BCD3C94
#define IMAINWINDOW_H_87FB17B9_ABA6_42D6_8B00_1B898BCD3C94

namespace cxgui
{

/*********************************************************************************************//**
 * @brief DESCRIPTION
 *
 * @invariant
 * @invariant
 *
 * DESCRIPTION
 *
 ************************************************************************************************/
class IMainWindow
{

public:

    virtual ~IMainWindow() = default;

    virtual int Show() = 0;

};

} // namespace cxgui

#endif // IMAINWINDOW_H_87FB17B9_ABA6_42D6_8B00_1B898BCD3C94
