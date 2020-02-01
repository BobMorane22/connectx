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
 * @file CSVMessageFormatter.h
 * @date 2020
 *
 * Comma Separated Values (CSV) message formatter.
 *
 *************************************************************************************************/

#ifndef CSVMESSAGEFORMATTER_H_29E79C64_F1E1_4609_8098_6C5277CE5DDA
#define CSVMESSAGEFORMATTER_H_29E79C64_F1E1_4609_8098_6C5277CE5DDA

#include <memory>

#include "IMessageFormatter.h"
#include "ITimestampFormatter.h"

namespace cxlog
{

/***********************************************************************************************//**
 * @brief CSV message formatter.
 *
 * Formats logger information and a message into a CSV compliant entry.
 *
 **************************************************************************************************/
class CSVMessageFormatter final : public IMessageFormatter
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_timeFormatter A timestamp formatter.
     *
     **********************************************************************************************/
    CSVMessageFormatter(std::unique_ptr<ITimestampFormatter>&& p_timeFormatter);

    /*******************************************************************************************//**
     * @brief Format CSV headers.
     *
     * Formats titles for every CSV entry in a message. Every title element is also in CSV form,
     * to help when the resulting log file is opened in a spreadsheet reader.
     *
     * @return A string containing the formatted headers.
     *
     **********************************************************************************************/
    std::string FormatHeaders() const override final;

    /*******************************************************************************************//**
     * @brief Formats a message entry according to different informations supplied by the logger.
     *
     * Takes different informations (including, of course, a message) supplied by the logger
     * and formats them to a specific format (ex.: text, CSV, HTML, etc.).
     *
     * @param p_verbosityLevel The message verbosity level.
     * @param p_fileName       The source file in which the logging occured.
     * @param p_functionName   The function name in which the logging occured.
     * @param p_lineNumber     The line number in the source file where the logging occured.
     * @param p_message        The message to log.
     *
     * @return The formatted message.
     *
     **********************************************************************************************/
    virtual std::string FormatMessage(const VerbosityLevel p_verbosityLevel,
                                      const std::string&   p_fileName,
                                      const std::string&   p_functionName,
                                      const size_t         p_lineNumber,
                                      const std::string&   p_message) const override final;


private:

    std::unique_ptr<ITimestampFormatter> m_timeFormatter;
};

} // namespace cxlog

#endif // CSVMESSAGEFORMATTER_H_29E79C64_F1E1_4609_8098_6C5277CE5DDA
