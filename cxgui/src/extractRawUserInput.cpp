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
 * @file extractRawUserInput.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <stdexcept>

#include <extractRawUserInput.h>

namespace
{

constexpr char NUMERICAL_VALUE_EXPECTED[] = "Numerical values expected.";
constexpr char NUMERICAL_VALUE_OUT_OF_BOUND[] = "Numerical values out of range.";

} // namespace

cxmodel::Status cxgui::extractRawUserInput(const std::string& p_raw, unsigned long& p_extracted)
{
    try
    {
        p_extracted = std::stoul(p_raw);
    }
    catch(const std::invalid_argument& p_exception)
    {
        return cxmodel::MakeError(NUMERICAL_VALUE_EXPECTED);
    }
    catch(const std::out_of_range& p_exception)
    {
        return cxmodel::MakeError(NUMERICAL_VALUE_OUT_OF_BOUND);;
    }

    return cxmodel::MakeSuccess();
}
