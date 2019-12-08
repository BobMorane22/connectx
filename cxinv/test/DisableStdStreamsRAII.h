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
 * @file DisableStdStreamsRAII.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef DISABLESTDSTREAMSRAII_H_FCB7CC7C_606B_4076_BEA5_A68168F20EF8
#define DISABLESTDSTREAMSRAII_H_FCB7CC7C_606B_4076_BEA5_A68168F20EF8

#include <sstream>

/*********************************************************************************************//**
 * @brief Disable/enable @c stdout and @c stderr.
 *
 * At construction, both streams are redirected to an @c std::stringstream (e.g. nothing gets
 * printed to the console). At destruction, both streams are redirected back to their original
 * targets. Use this class as a data member to either disable streaming to the console, or
 * to access the streaming data in a @c std::string (e.g. for testing).
 *
 ************************************************************************************************/
class DisableStdStreamsRAII final
{

public:

    DisableStdStreamsRAII();
    ~DisableStdStreamsRAII();

    void DisableStdOut();
    void EnableStdOut();
    void DisableStdErr();
    void EnableStdErr();

    std::string GetStdOutContents() const;
    std::string GetStdErrContents() const;


private:

    std::stringstream m_stdOutBuffer;
    std::streambuf *m_stdOutBufferContents;

    std::stringstream m_stdErrBuffer;
    std::streambuf *m_stdErrBufferContents;

};

#endif // DISABLESTDSTREAMSRAII_H_FCB7CC7C_606B_4076_BEA5_A68168F20EF8
