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
 * @file Model.h
 * @date 2019
 *
 *************************************************************************************************/

#ifndef MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC
#define MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC

#include <memory>

#include <cxlog/include/ILogger.h>

#include "ICommandStack.h"
#include "IModel.h"

namespace cxmodel
{

/*********************************************************************************************//**
 * @brief Connect X model.
 *
 * @invariant The command stack is valid.
 *
 * This class holds the Connect X related business rules.
 *
 ************************************************************************************************/
class Model : public IModel, public cxlog::ILogger
{

public:

    /******************************************************************************************//**
     * @brief Constructor.
     *
     * @pre p_cmdStack is valid.
     * @pre p_cmdStack is empty.
     *
     * @param p_cmdStack The command stack.
     *
     ********************************************************************************************/
    Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cxlog::ILogger& p_logger);
    ~Model() override;

    // IModel
    std::string GetName() const override;
    std::string GetVersionNumber() const override;

    void CreateNewGame(const GameInformation& p_gameInformation) override;
    GameInformation GetGameInformation() const override;

    void Undo() override;
    void Redo() override;

    void Signal() override;

    // ILogger
    void Log(const cxlog::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message) override;
    void SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel) override;
    cxlog::VerbosityLevel GetVerbosityLevel() const override;


private:

    void CheckInvariants();

    GameInformation m_gameInformation;

    std::unique_ptr<ICommandStack> m_cmdStack;

    static constexpr char m_NAME[] = "Connect X";
    static constexpr unsigned int m_MAJOR_VERSION_NB = 0u;
    static constexpr unsigned int m_MINOR_VERSION_NB = 11u;

    cxlog::ILogger& m_logger;
};

} // namespace cxmodel

#endif // MODEL_H_8CC20E7E_7466_4977_9435_7E09ADBD10FC
