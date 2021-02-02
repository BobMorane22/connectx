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
 * @file HandleAssertTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef HANDLEASSERTTESTFIXTURE_H_86DDB7C1_6022_4421_8477_EBDA35EC90EC
#define HANDLEASSERTTESTFIXTURE_H_86DDB7C1_6022_4421_8477_EBDA35EC90EC

#include <gtest/gtest.h>

#include <cxunit/include/DisableStdStreamsRAII.h>

#include <assertion.h>

/*********************************************************************************************//**
 * @brief Test fixture for the class @c cxinv::HandleAssert function.
 *
 * This fixture guarantees correct disabling/enabling of the standard streams through RAII.
 *
 ************************************************************************************************/
class HandleAssertTestFixture : public ::testing::Test
{

public:

    std::string GetStdOutContents() const;
    std::string GetStdErrContents() const;

    std::string MakeExpectedMessage(cxinv::AssertLabel p_label, const char* p_message = nullptr) const;


protected:

    const char* m__FILE_{"File.cpp"};
    const char* m__FUNCTION_{"Function()"};
    const long  m__LINE_{10};
    const char* m_CONDITION_EXPRESSION{"(3 > 5)"};
    const char* m_VALID_MESSAGE{"A valid message"};


private:

    cxunit::DisableStdStreamsRAII m_disableStreamsRAII;

};

#endif // HANDLEASSERTTESTFIXTURE_H_86DDB7C1_6022_4421_8477_EBDA35EC90EC
