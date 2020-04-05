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
 * @file DisableStdStreamsRAII.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include "DisableStdStreamsRAII.h"

#include <iostream>


DisableStdStreamsRAII::DisableStdStreamsRAII()
 : m_stdOutBufferContents{std::cout.rdbuf()}
 , m_stdErrBufferContents{std::cerr.rdbuf()}
{
    DisableStdOut();
    DisableStdErr();
}

DisableStdStreamsRAII::~DisableStdStreamsRAII()
{
    EnableStdOut();
    EnableStdErr();
}

void DisableStdStreamsRAII::DisableStdOut()
{
    std::cout.rdbuf(m_stdOutBuffer.rdbuf());
}

void DisableStdStreamsRAII::EnableStdOut()
{
    std::cout.rdbuf(m_stdOutBufferContents);
}

void DisableStdStreamsRAII::DisableStdErr()
{
    std::cerr.rdbuf(m_stdErrBuffer.rdbuf());
}

void DisableStdStreamsRAII::EnableStdErr()
{
    std::cerr.rdbuf(m_stdErrBufferContents);
}

std::string DisableStdStreamsRAII::GetStdOutContents() const
{
    return m_stdOutBuffer.str();
}

std::string DisableStdStreamsRAII::GetStdErrContents() const
{
    return m_stdErrBuffer.str();
}
