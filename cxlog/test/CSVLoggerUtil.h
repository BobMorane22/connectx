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
 * @file CSVLoggerUtil.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef CSVLOGGERUTIL_H_E188DB4B_30F1_4D3A_AB1B_54E82EBF753B
#define CSVLOGGERUTIL_H_E188DB4B_30F1_4D3A_AB1B_54E82EBF753B

#include <memory.h>
#include <sstream>

#include <cxlog/include/ChainLogger.h>

const std::string BASIC_STRING_TO_LOG{"CSV logger test"};

const std::string FATAL_PREFIX  {"FATAL, "  };
const std::string ERROR_PREFIX  {"ERROR, "  };
const std::string WARNING_PREFIX{"WARNING, "};
const std::string INFO_PREFIX   {"INFO, "   };
const std::string DEBUG_PREFIX  {"DEBUG, "  };

const std::string _FILE_    {"File.cpp"};
const std::string _FUNCTION_{"nsp::function()"};
const size_t      _LINE_    {200};

const std::string SEPARATOR  {", "};
const std::string END_OF_LINE{"\n"};

const std::string EMPTY_STRING{std::string()};

std::string GenerateLineToLog();
std::string FatalResult();
std::string ErrorResult();
std::string WarningResult();
std::string InfoResult();
std::string DebugResult();
std::string HeaderLine();

std::unique_ptr<cxlog::ILogger> CreateCSVStringStreamLogger(std::ostringstream& p_stream,
                                                            const bool p_generateHeader = false);

std::unique_ptr<cxlog::ChainLogger> CreateCSVStringStreamChainLogger(std::ostringstream& p_stream,
                                                                    const bool p_generateHeader = false);

#endif // CSVLOGGERUTIL_H_E188DB4B_30F1_4D3A_AB1B_54E82EBF753B
