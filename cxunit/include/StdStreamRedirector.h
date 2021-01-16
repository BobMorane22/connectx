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
 *  - `MyFixtureNoStreamRedirector` (equivalent to `MyFixture`).
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
 * @brief Standard stream redirector.
 *
 * In this scenario, nothing gets redirected. The created class is essentially the test
 * fixture itself, with no possible redirection.
 *
 * @tparam T The redirected class (not that is must be a test fixture to compile).
 * @tparam R The redirection scenario (`Redirection::NONE` in this case).
 *
 ************************************************************************************************/
template <typename T, Redirection R>
class StdStreamRedirector : public T
{
    static_assert(std::is_base_of_v<::testing::Test, T>);
};

/*********************************************************************************************//**
 * @brief Standard stream redirector.
 *
 * In this scenario, the standard output (STDOUT) gets redirected, but not the standard error
 * output. The created class is essentially the test with an additionnal redirection method.
 * The class acts as an RAII and streams are automatically redirected.
 *
 * @tparam T The redirected class (not that is must be a test fixture to compile).
 * @tparam R The redirection scenario (`Redirection::STDOUT` in this case).
 *
 ************************************************************************************************/
template <typename T>
class StdStreamRedirector<T, Redirection::STDOUT> : public T
{
    static_assert(std::is_base_of_v<::testing::Test, T>);

public:

    std::string GetStdOutContents() const {return m_raii.GetStdOutContents();}

private:

    DisableStdStreamsRAII m_raii;

};

/*********************************************************************************************//**
 * @brief Standard stream redirector.
 *
 * In this scenario, the standard error output (STDERR) gets redirected, but not the standard
 * output. The created class is essentially the test with an additionnal redirection method.
 * The class acts as an RAII and streams are automatically redirected.
 *
 * @tparam T The redirected class (not that is must be a test fixture to compile).
 * @tparam R The redirection scenario (`Redirection::STDERR` in this case).
 *
 ************************************************************************************************/
template <typename T>
class StdStreamRedirector<T, Redirection::STDERR> : public T
{
    static_assert(std::is_base_of_v<::testing::Test, T>);

public:

    std::string GetStdErrContents() const {return m_raii.GetStdErrContents();}

private:

    DisableStdStreamsRAII m_raii;

};

/*********************************************************************************************//**
 * @brief Standard stream redirector.
 *
 * In this scenario, both standard outputs (STOUT and STDERR) are redirected. The created class
 * is essentially the test with two additionnal redirection methods. The class acts as an RAII
 * and streams are automatically redirected. 
 *
 * @tparam T The redirected class (not that is must be a test fixture to compile).
 * @tparam R The redirection scenario (`Redirection::STDERR` in this case).
 *
 ************************************************************************************************/
template <typename T>
class StdStreamRedirector<T, Redirection::BOTH> : public T
{
    static_assert(std::is_base_of_v<::testing::Test, T>);

public:

    std::string GetStdOutContents() const {return m_raii.GetStdOutContents();}
    std::string GetStdErrContents() const {return m_raii.GetStdErrContents();}

private:

    DisableStdStreamsRAII m_raii;

};

} // namespace cxunit

#endif // STDSTREAMREDIRECTOR_H_427CDDDB_A0AD_4B25_A294_D6805EC6F06D
