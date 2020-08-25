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

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/GetWindowTitle_ValidPresenter_ValidStringReturned)
{
    ASSERT_EQ(GetPresenter().GetWindowTitle(), "About");
}

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/GetApplicationName_ValidPresenter_ValidStringReturned)
{
    const auto& model = GetModel();

    ASSERT_EQ(GetPresenter().GetApplicationName(), model.GetName());
}

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/GetVersionNumber_ValidPresenter_ValidStringReturned)
{
    ASSERT_EQ(GetPresenter().GetVersionNumber(), GetModel().GetVersionNumber());
}

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/GetApplicationDescription_ValidPresenter_ValidStringReturned)
{
    ASSERT_EQ(GetPresenter().GetApplicationDescription(), "Connect X is a scalable Four-In-A-Row clone");
}

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/GetLicenseDescription_ValidPresenter_ValidStringReturned)
{
    ASSERT_EQ(GetPresenter().GetLicenseDescription(), "License: GNU GPL v3");
}

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/GetCopyrightNotice_ValidPresenter_ValidStringReturned)
{
    ASSERT_EQ(GetPresenter().GetCopyrightNotice(), "Copyright © 2020 - Éric Poirier");
}

TEST_F(AboutWindowPresenterTestFixture, /*DISABLED_*/Update_GetCloseText_ValidStringReturned)
{
    ASSERT_EQ(GetPresenter().GetCloseText(), "Close");
}
