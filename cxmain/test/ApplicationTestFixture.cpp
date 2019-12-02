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
 * @file ApplicationTestFixture.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <iostream>

#include <ApplicationTestFixture.h>

ApplicationTestFixture::ApplicationTestFixture()
 : m_stdOutBufferContents{std::cout.rdbuf()}
 , m_stdErrBufferContents{std::cerr.rdbuf()}
{
    DisableStdOut();
    DisableStdErr();
}

ApplicationTestFixture::~ApplicationTestFixture()
{
    EnableStdOut();
    EnableStdErr();
}

void ApplicationTestFixture::DisableStdOut()
{
    std::cout.rdbuf(m_stdOutBuffer.rdbuf());
}

void ApplicationTestFixture::EnableStdOut()
{
    std::cout.rdbuf(m_stdOutBufferContents);
}

void ApplicationTestFixture::DisableStdErr()
{
    std::cerr.rdbuf(m_stdErrBuffer.rdbuf());
}

void ApplicationTestFixture::EnableStdErr()
{
    std::cerr.rdbuf(m_stdErrBufferContents);
}
