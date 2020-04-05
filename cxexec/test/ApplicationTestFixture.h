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
 * @file ApplicationTestFixture.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418
#define APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418

#include <gtest/gtest.h>

#include "DisableStdStreamsRAII.h"
#include "LoggerMock.h"
#include "ModelMock.h"

/*********************************************************************************************//**
 * @brief Test fixture for the class @c cx::Application
 *
 * This fixture guarantees correct disabling/enabling of the standard streams through RAII.
 *
 ************************************************************************************************/
class ApplicationTestFixture : public ::testing::Test
{
public:

    cxlog::ILogger& GetLogger();
    cxmodel::IModel& GetModel();

    std::string GetStdOutContents() const;
    std::string GetStdErrContents() const;


private:

    LoggerMock m_logger;
    ModelMock m_model;
    DisableStdStreamsRAII m_disableStreamsRAII;
};

#endif // APPLICATIONTESTFIXTURE_H_91B6841E_7598_474B_BE68_991DB1816418
