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
 * @file assertion.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef ASSERTION_H_0470D299_880C_415F_BEE0_57ED14327B58
#define ASSERTION_H_0470D299_880C_415F_BEE0_57ED14327B58

#include <memory>

#ifndef NDEBUG
namespace cxinv
{

/*********************************************************************************************//**
 * @private
 *
 * @brief Assertion label types.
 *
 * Defines different label (i.e. 'kinds') of assertions.
 *
 ************************************************************************************************/
enum class AssertLabel
{
    /** A classic runtime assertion. */
    ASSERTION,

    /** A function/method precondition. Must be respected to ensure adequate function/method
        execution. If the preconditions are not respected, the function/method behavior is
        undefined. */
    PRECONDITION,

    /** A function/method postcondition. Must hold if the preconditions hold. */
    POSTCONDITION,

    /** A class invariant. Must hold for some instance as long as it is alive. */
    INVARIANT,
};

/*********************************************************************************************//**
 * @private
 *
 * @brief Handles assertions of various types.
 *
 * Handles assertions of various types by formatting a proper error message and aborting, if
 * needed. Never call this function directly, but always through the appropriate assertion
 * macros.
 *
 * @param p_label
 *      The assertion label. This defines what kind of assertion is treated.
 * @param p_conditionRes
 *      The logical condition that is asserted.
 * @param p_conditionExpr
 *      The logical expression (as a readable C++ string) that is asserted.
 * @param p_fileName
 *      The file name into which the assertion is located.
 * @param p_functionName
 *      The function name into which the assertion is located.
 * @param p_lineNumber
 *      The line number at which the assertion is located.
 * @param p_message
 *      An optional assertion message.
 *
 * @return
 *      The result of evaluating p_conditionRes.
 *
 * @warning
 *      Never use this function by itself! Use assertion macros instead.
 *
 ************************************************************************************************/
bool HandleAssert(const AssertLabel p_label,
                  const bool        p_conditionRes,
                  const char*       p_conditionExpr,
                  const char*       p_fileName,
                  const char*       p_functionName,
                  const long        p_lineNumber,
                  const char*       p_message = nullptr);

/*********************************************************************************************//**
 * @private
 *
 * @brief Handles assertions of unique pointers.
 *
 * Handles assertions of various types by formatting a proper error message and aborting, if
 * needed. Never call this function directly, but always through the appropriate assertion
 * macros.
 *
 * @tparam T
 *      The underlying pointer type.
 *
 * @param p_label
 *      The assertion label. This defines what kind of assertion is treated.
 * @param p_ptrRes
 *      The unique pointer that is asserted (i.e. checked for null).
 * @param p_conditionExpr
 *      The logical expression (as a readable C++ string) that is asserted.
 * @param p_fileName
 *      The file name into which the assertion is located.
 * @param p_functionName
 *      The function name into which the assertion is located.
 * @param p_lineNumber
 *      The line number at which the assertion is located.
 * @param p_message
 *      An optional assertion message.
 *
 * @return
 *      The result of evaluating p_conditionRes.
 *
 * @warning
 *      Never use this function by itself! Use assertion macros instead.
 *
 ************************************************************************************************/
template<typename T>
bool HandleAssert(const AssertLabel         p_label,
                  const std::unique_ptr<T>& p_ptrRes,
                  const char*               p_conditionExpr,
                  const char*               p_fileName,
                  const char*               p_functionName,
                  const long                p_lineNumber,
                  const char*               p_message = nullptr)
{
    return HandleAssert(p_label,
                        p_ptrRes != nullptr,
                        p_conditionExpr,
                        p_fileName,
                        p_functionName,
                        p_lineNumber,
                        p_message);
}

/*********************************************************************************************//**
 * @private
 *
 * @brief Handles assertions of various types.
 *
 * Handles assertions of various types by formatting a proper error message and aborting, if
 * needed. Never call this function directly, but always through the appropriate assertion
 * macros.
 *
 * @tparam T
 *      The underlying pointer type.
 *
 * @param p_label
 *      The assertion label. This defines what kind of assertion is treated.
 * @param p_ptrRes
 *      The shared pointer that is asserted (i.e. checked for null).
 * @param p_conditionExpr
 *      The logical expression (as a readable C++ string) that is asserted.
 * @param p_fileName
 *      The file name into which the assertion is located.
 * @param p_functionName
 *      The function name into which the assertion is located.
 * @param p_lineNumber
 *      The line number at which the assertion is located.
 * @param p_message
 *      An optional assertion message.
 *
 * @return
 *      The result of evaluating p_conditionRes.
 *
 * @warning
 *      Never use this function by itself! Use assertion macros instead.
 *
 ************************************************************************************************/
template<typename T>
bool HandleAssert(const AssertLabel         p_label,
                  const std::shared_ptr<T>& p_ptrRes,
                  const char*               p_conditionExpr,
                  const char*               p_fileName,
                  const char*               p_functionName,
                  const long                p_lineNumber,
                  const char*               p_message = nullptr)
{
    return HandleAssert(p_label,
                        p_ptrRes != nullptr,
                        p_conditionExpr,
                        p_fileName,
                        p_functionName,
                        p_lineNumber,
                        p_message);
}

} // namespace cxinv

#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup assertmacros
 *
 * @brief Standard assertion MACRO (no message attached)
 *
 * Asserts that `p_condition` is `true`. If you `#define` the `ABORT_ON_ERROR` flag, this
 * MACRO will also abort on a false condition.
 *
 * @param p_condition
 *      The condition to assert.
 *
 *************************************************************************************************/
#define ASSERT(p_condition) cxinv::HandleAssert(cxinv::AssertLabel::ASSERTION,  \
                                                static_cast<bool>(p_condition), \
                                                #p_condition,                   \
                                                __FILE__,                       \
                                                __FUNCTION__,                   \
                                                __LINE__,                       \
                                                nullptr                         \
                                                )
#else
#define ASSERT(p_condition) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup assertmacros
 *
 * @brief Standard assertion MACRO (with message attached)
 *
 * Asserts that `p_condition` is `true`. If you `#define` the `ABORT_ON_ERROR` flag, this
 * MACRO will also abort on a `false` condition. On assertion, a custom message defined by the
 * programmer will be printed out along with the assertion information.
 *
 * @param p_condition
 *      The condition to assert.
 * @param p_message
 *      The message to print.
 *
 *************************************************************************************************/
#define ASSERT_MSG(p_condition, p_message) cxinv::HandleAssert(cxinv::AssertLabel::ASSERTION,  \
                                                               static_cast<bool>(p_condition), \
                                                               #p_condition,                   \
                                                               __FILE__,                       \
                                                               __FUNCTION__,                   \
                                                               __LINE__,                       \
                                                               p_message                       \
                                                               )
#else
#define ASSERT_MSG(p_condition, p_message) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup assertmacros
 *
 * @brief Unconditional assertion MACRO (no message attached).
 *
 * Will assert unconditionally. Use this when you know something went wrong and an assertion
 * must occur. If you `#define` the `ABORT_ON_ERROR` flag, this MACRO will also abort.
 *
 *************************************************************************************************/
#define ASSERT_ERROR() ASSERT(false)
#else
#define ASSERT_ERROR() ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup assertmacros
 *
 * @brief Unconditional assertion MACRO (no message attached).
 *
 * Will assert unconditionally. Use this when you know something went wrong and an assertion
 * must occur. If you `#define` the `ABORT_ON_ERROR` flag, this MACRO will also abort.
 * On assertion, a custom message defined by the programmer will be printed out along with the
 * assertion information.
 *
 * @param p_message
 *      The message to print.
 *
 ************************************************************************************************/
#define ASSERT_ERROR_MSG(p_message) ASSERT_MSG(false, p_message)
#else
#define ASSERT_ERROR_MSG(p_message) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup assertmacros
 *
 * @brief Standard assertion MACRO (no message attached), inline version.
 *
 * Asserts that `p_condition` is `true`. If you `#define` the `ABORT_ON_ERROR` flag, this
 * MACRO will also abort on a `false` condition. When using this inline version, the checked
 * condition is also included in release builds, stripped of the assertion mechanism. This
 * is useful in `if` statements, for example.
 *
 * @param p_condition
 *      The condition to assert.
 *
 *************************************************************************************************/
#define INL_ASSERT(p_condition) cxinv::HandleAssert(cxinv::AssertLabel::ASSERTION,  \
                                                    static_cast<bool>(p_condition), \
                                                    #p_condition,                   \
                                                    __FILE__,                       \
                                                    __FUNCTION__,                   \
                                                    __LINE__,                       \
                                                    nullptr                         \
                                                    )
#else
#define INL_ASSERT(p_condition) (p_condition)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup contractmacros
 *
 * @brief Standard precondition MACRO.
 *
 * Asserts that `p_preCondition` is `true`. If you `#define` the `ABORT_ON_ERROR` flag, this
 * MACRO will also abort on a `false` condition.
 *
 * @param p_preCondition
 *      The precondition to assert.
 *
 ************************************************************************************************/
#define PRECONDITION(p_preCondition) cxinv::HandleAssert(cxinv::AssertLabel::PRECONDITION,  \
                                                         static_cast<bool>(p_preCondition), \
                                                         #p_preCondition,                   \
                                                         __FILE__,                          \
                                                         __FUNCTION__,                      \
                                                         __LINE__                           \
                                                         )
#else
#define PRECONDITION(p_preCondition) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup contractmacros
 *
 * @brief Standard precondition MACRO, inline version.
 *
 * Asserts that `p_preCondition` is ` true`. If you `#define` the `ABORT_ON_ERROR` flag,
 * this MACRO will also abort on a `false` condition. When using this inline version, the checked
 * condition is also included in release builds, stripped of the assertion mechanism. This
 * is useful in `if` statements, for example.
 *
 * @param p_preCondition
 *      The precondition to assert.
 *
 *************************************************************************************************/
#define INL_PRECONDITION(p_preCondition) cxinv::HandleAssert(cxinv::AssertLabel::PRECONDITION,  \
                                                             static_cast<bool>(p_preCondition), \
                                                             #p_preCondition,                   \
                                                             __FILE__,                          \
                                                             __FUNCTION__,                      \
                                                             __LINE__                           \
                                                             )
#else
#define INL_PRECONDITION(p_condition) (p_condition)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup contractmacros
 *
 * @brief Standard postcondition MACRO.
 *
 * Asserts that `p_postCondition` is `true`. If you `#define` the `ABORT_ON_ERROR` flag, this
 * MACRO will also abort on a `false` condition.
 *
 * @param p_postCondition
 *      The postcondition to assert.
 *
 ************************************************************************************************/
#define POSTCONDITION(p_postCondition) cxinv::HandleAssert(cxinv::AssertLabel::POSTCONDITION,  \
                                                           static_cast<bool>(p_postCondition), \
                                                           #p_postCondition,                   \
                                                           __FILE__,                           \
                                                           __FUNCTION__,                       \
                                                           __LINE__                            \
                                                           )
#else
#define POSTCONDITION(p_postCondition) ((void)0)
#endif // NDEBUG

#ifndef NDEBUG
/*********************************************************************************************//**
 * @ingroup contractmacros
 *
 * @brief Standard invariant MACRO.
 *
 * Asserts that `p_invariant` is `true`. If you `#define` the `ABORT_ON_ERROR` flag, this
 * MACRO will also abort on a `false` condition.
 *
 * @param p_invariant
 *      The invariant to assert.
 *
 ************************************************************************************************/
#define INVARIANT(p_invariant) cxinv::HandleAssert(cxinv::AssertLabel::INVARIANT,  \
                                                   static_cast<bool>(p_invariant), \
                                                   #p_invariant,                   \
                                                   __FILE__,                       \
                                                   __FUNCTION__,                   \
                                                   __LINE__                        \
                                                   )
#else
#define INVARIANT(p_invariant) ((void)0)
#endif // NDEBUG

#define IF_CONDITION_NOT_MET_DO_IMPL(p_assertType, p_condition, p_action) \
    if(!p_assertType(p_condition))                                        \
    {                                                                     \
        p_action                                                          \
    }                                                                     \
    (void)0                                                               \

/**********************************************************************************************//**
 * @ingroup contractmacros
 *
 * @brief Performs an action is some precondition is not met.
 *
 * @param p_precondition
 *      A boolean expression representing the precondition.
 * @param p_action
 *      The action to perform is the precondition is not met.
 *
 *************************************************************************************************/
#define IF_PRECONDITION_NOT_MET_DO(p_precondition, p_action)             \
    IF_CONDITION_NOT_MET_DO_IMPL(INL_PRECONDITION, p_precondition, p_action) \

/**********************************************************************************************//**
 * @ingroup assertmacros
 *
 * @brief Performs an action is some condition is not met.
 *
 * @param p_condition
 *      A boolean expression representing the condition.
 * @param p_action
 *      The action to perform is the precondition is not met.
 *
 *************************************************************************************************/
#define IF_CONDITION_NOT_MET_DO(p_condition, p_action)          \
    IF_CONDITION_NOT_MET_DO_IMPL(INL_ASSERT, p_condition, p_action) \

#endif // ASSERTION_H_0470D299_880C_415F_BEE0_57ED14327B58
