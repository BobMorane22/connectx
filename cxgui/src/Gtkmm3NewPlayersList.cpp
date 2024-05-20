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
 * @todo Replace `bool` by `Status` in return types for success/fail.
 * @todo Simplify calls by using attributes instead of arguments (see private section).
 * @todo Use classic signal to expose the `RowUpdatedSignalConnect` functionnality.
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxstd/helpers.h>
#include <cxgui/common.h>
#include <cxgui/EnabledState.h>
#include <cxgui/Gtkmm3NewPlayersList.h>
#include <cxgui/IAbstractConnectXWidgetsFactory.h>
#include <cxgui/IAbstractWidgetsFactory.h>
#include <cxgui/IColorPicker.h>
#include <cxgui/IOnOffSwitch.h>
#include <cxgui/IEditBox.h>
#include <cxgui/ILabel.h>
#include <cxgui/ILayout.h>
#include <cxgui/INewGameViewPresenter.h>
#include <cxgui/ISignal.h>
#include <cxgui/Margins.h>
#include <cxgui/OnOffState.h>
#include <cxgui/WidgetsFactories.h>

namespace
{

template<typename T>
bool IsNullptr(const std::unique_ptr<T>& p_item)
{
    return (p_item == nullptr);
}

} // namespace

cxgui::Gtkmm3NewPlayersList::Gtkmm3NewPlayersList(
    const INewGameViewPresenter& p_presenter,
    const WidgetsFactories& p_widgetsFactories)
: m_presenter{p_presenter}
, m_widgetsFactories{p_widgetsFactories}
{
    const IAbstractWidgetsFactory& standardWidgetsFactory = p_widgetsFactories.GetStandardWidgetsFactory();
    m_layout = standardWidgetsFactory.CreateLayout();

    {
        auto* widgetAsGtk = dynamic_cast<Gtk::Widget*>(m_layout.get());
        ASSERT(widgetAsGtk);
        attach(*widgetAsGtk, 0, 0, 1, 1);
    }

    RegisterTitleRow(
        p_widgetsFactories.GetStandardWidgetsFactory());

    RegisterNewPlayerRow(
        m_widgetsFactories,
        1u,
        GetAllColors(),
        EnabledState::Enabled);

    RegisterNewPlayerRow(
        m_widgetsFactories,
        2u,
        GetAllColors(),
        EnabledState::Enabled);

    POSTCONDITION(m_layout);

    InvariantsCheck();
}

cxgui::Gtkmm3NewPlayersList::~Gtkmm3NewPlayersList() = default;

void cxgui::Gtkmm3NewPlayersList::SetDelegate(
    std::unique_ptr<cxgui::IWidget> p_delegate)
{
    IF_PRECONDITION_NOT_MET_DO(p_delegate, return;);

    m_delegate = std::move(p_delegate);

    POSTCONDITION(m_delegate);

    InvariantsCheck();
}

size_t cxgui::Gtkmm3NewPlayersList::GetNbPlayers() const
{
    return m_playerNames.size();
}

cxmodel::ChipColor cxgui::Gtkmm3NewPlayersList::GetRowPlayerChipColor(
    const size_t p_index) const
{
    PRECONDITION(p_index < GetNbPlayers());

    const std::unique_ptr<IColorPicker>& control = m_playerChipColors[p_index];
    IF_CONDITION_NOT_MET_DO(control, return cxmodel::MakeTransparent(););

    return control->GetCurrentSelection();
}

std::string cxgui::Gtkmm3NewPlayersList::GetPlayerNameAtRow(
    const size_t p_index) const
{
    PRECONDITION(p_index < GetNbPlayers());

    const std::unique_ptr<IEditBox>& control = m_playerNames[p_index];
    IF_CONDITION_NOT_MET_DO(control, return {};);

    return control->GetContents();
}

std::vector<cxmodel::ChipColor> cxgui::Gtkmm3NewPlayersList::GetAllColors() const
{
    std::vector<cxmodel::ChipColor> colors;

    for(const std::unique_ptr<IColorPicker>& control : m_playerChipColors)
    {
        IF_CONDITION_NOT_MET_DO(control, return {};);
        colors.push_back(control->GetCurrentSelection());
    }

    return colors;
}

std::vector<std::string> cxgui::Gtkmm3NewPlayersList::GetAllPlayerNames() const
{
    std::vector<std::string> names;

    for(const std::unique_ptr<IEditBox>& control : m_playerNames)
    {
        IF_CONDITION_NOT_MET_DO(control, return {};);
        names.push_back(control->GetContents());
    }

    return names;
}

std::vector<cxmodel::PlayerType> cxgui::Gtkmm3NewPlayersList::GetAllPlayerTypes() const
{
    std::vector<cxmodel::PlayerType> types;

    for(const std::unique_ptr<IOnOffSwitch>& control : m_playerTypes)
    {
        IF_CONDITION_NOT_MET_DO(control, return {};);

        auto playerType = cxmodel::PlayerType::HUMAN;
        if(control->GetState() == cxgui::OnOffState::ON)
        {
            playerType = cxmodel::PlayerType::BOT;
        }

        types.push_back(playerType);
    }

    return types;
}

bool cxgui::Gtkmm3NewPlayersList::AddPlayer(
    size_t p_rowIndex)
{
    if(p_rowIndex > 0u)
    {
        IF_PRECONDITION_NOT_MET_DO(m_presenter.CanAddAnotherPlayer(p_rowIndex - 1u), return false;);
    }

    const size_t sizeBefore{GetNbPlayers()};

    RegisterNewPlayerRow(
        m_widgetsFactories,
        p_rowIndex,
        GetAllColors(),
        EnabledState::Enabled);
        
    const size_t sizeAfter{GetNbPlayers()};

    // We check if the new row has indeed been added:
    IF_CONDITION_NOT_MET_DO(sizeAfter == sizeBefore + 1, return false;);

    show_all();

    InvariantsCheck();

    return true;
}

bool cxgui::Gtkmm3NewPlayersList::RemovePlayer(
    const size_t p_index)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);

    const bool result = RemovePlayerRow(p_index);

    InvariantsCheck();

    return result;
}

bool cxgui::Gtkmm3NewPlayersList::UpdatePlayer(
    const size_t p_index,
    cxmodel::PlayerType p_playerNewType,
    const std::string& p_playerNewName,
    const cxmodel::ChipColor& p_playerNewChipColor)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);
    IF_PRECONDITION_NOT_MET_DO(!p_playerNewName.empty(), return false;);

    const bool result = UpdatePlayerRow(p_index, p_playerNewType, p_playerNewName, p_playerNewChipColor);

    InvariantsCheck();

    return result;
}

void cxgui::Gtkmm3NewPlayersList::RowUpdatedSignalConnect(
    const std::function<void()>& p_slot)
{
    RETURN_IF(!p_slot,);

    // We apply the slot on all existing rows:
    for(std::unique_ptr<IOnOffSwitch>& control : m_playerTypes)
    {
        IF_CONDITION_NOT_MET_DO(control, continue;);
        control->OnStateChanged()->Connect(p_slot);
    }

    for(std::unique_ptr<IEditBox>& control : m_playerNames)
    {
        IF_CONDITION_NOT_MET_DO(control, continue;);
        control->OnContentsChanged()->Connect(p_slot);
    }

    for(std::unique_ptr<IColorPicker>& control : m_playerChipColors)
    {
        IF_CONDITION_NOT_MET_DO(control, continue;);
        control->OnSelectionChanged()->Connect(p_slot);
    }

    InvariantsCheck();
}

void cxgui::Gtkmm3NewPlayersList::RegisterTitleRow(
    const cxgui::IAbstractWidgetsFactory& p_widgetsFactory)
{
    m_isBotTitle = p_widgetsFactory.CreateLabel(m_presenter.GetNewGameViewIsManagedColumnHeaderText());
    m_playerNameTitle = p_widgetsFactory.CreateLabel(m_presenter.GetNewGameViewNameColumnHeaderText());
    m_chipColorTitle = p_widgetsFactory.CreateLabel(m_presenter.GetNewGameViewDiscColumnHeaderText());

    m_layout->Register(
        *m_isBotTitle,
        {cxmodel::Row{0u}, ILayout::RowSpan{1u}},
        {cxmodel::Column{0u}, ILayout::ColumnSpan{1u}},
        {ILayout::VerticalAlignement::CENTER, ILayout::HorizontalAlignement::CENTER});

    m_layout->Register(
        *m_playerNameTitle,
        {cxmodel::Row{0u}, ILayout::RowSpan{1u}},
        {cxmodel::Column{1u}, ILayout::ColumnSpan{1u}});

    m_layout->Register(
        *m_chipColorTitle,
        {cxmodel::Row{0u}, ILayout::RowSpan{1u}},
        {cxmodel::Column{2u}, ILayout::ColumnSpan{1u}});

    POSTCONDITION(m_isBotTitle);
    POSTCONDITION(m_playerNameTitle);
    POSTCONDITION(m_chipColorTitle);

    InvariantsCheck();
}

void cxgui::Gtkmm3NewPlayersList::RegisterNewPlayerRow(
    const WidgetsFactories& p_widgetsFactories,
    size_t p_rowIndex,
    const std::vector<cxmodel::ChipColor>& p_alreadyChosenColors,
    EnabledState p_enabled)
{
    if(p_rowIndex > 0u)
    {
        PRECONDITION(m_presenter.CanAddAnotherPlayer(p_rowIndex - 1u));
    }

    // Creating the widgets:
    const IAbstractWidgetsFactory& standardWidgetsFactory = p_widgetsFactories.GetStandardWidgetsFactory();
    const IAbstractConnectXWidgetsFactory& connectXWidgetsFactory = p_widgetsFactories.GetConnectXWidgetsFactory();

    std::unique_ptr<IEditBox> playerName = standardWidgetsFactory.CreateEditBox();

    const auto defaultColors = GetRemainingDefaultColors(p_alreadyChosenColors, m_presenter);
    IF_CONDITION_NOT_MET_DO(!defaultColors.empty(), return;);
    std::unique_ptr<IColorPicker> playerChipColor = connectXWidgetsFactory.CreateColorPicker(defaultColors);

    std::unique_ptr<IOnOffSwitch> playerType = standardWidgetsFactory.CreateOnOffSwitch();

    // Configuring the widgets:
    playerName->UpdateContents(m_presenter.GetDefaultPlayerName(p_rowIndex));
    playerName->SetMargins({TopMargin{0}, BottomMargin{0}, LeftMargin{0}, RightMargin{CONTROL_SIDE_MARGIN}});

    playerChipColor->SetCurrentSelection(defaultColors.front());

    if(m_presenter.GetDefaultPlayerType(p_rowIndex) == cxmodel::PlayerType::BOT) 
    {
        playerType->SetState(cxgui::OnOffState::ON);
    }
    else
    {
        playerType->SetState(cxgui::OnOffState::OFF);
    }

    playerType->SetEnabled(p_enabled);
    playerType->SetMargins({TopMargin{0}, BottomMargin{0}, LeftMargin{0}, RightMargin{cxgui::CONTROL_SIDE_MARGIN}});

    // Registering the widgets:
    constexpr cxgui::ILayout::RowSpan rowSpan{1u};
    constexpr cxgui::ILayout::ColumnSpan columnSpan{1u};
    const cxmodel::Row row{m_playerNames.size() + 1u};
    constexpr cxgui::ILayout::Alignement alignCenter{cxgui::ILayout::VerticalAlignement::CENTER, cxgui::ILayout::HorizontalAlignement::CENTER};
    m_layout->Register(*playerType,      {row, rowSpan}, {cxmodel::Column{0u}, columnSpan}, alignCenter);
    m_layout->Register(*playerName,      {row, rowSpan}, {cxmodel::Column{1u}, columnSpan});
    m_layout->Register(*playerChipColor, {row, rowSpan}, {cxmodel::Column{2u}, columnSpan});

    m_playerTypes.push_back(std::move(playerType));
    m_playerNames.push_back(std::move(playerName));
    m_playerChipColors.push_back(std::move(playerChipColor));

    InvariantsCheck();
}

bool cxgui::Gtkmm3NewPlayersList::RemovePlayerRow(
    const size_t p_index)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);

    // Remove the row from the rows container:
    {
        const std::unique_ptr<IOnOffSwitch>& control = m_playerTypes[p_index];
        IF_CONDITION_NOT_MET_DO(control, return false;);
        m_layout->Unregister(*control);
    }
    {
        const std::unique_ptr<IEditBox>& control = m_playerNames[p_index];
        IF_CONDITION_NOT_MET_DO(control, return false;);
        m_layout->Unregister(*control);
    }
    {
        const std::unique_ptr<IColorPicker>& control = m_playerChipColors[p_index];
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

bool cxgui::Gtkmm3NewPlayersList::UpdatePlayerRow(
    const size_t p_index,
    cxmodel::PlayerType p_playerNewType,
    const std::string& p_playerNewName,
    const cxmodel::ChipColor& p_playerNewChipColor)
{
    IF_PRECONDITION_NOT_MET_DO(p_index < GetNbPlayers(), return false;);
    IF_PRECONDITION_NOT_MET_DO(!p_playerNewName.empty(), return false;);

    const cxmodel::Row row{p_index};
    constexpr cxmodel::Column column0{0u};
    {
        IWidget* widget = m_layout->GetWidgetAtPosition(row, column0);
        auto* control = dynamic_cast<IOnOffSwitch*>(widget);
        IF_CONDITION_NOT_MET_DO(control, return false;);

        auto newState = OnOffState::ON;
        if(p_playerNewType == cxmodel::PlayerType::HUMAN)
        {
            newState = OnOffState::OFF;
        }

        control->SetState(newState);
    }

    constexpr cxmodel::Column column1{1u};
    {
        IWidget* widget = m_layout->GetWidgetAtPosition(row, column1);
        auto* control = dynamic_cast<IEditBox*>(widget);
        IF_CONDITION_NOT_MET_DO(control, return false;);

        control->UpdateContents(p_playerNewName);
    }

    constexpr cxmodel::Column column2{2u};
    {
        IWidget* widget = m_layout->GetWidgetAtPosition(row, column2);
        auto* control = dynamic_cast<IColorPicker*>(widget);
        IF_CONDITION_NOT_MET_DO(control, return false;);

        control->SetCurrentSelection(p_playerNewChipColor);
    }

    InvariantsCheck();

    return true;
}

void cxgui::Gtkmm3NewPlayersList::InvariantsCheck() const
{
    INVARIANT(m_layout);

    INVARIANT(m_isBotTitle);
    INVARIANT(m_playerNameTitle);
    INVARIANT(m_chipColorTitle);

    INVARIANT(std::none_of(std::cbegin(m_playerTypes),      std::cend(m_playerTypes),      IsNullptr<IOnOffSwitch>));
    INVARIANT(std::none_of(std::cbegin(m_playerNames),      std::cend(m_playerNames),      IsNullptr<IEditBox>));
    INVARIANT(std::none_of(std::cbegin(m_playerChipColors), std::cend(m_playerChipColors), IsNullptr<IColorPicker>));

    INVARIANT(m_playerTypes.size() == m_playerNames.size());
    INVARIANT(m_playerNames.size() == m_playerChipColors.size());
}

size_t cxgui::Gtkmm3NewPlayersList::GetWidth() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetWidth();
}

size_t cxgui::Gtkmm3NewPlayersList::GetHeight() const
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return 0u;);
    return m_delegate->GetHeight();
}

void cxgui::Gtkmm3NewPlayersList::SetEnabled(
    EnabledState p_enabled)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetEnabled(p_enabled);

    InvariantsCheck();
}

void cxgui::Gtkmm3NewPlayersList::SetMargins(
    const Margins& p_newMarginSizes)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetMargins(p_newMarginSizes);

    InvariantsCheck();
}

void cxgui::Gtkmm3NewPlayersList::SetTooltip(
    const std::string& p_tooltipContents)
{
    IF_CONDITION_NOT_MET_DO(m_delegate, return;);
    m_delegate->SetTooltip(p_tooltipContents);

    InvariantsCheck();
}
