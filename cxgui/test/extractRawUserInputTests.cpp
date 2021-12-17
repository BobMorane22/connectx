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
 * @file extractRawUserInputTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxgui/extractRawUserInput.h>

TEST(ExtractRawUserInput, ExtractRawUserInputUL_ValidInput_ReturnsSuccess)
{
    const std::string raw = "1";

    size_t result = 0u;
    const auto status = cxgui::extractRawUserInput(raw, result);

    ASSERT_TRUE(status.IsSuccess());
}

TEST(ExtractRawUserInput, ExtractRawUserInputUL_ValidInput_ValueExtracted)
{
    const std::string raw = "1";

    size_t result = 0u;
    const auto status = cxgui::extractRawUserInput(raw, result);

    ASSERT_EQ(1u, result);
}

TEST(ExtractRawUserInput, ExtractRawUserInputUL_InvalidAlphaInput_ErrorReturned)
{
    const std::string raw = "a";

    size_t result = 0u;
    const auto status = cxgui::extractRawUserInput(raw, result);

    ASSERT_FALSE(status.IsSuccess());
    ASSERT_EQ("Numerical values expected.", status.GetMessage());
}

TEST(ExtractRawUserInput, ExtractRawUserInputUL_InvalidNumericalInput_ErrorReturned)
{
    const std::string raw = "99999999999999999999999";

    size_t result = 0u;
    const auto status = cxgui::extractRawUserInput(raw, result);

    ASSERT_FALSE(status.IsSuccess());
    ASSERT_EQ("Numerical values out of range.", status.GetMessage());
}
