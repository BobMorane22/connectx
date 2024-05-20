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
 * @file INewPlayersList.h
 * @date 2022
 *
 *************************************************************************************************/

#ifndef INEWPLAYERSLIST_H_683F8110_A4C7_4915_A304_7940FD621B84
#define INEWPLAYERSLIST_H_683F8110_A4C7_4915_A304_7940FD621B84

#include <functional>
#include <string>
#include <vector>

#include <cxmodel/ChipColor.h>
#include <cxmodel/IPlayer.h>
#include <cxgui/IWidget.h>

namespace cxmodel
{
    enum class PlayerType;
}

namespace cxgui
{
    class INewGameViewPresenter;
}

namespace cxgui
{

/***********************************************************************************************//**
 * @brief Interface for a widget to list players.
 *
 * Widget containing rows of players to be registered for a Connect X game, as well as the color
 * they have chosen for their chips.
 *
 **************************************************************************************************/
class INewPlayersList : public cxgui::IWidget
{ 

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~INewPlayersList() = default;

    /*******************************************************************************************//**
     * @brief Accesses the number of players in the list.
     *
     * @return
     *      The number of players in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual size_t GetNbPlayers() const = 0;

    /*******************************************************************************************//**
     * @brief Accesses a specific row's player chip color.
     *
     * For a given row index, gets the specific row's player chip color.
     *
     * @param p_index
     *      The row index.
     *
     * @pre
     *      The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return
     *      The row's player chip color.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual cxmodel::ChipColor GetRowPlayerChipColor(
        const size_t p_index) const = 0;

    /*******************************************************************************************//**
     * @brief Accesses a specific row's player name.
     *
     * For a given row index, gets the specific row's player name.
     *
     * @param p_index
     *      The row index.
     *
     * @pre
     *      The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return
     *      The row's player name.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::string GetPlayerNameAtRow(
        const size_t p_index) const = 0;

    /*******************************************************************************************//**
     * @brief Accesses all player chip colors in the list.
     *
     * @return
     *      An @c std::vector containing all the player chip colors in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::vector<cxmodel::ChipColor> GetAllColors() const = 0;

    /*******************************************************************************************//**
     * @brief Accesses all player names in the list.
     *
     * @return
     *      An @c std::vector containing all the player names in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::vector<std::string> GetAllPlayerNames() const = 0;

    /*******************************************************************************************//**
     * @brief Accesses all player types in the list.
     *
     * @return
     *      An @c std::vector containing all the player types in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::vector<cxmodel::PlayerType> GetAllPlayerTypes() const = 0;

    /*******************************************************************************************//**
     * @brief Adds a player to the list.
     *
     * Adds a player to the list. The player is appended at the end of the list.
     *
     * @param p_presenter
     *      A New Game view compatible presenter.
     *
     * @param p_rowIndex
     *      The new row index.
     *
     * @pre
     *      The player's row index is not bigger than the maximum players allowed.
     *
     * @return
     *      `true` if the row could be added, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual bool AddPlayer(
        const INewGameViewPresenter& p_presenter,
        size_t p_rowIndex) = 0;

    /*******************************************************************************************//**
     * @brief Removes a player from the list, by index.
     *
     * @param p_index
     *      The player's row index in the list.
     *
     * @pre
     *      The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return
     *      `true` if the specified player was successfully removed, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual bool RemovePlayer(
        const size_t p_index) = 0;

    /*******************************************************************************************//**
     * @brief Updates a player, by index.
     *
     * Updates player information from its index in the list. You can update the player name and
     * the player chip color.
     *
     * @param p_index
     *      The row index.
     *
     * @param p_newPlayerNewName
     *      The player name.
     *
     * @param p_newPlayerNewChipColor
     *      The player chip color.
     *
     * @param p_newPlayerType
     *      The player type (human or bot).
     *
     * @pre
     *      The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @pre
     *      The player name is not an empty string.
     *
     * @return
     *      `true` if the specified row was successfully updated, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual bool UpdatePlayer(
        const size_t p_index,
        const std::string& p_newPlayerNewName,
        const cxmodel::ChipColor& p_newPlayerNewChipColor,
        cxmodel::PlayerType p_newPlayerType) = 0;

    /***********************************************************************************************
     * @brief Connects a slot to be called when the row is updated.
     *
     * @param p_slot
     *      The slot to call.
     *
     **********************************************************************************************/
    virtual void RowUpdatedSignalConnect(
        const std::function<void()>& p_slot) = 0;

};

} // namespace cxgui

#endif // INEWPLAYERSLIST_H_683F8110_A4C7_4915_A304_7940FD621B84
