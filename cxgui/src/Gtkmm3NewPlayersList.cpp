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
 * @file Gtkmm3NewPlayersList.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <gtkmm/entry.h>
#include <gtkmm/grid.h>

#include <cxinv/assertion.h>
#include <cxstd/helpers.h>
#include <cxmodel/IPlayer.h>
#include <cxgui/ColorComboBox.h>
#include <cxgui/common.h>
#include <cxgui/EnabledState.h>
#include <cxgui/Gtkmm3OnOffSwitch.h>
#include <cxgui/Gtkmm3WidgetDelegate.h>
#include <cxgui/INewGameViewPresenter.h>
#include <cxgui/ISignal.h>
#include <cxgui/Margins.h>
#include <cxgui/OnOffState.h>
#include <cxgui/Gtkmm3NewPlayersList.h>

namespace cxgui
{

/***************************************************************************************************
 * @class NewPlayerTitleRow
 *
 * @brief Title row for the new players list.
 *
 **************************************************************************************************/
class NewPlayerTitleRow : public Gtk::Grid
{

public:

    NewPlayerTitleRow(const INewGameViewPresenter& p_presenter);

    void SetIsBotTitleWidth(int p_newWidth);
    void SetPlayerNameTitleWidth(int p_newWidth);
    void SetDiscColorTitleWidth(int p_newWidth);

private:

    Gtk::Label m_isBotTitle;
    Gtk::Label m_playerNameTitle;
    Gtk::Label m_discColorTitle;
};

/***************************************************************************************************
 * @class NewPlayerRow
 *
 * @brief This widget represents the new information needed by the application to register a
 *        new player.
 *
 * The informations needed are:
 *
 *   - The player's type.
 *   - The player's name.
 *   - The player's disc color.
 *
 * This widget is not intended to be used by itself. Rather, it should be bundled together in
 * some `Gtk::ListBox` widget with others like it. `cxexec::Gtkmm3NewPlayersList` is an example.
 *
 * @invariant The member variable `m_playerName` does not contain an empty string.
 *
 * @see cxexec::Gtkmm3NewPlayersList
 *
 **************************************************************************************************/
class NewPlayerRow final : public Gtk::ListBoxRow
{

public:

    /***********************************************************************************************
     * @brief Constructor.
     *
     * Creates a new player row, according to default values from the presenter. These default values
     * can vary according to how many players already are registered in the game.
     *
     * @param p_presenter
     *      A New Game view compatible presenter.
     *
     * @param p_rowIndex
     *      The row index for this new row.
     *
     * @param p_alreadyChosenColors
     *      A list of colors that cannot be picked from.
     *
     * @param p_enabled
     *      A flag indicating is a user can iterract with the row.
     *
     * @pre
     *      The row number does not exceed the maximum number of players allowed in the game.
     *
     **********************************************************************************************/
    NewPlayerRow(const cxgui::INewGameViewPresenter& p_presenter,
                 size_t p_rowIndex,
                 const std::vector<cxmodel::ChipColor>& p_alreadyChosenColors,
                 EnabledState p_enabled);

    /***********************************************************************************************
     * @brief Default destructor.
     *
     **********************************************************************************************/
    virtual ~NewPlayerRow();

    /***********************************************************************************************
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
    [[nodiscard]] std::string GetPlayerName() const;

    /***********************************************************************************************
     * @brief Accessor for the player's disc color.
     *
     * @return The player's actual disc color.
     *
     **********************************************************************************************/
    [[nodiscard]] cxmodel::ChipColor GetPlayerDiscColor() const;

    /***********************************************************************************************
     * @brief Accessor for the player type (human or bot).
     *
     * @return The player's actual type.
     *
     **********************************************************************************************/
    [[nodiscard]] cxmodel::PlayerType GetPlayerType() const;

    /***********************************************************************************************
     * @brief Connects a slot to be called when the row is updated.
     *
     * @param p_slot The slot to call.
     *
     **********************************************************************************************/
    void RowUpdatedSignalConnect(const std::function<void()>& p_slot);

private:

    // This friendship is needed because the list has to be able to ask its top
    // row to compute the dimensions of its child widgets. These dimensions are
    // later used to resize the column titles appropriately, so that their dimensions
    // match the colum contents.
    friend Gtkmm3NewPlayersList;

    void CheckInvariants() const;
    void RetreiveColumnDimensions(Gtkmm3NewPlayersList& parent_) const;

    Gtk::Grid m_layout;
    std::shared_ptr<cxgui::IOnOffSwitch> m_typeSwitch; // needed because a grid is used.
    Gtk::Entry m_playerName;
    std::unique_ptr<cxgui::ColorComboBox> m_playerDiscColor;

};

/***************************************************************************************************
 * @brief Equality operator.
 *
 * Checks if two `NewPlayerRow, are equal. Two `NewPlayerRow` are equal *if and only if*
 * they share the same player name and the same player disc color.
 *
 * @param p_lhs The first `NewPlayerRow` object to compare against.
 * @param p_rhs The second `NewPlayerRow` object to compare against.
 *
 * @return Returns `true` if both objects are considered equal and `false` otherwise.
 *
 **************************************************************************************************/
[[nodiscard]] bool operator==(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs);

/***************************************************************************************************
 * @brief Non-equality operator.
 *
 * Checks if two `NewPlayerRow`s are NOT equal. Two `NewPlayerRow`s are NOT equal if they differ
 * in their player names and/or in their player disc colors.
 *
 * @param p_lhs The first `NewPlayerRow` object to compare against.
 * @param p_rhs The second `NewPlayerRow` object to compare against.
 *
 * @return Returns `true` if both objects are considered NOT equal and `false` otherwise.
 *
 **************************************************************************************************/
[[nodiscard]] bool operator!=(const NewPlayerRow& p_lhs, const NewPlayerRow& p_rhs);

} // namespace cxgui

cxgui::NewPlayerTitleRow::NewPlayerTitleRow(const INewGameViewPresenter& p_presenter)
: m_isBotTitle{p_presenter.GetNewGameViewIsManagedColumnHeaderText()}
, m_playerNameTitle{p_presenter.GetNewGameViewNameColumnHeaderText()}
, m_discColorTitle{p_presenter.GetNewGameViewDiscColumnHeaderText()}
{
    m_isBotTitle.set_valign(Gtk::Align::ALIGN_CENTER);
    m_isBotTitle.set_halign(Gtk::Align::ALIGN_CENTER);
    m_isBotTitle.set_margin_end(cxgui::CONTROL_BOTTOM_MARGIN);

    m_playerNameTitle.set_hexpand(true);
    m_discColorTitle.set_hexpand(true);

    attach(m_isBotTitle,      0, 0, 1, 1);
    attach(m_playerNameTitle, 1, 0, 1, 1);
    attach(m_discColorTitle,  2, 0, 1, 1);
}

void cxgui::NewPlayerTitleRow::SetIsBotTitleWidth(int p_newWidth)
{
    m_isBotTitle.set_size_request(p_newWidth);
}

void cxgui::NewPlayerTitleRow::SetPlayerNameTitleWidth(int p_newWidth)
{
    m_playerNameTitle.set_size_request(p_newWidth);
}

void cxgui::NewPlayerTitleRow::SetDiscColorTitleWidth(int p_newWidth)
{
    m_discColorTitle.set_size_request(p_newWidth);
}

cxgui::NewPlayerRow::NewPlayerRow(const cxgui::INewGameViewPresenter& p_presenter,
                                  size_t p_rowIndex,
                                  const std::vector<cxmodel::ChipColor>& p_alreadyChosenColors,
                                  EnabledState p_enabled)
{
    if(p_rowIndex > 0u)
    {
        PRECONDITION(p_presenter.CanAddAnotherPlayer(p_rowIndex - 1u));
    }

    m_playerName.set_text(p_presenter.GetDefaultPlayerName(p_rowIndex));
    m_playerName.set_margin_end(cxgui::CONTROL_BOTTOM_MARGIN);

    const auto defaultColors = cxgui::GetRemainingDefaultColors(p_alreadyChosenColors, p_presenter);
    IF_CONDITION_NOT_MET_DO(!defaultColors.empty(), return;);

    m_playerDiscColor = std::make_unique<ColorComboBox>(defaultColors);
    ASSERT(m_playerDiscColor);

    m_playerDiscColor->SetCurrentSelection(defaultColors.front());

    m_typeSwitch = CreateWidget<cxgui::Gtkmm3OnOffSwitch>();
    if(p_presenter.GetDefaultPlayerType(p_rowIndex) == cxmodel::PlayerType::BOT) 
    {
        m_typeSwitch->SetState(cxgui::OnOffState::ON);
    }
    else
    {
        m_typeSwitch->SetState(cxgui::OnOffState::OFF);
    }

    m_typeSwitch->SetEnabled(p_enabled);

    m_typeSwitch->SetMargins({
        TopMargin{0},
        BottomMargin{cxgui::CONTROL_BOTTOM_MARGIN},
        LeftMargin{0},
        RightMargin{0}
    });

    auto* gtkSwitch = dynamic_cast<Gtk::Switch*>(m_typeSwitch.get());
    ASSERT(gtkSwitch);

    gtkSwitch->set_valign(Gtk::Align::ALIGN_CENTER);
    gtkSwitch->set_halign(Gtk::Align::ALIGN_CENTER);

    m_layout.add(*gtkSwitch);
    m_layout.add(m_playerName);
    m_layout.add(*m_playerDiscColor);

    m_playerName.set_hexpand(true);
    m_playerDiscColor->set_hexpand(true);

    add(m_layout);

    CheckInvariants();
}

cxgui::NewPlayerRow::~NewPlayerRow() = default;

void cxgui::NewPlayerRow::Update(const std::string& p_playerNewName,
                                 const cxmodel::ChipColor& p_playerNewDiscColor,
                                 const cxmodel::PlayerType p_newType)
{
    IF_PRECONDITION_NOT_MET_DO(m_playerDiscColor, return;);
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
    m_playerDiscColor->SetCurrentSelection(p_playerNewDiscColor);

    CheckInvariants();
}

std::string cxgui::NewPlayerRow::GetPlayerName() const
{
    return m_playerName.get_text();
}

cxmodel::ChipColor cxgui::NewPlayerRow::GetPlayerDiscColor() const
{
    IF_PRECONDITION_NOT_MET_DO(m_playerDiscColor, return cxmodel::MakeTransparent(););

    return m_playerDiscColor->GetCurrentSelection();
}

cxmodel::PlayerType cxgui::NewPlayerRow::GetPlayerType() const
{
    if(m_typeSwitch->GetState() == cxgui::OnOffState::ON)
    {
        return cxmodel::PlayerType::BOT;
    }

    return cxmodel::PlayerType::HUMAN;
}

void cxgui::NewPlayerRow::RowUpdatedSignalConnect(const std::function<void()>& p_slot)
{
    IF_CONDITION_NOT_MET_DO(m_typeSwitch, return;);
    RETURN_IF(!p_slot,);

    m_typeSwitch->OnStateChanged()->Connect(p_slot);
    m_playerName.signal_changed().connect(p_slot);
    m_playerDiscColor->signal_changed().connect(p_slot);

    CheckInvariants();
}

void cxgui::NewPlayerRow::CheckInvariants() const
{
    INVARIANT(!m_playerName.get_text().empty());
}

void cxgui::NewPlayerRow::RetreiveColumnDimensions(Gtkmm3NewPlayersList& parent_) const
{
    parent_.m_columnWidths.m_first = m_typeSwitch->GetWidth();
    parent_.m_columnWidths.m_second = m_playerName.get_width();
    parent_.m_columnWidths.m_third = m_playerDiscColor->get_width();
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

cxgui::Gtkmm3NewPlayersList::Gtkmm3NewPlayersList(const INewGameViewPresenter& p_presenter)
{
    m_titleRow = std::make_unique<NewPlayerTitleRow>(p_presenter);
    ASSERT(m_titleRow);

    add(*Gtk::manage(new NewPlayerRow(p_presenter, 1u, GetAllColors(), EnabledState::Enabled)));
    add(*Gtk::manage(new NewPlayerRow(p_presenter, 2u, GetAllColors(), EnabledState::Enabled)));

    AddColumnHeaders();
}

cxgui::Gtkmm3NewPlayersList::~Gtkmm3NewPlayersList() = default;

void cxgui::Gtkmm3NewPlayersList::SetDelegate(std::unique_ptr<cxgui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);
}

size_t cxgui::Gtkmm3NewPlayersList::GetWidth() const
{
    RETURN_IF(!m_delegate, 0u);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3NewPlayersList::GetHeight() const
{
    RETURN_IF(!m_delegate, 0u);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3NewPlayersList::SetEnabled(EnabledState p_enabled)
{
    RETURN_IF(!m_delegate,);
    m_delegate->SetEnabled(p_enabled);
}

void cxgui::Gtkmm3NewPlayersList::SetMargins(const Margins& p_newMarginSizes)
{
    RETURN_IF(!m_delegate,);
    m_delegate->SetMargins(p_newMarginSizes);
}

std::size_t cxgui::Gtkmm3NewPlayersList::GetSize() const
{
    return get_children().size();
}

cxmodel::ChipColor cxgui::Gtkmm3NewPlayersList::GetRowPlayerDiscColor(const std::size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    const cxgui::NewPlayerRow* specificRow{GetRow(p_index)};
    IF_CONDITION_NOT_MET_DO(specificRow, return cxmodel::MakeTransparent(););

    return specificRow->GetPlayerDiscColor();
}

std::string cxgui::Gtkmm3NewPlayersList::GetPlayerNameAtRow(const std::size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    const cxgui::NewPlayerRow* specificRow{GetRow(p_index)};
    IF_CONDITION_NOT_MET_DO(specificRow, return {};);

    return specificRow->GetPlayerName();
}

std::vector<cxmodel::ChipColor> cxgui::Gtkmm3NewPlayersList::GetAllColors() const
{
    std::vector<cxmodel::ChipColor> colors;

    for(const auto row : GetRows())
    {
        colors.push_back(row->GetPlayerDiscColor());
    }

    return colors;
}

std::vector<std::string> cxgui::Gtkmm3NewPlayersList::GetAllPlayerNames() const
{
    std::vector<std::string> names;

    for(const auto row : GetRows())
    {
        names.push_back(row->GetPlayerName());
    }

    return names;
}

std::vector<cxmodel::PlayerType> cxgui::Gtkmm3NewPlayersList::GetAllPlayerTypes() const
{
    std::vector<cxmodel::PlayerType> types;

    for(const auto row : GetRows())
    {
        types.push_back(row->GetPlayerType());
    }

    return types;
}

bool cxgui::Gtkmm3NewPlayersList::AddRow(const cxgui::INewGameViewPresenter& p_presenter, size_t p_rowIndex)
{
    if(p_rowIndex > 0u)
    {
        IF_PRECONDITION_NOT_MET_DO(p_presenter.CanAddAnotherPlayer(p_rowIndex - 1u), return false;);
    }

    const size_t sizeBefore{GetSize()};

    auto* row = Gtk::manage(new NewPlayerRow(p_presenter, p_rowIndex, GetAllColors(), EnabledState::Enabled));
    IF_CONDITION_NOT_MET_DO(row, return false;);
    
    IF_CONDITION_NOT_MET_DO(m_rowUpdatedSlot, return false;);
    row->RowUpdatedSignalConnect(m_rowUpdatedSlot);
    add(*row);

    const std::size_t sizeAfter{GetSize()};

    // We check if the new row has indeed been added:
    IF_CONDITION_NOT_MET_DO(sizeAfter == sizeBefore + 1, return false;);

    show_all();

    return true;
}

bool cxgui::Gtkmm3NewPlayersList::RemoveRow(const std::size_t p_index)
{
    PRECONDITION(p_index < GetSize());

    cxgui::NewPlayerRow* specificRow{GetRow(p_index)};
    IF_CONDITION_NOT_MET_DO(specificRow, return false;);

    return RemoveManaged(specificRow);
}

bool cxgui::Gtkmm3NewPlayersList::UpdateRow(const std::size_t p_index,
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

void cxgui::Gtkmm3NewPlayersList::Clear()
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

const cxgui::NewPlayerRow* cxgui::Gtkmm3NewPlayersList::GetRow(const size_t p_index) const
{
    PRECONDITION(p_index < GetSize());

    // We get the address of all the non-internal children (const version):
    const std::vector<const Gtk::Widget*> rows = get_children();

    // We cast the needed widget to its most specific row type:
    const cxgui::NewPlayerRow* row = static_cast<const cxgui::NewPlayerRow*>(rows[p_index]);

    POSTCONDITION(row);

    return row;
}

cxgui::NewPlayerRow* cxgui::Gtkmm3NewPlayersList::GetRow(const size_t p_index)
{
    PRECONDITION(p_index < GetSize());

    cxgui::NewPlayerRow* row{const_cast<cxgui::NewPlayerRow*>(static_cast<const cxgui::Gtkmm3NewPlayersList*>(this)->GetRow(p_index))};

    POSTCONDITION(row);

    return row;
}

std::vector<const cxgui::NewPlayerRow*> cxgui::Gtkmm3NewPlayersList::GetRows() const
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

std::vector<cxgui::NewPlayerRow*> cxgui::Gtkmm3NewPlayersList::GetRows()
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

// The Gtk::ListBoxRow widget does not have column headers, since on each row,
// the widget contents may vary. However, each row of a cxgui::Gtkmm3NewPlayersList
// will contain the same widgets, and we want to simulate column headers.
//
// If the Gtk::ListBoxRow cannot have column headers, it can have row headers,
// that is, each row can have its own header. We exploit this feature and
// add a header to the first row only. We then resize it on the realize
// signal. At this point, the row widgets' sizes have been allocated and we
// can retreive them to update the header to fit them.
void cxgui::Gtkmm3NewPlayersList::AddColumnHeaders()
{
    // Each row of 
    set_header_func([this](Gtk::ListBoxRow* p_row, Gtk::ListBoxRow* /*p_before*/)
                    {
                        IF_PRECONDITION_NOT_MET_DO(p_row != nullptr, return;);

                        if(p_row->get_index() == 0u)
                        {
                            p_row->set_header(*m_titleRow);
                            m_titleRow->show_all();

                            m_titleRow->signal_realize().connect([this](){FitColumnHeaders();});
                        }
                    });
}

// Fit the dimensions of the header widgets with the contents of the column
// widgets. This should only be called on the first row, since we do not
// want headers of other rows.
void cxgui::Gtkmm3NewPlayersList::FitColumnHeaders()
{
    cxgui::NewPlayerRow* topRow = GetRow(0u);
    IF_CONDITION_NOT_MET_DO(topRow != nullptr, return;);

    topRow->RetreiveColumnDimensions(*this);

    m_titleRow->SetIsBotTitleWidth(m_columnWidths.m_first);
    m_titleRow->SetPlayerNameTitleWidth(m_columnWidths.m_second);
    m_titleRow->SetDiscColorTitleWidth(m_columnWidths.m_third);
}

bool cxgui::Gtkmm3NewPlayersList::RemoveManaged(cxgui::NewPlayerRow* p_row)
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

void cxgui::Gtkmm3NewPlayersList::RowUpdatedSignalConnect(const std::function<void()>& p_slot)
{
    if(!p_slot)
    {
        return;
    }

    // We save the slot for all new rows:
    m_rowUpdatedSlot = p_slot;

    // We apply the slot on all existing rows:
    auto rows = cxgui::Gtkmm3NewPlayersList::GetRows();
    for(auto* row : rows)
    {
        IF_CONDITION_NOT_MET_DO(row, continue;);
        row->RowUpdatedSignalConnect(m_rowUpdatedSlot);
    }
}
