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
 * @file IGtkmmBackend.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef IGTKMMBACKEND_H_102853A0_F3CA_49FF_8458_92A0F06A7E5E

namespace Gtk
{
    class Widget;
}

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Interface for Gtkmm wrapped widgets.
 *
 * The interface gives access to the underlying Gtkmm type. Use with caution! This is meant to
 * be a temporary "fix" until a complete widget abstraction has been put in place.
 *
 * @tparam GtkmmWidget The underlying Gtkmm widget type.
 *
 *************************************************************************************************/
template<typename GtkmmWidget>
class IGtkmmBackend
{

public:

    /******************************************************************************************//**
     * @brief Default destructor.
     *
     *********************************************************************************************/
    virtual ~IGtkmmBackend() = default;

    /******************************************************************************************//**
     * @brief Underlying Gtkmm instance accessor (non-const).
     *
     * @return The underlying Gtkmm instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual GtkmmWidget& GetUnderlying() = 0;

    /******************************************************************************************//**
     * @brief Underlying Gtkmm instance accessor (const).
     *
     * @return The underlying Gtkmm instance.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual const GtkmmWidget& GetUnderlying() const = 0;

};

} // namespace cxgui

#define IGTKMMBACKEND_H_102853A0_F3CA_49FF_8458_92A0F06A7E5E
#endif // IGTKMMBACKEND_H_102853A0_F3CA_49FF_8458_92A0F06A7E5E
