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
#include <iostream>

#include <gtkmm/entry.h>
#include <gtkmm/grid.h>

#include <cxinv/assertion.h>
#include <cxmodel/IPlayer.h>
#include <cxgui/ColorComboBox.h>
#include <cxgui/common.h>
#include <cxgui/OnOffState.h>
#include <cxgui/OnOffSwitch.h>
#include <cxgui/NewPlayerList.h>

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
 *   <li> The player's type       </li>
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
     * @param p_type             A flag indicating if the player is human, or managed.
     *
     **********************************************************************************************/
    NewPlayerRow(const std::string& p_playerName,
                 const cxmodel::ChipColor& p_playerDiscColor,
                 cxmodel::PlayerType p_type);

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
     * @param p_newType             The new flag indicating if the player is human, or managed.
     *
     **********************************************************************************************/
    void Update(const std::string& p_playerNewName,
                const cxmodel::ChipColor& p_playerNewDiscColor,
                const cxmodel::PlayerType p_newType);

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

    /*******************************************************************************************//**
     * @brief Accessor for the player type (human or bot).
     *
     * @return The player's actual type.
     *
     **********************************************************************************************/
    [[nodiscard]] cxmodel::PlayerType GetPlayerType() const;

    void RetreiveDimensions(NewPlayersList& parent_)
    {

        auto* casted = dynamic_cast<cxgui::OnOffSwitch*>(m_typeSwitch.get());
        parent_.m_firstColumnWidth = casted->GetUnderlying().get_width();
        parent_.m_secondColumnWidth = m_playerName.get_width();
        parent_.m_thirdColumnWidth = m_playerDiscColor.get_width();
    }

private:

    void CheckInvariants() const;

    Gtk::Grid m_layout;
    std::unique_ptr<cxgui::IOnOffSwitch> m_typeSwitch; 
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

cxgui::NewPlayerRow::NewPlayerRow(const std::string& p_playerName,
                                  const cxmodel::ChipColor& p_playerDiscColor,
                                  const cxmodel::PlayerType p_type) 
{
    PRECONDITION(!p_playerName.empty());

    m_playerName.set_text(p_playerName);
    m_playerName.set_margin_end(cxgui::CONTROL_BOTTOM_MARGIN);

    // Add color to the combo box:
    m_playerDiscColor.SetCurrentSelection(p_playerDiscColor);

    // Populate the row layout for the ListView:
    auto typeSwitch = std::make_unique<cxgui::OnOffSwitch>();
    if(p_type == cxmodel::PlayerType::BOT) 
    {
        typeSwitch->SetState(cxgui::OnOffState::ON);
    }
    else
    {
        typeSwitch->SetState(cxgui::OnOffState::OFF);
    }

    Gtk::Switch& underlying = typeSwitch->GetUnderlying();
    underlying.set_valign(Gtk::Align::ALIGN_CENTER);
    underlying.set_halign(Gtk::Align::ALIGN_CENTER);
    underlying.set_margin_end(cxgui::CONTROL_BOTTOM_MARGIN);

    m_layout.add(underlying);
    m_typeSwitch = std::move(typeSwitch);
    m_layout.add(m_playerName);
    m_layout.add(m_playerDiscColor);

    m_playerName.set_hexpand(true);
    m_playerDiscColor.set_hexpand(true);

    add(m_layout);

    CheckInvariants();
}

cxgui::NewPlayerRow::~NewPlayerRow() = default;

void cxgui::NewPlayerRow::Update(const std::string& p_playerNewName,
                                 const cxmodel::ChipColor& p_playerNewDiscColor,
                                 const cxmodel::PlayerType p_newType)
{
    PRECONDITION(!p_playerNewName.empty());

    if(p_newType == cxmodel::PlayerType::BOT) 
    {
        m_typeSwitch->SetState(cxgui::OnOffState::ON);
    }
    else
    {
        m_typeSwitch->SetState(cxgui::OnOffState::OFF);
    }

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

cxmodel::PlayerType cxgui::NewPlayerRow::GetPlayerType() const
{
    if(m_typeSwitch->GetState() == cxgui::OnOffState::ON)
    {
        return cxmodel::PlayerType::BOT;
    }

    return cxmodel::PlayerType::HUMAN;
}

void cxgui::NewPlayerRow::CheckInvariants() const
{
    INVARIANT(!m_playerName.get_text().empty());
}

bool cxgui::operator==(const cxgui::NewPlayerRow& p_lhs, const cxgui::NewPlayerRow& p_rhs)
{
    return (p_lhs.GetPlayerName() == p_rhs.GetPlayerName()) &&
           (p_lhs.GetPlayerDiscColor() == p_rhs.GetPlayerDiscColor()) &&
           (p_lhs.GetPlayerType() == p_rhs.GetPlayerType());
}

bool cxgui::operator!=(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs)
{
    return !(p_lhs == p_rhs);
}

cxgui::NewPlayersList::NewPlayerTitleRow::NewPlayerTitleRow()
{
    m_isBotTitle.set_valign(Gtk::Align::ALIGN_CENTER);
    m_isBotTitle.set_halign(Gtk::Align::ALIGN_CENTER);
    m_isBotTitle.set_margin_end(cxgui::CONTROL_BOTTOM_MARGIN);

    m_playerNameTitle.set_hexpand(true);
    m_discColorTitle.set_hexpand(true);

    attach(m_isBotTitle, 0, 0, 1, 1);
    attach(m_playerNameTitle, 1, 0, 1, 1);
    attach(m_discColorTitle, 2, 0, 1, 1);
}

void cxgui::NewPlayersList::NewPlayerTitleRow::SetIsBotTitleWidth(int p_newWidth)
{
    m_isBotTitle.set_size_request(p_newWidth);
}

void cxgui::NewPlayersList::NewPlayerTitleRow::SetPlayerNameTitleWidth(int p_newWidth)
{
    m_playerNameTitle.set_size_request(p_newWidth);
}

void cxgui::NewPlayersList::NewPlayerTitleRow::SetDiscColorTitleWidth(int p_newWidth)
{
    m_discColorTitle.set_size_request(p_newWidth);
}

cxgui::NewPlayersList::NewPlayersList()
{
    // We use Gtk::manage here to let Gtkmm deal with the children deletions:
    add(*Gtk::manage(new NewPlayerRow("-- Player 1 --", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN)));
    add(*Gtk::manage(new NewPlayerRow("-- Player 2 --", cxmodel::MakeRed(), cxmodel::PlayerType::HUMAN)));

    set_header_func([this](Gtk::ListBoxRow* row, Gtk::ListBoxRow* /*before*/)
                    {
                        if(row->get_index() == 0)
                        {
                            row->set_header(m_titleRow);
                            m_titleRow.show_all();

                            m_titleRow.signal_realize().connect([this]()
                                                                {
                                                                    cxgui::NewPlayerRow* topRow = GetRow(0u);
                                                                    topRow->RetreiveDimensions(*this);
                                                                    m_titleRow.SetIsBotTitleWidth(m_firstColumnWidth);
                                                                    m_titleRow.SetPlayerNameTitleWidth(m_secondColumnWidth);
                                                                    m_titleRow.SetDiscColorTitleWidth(m_thirdColumnWidth);
                                                                });
                        }
                    });
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
    IF_CONDITION_NOT_MET_DO(specificRow, return cxmodel::MakeTransparent(););

    return specificRow->GetPlayerDiscColor();
}

std::string cxgui::NewPlayersList::GetPlayerNameAtRow(const std::size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    const cxgui::NewPlayerRow* specificRow{GetRow(p_index)};
    IF_CONDITION_NOT_MET_DO(specificRow, return {};);

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

bool cxgui::NewPlayersList::AddRow(const std::string& p_playerNewName,
                                   const cxmodel::ChipColor& p_playerNewDiscColor,
                                   cxmodel::PlayerType p_playerNewType)
{
    PRECONDITION(!p_playerNewName.empty());

    const std::size_t sizeBefore{GetSize()};

    add(*Gtk::manage(new NewPlayerRow(p_playerNewName, p_playerNewDiscColor, p_playerNewType)));

    const std::size_t sizeAfter{GetSize()};

    // We check if the new row has indeed been added:
    IF_CONDITION_NOT_MET_DO(sizeAfter == sizeBefore + 1, return false;);

    return true;
}

bool cxgui::NewPlayersList::RemoveRow(const std::size_t p_index)
{
    PRECONDITION(p_index < GetSize());

    cxgui::NewPlayerRow* specificRow{GetRow(p_index)};
    IF_CONDITION_NOT_MET_DO(specificRow, return false;);

    return RemoveManaged(specificRow);
}

bool cxgui::NewPlayersList::RemoveRow(const std::string& p_playerName,
                                      const cxmodel::ChipColor& p_playerDiscColor,
                                      cxmodel::PlayerType p_playerType)
{
    PRECONDITION(!p_playerName.empty());

    const cxgui::NewPlayerRow rowToRemoveData{p_playerName, p_playerDiscColor, p_playerType};
    cxgui::NewPlayerRow*      rowToRemoveAddress{nullptr};

    std::vector<cxgui::NewPlayerRow*> allRows = GetRows();

    for(auto* row : allRows)
    {
        IF_CONDITION_NOT_MET_DO(row, return false;);
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
                                      const cxmodel::ChipColor& p_playerNewDiscColor,
                                      const cxmodel::PlayerType p_playerNewType)
{
    PRECONDITION(p_index < GetSize());
    PRECONDITION(!p_playerNewName.empty());

    // All is fine, we can proceed with the update:
    cxgui::NewPlayerRow* rowToUpdate{GetRow(p_index)};
    IF_CONDITION_NOT_MET_DO(rowToUpdate, return false;);

    rowToUpdate->Update(p_playerNewName, p_playerNewDiscColor, p_playerNewType);

    return true;
}

void cxgui::NewPlayersList::Clear()
{
    std::vector<NewPlayerRow*> allRows = GetRows();

    for(auto* row : allRows)
    {
        IF_CONDITION_NOT_MET_DO(row, continue;);
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

    IF_CONDITION_NOT_MET_DO(nbRowsBefore == nbRowsAfter + 1, return false;);

    return true;
}
