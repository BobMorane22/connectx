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
 * @file NewPlayerList.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef NEWPLAYERLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724
#define NEWPLAYERLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724

#include <string>
#include <vector>

#include <cxmodel/ChipColor.h>

#include <gtkmm/listbox.h>

namespace cxgui
{

class INewGameViewPresenter;
class NewPlayerRow;
class NewPlayerTitleRow;

}

namespace cxgui
{

/***********************************************************************************************//**
 * @brief Widget to list players.
 *
 * Widget containing rows of players to be registered for a Connect X game, as well as the color
 * they have chosen for their discs.
 *
 * @see cxgui::NewPlayerRow
 *
 **************************************************************************************************/
class NewPlayersList final : public Gtk::ListBox
{

public:

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Constructs a list of two players with different colors. This is the basic Connect X
     * configuration, and is equivalent to the classic Connect 4 requirements.
     *
     **********************************************************************************************/
    NewPlayersList(const INewGameViewPresenter& p_presenter);

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~NewPlayersList();

    /*******************************************************************************************//**
     * @brief Accesses the size of the list.
     *
     * The size of the list is the number of players (visually, the number of rows) contained
     * in the widget.
     *
     * @return The size of the list.
     *
     **********************************************************************************************/
    [[nodiscard]] std::size_t GetSize() const;

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
    [[nodiscard]] cxmodel::ChipColor GetRowPlayerDiscColor(const std::size_t p_index) const;

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
    [[nodiscard]] std::string GetPlayerNameAtRow(const std::size_t p_index) const;

    /*******************************************************************************************//**
     * @brief Accesses all player disc colors in the list.
     *
     * @return An @c std::vector containing all the player disc colors in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] std::vector<cxmodel::ChipColor> GetAllColors() const;

    /*******************************************************************************************//**
     * @brief Accesses all player names in the list.
     *
     * @return An @c std::vector containing all the player names in the list.
     *
     **********************************************************************************************/
    [[nodiscard]] std::vector<std::string> GetAllPlayerNames() const;

    /*******************************************************************************************//**
     * @brief Adds a row to the list.
     *
     * Adds a row to the list. The row is appended at the end of the list.
     *
     * @param p_playerNewName      The player's name.
     * @param p_playerNewDiscColor The player's disc color.
     * @param p_playerNewType      The player's new type (human or bot).
     *
     * @pre The player name is not an empty string.
     *
     * @return `true` if the row could be added, `false` otherwise.
     *
     * @see cxutil::ReturnCode
     *
     **********************************************************************************************/
    [[nodiscard]] bool AddRow(const std::string& p_playerNewName,
                              const cxmodel::ChipColor& p_playerNewDiscColor,
                              cxmodel::PlayerType p_playerNewType);

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
    [[nodiscard]] bool RemoveRow(const std::size_t p_index);

    /*******************************************************************************************//**
     * @brief Removes a row from the list.
     *
     * Removes a row from the list. The row must match a given player name and disc color.. If
     * the player name and the disc color pair is not found, an error is returned and nothing
     * is removed.
     *
     * @param p_playerName      The player's name.
     * @param p_playerDiscColor The player's disc color.
     * @param p_playerType      The player's type (human or bot).
     *
     * @pre The player name is not an empty string.
     *
     * @return `true` if the specified row was successfully removed, `false` otherwise.
     *
     **********************************************************************************************/
    [[nodiscard]] bool RemoveRow(const std::string& p_playerName,
                                 const cxmodel::ChipColor& p_playerDiscColor,
                                 cxmodel::PlayerType p_playerType);

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
    [[nodiscard]] bool UpdateRow(const std::size_t p_index,
                                 const std::string& p_newPlayerNewName,
                                 const cxmodel::ChipColor& p_newPlayerNewDiscColor,
                                 cxmodel::PlayerType p_newPlayerType);

    /*******************************************************************************************//**
     * @brief Clears the list content.
     *
     * Removes every players in the list, leaving the container empty (visually, there are
     * no rows left).
     *
     * @post The list is empty (no more rows).
     *
     **********************************************************************************************/
    void Clear();

private:

    // This friendship is needed because the top row needs to make its child widgets'
    // dimensions available to the list so they can be passed on the the list titles.
    // Otherwise, it is impossible for the list titles to fit with the column contents.
    friend NewPlayerRow;

    struct ColumnWidth
    {
        int m_first = 0u;
        int m_second = 0u;
        int m_third = 0u;
    };

    ColumnWidth m_columnWidths;

    std::unique_ptr<NewPlayerTitleRow> m_titleRow;

    const cxgui::NewPlayerRow* GetRow(const size_t p_index) const;
    cxgui::NewPlayerRow* GetRow(const size_t p_index);

    std::vector<const cxgui::NewPlayerRow*> GetRows() const;
    std::vector<cxgui::NewPlayerRow*> GetRows();

    void AddColumnHeaders();
    void FitColumnHeaders();

    bool RemoveManaged(cxgui::NewPlayerRow* p_row);

};

} // namespace cxgui

#endif // NEWPLAYERLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724
