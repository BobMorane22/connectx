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
 * @file AnimatedBoardTimerRAII.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef ANIMATEDBOARDTIMERRAII_H_059D3527_FB5A_4FF2_9A36_2786BDA81BDC
#define ANIMATEDBOARDTIMERRAII_H_059D3527_FB5A_4FF2_9A36_2786BDA81BDC

#include <memory>

#include <glibmm/main.h>

#include "ITimer.h"

namespace cxgui
{

/**********************************************************************************************//**
 * @brief A RAII for the animated board frame drawing timer.
 *
 * With this RAII, the timer is automatically started at creation and stopped at destruction.
 *
 *************************************************************************************************/
class AnimatedBoardTimerRAII
{

public:

    /**********************************************************************************************//**
     * @brief Constrcutor.
     *
     * Starts the underlying time with the speficied callback and period. The timer will
     * run for the lifetime of this RAII.
     *
     * @param p_callback
     *      The callback to be executed at every tick of the timer.
     * @param p_period
     *      The period of time (in ms) in between each timer tick.
     *
     * @pre
     *      The callback function is valid.
     * @pre
     *      The period is greater than 0 ms.
     *
     *************************************************************************************************/
    AnimatedBoardTimerRAII(ITimer::Callback&& p_callback, Period&& p_period);

    /**********************************************************************************************//**
     * @brief Destructor.
     *
     * Stops the underlying timer.
     *
     *************************************************************************************************/
    ~AnimatedBoardTimerRAII();

private:

    // Specific implementation of a timer using the Glib technology.
    // This timer is used specifically in the animations of the game
    // board, for frames drawing.
    class AnimatedBoardTimer : public ITimer
    {

    public:

        AnimatedBoardTimer();

        void SetCallback(Callback&& p_callback) override;
        void SetPeriod(Period&& p_period) override;

        void Start() override;
        void Stop() override;

    private:

        ITimer::Callback m_callback;
        Period m_period;
        sigc::connection m_timer;
    };

    std::unique_ptr<ITimer> m_animatedBoardTimer;

};

} // namespace cxgui

#endif // ANIMATEDBOARDTIMERRAII_H_059D3527_FB5A_4FF2_9A36_2786BDA81BDC
