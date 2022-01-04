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
 * @file Radius.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef RADIUS_H_0CA889EE_C37D_424C_B589_723A9EAAFBF7
#define RADIUS_H_0CA889EE_C37D_424C_B589_723A9EAAFBF7

#include <cxstd/StrongType.h>

namespace cxmath
{

/**********************************************************************************************//**
 * @brief Represents the radius of a circle or a sphere.
 *
 *************************************************************************************************/
using Radius = cxstd::StrongType<double, struct RadiusTag,
                                 cxstd::EqualityComparable,
                                 cxstd::Comparable,
                                 cxstd::Addable>;

} // namespace cxmath

#endif // RADIUS_H_0CA889EE_C37D_424C_B589_723A9EAAFBF7
