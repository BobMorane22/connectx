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
 * @file Model.cpp
 * @date 2019
 *
 *************************************************************************************************/

#include <sstream>

#include <cxinv/include/assertion.h>

#include <CommandCreateNewGame.h>
#include <CommandStack.h>
#include <Model.h>
#include <NotificationContext.h>

cxmodel::Model::Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cxlog::ILogger& p_logger)
 : m_cmdStack{std::move(p_cmdStack)}
 , m_logger{p_logger}
{
    PRECONDITION(m_cmdStack != nullptr);

    if(m_cmdStack != nullptr)
    {
        PRECONDITION(m_cmdStack->IsEmpty());
    }

    CheckInvariants();
}

cxmodel::Model::~Model()
{
    DetatchAll();
}

std::string cxmodel::Model::GetName() const
{
    return std::string{m_NAME};
}

std::string cxmodel::Model::GetVersionNumber() const
{
    std::stringstream stream;

    stream << "v" << m_MAJOR_VERSION_NB << "." << m_MINOR_VERSION_NB;

    return stream.str();
}

void cxmodel::Model::CreateNewGame(const GameInformation& p_gameInformation)
{
    PRECONDITION(p_gameInformation.m_inARowValue > 1);
    PRECONDITION(p_gameInformation.m_gridWidth > 0);
    PRECONDITION(p_gameInformation.m_gridHeight > 0);
    PRECONDITION(p_gameInformation.GetPlayersInformation().size() > 1);

    for(const auto& playerInfo : p_gameInformation.GetPlayersInformation())
    {
        PRECONDITION(!playerInfo.m_name.empty());
        PRECONDITION(!playerInfo.m_discColor.empty());
    }

    std::unique_ptr<ICommand> command = std::make_unique<CommandCreateNewGame>(m_gameInformation, p_gameInformation);
    m_cmdStack->Execute(std::move(command));

    Notify(NotificationContext::CREATE_NEW_GAME);

    std::ostringstream stream;

    stream << "New game created:"   << std::endl
           << "  In-a-row value:  " << m_gameInformation.m_inARowValue << std::endl
           << "  Grid dimensions: " << "Width = " << m_gameInformation.m_gridWidth << ", "
                                    << "Height = " << m_gameInformation.m_gridHeight << std::endl
           << "Number of players: " << m_gameInformation.GetPlayersInformation().size() << std::endl;

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());
}

cxmodel::GameInformation cxmodel::Model::GetGameInformation() const
{
    return m_gameInformation;
}

void cxmodel::Model::Undo()
{
    m_cmdStack->Undo();

    Notify(NotificationContext::UNDO);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Last action undoed.");

    CheckInvariants();
}

void cxmodel::Model::Redo()
{
    m_cmdStack->Redo();

    Notify(NotificationContext::REDO);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Last action redoed.");

    CheckInvariants();
}

void cxmodel::Model::Signal()
{
    Notify(NotificationContext::SIGNAL);
}

void cxmodel::Model::Log(const cxlog::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message)
{
    m_logger.Log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);
}

void cxmodel::Model::SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel)
{
    m_logger.SetVerbosityLevel(p_verbosityLevel);
}

cxlog::VerbosityLevel cxmodel::Model::GetVerbosityLevel() const
{
    return m_logger.GetVerbosityLevel();
}

void cxmodel::Model::CheckInvariants()
{
    INVARIANT(m_cmdStack != nullptr);
}
