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

namespace cxstd
{

/**********************************************************************************************//**
 * @brief A wrapper to make data types strong.
 *
 * @tparam Underlying The underlying data type.
 * @tparam Phantom    A one-time type to differentiate strong types using the same underlying
 *                    types from one another.
 *
 * Original idea taken from Jonathan Boccara's excelent blog Fluent{C++}:
 *
 *          https://www.fluentcpp.com/2016/12/08/strong-types-for-strong-interfaces/
 *
 *************************************************************************************************/
template <typename Underlying, typename Phantom>
class StrongType
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_value The value of the wrapped type instance.
     *
     *********************************************************************************************/
    explicit StrongType(const Underlying& p_value)
    : m_value(p_value)
    {
    }

    /******************************************************************************************//**
     * @brief Move constructor.
     *
     * @param p_value The value of the wrapped type instance.
     *
     *********************************************************************************************/
    explicit StrongType(Underlying&& p_value)
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

} // namespace cxstd

#endif // STRONGTYPE_H_4E2D47C9_3530_4EF1_8A36_EE3FB6958D12
