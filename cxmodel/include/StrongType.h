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
 * @file StrongType.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef STRONGTYPE_H_4E2D47C9_3530_4EF1_8A36_EE3FB6958D12
#define STRONGTYPE_H_4E2D47C9_3530_4EF1_8A36_EE3FB6958D12

#include <type_traits>
#include <utility>

namespace cxstd
{

/**********************************************************************************************//**
 * @brief A wrapper to make data types strong.
 *
 * @tparam Underlying The underlying data type.
 * @tparam Phantom    A one-time type to differentiate strong types using the same underlying
 *                    types from one another.
 * @tparam Capacities Capacities the type will inherit.
 *
 * Original idea taken from Jonathan Boccara's excelent blog Fluent{C++}:
 *
 *          https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
 *
 *************************************************************************************************/
template <typename Underlying, typename Phantom, template<typename> class... Capacities>
class StrongType : public Capacities<StrongType<Underlying, Phantom, Capacities...>>...
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_value The value of the wrapped type instance.
     *
     *********************************************************************************************/
    explicit constexpr StrongType(const Underlying& p_value)
    : m_value(p_value)
    {
    }

    /******************************************************************************************//**
     * @brief Move constructor.
     *
     * @param p_value The value of the wrapped type instance.
     *
     *********************************************************************************************/
    explicit constexpr StrongType(Underlying&& p_value)
    : m_value(std::move(p_value))
    {
    }

    /******************************************************************************************//**
     * @brief Write access to the underlying instance.
     *
     *********************************************************************************************/
    Underlying& Get()
    {
        return m_value;
    } 

    /******************************************************************************************//**
     * @brief Read access to the underlying instance.
     *
     *********************************************************************************************/
    const Underlying& Get() const
    {
        return m_value;
    }
    
private:

    Underlying m_value;

};

/******************************************************************************************//**
 * @brief Strong type capacity for comparing if two instances are equal or different.
 *
 * @tparam CRTP A "Curiously Recurring Template Parameter", which is in fact the strong
 *              type to which to add the capacity.
 *
 * More precisely, the capacity adds two operators: `==` and `!=`. Note that the underlying
 * type behind `CRTP` must support these operators.
 *
 *********************************************************************************************/
template<typename CRTP>
struct EqualityComparable
{

    /**************************************************************************************//**
     * @brief Equal-to operator.
     *
     * @param p_other The other instance, to compare with `this`.
     *
     * @return `true` if both instances have equal underlying type. `false` otherwise.
     *
     *****************************************************************************************/
    [[nodiscard]] constexpr bool operator==(const CRTP& p_other) const
    {
        return static_cast<const CRTP*>(this)->Get() == static_cast<const CRTP*>(&p_other)->Get();
    }

    /**************************************************************************************//**
     * @brief Not equal-to operator.
     *
     * @param p_other The other instance, to compare with `this`.
     *
     * @return `true` if both instances have equal different type. `false` otherwise.
     *
     *****************************************************************************************/
    [[nodiscard]] constexpr bool operator!=(const CRTP& p_other) const
    {
        return !(*this == p_other);
    }
};

/******************************************************************************************//**
 * @brief Strong type capacity for adding (and substracting) two instances.
 *
 * @tparam CRTP A "Curiously Recurring Template Parameter", which is in fact the strong
 *              type to which to add the capacity.
 *
 * More precisely, the capacity adds four operators: `+`, `-`, `+=` and `-=`. Note that
 * the underlying type behind `CRTP` must support these operators.
 *
 *********************************************************************************************/
template<typename CRTP>
struct Addable
{

    /**************************************************************************************//**
     * @brief Addition operator.
     *
     * @param p_other The other instance to add.
     *
     * @return The addition result.
     *
     *****************************************************************************************/
    [[nodiscard]] CRTP operator+(const CRTP& p_other) const
    {
        return CRTP{static_cast<const CRTP*>(this)->Get() + static_cast<const CRTP*>(&p_other)->Get()};
    }

    /**************************************************************************************//**
     * @brief Substraction operator.
     *
     * @param p_other The other instance to substract.
     *
     * @return The substraction result.
     *
     *****************************************************************************************/
    [[nodiscard]] CRTP operator-(const CRTP& p_other) const
    {
        CRTP copy{static_cast<const CRTP*>(this)->Get()};

        return copy -= p_other;
    }

    /**************************************************************************************//**
     * @brief Increment addition operator.
     *
     * @param p_other The other instance to add.
     *
     * @return The addition result.
     *
     *****************************************************************************************/
    CRTP& operator+=(const CRTP& p_other)
    {
        CRTP* lhs = static_cast<CRTP*>(this);
        const CRTP* rhs = static_cast<const CRTP*>(&p_other);

        lhs->Get() += rhs->Get();

        return *lhs;
    }

    /**************************************************************************************//**
     * @brief Increment substraction operator.
     *
     * @param p_other The other instance to substract.
     *
     * @return The substraction result.
     *
     *****************************************************************************************/
    CRTP& operator-=(const CRTP& p_other)
    {
        CRTP* lhs = static_cast<CRTP*>(this);
        const CRTP* rhs = static_cast<const CRTP*>(&p_other);

        lhs->Get() -= rhs->Get();

        return *lhs;
    }
};

/******************************************************************************************//**
 * @brief Strong type capacity for comparing.
 *
 * @tparam CRTP A "Curiously Recurring Template Parameter", which is in fact the strong
 *              type to which to add the capacity.
 *
 * More precisely, the capacity adds four operators: `<`, `<=`, `>` and `>=`. Note that
 * the underlying type behind `CRTP` must support these operators.
 *
 *********************************************************************************************/
template<typename CRTP>
struct Comparable
{

    /**************************************************************************************//**
     * @brief Less than operator.
     *
     * @param p_other The other instance, to compare with `this`.
     *
     * @return `true` if `p_other` is greater than this. `false` otherwise.
     *
     *****************************************************************************************/
    [[nodiscard]] constexpr bool operator<(const CRTP& p_other) const
    {
        static_assert(std::is_base_of_v<cxstd::EqualityComparable<CRTP>, CRTP>, "Equality comparison must be defined.");

        return static_cast<const CRTP*>(this)->Get() < static_cast<const CRTP*>(&p_other)->Get();
    }

    /**************************************************************************************//**
     * @brief Greater than operator.
     *
     * @param p_other The other instance, to compare with `this`.
     *
     * @return `true` if `p_other` is smaller than this. `false` otherwise.
     *
     *****************************************************************************************/
    [[nodiscard]] constexpr bool operator>(const CRTP& p_other) const
    {
        static_assert(std::is_base_of_v<cxstd::EqualityComparable<CRTP>, CRTP>, "Equality comparison must be defined.");

        return static_cast<const CRTP*>(this)->Get() > static_cast<const CRTP*>(&p_other)->Get();
    }

    /**************************************************************************************//**
     * @brief Less than or equal to operator.
     *
     * @param p_other The other instance, to compare with `this`.
     *
     * @return `true` if `p_other` is equal or greater than this. `false` otherwise.
     *
     *****************************************************************************************/
    [[nodiscard]] constexpr bool operator<=(const CRTP& p_other) const
    {
        static_assert(std::is_base_of_v<cxstd::EqualityComparable<CRTP>, CRTP>, "Equality comparison must be defined.");

        return static_cast<const CRTP*>(this)->Get() <= static_cast<const CRTP*>(&p_other)->Get();
    }

    /**************************************************************************************//**
     * @brief Greater than operator.
     *
     * @param p_other The other instance, to compare with `this`.
     *
     * @return `true` if `p_other` is equal to or smaller than this. `false` otherwise.
     *
     *****************************************************************************************/
    [[nodiscard]] constexpr bool operator>=(const CRTP& p_other) const
    {
        static_assert(std::is_base_of_v<cxstd::EqualityComparable<CRTP>, CRTP>, "Equality comparison must be defined.");

        return static_cast<const CRTP*>(this)->Get() >= static_cast<const CRTP*>(&p_other)->Get();
    }
};

} // namespace cxstd

#endif // STRONGTYPE_H_4E2D47C9_3530_4EF1_8A36_EE3FB6958D12
