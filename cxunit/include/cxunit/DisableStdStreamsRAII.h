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
 * @brief Disable/enable stdout and stderr.
 *
 * Redirects both streams (i.e. stdout and stderr) to some internal storage. Their contents
 * are made available as a `std::string` so that they can be inspected during testing. Upon
 * destruction, both streams are redirected back to their original targets.
 *
 ************************************************************************************************/
class DisableStdStreamsRAII final
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * Redirects the standard and error streams (i.e stdout and stderr) to some buffer.
     *
     *********************************************************************************************/
    DisableStdStreamsRAII();

    /******************************************************************************************//**
     * @brief Destructor.
     *
     * Redirects the standard and error streams (i.e stdout and stderr) back to their original
     * targets.
     *
     *********************************************************************************************/
    ~DisableStdStreamsRAII();

    /******************************************************************************************//**
     * @brief Explicitely disable stdout.
     *
     * Contents printed to stdout will then be captured in some internal buffer and become
     * available during testing.
     *
     *********************************************************************************************/
    void DisableStdOut();

    /******************************************************************************************//**
     * @brief Explicitely enable stdout.
     *
     * This will deactivate stdout redirection. The stream will then behave as it does normally.
     * This is useful if you only want to capture stderr.
     *
     *********************************************************************************************/
    void EnableStdOut();

    /******************************************************************************************//**
     * @brief Explicitely disable stderr.
     *
     * Contents printed to stderr will then be captured in some internal buffer and become
     * available during testing.
     *
     *********************************************************************************************/
    void DisableStdErr();

    /******************************************************************************************//**
     * @brief Explicitely enable stderr.
     *
     * This will deactivate stderr redirection. The stream will then behave as it does normally.
     * This is useful if you only want to capture stdout.
     *
     *********************************************************************************************/
    void EnableStdErr();

    /******************************************************************************************//**
     * @brief Gets the redirected stdout content.
     *
     * @return A string with the contents of stdout since it was redirected.
     *
     *********************************************************************************************/
    std::string GetStdOutContents() const;

    /******************************************************************************************//**
     * @brief Gets the redirected stderr content.
     *
     * @return A string with the contents of stderr since it was redirected.
     *
     *********************************************************************************************/
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
