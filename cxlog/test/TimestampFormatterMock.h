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
 * @file TimestampFormatterMock.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef TIMESTAMPFORMATTERMOCK_H_E4AAF62B_2F24_4EC0_8FA1_45C40EF31747
#define TIMESTAMPFORMATTERMOCK_H_E4AAF62B_2F24_4EC0_8FA1_45C40EF31747

#include <cxlog/include/ITimestampFormatter.h>

class TimestampFormatterMock : public cxlog::ITimestampFormatter
{

public:

    ~TimestampFormatterMock() override = default;

    std::string FormatTimestamp() const override {return "AAAA:MM:JJTHH:MM:SS:mm";}
};

#endif // TIMESTAMPFORMATTERMOCK_H_E4AAF62B_2F24_4EC0_8FA1_45C40EF31747
