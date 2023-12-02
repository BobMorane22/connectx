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
 * they have chosen for their discs.
 *
 **************************************************************************************************/
class INewPlayersList : public cxgui::IWidget
{ 
public:

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override = 0;
    [[nodiscard]] size_t GetHeight() const override = 0;
    void SetEnabled(EnabledState p_enabled) override = 0;
    void SetMargins(const Margins& p_newMarginSizes) override = 0;

public:

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~INewPlayersList() = default;

    /*******************************************************************************************//**
     * @brief Accesses the size of the list.
     *
     * The size of the list is the number of players (visually, the number of rows) contained
     * in the widget.
     *
     * @return The size of the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::size_t GetSize() const = 0;

    /*******************************************************************************************//**
     * @brief Accesses a specific row's player disc color.
     *
     * For a given row index, gets the specific row's player disc color.
     *
     * @param p_index The row index.
     *
     * @pre The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return The row's player disc color.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual cxmodel::ChipColor GetRowPlayerDiscColor(const std::size_t p_index) const = 0;

    /*******************************************************************************************//**
     * @brief Accesses a specific row's player name.
     *
     * For a given row index, gets the specific row's player name.
     *
     * @param p_index The row index.
     *
     * @pre The row index is at most the number of players in the list, minus one (zero-based).
     *
     * @return The row's player name.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::string GetPlayerNameAtRow(const std::size_t p_index) const = 0;

    /*******************************************************************************************//**
     * @brief Accesses all player disc colors in the list.
     *
     * @return An @c std::vector containing all the player disc colors in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::vector<cxmodel::ChipColor> GetAllColors() const = 0;

    /*******************************************************************************************//**
     * @brief Accesses all player names in the list.
     *
     * @return An @c std::vector containing all the player names in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::vector<std::string> GetAllPlayerNames() const = 0;

    /*******************************************************************************************//**
     * @brief Accesses all player types in the list.
     *
     * @return An @c std::vector containing all the player types in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual std::vector<cxmodel::PlayerType> GetAllPlayerTypes() const = 0;

    /*******************************************************************************************//**
     * @brief Adds a row to the list.
     *
     * Adds a row to the list. The row is appended at the end of the list.
     *
     * @param p_presenter A New Game view compatible presenter.
     * @param p_rowIndex The new row index.
     *
     * @pre The new row index is not bigger than the maximum players allowed.
     *
     * @return `true` if the row could be added, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual bool AddRow(const INewGameViewPresenter& p_presenter, size_t p_rowIndex) = 0;

    /*******************************************************************************************//**
     * @brief Removes a row from the list by its index.
     *
     * @param p_index The row index.
     *
     * @pre p_index The row index is at most the number of players in the list,
     *              minus one (zero-based).
     *
     * @return `true` if the specified row was successfully removed, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual bool RemoveRow(const std::size_t p_index) = 0;

    /*******************************************************************************************//**
     * @brief Updates a row from its index.
     *
     * Updates row information from its index. You can update the player name and the player disc
     * color.
     *
     * @param p_index                 The row index.
     * @param p_newPlayerNewName      The player name.
     * @param p_newPlayerNewDiscColor The player disc color.
     * @param p_newPlayerType         The player type (human or bot).
     *
     * @pre The row index is at most the number of players in the list, minus one (zero-based).
     * @pre The player name is not an empty string.
     *
     * @return `true` if the specified row was successfully updated, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] virtual bool UpdateRow(const std::size_t p_index,
                                         const std::string& p_newPlayerNewName,
                                         const cxmodel::ChipColor& p_newPlayerNewDiscColor,
                                         cxmodel::PlayerType p_newPlayerType) = 0;

    /*******************************************************************************************//**
     * @brief Clears the list content.
     *
     * Removes every players in the list, leaving the container empty (visually, there are
     * no rows left).
     *
     * @post The list is empty (no more rows).
     *
     **********************************************************************************************/
    virtual void Clear() = 0;

    /***********************************************************************************************
     * @brief Connects a slot to be called when the row is updated.
     *
     * @param p_slot The slot to call.
     *
     **********************************************************************************************/
    virtual void RowUpdatedSignalConnect(const std::function<void()>& p_slot) = 0;

};

} // namespace cxgui

#endif // INEWPLAYERSLIST_H_683F8110_A4C7_4915_A304_7940FD621B84
