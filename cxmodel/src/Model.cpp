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
#include <cxmodel/CommandCompletionStatus.h>
#include <cxmodel/CommandCreateNewGame.h>
#include <cxmodel/CommandDropChip.h>
#include <cxmodel/CommandStack.h>
#include <cxmodel/Disc.h>
#include <cxmodel/GameResolutionStrategyFactory.h>
#include <cxmodel/INextDropColumnComputationStrategy.h>
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

const cx::model::Disc NO_DISC{cx::model::MakeTransparent()};

const cx::model::IPlayer& GetDefaultActivePlayer()
{
    static auto player = CreatePlayer("Woops (active)!", {0, 0, 0, 0}, cx::model::PlayerType::HUMAN);
    return *player;
}

const cx::model::IPlayer& GetDefaultNextPlayer()
{
    static auto player = CreatePlayer("Woops (next)!", {0, 0, 0, 0}, cx::model::PlayerType::HUMAN);
    return *player;
}

} // namespace

cx::model::Model::Model(std::unique_ptr<ICommandStack>&& p_cmdStack, cx::log::ILogger& p_logger)
 : m_logger{p_logger}
 , m_cmdStack{std::move(p_cmdStack)}
 , m_currentDropCommands{nullptr}
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

cx::model::Model::~Model()
{
    DetatchAll();
}

void cx::model::Model::Update(cx::model::ModelNotificationContext p_context, cx::model::ModelSubject* p_subject)
{
    if(INL_ASSERT(p_subject))
    {
        Notify(p_context);
    }
}

std::string cx::model::Model::GetName() const
{
    return std::string{NAME};
}

std::string cx::model::Model::GetVersionNumber() const
{
    std::stringstream stream;

    stream << "v" << cx::model::GetVersionMajor() << "." << cx::model::GetVersionMinor();

    return stream.str();
}

size_t cx::model::Model::GetMinimumGridHeight() const
{
    return GRID_MIN_HEIGHT;
}

size_t cx::model::Model::GetMinimumGridWidth() const
{
    return GRID_MIN_WIDTH;
}

size_t cx::model::Model::GetMinimumInARowValue() const
{
    return IN_A_ROW_MIN;
}

size_t cx::model::Model::GetMaximumGridHeight() const
{
    return GRID_MAX_HEIGHT;
}

size_t cx::model::Model::GetMaximumGridWidth() const
{
    return GRID_MAX_WIDTH;
}

size_t cx::model::Model::GetMaximumInARowValue() const
{
    return IN_A_ROW_MAX;
}

size_t cx::model::Model::GetMinimumNumberOfPlayers() const
{
    return NUMBER_OF_PLAYERS_MIN;
}

size_t cx::model::Model::GetMaximumNumberOfPlayers() const
{
    return NUMBER_OF_PLAYERS_MAX;
}

void cx::model::Model::CreateNewGame(NewGameInformation p_gameInformation)
{
    PRECONDITION(p_gameInformation.m_gridWidth > 0);
    PRECONDITION(p_gameInformation.m_gridHeight > 0);
    PRECONDITION(p_gameInformation.m_inARowValue > 1);
    PRECONDITION(p_gameInformation.m_players.size() > 1);

    //PRECONDITION(std::all_of(p_gameInformation.GetNewPlayers().cbegin(),
    //                         p_gameInformation.GetNewPlayers().cend(),
    //                         [](const cx::model::Player& p_player)
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

    ComputeNextDropColumn(DropColumnComputation::RANDOM);

    Notify(ModelNotificationContext::CREATE_NEW_GAME);

    std::ostringstream stream;

    stream << "New game created: " <<
              "In-a-row value=" << m_inARowValue <<
              ", Grid dimensions=(W" << m_board->GetNbColumns() << ", H" << m_board->GetNbRows() << ")"
              ", Number of players=" << m_playersInfo.m_players.size();

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, stream.str());

    CheckInvariants();
}

void cx::model::Model::DropChip(const cx::model::IChip& p_chip, size_t p_column)
{
    IF_PRECONDITION_NOT_MET_DO(m_board, return;);
    IF_PRECONDITION_NOT_MET_DO(p_column < m_board->GetNbColumns(), return;);

    // Before executing the drop, we take a copy of these indexes for later usage:
    const size_t activePlayerIndexBefore = m_playersInfo.m_activePlayerIndex;
    const size_t nextPlayerIndexBefore = m_playersInfo.m_nextPlayerIndex;

    // We create the command and execute the drop:
    auto command = std::make_unique<CommandDropChip>(*m_board,
                                                     m_playersInfo,
                                                     std::make_unique<cx::model::Disc>(p_chip.GetColor()),
                                                     p_column,
                                                     m_takenPositions,
                                                     m_logger);
    IF_CONDITION_NOT_MET_DO(command, return;);                                                                          
    command->Attach(this);

    // We save this condition for later because once the command is executed,
    // the next player is not the same:
    const bool shouldResetDropCommands = !GetNextPlayer().IsManaged();
    if(!GetActivePlayer().IsManaged())
    {
        auto dropCommands = std::make_unique<CompositeCommand>();
        IF_CONDITION_NOT_MET_DO(dropCommands, return;);

        dropCommands->Add(std::move(command));

        m_currentDropCommands = dropCommands.get();

        IF_CONDITION_NOT_MET_DO(m_cmdStack->Execute(std::move(dropCommands)) <= CommandCompletionStatus::FAILED_EXPECTED, return;);

        if(shouldResetDropCommands)
        {
            m_currentDropCommands = nullptr;
        }
    }
    else
    {
        IF_CONDITION_NOT_MET_DO(command->Execute() == CommandCompletionStatus::SUCCESS, return;);

        if(m_currentDropCommands)
        {
            m_currentDropCommands->Add(std::move(command));
        }

        if(shouldResetDropCommands)
        {
            m_currentDropCommands = nullptr;
        }
    }

    // Won and tie checks come next. They are not part of the command because they never
    // have to be rechecked once the initial drop is done. Undoing or redoing a drop can
    // never lead to a win or a tie if the initial drop didn't.
    if(IsWon())
    {
        // In the case of a win, we must revert the next player -> active player update, since
        // the next player will never be able to play:
        m_playersInfo.m_activePlayerIndex = activePlayerIndexBefore;
        m_playersInfo.m_nextPlayerIndex = nextPlayerIndexBefore;

        Notify(ModelNotificationContext::GAME_WON);

        Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game won by : " + GetActivePlayer().GetName());

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

        Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game tied!");

        CheckInvariants();

        return;
    }

    ComputeNextDropColumn(DropColumnComputation::RANDOM);

    CheckInvariants();
}

void cx::model::Model::MoveLeftOneColumn()
{
    Notify(ModelNotificationContext::CHIP_MOVED_LEFT_ONE_COLUMN);

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip moved left one column.");

    CheckInvariants();
}

void cx::model::Model::MoveRightOneColumn()
{
    Notify(ModelNotificationContext::CHIP_MOVED_RIGHT_ONE_COLUMN);

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Chip moved right one column.");

    CheckInvariants();
}

void cx::model::Model::EndCurrentGame()
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

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game ended.");
}

void cx::model::Model::ReinitializeCurrentGame()
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

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Game reinitialized.");
}

size_t cx::model::Model::GetCurrentGridHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_board, return 0u;);

    return m_board->GetNbRows();
}

size_t cx::model::Model::GetCurrentGridWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_board, return 0u;);

    return m_board->GetNbColumns();
}

size_t cx::model::Model::GetCurrentInARowValue() const
{
    return m_inARowValue;
}

const cx::model::IPlayer& cx::model::Model::GetActivePlayer() const
{
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_players.size() >= 2, return GetDefaultActivePlayer(););

    return *m_playersInfo.m_players[m_playersInfo.m_activePlayerIndex];
}

const cx::model::IPlayer& cx::model::Model::GetNextPlayer() const
{
    IF_CONDITION_NOT_MET_DO(m_playersInfo.m_players.size() >= 2, return GetDefaultNextPlayer(););

    return *m_playersInfo.m_players[m_playersInfo.m_nextPlayerIndex];
}

const cx::model::IChip& cx::model::Model::GetChip(size_t p_row, size_t p_column) const
{
    if(p_row >= GetCurrentGridHeight() || p_column >= GetCurrentGridWidth())
    {
        return NO_DISC;
    }

    IF_CONDITION_NOT_MET_DO(m_board, return NO_DISC;);

    return m_board->GetChip({p_row, p_column});
}

bool cx::model::Model::IsWon() const
{
    IF_CONDITION_NOT_MET_DO(m_winResolutionStrategy, return false;);

    return m_winResolutionStrategy->Handle(GetActivePlayer());
}

bool cx::model::Model::IsTie() const
{
    IF_CONDITION_NOT_MET_DO(m_board, return false;);
    IF_CONDITION_NOT_MET_DO(m_tieResolutionStrategy, return false;);

    return m_tieResolutionStrategy->Handle(GetActivePlayer());
}

void cx::model::Model::Undo()
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return;);

    m_cmdStack->Undo();

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Last action undoed.");

    CheckInvariants();
}

void cx::model::Model::Redo()
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return;);

    m_cmdStack->Redo();

    Log(cx::log::VerbosityLevel::DEBUG, __FILE__, __FUNCTION__, __LINE__, "Last action redoed.");

    CheckInvariants();
}

bool cx::model::Model::CanUndo() const
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return false;);

    return m_cmdStack->CanUndo();
}

bool cx::model::Model::CanRedo() const
{
    IF_CONDITION_NOT_MET_DO(m_cmdStack, return false;);

    return m_cmdStack->CanRedo();
}

void cx::model::Model::Log(const cx::log::VerbosityLevel p_verbosityLevel, const std::string& p_fileName, const std::string& p_functionName, const size_t p_lineNumber, const std::string& p_message)
{
    m_logger.Log(p_verbosityLevel, p_fileName, p_functionName, p_lineNumber, p_message);

    CheckInvariants();
}

void cx::model::Model::SetVerbosityLevel(const cx::log::VerbosityLevel p_verbosityLevel)
{
    m_logger.SetVerbosityLevel(p_verbosityLevel);

    CheckInvariants();
}

cx::log::VerbosityLevel cx::model::Model::GetVerbosityLevel() const
{
    return m_logger.GetVerbosityLevel();
}

void cx::model::Model::ComputeNextDropColumn(DropColumnComputation p_algorithm)
{
    auto strategy = NextDropColumnComputationStrategyCreate(p_algorithm);
    IF_CONDITION_NOT_MET_DO(strategy, return;);

    m_botTarget = strategy->Compute(*m_board);

    CheckInvariants();
}

size_t cx::model::Model::GetCurrentBotTarget() const
{
    return m_botTarget;
}

void cx::model::Model::CheckInvariants()
{
    INVARIANT(m_cmdStack);

    if(m_board)
    {
        INVARIANT(m_botTarget < GetCurrentGridWidth());
    }
}

