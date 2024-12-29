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
 * @file helpers.h
 * @date 2023
 *
 * Generic helper utilities.
 *
 *************************************************************************************************/

#ifndef HELPERS_H_3AE5AA7A_CC26_4C4F_99E2_0418EDA361C2
#define HELPERS_H_3AE5AA7A_CC26_4C4F_99E2_0418EDA361C2

#define GET_RETURN_IF_IMPL_FROM_ARGS(p_arg1, p_arg2, p_arg3, p_arg4) \
    p_arg4                                                           \

/*********************************************************************************************//**
 * @brief Conditional return.
 *
 * @ingroup helpermacros
 *
 * Immediately return from a function when a predicate is met. For example, in a function
 * returning an `int`, one might write:
 *
 * ```
 * RETURN_IF(!predicate, -1);
 * ```
 *
 * The macro can even be used in a function returning `void`, as such:
 *
 * ```
 * RETURN_IF(!predicate,);
 * ```
 *
 * This macro is used to hide repetitive boiler plate code only. It should be used in valid
 * contexts only, where returning only is not used as an error handling mechanism.
 *
 * @param ...
 *      The first parameter should be the predicate to test. The second (optional) parameter
 *
 ************************************************************************************************/
#define RETURN_IF(...)                               \
    RETURN_IF_IMPL_CHOOSER(__VA_ARGS__)(__VA_ARGS__) \

#define RETURN_IF_WITH_VALUE_IMPL(p_condition, p_return) \
    if((p_condition))                                    \
    {                                                    \
        return p_return;                                 \
    }                                                    \
    (void)0                                              \

#define RETURN_IF_WITH_VOID_IMPL(p_condition) \
    if((p_condition))                         \
    {                                         \
        return;                               \
    }                                         \
    (void)0                                   \

#define RETURN_IF_IMPL_CHOOSER(...)                         \
    GET_RETURN_IF_IMPL_FROM_ARGS(__VA_ARGS__,               \
                                 RETURN_IF_WITH_VOID_IMPL,  \
                                 RETURN_IF_WITH_VALUE_IMPL) \


#endif // HELPERS_H_3AE5AA7A_CC26_4C4F_99E2_0418EDA361C2
