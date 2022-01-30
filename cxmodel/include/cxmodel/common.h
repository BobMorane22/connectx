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
 * @file common.h
 * @date 2021
 *
 *************************************************************************************************/

#ifndef COMMON_H_EEBB0E3B_68E6_4C58_9FA4_E3D2897F7734
#define COMMON_H_EEBB0E3B_68E6_4C58_9FA4_E3D2897F7734

#include <cstddef>

#include <cxstd/StrongType.h>

namespace cxmodel
{

/** Represents a row in the game board. */
using Row = cxstd::StrongType<size_t, struct RowTag,
                              cxstd::EqualityComparable,
                              cxstd::Comparable,
                              cxstd::Addable
>;

/** Represents the height of the game board, in terms of the number of column. */
using Height = cxstd::StrongType<size_t, struct BoardHeightTag,
                                 cxstd::EqualityComparable,
                                 cxstd::Comparable,
                                 cxstd::Addable
>;

/** Represents a column in the game board. */
using Column = cxstd::StrongType<size_t, struct ColumnTag,
                                 cxstd::EqualityComparable,
                                 cxstd::Comparable,
                                 cxstd::Addable
>;

/** Represents the width of the game board, in terms of the number of column. */
using Width = cxstd::StrongType<size_t, struct BoardWidthTag,
                                cxstd::EqualityComparable,
                                cxstd::Comparable,
                                cxstd::Addable
>;

} // namespace cxmodel

#endif // COMMON_H_EEBB0E3B_68E6_4C58_9FA4_E3D2897F7734
