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
 * @file IPlayer.cpp
 * @date 2022
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxmodel/ChipColor.h>
#include <cxmodel/Disc.h>
#include <cxmodel/IPlayer.h>

namespace cx::model
{

/*************************************************************************************************
 * @brief Connect X Player null object.
 *
 * This player should never exist in Connect X. It is the default player returned by the
 * factory when creation fails.
 *
 ************************************************************************************************/
class NoPlayer final : public IPlayer
{

public:

    NoPlayer()
    {
        m_chip = std::make_unique<Disc>(cx::model::MakeTransparent());
    }

    [[nodiscard]] std::string GetName() const override {return {};}
    [[nodiscard]] const IChip& GetChip() const override {return *m_chip;}
    [[nodiscard]] bool IsManaged() const override {return false;}

private:

     std::unique_ptr<IChip> m_chip;

};

/*************************************************************************************************
 * @brief Abstract Connect X player.
 *
 * In Connect X, all players have a name and an associated chip. This base class regroups this
 * information to avoid duplication. It should never be used externally.
 *
 ************************************************************************************************/
class Player : public IPlayer
{

public:

    /**********************************************************************************************
     * @brief Constructor.
     *
     * @pre The player name is not empty.
     *
     * @param p_name      The player name.
     * @param p_chipColor The player's chip color.
     *
     ********************************************************************************************/
    Player(const std::string& p_name, const ChipColor& p_chipColor)
    : m_name{p_name}
    , m_chip{std::make_unique<cx::model::Disc>(p_chipColor)}
    {
        PRECONDITION(!p_name.empty());
    }

    /**********************************************************************************************
     * @brief Copy assignment operator.
     *
     * @param p_player The player to copy-assign.
     *
     ********************************************************************************************/
    Player& operator=(const Player& p_player);

    // cx::model::IPlayer:
    [[nodiscard]] std::string GetName() const override {return m_name;};
    [[nodiscard]] const IChip& GetChip() const override {return *m_chip;};
    [[nodiscard]] bool IsManaged() const override = 0;

private:

    std::string m_name;
    std::unique_ptr<IChip> m_chip;

};

/*************************************************************************************************
 * @brief Human Connect X player.
 *
 * This is a Connect X player which represents a real human being, playing the game. His moves
 * are not managed by Connect X.
 *
 ************************************************************************************************/
class HumanPlayer final : public Player
{

public:

    /**********************************************************************************************
     * @brief Constructor.
     *
     * @pre The player name is not empty.
     *
     * @param p_name      The player name.
     * @param p_chipColor The player's chip color.
     *
     ********************************************************************************************/
    HumanPlayer(const std::string& p_name, const ChipColor& p_chipColor)
    : Player(p_name, p_chipColor)
    {
    }

    // cx::model::IPlayer:
    [[nodiscard]] bool IsManaged() const override {return false;}

};

/*************************************************************************************************
 * @brief Non-human Connect X player.
 *
 * This is a Connect X player which does not represents a real human being. It only exists to
 * add the illusion more players participate in a game. They are reffered to as bots.
 *
 ************************************************************************************************/
class BotPlayer final : public Player
{

public:

    /**********************************************************************************************
     * @brief Constructor.
     *
     * @pre The player name is not empty.
     *
     * @param p_name      The player name.
     * @param p_chipColor The player's chip color.
     *
     ********************************************************************************************/
    BotPlayer(const std::string& p_name, const ChipColor& p_chipColor)
    : Player(p_name, p_chipColor)
    {
    }

    // cx::model::IPlayer:
    [[nodiscard]] bool IsManaged() const override {return true;}

};

} // namespace cx::model

[[nodiscard]] std::unique_ptr<cx::model::IPlayer> cx::model::CreatePlayer(const std::string& p_name,
                                                                      const ChipColor& p_chipColor,
                                                                      PlayerType p_type)
{
    std::unique_ptr<cx::model::IPlayer> player = std::make_unique<NoPlayer>();

    IF_PRECONDITION_NOT_MET_DO(!p_name.empty(), return player;);

    switch(p_type)
    {
        case cx::model::PlayerType::HUMAN:
            return std::make_unique<HumanPlayer>(p_name, p_chipColor);

        case cx::model::PlayerType::BOT:
            return std::make_unique<BotPlayer>(p_name, p_chipColor);

        default:
            ASSERT_ERROR_MSG("Unknown player type.");
            break;
    }

    return player;
}

bool cx::model::operator==(const cx::model::IPlayer& p_lhs, const cx::model::IPlayer& p_rhs)
{
    return (p_lhs.GetChip() == p_rhs.GetChip()) && (p_lhs.IsManaged() == p_rhs.IsManaged());
}

bool cx::model::operator!=(const cx::model::IPlayer& p_lhs, const cx::model::IPlayer& p_rhs)
{
    return !(p_lhs == p_rhs);
}
