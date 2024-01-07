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
 * @file ISignal.h
 * @date 2024
 *
 *************************************************************************************************/

#ifndef ISIGNAL_H_8B7B8C55_0270_4508_9512_C441816FBCAE
#define ISIGNAL_H_8B7B8C55_0270_4508_9512_C441816FBCAE

#include <functional>
#include <memory>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Connexion between a signal and a signal handler.
 *
 * When a signal handler is "connected" to a signal, it means that when the signal is triggered,
 * the connected signal handler will be executed.
 *
 * @see cxgui::ISignal
 *
 *************************************************************************************************/
class IConnection
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~IConnection() = default;

    /******************************************************************************************//**
     * @brief Indicates if the connexion is valid.
     *
     * A connexion is valid if a signal has been bound to a handler.
     *
     *********************************************************************************************/
    [[nodiscard]] virtual bool IsConnected() const = 0;

    /******************************************************************************************//**
     * @brief Destroys the connexion between the signal and the signal handler.
     *
     * After calling this, triggering the signal will no longer call the signal handler that
     * was previously connected to it.
     *
     *********************************************************************************************/
    virtual void Disconnect() = 0;

};

/**********************************************************************************************//**
 * @brief Signal triggered by widgets or other elements related to the user interface.
 *
 * Every signal can be connected to a signal handler (aka a slot) that will be executed when
 * the signal is triggered.
 *
 * @tparam ReturnType
 *      The associated signal handler's return type.
 * @tparam Arguments
 *      The associated signal handler's arguments' types.
 *
 * @see cxgui::IConnection
 *
 *************************************************************************************************/
template<typename ReturnType, typename... Arguments>
class ISignal
{

public:

    /******************************************************************************************//**
     * @brief Destructor.
     *
     *********************************************************************************************/
    virtual ~ISignal() = default;

    /******************************************************************************************//**
     * @brief Connects a signal handler to the signal.
     *
     * @param p_slot
     *      The signal handler that will be executed every time the signal is triggered.
     *
     * @return
     *      The connection between the signal and the signal handler.
     *
     *********************************************************************************************/
    virtual std::unique_ptr<IConnection> Connect(const std::function<ReturnType(Arguments...)>& p_slot) = 0;

};

} // namespace cxgui

#endif // ISIGNAL_H_8B7B8C55_0270_4508_9512_C441816FBCAE
