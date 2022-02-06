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
 * @file ITimer.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ITIMER_H_D383D25B_7FDA_4258_8982_960691C534E8
#define ITIMER_H_D383D25B_7FDA_4258_8982_960691C534E8

#include <functional>

#include <cxstd/StrongType.h>

namespace cxgui
{

/**********************************************************************************************//**
 * @brief Period of time (in ms) between each of the timer ticks.
 *
 *************************************************************************************************/
using Period = cxstd::StrongType<double, struct PeriodTag>;

/**********************************************************************************************//**
 * @brief A timer interface.
 *
 * Every specified period of time, the timer executes a specified callback. Once set up as
 * needed, the timer can then be started and stoped.
 *
 *************************************************************************************************/
class ITimer
{

public:

    /**********************************************************************************************//**
     * @brief Callback to be executed at every tick of the timer.
     *
     *************************************************************************************************/
    using Callback = std::function<bool()>;    

    /**********************************************************************************************//**
     * @brief Destructor.
     *
     *************************************************************************************************/
    virtual ~ITimer() = default;

    /**********************************************************************************************//**
     * @brief Sets a callback to be executed at every tick of the timer.
     *
     * The timer must be stopped and started again for the new callback to take effect.
     *
     * @param p_callback The callback to be executed at every tick of the timer.
     *
     *************************************************************************************************/
    virtual void SetCallback(Callback&& p_callback) = 0;

    /**********************************************************************************************//**
     * @brief Sets the period of time (in ms) in between each timer tick.
     *
     * The timer must be stopped and started again for the new period to take effect.
     *
     * @param p_period The period of time (in ms) in between each timer tick.
     *
     *************************************************************************************************/
    virtual void SetPeriod(Period&& p_period) = 0;

    /**********************************************************************************************//**
     * @brief Starts the timer.
     *
     * Once this is called, the registered callback function is called at every period of time.
     *
     *************************************************************************************************/
    virtual void Start() = 0;

    /**********************************************************************************************//**
     * @brief Stops the timer.
     *
     * Once this is called, the registered callback is not called again.
     *
     *************************************************************************************************/
    virtual void Stop() = 0;

};

} // namespace cxgui

#endif // ITIMER_H_D383D25B_7FDA_4258_8982_960691C534E8
