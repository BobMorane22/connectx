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
 * @file StdStreamRedirector.h
 * @date 2021
 *
 * Wrapper classes for test fixtures that add the possibility to redirect output streams.
 *
 *************************************************************************************************/

#ifndef STDSTREAMREDIRECTOR_H_427CDDDB_A0AD_4B25_A294_D6805EC6F06D
#define STDSTREAMREDIRECTOR_H_427CDDDB_A0AD_4B25_A294_D6805EC6F06D

#include <type_traits>

#include <gtest/gtest.h>

#include "DisableStdStreamsRAII.h"

/*********************************************************************************************//**
 * @brief Generates aliases for all redirection scenarios.
 *
 * For a fixture class name `MyFixture`, the following aliases are created:
 *
 *  - `MyFixtureNoStreamRedirector`     : equivalent to `MyFixture`.
 *  - `MyFixtureStdOutStreamRedirector` : use this alias to redirect STDOUT only.
 *  - `MyFixtureStdErrStreamRedirector` : use this alias to redirect STDERR only.
 *  - `MyFixtureBothStreamsRedirector`  : use this alias to redirect both STDOUT and STDERR.
 *
 * @param p_fixtureClassName The test fixture class name.
 *
 ************************************************************************************************/
#define ADD_STREAM_REDIRECTORS(p_fixtureClassName)                                                                                \
    using p_fixtureClassName##NoStreamRedirector     = cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::NONE>;   \
    using p_fixtureClassName##StdOutStreamRedirector = cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::STDOUT>; \
    using p_fixtureClassName##StdErrStreamRedirector = cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::STDERR>; \
    using p_fixtureClassName##BothStreamsRedirector  = cxunit::StdStreamRedirector<StdStreamWriter, cxunit::Redirection::BOTH>


namespace cxunit
{

/*********************************************************************************************//**
 * @brief Possible standard stream redirection scenarios.
 *
 ************************************************************************************************/
enum class Redirection
{
    NONE,
    STDOUT,
    STDERR,
    BOTH,
};

/*********************************************************************************************//**
 * @brief Automatically redirect outputs.
 *
 * For a test fixture `T`, adds specific streams redirection according to a specified scenario.
 * Using this, the user can add stream redirection, for his/her fixture `T`, only for the needed
 * stream. For example, only STDERR could be redirected and STDOUT left untouched.
 *
 * @note Instances of this should only be declared via the `ADD_STREAM_REDIRECTORS` macro (see above).
 * @note Will only compile for test fixtures.
 *
 * @tparam T The test fixture.
 * @tparam R The redirection scenario.
 *
 ************************************************************************************************/
template <typename T, Redirection R>
class StdStreamRedirector : public T
{

public:

    /*****************************************************************************************//**
     * @brief Constructor.
     *
     * Since the stream redirector member is an RAII, all streams are redirected by default
     * for any scenario. The job of this constructor is to re-enable specific streams (if
     * needed) according to the chosen scenario.
     *
     ********************************************************************************************/
    StdStreamRedirector()
    {
        if constexpr(R == Redirection::NONE)
        {
            m_raii.EnableStdOut();
            m_raii.EnableStdErr();
        }
        else if(R == Redirection::STDOUT)
        {
            m_raii.EnableStdErr();
        }
        else if(R == Redirection::STDERR)
        {
            m_raii.EnableStdOut();
        }
    }

    /*****************************************************************************************//**
     * @brief Gets the redirected STDOUT contents as a string.
     *
     * Only available for the `Redirection::STDOUT` and `Redirection::BOTH` scenarios.
     *
     ********************************************************************************************/
    template<
        Redirection Q = R,
        typename = std::enable_if_t<(Q == Redirection::STDOUT || Q == Redirection::BOTH)>
    >
    std::string GetStdOutContents() const
    {
        return m_raii.GetStdOutContents();
    }

    /*****************************************************************************************//**
     * @brief Gets the redirected STDERR contents as a string.
     *
     * Only available for the `Redirection::STDERR` and `Redirection::BOTH` scenarios.
     *
     ********************************************************************************************/
    template<
        Redirection Q = R,
        typename = std::enable_if_t<(Q == Redirection::STDERR || Q == Redirection::BOTH)>
    >
    std::string GetStdErrContents() const
    {
        return m_raii.GetStdErrContents();
    }

private:

    static_assert(std::is_base_of_v<::testing::Test, T>);

    DisableStdStreamsRAII m_raii;

};

} // namespace cxunit

#endif // STDSTREAMREDIRECTOR_H_427CDDDB_A0AD_4B25_A294_D6805EC6F06D
