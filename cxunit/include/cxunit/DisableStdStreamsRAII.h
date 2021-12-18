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

#ifndef DISABLESTDSTREAMSRAII_H_96B3CE7F_EAD5_42AF_9745_53ADE74A7697
#define DISABLESTDSTREAMSRAII_H_96B3CE7F_EAD5_42AF_9745_53ADE74A7697

#include <gtest/gtest.h>

#include <sstream>

namespace cxunit
{

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

/*************************************************************************************************
 * @brief Test assertions occured.
 *
 * Assertions types are defined in cxinv. In release, this does nothing.
 *
 * @param p_streamRedirector
 *      A stream redirector. This class must implement the `GetStdErrContents` method. As
 *      defined in `cxunit::DisableStdStreamsRAII`.
 * @param p_assertionKeyword
 *      The string differentiating assertion types in the standard error stream.
 *
 * @see cxinv/assertion.h.
 *
 ************************************************************************************************/
#ifndef NDEBUG
#define ASSERT_ASSERTION_FAILED_IMPL(p_streamRedirector, p_assertionKeyword)         \
    {                                                                                \
        const std::string streamContents = (p_streamRedirector).GetStdErrContents(); \
        ASSERT_TRUE(streamContents.find(p_assertionKeyword) != std::string::npos);   \
    }                                                                      
#else
#define ASSERT_ASSERTION_FAILED_IMPL(p_streamRedirector, p_assertionKeyword) ASSERT_TRUE(true);
#endif

/*********************************************************************************************//**
 * @brief Test an assertion failed.
 *
 * In release, this does nothing.
 *
 * @param p_streamRedirector
 *      A stream redirector. This class must implement the `GetStdErrContents` method. As
 *      defined in `cxunit::DisableStdStreamsRAII`.
 *
 ************************************************************************************************/
#define ASSERT_ASSERTION_FAILED(p_streamRedirector) ASSERT_ASSERTION_FAILED_IMPL(p_streamRedirector, "Assertion")

/*********************************************************************************************//**
 * @brief Test a precondition failed.
 *
 * In release, this does nothing.
 *
 * @param p_streamRedirector
 *      A stream redirector. This class must implement the `GetStdErrContents` method. As
 *      defined in `cxunit::DisableStdStreamsRAII`.
 *
 ************************************************************************************************/
#define ASSERT_PRECONDITION_FAILED(p_streamRedirector) ASSERT_ASSERTION_FAILED_IMPL(p_streamRedirector, "Precondition")

/*********************************************************************************************//**
 * @brief Test a postcondition failed.
 *
 * In release, this does nothing.
 *
 * @param p_streamRedirector
 *      A stream redirector. This class must implement the `GetStdErrContents` method. As
 *      defined in `cxunit::DisableStdStreamsRAII`.
 *
 ************************************************************************************************/
#define ASSERT_POSTCONDITION_FAILED(p_streamRedirector) ASSERT_ASSERTION_FAILED_IMPL(p_streamRedirector, "Postcondition")

/*********************************************************************************************//**
 * @brief Test an invariant failed.
 *
 * In release, this does nothing.
 *
 * @param p_streamRedirector
 *      A stream redirector. This class must implement the `GetStdErrContents` method. As
 *      defined in `cxunit::DisableStdStreamsRAII`.
 *
 ************************************************************************************************/
#define ASSERT_INVARIANT_FAILED(p_streamRedirector) ASSERT_ASSERTION_FAILED_IMPL(p_streamRedirector, "Invariant")

} // cxunit

#endif // DISABLESTDSTREAMSRAII_H_96B3CE7F_EAD5_42AF_9745_53ADE74A7697
