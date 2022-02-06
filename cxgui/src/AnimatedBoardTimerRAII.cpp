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
 * @file AnimatedBoardTimerRAII.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>

#include <cxgui/AnimatedBoardTimerRAII.h>

cxgui::AnimatedBoardTimerRAII::AnimatedBoardTimer::AnimatedBoardTimer()
: m_period{Period{1000.0}}
{
}

void cxgui::AnimatedBoardTimerRAII::AnimatedBoardTimer::SetCallback(Callback&& p_callback)
{
    IF_PRECONDITION_NOT_MET_DO(bool(p_callback), return;);

    m_callback = std::move(p_callback);
}

void cxgui::AnimatedBoardTimerRAII::AnimatedBoardTimer::SetPeriod(Period&& p_period)
{
    IF_PRECONDITION_NOT_MET_DO(p_period.Get() > 0.0, return;);

    m_period = std::move(p_period);
}

void cxgui::AnimatedBoardTimerRAII::AnimatedBoardTimer::Start()
{
    IF_PRECONDITION_NOT_MET_DO(bool(m_callback), return;);
    IF_PRECONDITION_NOT_MET_DO(m_period.Get() > 0.0, return;);

    m_timer = Glib::signal_timeout().connect(m_callback, m_period.Get());
}

void cxgui::AnimatedBoardTimerRAII::AnimatedBoardTimer::Stop()
{
    m_timer.disconnect();
}

cxgui::AnimatedBoardTimerRAII::AnimatedBoardTimerRAII(ITimer::Callback&& p_callback, Period&& p_period)
{
    PRECONDITION(bool(p_callback));
    PRECONDITION(p_period.Get() > 0.0);

    m_animatedBoardTimer = std::make_unique<AnimatedBoardTimer>();

    m_animatedBoardTimer->SetCallback(std::move(p_callback));
    m_animatedBoardTimer->SetPeriod(std::move(p_period));

    m_animatedBoardTimer->Start();
}

cxgui::AnimatedBoardTimerRAII::~AnimatedBoardTimerRAII()
{
    m_animatedBoardTimer->Stop();
}
