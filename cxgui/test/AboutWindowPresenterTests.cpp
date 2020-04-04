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
 * @file AboutWindowPresenterTests.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include "AboutWindowPresenterTestFixture.h"

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetWindowTitle_TextNotEmpty)
{
    ASSERT_FALSE(GetPresenter().GetWindowTitle().empty());
}

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetApplicationName_TextEmpty)
{
    ASSERT_TRUE(GetPresenter().GetApplicationName().empty());
}

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetVersionNumber_TextEmpty)
{
    ASSERT_TRUE(GetPresenter().GetVersionNumber().empty());
}

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetApplicationDescription_TextNotEmpty)
{
    ASSERT_FALSE(GetPresenter().GetApplicationDescription().empty());
}

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetLicenseDescription_TextNotEmpty)
{
    ASSERT_FALSE(GetPresenter().GetLicenseDescription().empty());
}

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetCopyrightNotice_TextNotEmpty)
{
    ASSERT_FALSE(GetPresenter().GetCopyrightNotice().empty());
}

TEST_F(AboutWindowPresenterTestFixture, NoUpdate_GetCloseText_TextNotEmpty)
{
    ASSERT_FALSE(GetPresenter().GetCloseText().empty());
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetWindowTitle_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetWindowTitle(), "About");
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetApplicationName_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetApplicationName(), GetModel().GetName());
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetVersionNumber_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetVersionNumber(), GetModel().GetVersionNumber());
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetApplicationDescription_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetApplicationDescription(), "Connect X is a scalable Four-In-A-Row clone");
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetLicenseDescription_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetLicenseDescription(), "License: GNU GPL v3");
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetCopyrightNotice_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetCopyrightNotice(), "Copyright © 2020 - Éric Poirier");
}

TEST_F(AboutWindowPresenterTestFixture, Update_GetCloseText_ValidString)
{
    GetModel().Signal();

    ASSERT_EQ(GetPresenter().GetCloseText(), "Close");
}
