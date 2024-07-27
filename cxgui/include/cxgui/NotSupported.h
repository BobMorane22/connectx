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
 * @file NoSupported.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef NOTSUPPORTED_H_1D4D06A8_C263_42FA_A117_3DDD243AEAF2
#define NOTSUPPORTED_H_1D4D06A8_C263_42FA_A117_3DDD243AEAF2

#include <cxinv/assertion.h>
#include <cxgui/ISignal.h>

namespace cx::cmn::ui
{

/**********************************************************************************************//**
 * @brief Indicates a signal is not supported by some widget.
 *
 * Some widgets do not support specific signals. This specific implementation does nothing and
 * returns a closed connection, with which nothing is possible. When connecting to this signal,
 * an assertion automatically fails to notify the programmer.
 *
 * @warning
 *      This class should be used with care. In fact, in the best possible scenario, it would
 *      not be necessary. Whenever using this in a newly design widget, ask yourself if what
 *      you design really is a widget. Most of the time you will find it is not.
 *
 *************************************************************************************************/
template<typename ReturnType, typename... Arguments>
class NotSupported : public ISignal<ReturnType, Arguments...>
{

public:

    /******************************************************************************************//**
     * @brief Connect to the signal.
     *
     * @warning
     *      Calling this raises an assertion.
     *
     * @param p_slot
     *      The slot to connect to the signal (unused).
     *
     * @return
     *      A closed connection.
     *
     *********************************************************************************************/
    std::unique_ptr<IConnection> Connect(const std::function<ReturnType(Arguments...)>& /*p_slot*/) override
    {
        ASSERT_ERROR_MSG("Un supported signal for this widget");
        return std::make_unique<ClosedConnection>();
    }

private:

    /**********************************************************************************************
     * @brief A closed connection.
     *
     *********************************************************************************************/
    class ClosedConnection : public IConnection
    {

    public:

        [[nodiscard]] virtual bool IsConnected() const override {return false;};
        void Disconnect() override {};
    };

};

} // namespace cx::cmn::ui

#endif // NOTSUPPORTED_H_1D4D06A8_C263_42FA_A117_3DDD243AEAF2
