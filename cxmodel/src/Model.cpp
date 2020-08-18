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

#include <exception>
#include <sstream>

#include <cxinv/include/assertion.h>

#include <CommandCreateNewGame.h>
#include <CommandStack.h>
#include <Model.h>
#include <NotificationContext.h>

namespace
{

static constexpr char NAME[] = "Connect X";

static constexpr unsigned int MAJOR_VERSION_NB = 0u;
static constexpr unsigned int MINOR_VERSION_NB = 15u;

static constexpr size_t GRID_MIN_HEIGHT = 6u;
static constexpr size_t GRID_MAX_HEIGHT = 64u;
static constexpr size_t GRID_MIN_WIDTH = 7u;
static constexpr size_t GRID_MAX_WIDTH = 64u;

static constexpr size_t IN_A_ROW_MIN = 3u;
static constexpr size_t IN_A_ROW_MAX = 8u;

static constexpr size_t NUMBER_OF_PLAYERS_MIN = 2u;
static constexpr size_t NUMBER_OF_PLAYERS_MAX = 10u;

static const cxmodel::Player ACTIVE_PLAYER = {"Woops (active)!", {0, 0, 0, 0}};
static const cxmodel::Player NEXT_PLAYER ={"Woops! (next)", {0, 0, 0, 0}};

} // namespace

cxmodel::Model::Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cxlog::ILogger& p_logger)
 : m_cmdStack{std::move(p_cmdStack)}
 , m_logger{p_logger}
 , m_gridWidth{7u}
 , m_gridHeight{6u}
 , m_inARowValue{4u}
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
    return std::string{NAME};
}

std::string cxmodel::Model::GetVersionNumber() const
{
    std::stringstream stream;

    stream << "v" << MAJOR_VERSION_NB << "." << MINOR_VERSION_NB;

    return stream.str();
}

size_t cxmodel::Model::GetMinimumGridHeight() const
{
    return GRID_MIN_HEIGHT;
}

size_t cxmodel::Model::GetMinimumGridWidth() const
{
    return GRID_MIN_WIDTH;
}

size_t cxmodel::Model::GetMinimumInARowValue() const
{
    return IN_A_ROW_MIN;
}

size_t cxmodel::Model::GetMaximumGridHeight() const
{
    return GRID_MAX_HEIGHT;
}

size_t cxmodel::Model::GetMaximumGridWidth() const
{
    return GRID_MAX_WIDTH;
}

size_t cxmodel::Model::GetMaximumInARowValue() const
{
    return IN_A_ROW_MAX;
}

size_t cxmodel::Model::GetMinimumNumberOfPlayers() const
{
    return NUMBER_OF_PLAYERS_MIN;
}

size_t cxmodel::Model::GetMaximumNumberOfPlayers() const
{
    return NUMBER_OF_PLAYERS_MAX;
}

void cxmodel::Model::CreateNewGame(const NewGameInformation& p_gameInformation)
{
    PRECONDITION(p_gameInformation.m_gridWidth > 0);
    PRECONDITION(p_gameInformation.m_gridHeight > 0);
    PRECONDITION(p_gameInformation.m_inARowValue > 1);
    PRECONDITION(p_gameInformation.GetNewPlayers().size() > 1);

    for(const auto& newPlayer : p_gameInformation.GetNewPlayers())
    {
        PRECONDITION(!newPlayer.GetName().empty());
    }

    std::unique_ptr<ICommand> command = std::make_unique<CommandCreateNewGame>(m_players, m_gridWidth, m_gridHeight, m_inARowValue, p_gameInformation);
    m_cmdStack->Execute(std::move(command));

    Notify(NotificationContext::CREATE_NEW_GAME);

    std::ostringstream stream;

    stream << "New game created:"   << std::endl
           << "  In-a-row value:  " << m_inARowValue << std::endl
           << "  Grid dimensions: " << "Width = " << m_gridWidth << ", "
                                    << "Height = " << m_gridHeight << std::endl
           << "Number of players: " << m_players.size() << std::endl;

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());

    CheckInvariants();
}

size_t cxmodel::Model::GetCurrentGridHeight() const
{
    return m_gridHeight;
}

size_t cxmodel::Model::GetCurrentGridWidth() const
{
    return m_gridWidth;
}

size_t cxmodel::Model::GetCurrentInARowValue() const
{
    return m_inARowValue;
}

const cxmodel::Player& cxmodel::Model::GetActivePlayer() const
{
    if(!ASSERT(m_players.size() >= 2))
    {
        return ACTIVE_PLAYER;
    }

    return m_players[0];
}

const cxmodel::Player& cxmodel::Model::GetNextPlayer() const
{
    if(!ASSERT(m_players.size() >= 2))
    {
        return NEXT_PLAYER;
    }

    return m_players[1];
}

bool cxmodel::Model::IsWon() const
{
    throw std::logic_error{"Not yet implemented."};
}

bool cxmodel::Model::IsTie() const
{
    throw std::logic_error{"Not yet implemented."};
}

bool cxmodel::Model::IsEarlyTie() const
{
    throw std::logic_error{"Not yet implemented."};
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

void cxmodel::Model::Log(const cxlog::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message)
{
    m_logger.Log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);

    CheckInvariants();
}

void cxmodel::Model::SetVerbosityLevel(const cxlog::VerbosityLevel p_verbosityLevel)
{
    m_logger.SetVerbosityLevel(p_verbosityLevel);

    CheckInvariants();
}

cxlog::VerbosityLevel cxmodel::Model::GetVerbosityLevel() const
{
    return m_logger.GetVerbosityLevel();
}

void cxmodel::Model::CheckInvariants()
{
    INVARIANT(m_cmdStack != nullptr);
}
