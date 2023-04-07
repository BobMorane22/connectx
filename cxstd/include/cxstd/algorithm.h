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
 * @file algorithm.h
 * @date 2023
 *
 *************************************************************************************************/

#include <algorithm>

namespace cxstd
{

/**********************************************************************************************//**
 * @brief Computes the strict difference between two collections.
 *
 * Computes a new unsorted collection in which all elements also exist in `p_lhs`, but not in `p_rhs`.
 * For example:
 *
 @verbatim

  p_lhs  : { A, B, B, C, D, E, E }
  p_rhs  : { B, D, F }
  result : { A, C, E, E }

 @endverbatim
 *
 * In the example above, the elements are "sorted" to illustrate the behavior of the computation,
 * but this does not need to be the case. Here is the exact same example, where the data has
 * been suffled. Except the ordering in the resulting collection, the result is the same:
 *
 @verbatim

  p_lhs  : { E, B, D, C, A, E, B }
  p_rhs  : { F, B, D }
  result : { E, C, A, E }

 @endverbatim
 *
 * If duplicate elements exist in `p_lhs`, they will also exist as duplicates in the resulting
 * collection.
 *
 * @note
 *      Elements in the collections must implement `operator==`.
 * @note
 *      Elements in the collections must be copy constructible.
 * @note
 *      For collections with sortable items see the standard algorithms. Their performance
 *      is usually much better.
 *
 * @param p_lhs
 *      The *substracted from* collection.
 *
 * @param p_rhs
 *      The *substracted* collection.
 *
 * @return
 *      A collection containing the strict difference between `p_lhs` and `p_rhs`.
 *
 *************************************************************************************************/
template<typename UnsortedContainer>
UnsortedContainer ComputeStrictDifference(const UnsortedContainer& p_lhs, const UnsortedContainer& p_rhs)
{
    UnsortedContainer result;
    for(const auto& element : p_lhs)
    {
        if(std::find(p_rhs.cbegin(), p_rhs.cend(), element) != p_rhs.cend())
        {
            continue;
        }

        result.push_back(element);
    }

    return result;
}

/**********************************************************************************************//**
 * @brief Remove all duplicate elements from a collection.
 *
 * The collection is modified so that all duplicate elements now appear only once in the collection.
 *
 @verbatim

  in  : { A, B, B, C, D, E, E, E }
  out : { A, B, C, D, E }

 @endverbatim
 *
 * In the example above, the elements are "sorted" to illustrate the behavior of the computation,
 * but this does not need to be the case. Here is the exact same example, where the data has
 * been suffled. Except the ordering in the resulting collection, the result is the same:
 *
 @verbatim

  in  : { E, B, D, C, A, E, E, B }
  out : { E, B, D, C, A }

 @endverbatim
 *
 * @note
 *      Elements in the collections must implement `operator==`.
 * @note
 *      Elements in the collections must be copy constructible.
 * @note
 *      For collections with sortable items see the standard algorithms. Their performance
 *      is usually much better.
 *
 * @param p_collection
 *      The collection from which to remove duplicate elements.
 *
 *************************************************************************************************/
template<typename UnsortedContainer>
void Unique(UnsortedContainer& p_collection)
{
    UnsortedContainer unique;
    for(const auto& element : p_collection)
    {
        if(std::find(unique.cbegin(), unique.cend(), element) != unique.cend())
        {
            continue;
        }

        unique.push_back(element);
    }

    p_collection = unique;
}

} // namespace cxstd
