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
 * @file NewPlayerList.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtkmm/entry.h>
#include <gtkmm/grid.h>

#include <cxinv/include/assertion.h>
#include <cxgui/include/ColorComboBox.h>

#include <NewPlayerList.h>

namespace cxgui
{

/***********************************************************************************************//**
 * @class NewPlayerRow
 *
 * @brief This widget represents the new information needed by the application to register a
 *        new player.
 *
 * The informations needed are:
 *
 * <ul>
 *   <li> The player's name       </li>
 *   <li> The player's disc color </li>
 * </ul>
 *
 * This widget is not intended to be used by itself. Rather, it should be bundled together in
 * some Gtk::ListBox widget with others like it. @c cxexec::NewPlayersList is an example.
 *
 * @invariant The member variable @c m_playerName does not contain an empty string.
 *
 * @see cxexec::NewPlayersList
 *
 **************************************************************************************************/
class NewPlayerRow final : public Gtk::ListBoxRow
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * @param p_playerName       The name of the player.
     * @param p_playerDiscColor  The color chosen by or for the player's disc.
     *
     **********************************************************************************************/
    NewPlayerRow(const std::string& p_playerName, const cxmodel::ChipColor& p_playerDiscColor);

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~NewPlayerRow();

    /*******************************************************************************************//**
     * @brief Updates the player's information. The name and the disc color can be changed.
     *
     * @param p_playerNewName       The new name of the player.
     * @param p_playerNewDiscColor  The new color chosen by or for the player's disc.
     *
     **********************************************************************************************/
    void Update(const std::string& p_playerNewName, const cxmodel::ChipColor& p_playerNewDiscColor);

    /*******************************************************************************************//**
     * @brief  Accessor for the player's name.
     *
     * @return The player's actual name as a string.
     *
     **********************************************************************************************/
    std::string GetPlayerName() const;

    /*******************************************************************************************//**
     * @brief Accessor for the player's disc color.
     *
     * @return The player's actual disc color.
     *
     **********************************************************************************************/
    cxmodel::ChipColor GetPlayerDiscColor() const;

private:

    void CheckInvariants() const;

    Gtk::Grid m_layout;
    Gtk::Entry m_playerName;
    cxgui::ColorComboBox m_playerDiscColor;

};

/***********************************************************************************************//**
 * @brief Equality operator.
 *
 * Checks if two @c NewPlayerRow are equal. Two @c NewPlayerRow are equal <em>if and only if</em>
 * they share the same player name and the same player disc color.
 *
 * @param p_lhs The first @NewPlayerRow object to compare against.
 * @param p_rhs The second @NewPlayerRow object to compare against.
 *
 * @return @c true if both objects are considered equal @c false otherwise.
 *
 **************************************************************************************************/
bool operator==(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs);

/***********************************************************************************************//**
 * @brief Non-equality operator.
 *
 * Checks if two @c NewPlayerRow are NOT equal. Two @c NewPlayerRow are NOT equal if they differ
 * in their player names and/or in their player disc colors.
 *
 * @param p_lhs The first @NewPlayerRow object to compare against.
 * @param p_rhs The second @NewPlayerRow object to compare against.
 *
 * @return @return @c true if both objects are considered NOT equal @c false otherwise.
 *
 **************************************************************************************************/
bool operator!=(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs);

} // namespace cxgui

cxgui::NewPlayerRow::NewPlayerRow(const std::string& p_playerName, const cxmodel::ChipColor& p_playerDiscColor)
{
    PRECONDITION(!p_playerName.empty());

    m_playerName.set_text(p_playerName);

    // Add color to the combo box:
    m_playerDiscColor.SetCurrentSelection(p_playerDiscColor);

    // Populate the row layout for the ListView:
    m_layout.add(m_playerName);
    m_layout.add(m_playerDiscColor);

    // Make sure the player name combobox scales horizontally, but not the disc
    // color picker button:
    m_layout.set_column_homogeneous(true);
    m_playerName.set_hexpand(true);

    // Make sure columns have the same width:
    m_playerDiscColor.set_hexpand(true);

    add(m_layout);

    CheckInvariants();
}

cxgui::NewPlayerRow::~NewPlayerRow() = default;

void cxgui::NewPlayerRow::Update(const std::string& p_playerNewName, const cxmodel::ChipColor& p_playerNewDiscColor)
{
    PRECONDITION(!p_playerNewName.empty());

    m_playerName.set_text(p_playerNewName);
    m_playerDiscColor.SetCurrentSelection(p_playerNewDiscColor);

    CheckInvariants();
}

std::string cxgui::NewPlayerRow::GetPlayerName() const
{
    return m_playerName.get_text();
}

cxmodel::ChipColor cxgui::NewPlayerRow::GetPlayerDiscColor() const
{
    return m_playerDiscColor.GetCurrentSelection();
}

void cxgui::NewPlayerRow::CheckInvariants() const
{
    INVARIANT(!m_playerName.get_text().empty());
}

bool cxgui::operator==(const cxgui::NewPlayerRow& p_lhs, const cxgui::NewPlayerRow& p_rhs)
{
    return (p_lhs.GetPlayerName() == p_rhs.GetPlayerName()) &&
           (p_lhs.GetPlayerDiscColor() == p_rhs.GetPlayerDiscColor());
}

bool cxgui::operator!=(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs)
{
    return !(p_lhs == p_rhs);
}

cxgui::NewPlayersList::NewPlayersList()
{
    // We use Gtk::manage here to let Gtkmm deal with the children deletions:
    add(*Gtk::manage(new NewPlayerRow("-- Player 1 --", cxmodel::MakeBlue())));
    add(*Gtk::manage(new NewPlayerRow("-- Player 2 --", cxmodel::MakeBlue())));
}

cxgui::NewPlayersList::~NewPlayersList() = default;

std::size_t cxgui::NewPlayersList::GetSize() const
{
    return get_children().size();
}

cxmodel::ChipColor cxgui::NewPlayersList::GetRowPlayerDiscColor(const std::size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    const cxgui::NewPlayerRow* specificRow{GetRow(p_index)};

    if(!ASSERT(specificRow))
    {
        return cxmodel::MakeTransparent();
    }

    return specificRow->GetPlayerDiscColor();
}

std::string cxgui::NewPlayersList::GetPlayerNameAtRow(const std::size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    const cxgui::NewPlayerRow* specificRow{GetRow(p_index)};

    if(!ASSERT(specificRow))
    {
        return {};
    }

    return specificRow->GetPlayerName();
}

std::vector<cxmodel::ChipColor> cxgui::NewPlayersList::GetAllColors() const
{
    std::vector<cxmodel::ChipColor> colors;

    for(const auto row : GetRows())
    {
        colors.push_back(row->GetPlayerDiscColor());
    }

    return colors;
}

std::vector<std::string> cxgui::NewPlayersList::GetAllPlayerNames() const
{
    std::vector<std::string> names;

    for(const auto row : GetRows())
    {
        names.push_back(row->GetPlayerName());
    }

    return names;
}

bool cxgui::NewPlayersList::AddRow(const std::string& p_playerNewName, const cxmodel::ChipColor&  p_playerNewDiscColor)
{
    PRECONDITION(!p_playerNewName.empty());

    const std::size_t sizeBefore{GetSize()};

    add(*Gtk::manage(new NewPlayerRow(p_playerNewName, p_playerNewDiscColor)));

    const std::size_t sizeAfter{GetSize()};

    // We check if the new row has indeed been added:
    if(!ASSERT(sizeAfter == sizeBefore + 1))
    {
        return false;
    }

    return true;
}

bool cxgui::NewPlayersList::RemoveRow(const std::size_t p_index)
{
    PRECONDITION(p_index < GetSize());

    cxgui::NewPlayerRow* specificRow{GetRow(p_index)};

    if(!ASSERT(specificRow))
    {
        return false;
    }

    return RemoveManaged(specificRow);
}

bool cxgui::NewPlayersList::RemoveRow(const std::string& p_playerName, const cxmodel::ChipColor&  p_playerDiscColor)
{
    PRECONDITION(!p_playerName.empty());

    const cxgui::NewPlayerRow rowToRemoveData{p_playerName, p_playerDiscColor};
    cxgui::NewPlayerRow*      rowToRemoveAddress{nullptr};

    std::vector<cxgui::NewPlayerRow*> allRows = GetRows();

    for(auto row : allRows)
    {
        if(!ASSERT(row))
        {
            return false;
        }

        if(*row == rowToRemoveData)
        {
            // This is the address of the row we want to remove:
            rowToRemoveAddress = row;
        }
    }

    if(rowToRemoveAddress)
    {
        return RemoveManaged(rowToRemoveAddress);
    }

    return false;
}

bool cxgui::NewPlayersList::UpdateRow(const std::size_t p_index,
                                      const std::string& p_playerNewName,
                                      const cxmodel::ChipColor& p_playerNewDiscColor)
{
    PRECONDITION(p_index < GetSize());
    PRECONDITION(!p_playerNewName.empty());

    // All is fine, we can proceed with the update:
    cxgui::NewPlayerRow* rowToUpdate{GetRow(p_index)};
    if(!ASSERT(rowToUpdate))
    {
        return false;
    }

    rowToUpdate->Update(p_playerNewName, p_playerNewDiscColor);

    return true;
}

void cxgui::NewPlayersList::Clear()
{
    std::vector<NewPlayerRow*> allRows = GetRows();

    for(auto* row : allRows)
    {
        if(!ASSERT(row))
        {
            continue;
        }

        ASSERT(RemoveManaged(row));
    }

    // There should be no one left...
    POSTCONDITION(get_children().empty());
}

const cxgui::NewPlayerRow* cxgui::NewPlayersList::GetRow(const std::size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    // We get the address of all the non-internal children (const version):
    const std::vector<const Gtk::Widget*> rows = get_children();

    // We cast the needed widget to its most specific row type:
    const cxgui::NewPlayerRow* row = static_cast<const cxgui::NewPlayerRow*>(rows[p_index]);

    POSTCONDITION(row);

    return row;
}

cxgui::NewPlayerRow* cxgui::NewPlayersList::GetRow(const std::size_t p_index)
{
    PRECONDITION(p_index < GetSize());

    cxgui::NewPlayerRow* row{const_cast<cxgui::NewPlayerRow*>(static_cast<const cxgui::NewPlayersList*>(this)->GetRow(p_index))};

    POSTCONDITION(row);

    return row;
}

std::vector<const cxgui::NewPlayerRow*> cxgui::NewPlayersList::GetRows() const
{
    // We get the address of all the non-internal children:
    const std::vector<const Gtk::Widget*> baseRows = get_children();

    // We setup a new vector, with specific types:
    std::vector<const cxgui::NewPlayerRow*> specificRows;

    // We specialize every widget into its most specific type:
    for(auto row : baseRows)
    {
        specificRows.push_back(static_cast<const cxgui::NewPlayerRow*>(row));
    }

    POSTCONDITION(std::none_of(std::begin(specificRows),
                               std::end(specificRows),
                               [](const cxgui::NewPlayerRow* p_row)
                               {
                                   return p_row == nullptr;
                               }));

    return specificRows;
}

std::vector<cxgui::NewPlayerRow*> cxgui::NewPlayersList::GetRows()
{
    // We get the address of all the non-internal children:
    const std::vector<Gtk::Widget*> baseRows = get_children();

    // We setup a new vector, with specific types:
    std::vector<cxgui::NewPlayerRow*> specificRows;

    // We specialize every widget into its most specific type:
    for(auto row : baseRows)
    {
        specificRows.push_back(static_cast<cxgui::NewPlayerRow*>(row));
    }

    POSTCONDITION(std::none_of(std::begin(specificRows),
                               std::end(specificRows),
                               [](const cxgui::NewPlayerRow* p_row)
                               {
                                   return p_row == nullptr;
                               }));

    return specificRows;
}

bool cxgui::NewPlayersList::RemoveManaged(cxgui::NewPlayerRow* p_row)
{
    const std::vector<cxgui::NewPlayerRow*> allRows = GetRows();

    const bool rowDoesNotExist{std::none_of(std::begin(allRows),
                                            std::end(allRows),
                                            [p_row](const cxgui::NewPlayerRow* p_aRow)
                                            {
                                                return p_aRow == p_row;
                                            })};

    if(rowDoesNotExist)
    {
        return false;
    }

    const std::size_t nbRowsBefore{GetRows().size()};

    // Remove the row from the Gtk::Container:
    remove(*p_row);

    // Free it from the heap:
    delete(p_row);

    const std::size_t nbRowsAfter{GetRows().size()};

    if(!ASSERT(nbRowsBefore == nbRowsAfter + 1))
    {
        return false;
    }

    return true;
}
