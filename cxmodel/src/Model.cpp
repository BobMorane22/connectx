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

#include <cxinv/assertion.h>

#include <cxmodel/Board.h>
#include <cxmodel/CommandCreateNewGame.h>
#include <cxmodel/CommandDropChip.h>
#include <cxmodel/CommandStack.h>
#include <cxmodel/Disc.h>
#include <cxmodel/GameResolutionStrategyFactory.h>
#include <cxmodel/IPlayer.h>
#include <cxmodel/Model.h>
#include <cxmodel/ModelNotificationContext.h>
#include <cxmodel/version.h>

namespace
{

constexpr char NAME[] = "Connect X";

constexpr size_t GRID_MIN_HEIGHT = 6u;
constexpr size_t GRID_MAX_HEIGHT = 64u;
constexpr size_t GRID_MIN_WIDTH = 7u;
constexpr size_t GRID_MAX_WIDTH = 64u;

constexpr size_t IN_A_ROW_MIN = 3u;
constexpr size_t IN_A_ROW_MAX = 8u;

constexpr size_t NUMBER_OF_PLAYERS_MIN = 2u;
constexpr size_t NUMBER_OF_PLAYERS_MAX = 10u;

const cxmodel::Disc NO_DISC{cxmodel::MakeTransparent()};

const cxmodel::IPlayer& GetDefaultActivePlayer()
{
    static auto player = CreatePlayer("Woops (active)!", {0, 0, 0, 0}, cxmodel::PlayerType::HUMAN);
    return *player;
}

const cxmodel::IPlayer& GetDefaultNextPlayer()
{
    static auto player = CreatePlayer("Woops (next)!", {0, 0, 0, 0}, cxmodel::PlayerType::HUMAN);
    return *player;
}

} // namespace

cxmodel::Model::Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cxlog::ILogger& p_logger)
 : m_cmdStack{std::move(p_cmdStack)}
 , m_logger{p_logger}
 , m_playersInfo{{}, 0u, 1u}
 , m_inARowValue{4u}
{
    PRECONDITION(m_cmdStack);

    if(m_cmdStack)
    {
        PRECONDITION(m_cmdStack->IsEmpty());
    }

    CheckInvariants();
}

cxmodel::Model::~Model()
{
    DetatchAll();
}

void cxmodel::Model::Update(cxmodel::ModelNotificationContext p_context, cxmodel::ModelSubject* p_subject)
{
    if(INL_ASSERT(p_subject))
    {
        Notify(p_context);
    }
}

std::string cxmodel::Model::GetName() const
{
    return std::string{NAME};
}

std::string cxmodel::Model::GetVersionNumber() const
{
    std::stringstream stream;

    stream << "v" << cxmodel::GetVersionMajor() << "." << cxmodel::GetVersionMinor();

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

void cxmodel::Model::CreateNewGame(NewGameInformation p_gameInformation)
{
    PRECONDITION(p_gameInformation.m_gridWidth > 0);
    PRECONDITION(p_gameInformation.m_gridHeight > 0);
    PRECONDITION(p_gameInformation.m_inARowValue > 1);
    PRECONDITION(p_gameInformation.m_players.size() > 1);

    //PRECONDITION(std::all_of(p_gameInformation.GetNewPlayers().cbegin(),
    //                         p_gameInformation.GetNewPlayers().cend(),
    //                         [](const cxmodel::Player& p_player)
    //                         {
    //                            return !p_player.GetName().empty();
    //                         }));

    std::unique_ptr<ICommand> command = std::make_unique<CommandCreateNewGame>(*this, m_board, m_playersInfo.m_players, m_inARowValue, std::move(p_gameInformation));
    IF_CONDITION_NOT_MET_DO(command, return;);
    command->Execute();

    // WARNING: p_gameInformation has been moved from. Do not use anymore.

    IF_CONDITION_NOT_MET_DO(m_board, return;);

    m_winResolutionStrategy = GameResolutionStrategyFactory::Make(*m_board, m_inARowValue, m_playersInfo.m_players, m_takenPositions, GameResolution::WIN);
    IF_CONDITION_NOT_MET_DO(m_winResolutionStrategy, return;);

    m_tieResolutionStrategy = GameResolutionStrategyFactory::Make(*m_board, m_inARowValue, m_playersInfo.m_players, m_takenPositions, GameResolution::TIE);
    IF_CONDITION_NOT_MET_DO(m_tieResolutionStrategy, return;);

    Notify(ModelNotificationContext::CREATE_NEW_GAME);

    std::ostringstream stream;

    stream << "New game created: " <<
              "In-a-row value=" << m_inARowValue <<
              ", Grid dimensions=(W" << m_board->GetNbColumns() << ", H" << m_board->GetNbRows() << ")"
              ", Number of players=" << m_playersInfo.m_players.size();

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());

    CheckInvariants();
}

void cxmodel::Model::DropChip(const cxmodel::IChip& p_chip, size_t p_column)
{
    IF_PRECONDITION_NOT_MET_DO(m_board, return;);
    IF_PRECONDITION_NOT_MET_DO(p_column < m_board->GetNbColumns(), return;);

    // Here, we take a copy of the active player's index. If it is updated after the drop,
    // it means the drop worked and we can notify:
    const size_t activePlayerIndexBefore = m_playersInfo.m_activePlayerIndex;
    const size_t nextPlayerIndexBefore = m_playersInfo.m_nextPlayerIndex;

    const auto activePlayer = m_playersInfo.m_players[m_playersInfo.m_activePlayerIndex];
    if(!INL_PRECONDITION(activePlayer->GetChip() == p_chip))
    {
        const IChip& activePlayerChip = activePlayer->GetChip();
        std::ostringstream logStream;
        logStream << "Active player's color: (" << activePlayerChip.GetColor().R() << ", "
                                                << activePlayerChip.GetColor().G() << ", "
                                                << activePlayerChip.GetColor().B() << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

        logStream.str("");
        logStream << "Dropped disc color: (" << p_chip.GetColor().R() << ", "
                                             << p_chip.GetColor().G() << ", "
                                             << p_chip.GetColor().B() << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, logStream.str());

        return;
    }

    if(!m_board->IsColumnFull(p_column))
    {
        std::unique_ptr<cxmodel::CommandDropChip> command = std::make_unique<CommandDropChip>(*m_board,
                                                                                              m_playersInfo,
                                                                                              std::make_unique<cxmodel::Disc>(p_chip.GetColor()),
                                                                                              p_column,
                                                                                              m_takenPositions);
        IF_CONDITION_NOT_MET_DO(command, return;);                                                                          
        command->Attach(this);
        m_cmdStack->Execute(std::move(command));

        std::ostringstream stream;
        const IBoard::Position& droppedPosition = m_takenPositions.back();
        stream << activePlayer->GetName() << "'s chip dropped at (" << droppedPosition.m_row << ", " << droppedPosition.m_column << ")";
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());
    }
    else
    {
        m_logger.Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip drop failed for " + activePlayer->GetName());
        Notify(ModelNotificationContext::CHIP_DROPPED_FAILED);
    }

    if(IsWon())
    {
        // In the case of a win, we must revert the next player -> active player update, since
        // the next player will never be able to play:
        m_playersInfo.m_activePlayerIndex = activePlayerIndexBefore;
        m_playersInfo.m_nextPlayerIndex = nextPlayerIndexBefore;

        Notify(ModelNotificationContext::GAME_WON);

        Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game won by : " + GetActivePlayer().GetName());

        CheckInvariants();

        return;
    }

    if(IsTie())
    {
        // In the case of a tie, we must revert the next player -> active player update, since
        // the next player will never be able to play:
        m_playersInfo.m_activePlayerIndex = activePlayerIndexBefore;
        m_playersInfo.m_nextPlayerIndex = nextPlayerIndexBefore;

        Notify(ModelNotificationContext::GAME_TIED);

        Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game tied!");

        CheckInvariants();

        return;
    }

    CheckInvariants();
}

void cxmodel::Model::MoveLeft()
{
    Notify(ModelNotificationContext::CHIP_MOVED_LEFT);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip moved left.");

    CheckInvariants();
}

void cxmodel::Model::MoveRight()
{
    Notify(ModelNotificationContext::CHIP_MOVED_RIGHT);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip moved right.");

    CheckInvariants();
}

void cxmodel::Model::EndCurrentGame()
{
    // Clear the command stack:
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return;);
    m_cmdStack->Clear();

    // Clean the game board:
    IF_CONDITION_NOT_MET_DO(m_board, return;);
    m_board.reset();

    // Clear all player information:
    m_playersInfo = {{}, 0u, 1u};

    // Reset the in-a-row value to its default:
    m_inARowValue = 4u;

    // Reset the position record:
    m_takenPositions.clear();

    Notify(ModelNotificationContext::GAME_ENDED);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game ended.");
}

void cxmodel::Model::ReinitializeCurrentGame()
{
    // Clear the command stack:
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return;);
    m_cmdStack->Clear();

    // Clean the game board:
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    const size_t boardHeight = m_board->GetNbRows();
    const size_t boardWidth = m_board->GetNbColumns();

    m_board = std::make_unique<Board>(boardHeight, boardWidth, *this);
    IF_CONDITION_NOT_MET_DO(m_board, return;);

    // Reset the position record:
    m_takenPositions.clear();

    // Replace players:
    m_playersInfo.m_activePlayerIndex = 0u;
    m_playersInfo.m_nextPlayerIndex = 1u;

    // The win resolution strategy has to be recreated, as the old reference to the board
    // was destroyed upon assignement:
    m_winResolutionStrategy = GameResolutionStrategyFactory::Make(*m_board, m_inARowValue, m_playersInfo.m_players, m_takenPositions, GameResolution::WIN);
    IF_CONDITION_NOT_MET_DO(m_winResolutionStrategy, return;);

    // Same thing for the tie resolution strategy:
    m_tieResolutionStrategy = GameResolutionStrategyFactory::Make(*m_board, m_inARowValue, m_playersInfo.m_players, m_takenPositions, GameResolution::TIE);
    IF_CONDITION_NOT_MET_DO(m_tieResolutionStrategy, return;);

    Notify(ModelNotificationContext::GAME_REINITIALIZED);

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game reinitialized.");
}

size_t cxmodel::Model::GetCurrentGridHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_board, return 0u;);

    return m_board->GetNbRows();
}

size_t cxmodel::Model::GetCurrentGridWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_board, return 0u;);

    return m_board->GetNbColumns();
}

size_t cxmodel::Model::GetCurrentInARowValue() const
{
    return m_inARowValue;
}

const cxmodel::IPlayer& cxmodel::Model::GetActivePlayer() const
{
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_players.size() >= 2, return GetDefaultActivePlayer(););

    return *m_playersInfo.m_players[m_playersInfo.m_activePlayerIndex];
}

const cxmodel::IPlayer& cxmodel::Model::GetNextPlayer() const
{
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_players.size() >= 2, return GetDefaultNextPlayer(););

    return *m_playersInfo.m_players[m_playersInfo.m_nextPlayerIndex];
}

const cxmodel::IChip& cxmodel::Model::GetChip(size_t p_row, size_t p_column) const
{
    if(p_row >= GetCurrentGridHeight() || p_column >= GetCurrentGridWidth())
    {
        return NO_DISC;
    }

    IF_CONDITION_NOT_MET_DO(m_board, return NO_DISC;);

    return m_board->GetChip({p_row, p_column});
}

bool cxmodel::Model::IsWon() const
{
    IF_CONDITION_NOT_MET_DO(m_winResolutionStrategy, return false;);

    return m_winResolutionStrategy->Handle(GetActivePlayer());
}

bool cxmodel::Model::IsTie() const
{
    IF_CONDITION_NOT_MET_DO(m_board, return false;);
    IF_CONDITION_NOT_MET_DO(m_tieResolutionStrategy, return false;);

    return m_tieResolutionStrategy->Handle(GetActivePlayer());
}

void cxmodel::Model::Undo()
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return;);

    m_cmdStack->Undo();

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Last action undoed.");

    CheckInvariants();
}

void cxmodel::Model::Redo()
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return;);

    m_cmdStack->Redo();

    Log(cxlog::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Last action redoed.");

    CheckInvariants();
}

bool cxmodel::Model::CanUndo() const
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return false;);

    return m_cmdStack->CanUndo();
}

bool cxmodel::Model::CanRedo() const
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return false;);

    return m_cmdStack->CanRedo();
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
    INVARIANT(m_cmdStack);
}

size_t cxmodel::Model::ComputeNextDropColumn(DropColumnComputation p_algorithm) const
{
    (void)p_algorithm;
    return 0u;
}
