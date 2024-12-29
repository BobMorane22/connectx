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
 * @file Connection.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef GTKMM3CONNECTION_H_3A2FD5EA_6019_469D_AF00_EAD02B3C68E7
#define GTKMM3CONNECTION_H_3A2FD5EA_6019_469D_AF00_EAD02B3C68E7

#include <cxcmnui/ISignal.h>

#include <sigc++/connection.h>

namespace cx::cmn::ui::gtkmm3
{

/**********************************************************************************************//**
 * @brief Gtkmm 3 implementation of the `cx::cmn::ui::gtkmm3::IConnection` interface.
 *
 *************************************************************************************************/
class Connection : public IConnection
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_connection
     *      The underlying sigc connection.
     *
     *********************************************************************************************/
    explicit Connection(const sigc::connection& p_connection)
    : m_connection{p_connection}
    {
    }

    // cx::cmn::ui::IConnection.
    [[nodiscard]] bool IsConnected() const override
    {
        return m_connection.connected();
    }

    void Disconnect() override
    {
        m_connection.disconnect();
    }

private:

    sigc::connection m_connection;

};

} // namespace cx::cmn::ui::gtkmm3

#endif // GTKMM3CONNECTION_H_3A2FD5EA_6019_469D_AF00_EAD02B3C68E7
