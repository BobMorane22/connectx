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
 * @file NewPlayersList.cpp
 * @date 2020
 *
 *************************************************************************************************/

#include <algorithm>
#include <functional>

#include <cxinv/assertion.h>
#include <cxcmn/helpers.h>
#include <cxcmnui/common.h>
#include <cxcmnui/EnabledState.h>
#include <cxcmnui/EventPropagation.h>
#include <cxcmnui/IAbstractWidgetsFactory.h>
#include <cxcmnui/IOnOffSwitch.h>
#include <cxcmnui/IEditBox.h>
#include <cxcmnui/ILabel.h>
#include <cxcmnui/ILayout.h>
#include <cxcmnui/KeyboardKeyPressedEvent.h>
#include <cxcmnui/Margins.h>
#include <cxcmnui/OnOffState.h>
#include <cxui/IAbstractConnectXWidgetsFactory.h>
#include <cxui/IColorPicker.h>
#include <cxui/INewGameViewPresenter.h>
#include <cxui/WidgetsFactories.h>

#include "NewPlayersList.h"

namespace
{

template<typename T>
[[nodiscard]] bool IsNullptr(const std::unique_ptr<T>& p_item)
{
    return (p_item == nullptr);
}

const auto IS_CONNECTED = 
    [](const std::unique_ptr<cx::cmn::ui::IConnection>& p_connection)
    { 
        RETURN_IF(!p_connection, false);
        RETURN_IF(!p_connection->IsConnected(), false);
    
        return true;
    };

/**************************************************************************************************
 * @brief Gtkmm3 implementation of a connection for when a player is updated.
 *
 * This deals with all player related widgets connections at once, as a single entity.
 *
 *************************************************************************************************/
class Gtkmm3OnPlayerUpdatedConnection : public cx::cmn::ui::IConnection
{

public:

    explicit Gtkmm3OnPlayerUpdatedConnection(std::vector<std::unique_ptr<cx::cmn::ui::IConnection>> p_connections)
    {
        PRECONDITION(!p_connections.empty());
        PRECONDITION(std::all_of(std::cbegin(p_connections), std::cend(p_connections), IS_CONNECTED));

        m_connections = std::move(p_connections);
        m_isConnected = true;
    }

    [[nodiscard]] bool IsConnected() const override
    {
        return m_isConnected;
    }

    void Disconnect() override
    {
        for(auto&& connection : m_connections)
        {
            IF_CONDITION_NOT_MET_DO(connection, continue;);

            connection->Disconnect();
        }

        m_isConnected = false;

        POSTCONDITION(std::none_of(std::cbegin(m_connections), std::cend(m_connections), IS_CONNECTED));
    }

private:

    // All connexions from signals related to an updated player.
    std::vector<std::unique_ptr<cx::cmn::ui::IConnection>> m_connections;

    bool m_isConnected = false;

};

/**************************************************************************************************
 * @brief Gtkmm3 implementation of a signal for when a player is updated.
 *
 * This deals with all player related widgets signals at once, as a single entity.
 *
 *************************************************************************************************/
class Gtkmm3OnPlayerUpdatedSignal : public cx::cmn::ui::ISignal<void> 
{

public:

    Gtkmm3OnPlayerUpdatedSignal(
        std::vector<std::unique_ptr<cx::cmn::ui::IOnOffSwitch>>& p_playerTypes,
        std::vector<std::unique_ptr<cx::cmn::ui::IEditBox>>& p_playerNames,
        std::vector<std::unique_ptr<cx::ui::IColorPicker>>& p_playerChipColors)
    : m_playerTypes{p_playerTypes}
    , m_playerNames{p_playerNames}
    , m_playerChipColors{p_playerChipColors}
    {
    }

    [[nodiscard]] std::unique_ptr<cx::cmn::ui::IConnection> Connect(const std::function<void()>& p_slot) override
    {
        std::vector<std::unique_ptr<cx::cmn::ui::IConnection>> connections;

        // We apply the slot on all existing rows:
        for(std::unique_ptr<cx::cmn::ui::IOnOffSwitch>& control : m_playerTypes)
        {
            IF_CONDITION_NOT_MET_DO(control, continue;);
            connections.push_back(control->OnStateChanged()->Connect(p_slot));
        }

        for(std::unique_ptr<cx::cmn::ui::IEditBox>& control : m_playerNames)
        {
            IF_CONDITION_NOT_MET_DO(control, continue;);
            connections.push_back(control->OnContentsChanged()->Connect(p_slot));
        }

        for(std::unique_ptr<cx::ui::IColorPicker>& control : m_playerChipColors)
        {
            IF_CONDITION_NOT_MET_DO(control, continue;);
            connections.push_back(control->OnSelectionChanged()->Connect(p_slot));
        }

        return std::make_unique<Gtkmm3OnPlayerUpdatedConnection>(std::move(connections));
    }

private:

    std::vector<std::unique_ptr<cx::cmn::ui::IOnOffSwitch>>& m_playerTypes;
    std::vector<std::unique_ptr<cx::cmn::ui::IEditBox>>& m_playerNames;
    std::vector<std::unique_ptr<cx::ui::IColorPicker>>& m_playerChipColors;

};

} // namespace

cx::ui::gtkmm3::NewPlayersList::NewPlayersList(
    const cx::ui::INewGameViewPresenter& p_presenter,
    const cx::ui::WidgetsFactories& p_widgetsFactories)
: m_presenter{p_presenter}
, m_widgetsFactories{p_widgetsFactories}
{
    const cx::cmn::ui::IAbstractWidgetsFactory& standardWidgetsFactory = p_widgetsFactories.GetStandardWidgetsFactory();
    m_layout = standardWidgetsFactory.CreateLayout();

    {
        auto* widgetAsGtk = dynamic_cast<Gtk::Widget*>(m_layout.get());
        ASSERT(widgetAsGtk);
        attach(*widgetAsGtk, 0, 0, 1, 1);
    }

    RegisterTitleRow();
    RegisterNewPlayerRow(1u, GetAllColors(), cx::cmn::ui::EnabledState::Enabled);
    RegisterNewPlayerRow(2u, GetAllColors(), cx::cmn::ui::EnabledState::Enabled);

    POSTCONDITION(m_layout);

    InvariantsCheck();
}

cx::ui::gtkmm3::NewPlayersList::~NewPlayersList() = default;

void cx::ui::gtkmm3::NewPlayersList::SetDelegate(
    std::unique_ptr<cx::cmn::ui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);

    InvariantsCheck();
}

size_t cx::ui::gtkmm3::NewPlayersList::GetNbPlayers() const
{
    return m_playerNames.size();
}

cx::model::ChipColor cx::ui::gtkmm3::NewPlayersList::GetRowPlayerChipColor(
    const size_t p_index) const
{
    PRECONDITION(p_index < GetNbPlayers());

    const std::unique_ptr<cx::ui::IColorPicker>& control = m_playerChipColors[p_index];
    IF_CONDITION_NOT_MET_DO(control, return cx::model::MakeTransparent(););

    return control->GetCurrentSelection();
}

std::string cx::ui::gtkmm3::NewPlayersList::GetPlayerNameAtRow(
    const size_t p_index) const
{
    PRECONDITION(p_index < GetNbPlayers());

    const std::unique_ptr<cx::cmn::ui::IEditBox>& control = m_playerNames[p_index];
    IF_CONDITION_NOT_MET_DO(control, return {};);

    return control->GetContents();
}

std::vector<cx::model::ChipColor> cx::ui::gtkmm3::NewPlayersList::GetAllColors() const
{
    std::vector<cx::model::ChipColor> colors;

    for(const std::unique_ptr<cx::ui::IColorPicker>& control : m_playerChipColors)
    {
        IF_CONDITION_NOT_MET_DO(control, return {};);
        colors.push_back(control->GetCurrentSelection());
    }

    return colors;
}

std::vector<std::string> cx::ui::gtkmm3::NewPlayersList::GetAllPlayerNames() const
{
    std::vector<std::string> names;

    for(const std::unique_ptr<cx::cmn::ui::IEditBox>& control : m_playerNames)
    {
        IF_CONDITION_NOT_MET_DO(control, return {};);
        names.push_back(control->GetContents());
    }

    return names;
}

std::vector<cx::model::PlayerType> cx::ui::gtkmm3::NewPlayersList::GetAllPlayerTypes() const
{
    std::vector<cx::model::PlayerType> types;

    for(const std::unique_ptr<cx::cmn::ui::IOnOffSwitch>& control : m_playerTypes)
    {
        IF_CONDITION_NOT_MET_DO(control, return {};);

        auto playerType = cx::model::PlayerType::HUMAN;
        if(control->GetState() == cx::cmn::ui::OnOffState::ON)
        {
            playerType = cx::model::PlayerType::BOT;
        }

        types.push_back(playerType);
    }

    return types;
}

bool cx::ui::gtkmm3::NewPlayersList::AddPlayer(
    size_t p_rowIndex)
{
    if(p_rowIndex > 0u)
    {
        IF_PRECONDITION_NOT_MET_DO(m_presenter.CanAddAnotherPlayer(p_rowIndex - 1u), return false;);
    }

    const size_t sizeBefore{GetNbPlayers()};

    RegisterNewPlayerRow(p_rowIndex, GetAllColors(), cx::cmn::ui::EnabledState::Enabled);
        
    const size_t sizeAfter{GetNbPlayers()};

    // We check if the new row has indeed been added:
    IF_CONDITION_NOT_MET_DO(sizeAfter == sizeBefore + 1u, return false;);

    show_all();

    InvariantsCheck();

    return true;
}

bool cx::ui::gtkmm3::NewPlayersList::RemovePlayer(
    const size_t p_index)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);

    const bool result = RemovePlayerRow(p_index);

    InvariantsCheck();

    return result;
}

bool cx::ui::gtkmm3::NewPlayersList::UpdatePlayer(
    const size_t p_index,
    cx::model::PlayerType p_playerNewType,
    const std::string& p_playerNewName,
    const cx::model::ChipColor& p_playerNewChipColor)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);
    IF_PRECONDITION_NOT_MET_DO(!p_playerNewName.empty(), return false;);

    const bool result = UpdatePlayerRow(p_index, p_playerNewType, p_playerNewName, p_playerNewChipColor);

    InvariantsCheck();

    return result;
}

std::unique_ptr<cx::cmn::ui::ISignal<void>> cx::ui::gtkmm3::NewPlayersList::OnPlayerUpdated()
{
    auto signal = std::make_unique<Gtkmm3OnPlayerUpdatedSignal>(
                      m_playerTypes,
                      m_playerNames,
                      m_playerChipColors);

     InvariantsCheck();

     return signal;
}

void cx::ui::gtkmm3::NewPlayersList::RegisterTitleRow()
{
    const cx::cmn::ui::IAbstractWidgetsFactory& widgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();

    m_isBotTitle = widgetsFactory.CreateLabel(m_presenter.GetNewGameViewIsManagedColumnHeaderText());
    m_playerNameTitle = widgetsFactory.CreateLabel(m_presenter.GetNewGameViewNameColumnHeaderText());
    m_chipColorTitle = widgetsFactory.CreateLabel(m_presenter.GetNewGameViewDiscColumnHeaderText());

    using namespace cx::cmn::ui;

    m_layout->Register(
        *m_isBotTitle,
        {ILayout::Row{0u}, ILayout::RowSpan{1u}},
        {ILayout::Column{0u}, ILayout::ColumnSpan{1u}},
        {ILayout::VerticalAlignement::CENTER, ILayout::HorizontalAlignement::CENTER});

    m_layout->Register(
        *m_playerNameTitle,
        {ILayout::Row{0u}, ILayout::RowSpan{1u}},
        {ILayout::Column{1u}, ILayout::ColumnSpan{1u}});

    m_layout->Register(
        *m_chipColorTitle,
        {ILayout::Row{0u}, ILayout::RowSpan{1u}},
        {ILayout::Column{2u}, ILayout::ColumnSpan{1u}});

    POSTCONDITION(m_isBotTitle);
    POSTCONDITION(m_playerNameTitle);
    POSTCONDITION(m_chipColorTitle);

    InvariantsCheck();
}

void cx::ui::gtkmm3::NewPlayersList::RegisterNewPlayerRow(
    size_t p_rowIndex,
    const std::vector<cx::model::ChipColor>& p_alreadyChosenColors,
    cx::cmn::ui::EnabledState p_enabled)
{
    if(p_rowIndex > 0u)
    {
        PRECONDITION(m_presenter.CanAddAnotherPlayer(p_rowIndex - 1u));
    }

    // Creating the widgets:
    const cx::cmn::ui::IAbstractWidgetsFactory& standardWidgetsFactory = m_widgetsFactories.GetStandardWidgetsFactory();
    const cx::ui::IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = m_widgetsFactories.GetConnectXWidgetsFactory();

    std::unique_ptr<cx::cmn::ui::IEditBox> playerName = standardWidgetsFactory.CreateEditBox();

    const auto defaultColors = GetRemainingDefaultColors(p_alreadyChosenColors, m_presenter);
    IF_CONDITION_NOT_MET_DO(!defaultColors.empty(), return;);
    std::unique_ptr<cx::ui::IColorPicker> playerChipColor = connectXWidgetsFactory.CreateColorPicker(defaultColors);

    std::unique_ptr<cx::cmn::ui::IOnOffSwitch> playerType = standardWidgetsFactory.CreateOnOffSwitch();

    // Configuring the widgets:
    using namespace cx::cmn::ui;
    playerName->UpdateContents(m_presenter.GetDefaultPlayerName(p_rowIndex));
    playerName->SetMargins({TopMargin{0}, BottomMargin{0}, LeftMargin{0}, RightMargin{CONTROL_SIDE_MARGIN}});

    playerChipColor->SetCurrentSelection(defaultColors.front());

    if(m_presenter.GetDefaultPlayerType(p_rowIndex) == cx::model::PlayerType::BOT) 
    {
        playerType->SetState(cx::cmn::ui::OnOffState::ON);
    }
    else
    {
        playerType->SetState(cx::cmn::ui::OnOffState::OFF);
    }

    playerType->SetEnabled(p_enabled);
    playerType->SetMargins({TopMargin{0}, BottomMargin{0}, LeftMargin{0}, RightMargin{cx::cmn::ui::CONTROL_SIDE_MARGIN}});

    // Registering the widgets:
    using namespace cx::cmn::ui;

    constexpr ILayout::RowSpan rowSpan{1u};
    constexpr ILayout::ColumnSpan columnSpan{1u};
    const ILayout::Row row{p_rowIndex};
    constexpr ILayout::Alignement alignCenter{ILayout::VerticalAlignement::CENTER, ILayout::HorizontalAlignement::CENTER};
    m_layout->Register(*playerType,      {row, rowSpan}, {ILayout::Column{0u}, columnSpan}, alignCenter);
    m_layout->Register(*playerName,      {row, rowSpan}, {ILayout::Column{1u}, columnSpan});
    m_layout->Register(*playerChipColor, {row, rowSpan}, {ILayout::Column{2u}, columnSpan});

    m_playerTypes.push_back(std::move(playerType));
    m_playerNames.push_back(std::move(playerName));
    m_playerChipColors.push_back(std::move(playerChipColor));

    InvariantsCheck();
}

bool cx::ui::gtkmm3::NewPlayersList::RemovePlayerRow(
    const size_t p_index)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);

    // Remove the row from the rows container:
    {
        const std::unique_ptr<cx::cmn::ui::IOnOffSwitch>& control = m_playerTypes[p_index];
        IF_CONDITION_NOT_MET_DO(control, return false;);
        m_layout->Unregister(*control);
    }
    {
        const std::unique_ptr<cx::cmn::ui::IEditBox>& control = m_playerNames[p_index];
        IF_CONDITION_NOT_MET_DO(control, return false;);
        m_layout->Unregister(*control);
    }
    {
        const std::unique_ptr<cx::ui::IColorPicker>& control = m_playerChipColors[p_index];
        IF_CONDITION_NOT_MET_DO(control, return false;);
        m_layout->Unregister(*control);
    }

    // Remove the row data from memory:
    m_playerTypes.erase(m_playerTypes.begin() + p_index);
    m_playerNames.erase(m_playerNames.begin() + p_index);
    m_playerChipColors.erase(m_playerChipColors.begin() + p_index);
    
    InvariantsCheck();

    return true;
}

bool cx::ui::gtkmm3::NewPlayersList::UpdatePlayerRow(
    const size_t p_index,
    cx::model::PlayerType p_playerNewType,
    const std::string& p_playerNewName,
    const cx::model::ChipColor& p_playerNewChipColor)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);
    IF_PRECONDITION_NOT_MET_DO(!p_playerNewName.empty(), return false;);

    const cx::cmn::ui::ILayout::Row row{p_index};
    constexpr cx::cmn::ui::ILayout::Column column0{0u};
    {
        cx::cmn::ui::IWidget* widget = m_layout->GetWidgetAtPosition(row, column0);
        auto* control = dynamic_cast<cx::cmn::ui::IOnOffSwitch*>(widget);
        IF_CONDITION_NOT_MET_DO(control, return false;);

        auto newState = cx::cmn::ui::OnOffState::ON;
        if(p_playerNewType == cx::model::PlayerType::HUMAN)
        {
            newState = cx::cmn::ui::OnOffState::OFF;
        }

        control->SetState(newState);
    }

    constexpr cx::cmn::ui::ILayout::Column column1{1u};
    {
        cx::cmn::ui::IWidget* widget = m_layout->GetWidgetAtPosition(row, column1);
        auto* control = dynamic_cast<cx::cmn::ui::IEditBox*>(widget);
        IF_CONDITION_NOT_MET_DO(control, return false;);

        control->UpdateContents(p_playerNewName);
    }

    constexpr cx::cmn::ui::ILayout::Column column2{2u};
    {
        cx::cmn::ui::IWidget* widget = m_layout->GetWidgetAtPosition(row, column2);
        auto* control = dynamic_cast<cx::ui::IColorPicker*>(widget);
        IF_CONDITION_NOT_MET_DO(control, return false;);

        control->SetCurrentSelection(p_playerNewChipColor);
    }

    InvariantsCheck();

    return true;
}

void cx::ui::gtkmm3::NewPlayersList::InvariantsCheck() const
{
    INVARIANT(m_layout);

    INVARIANT(m_isBotTitle);
    INVARIANT(m_playerNameTitle);
    INVARIANT(m_chipColorTitle);

    INVARIANT(std::none_of(std::cbegin(m_playerTypes),      std::cend(m_playerTypes),      IsNullptr<cx::cmn::ui::IOnOffSwitch>));
    INVARIANT(std::none_of(std::cbegin(m_playerNames),      std::cend(m_playerNames),      IsNullptr<cx::cmn::ui::IEditBox>));
    INVARIANT(std::none_of(std::cbegin(m_playerChipColors), std::cend(m_playerChipColors), IsNullptr<cx::ui::IColorPicker>));

    INVARIANT(m_playerTypes.size() == m_playerNames.size());
    INVARIANT(m_playerNames.size() == m_playerChipColors.size());
}

size_t cx::ui::gtkmm3::NewPlayersList::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cx::ui::gtkmm3::NewPlayersList::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cx::ui::gtkmm3::NewPlayersList::SetEnabled(
    cx::cmn::ui::EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);

    InvariantsCheck();
}

void cx::ui::gtkmm3::NewPlayersList::SetMargins(
    const cx::cmn::ui::Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);

    InvariantsCheck();
}

void cx::ui::gtkmm3::NewPlayersList::SetTooltip(
    const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);

    InvariantsCheck();
}

std::unique_ptr<cx::cmn::ui::ISignal<cx::cmn::ui::EventPropagation, cx::cmn::ui::KeyboardKeyPressedEvent>> cx::ui::gtkmm3::NewPlayersList::OnKeyPressed()
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return nullptr;);
    return m_delegate->OnKeyPressed();
}
