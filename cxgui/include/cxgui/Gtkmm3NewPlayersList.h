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
 *  along with Connect X. If not, see <https://www.gnu.org/licenses/>.  *
 *************************************************************************************************/
/**********************************************************************************************//**
 * @file Gtkmm3NewPlayersList.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3NEWPLAYERSLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724
#define GTKMM3NEWPLAYERSLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724

#include <gtkmm/grid.h>

#include <cxgui/INewPlayersList.h>

namespace cxmodel
{
    enum class PlayerType;
}

namespace cxgui
{
    class IAbstractWidgetsFactory;
    class IColorPicker;
    class IEditBox;
    class ILabel;
    class ILayout;
    class INewGameViewPresenter;
    class NewPlayerRow;
    class NewPlayerTitleRow;
    class IOnOffSwitch;
    class WidgetsFactories;
}

namespace cxgui
{

/***********************************************************************************************//**
 * @brief Widget to list players.
 *
 * Widget containing rows of players to be registered for a Connect X game, as well as the color
 * they have chosen for their chips.
 *
 * @see cxgui::NewPlayerRow
 *
 **************************************************************************************************/
class Gtkmm3NewPlayersList final : public INewPlayersList,
                                   public Gtk::Grid
{

public:

    /*******************************************************************************************//**
     * @brief Constructor.
     *
     * Constructs a list of two players with different colors. This is the basic Connect X
     * configuration, and is equivalent to the classic Connect 4 requirements.
     *
     * @param
     *      Factories to create widgets.
     *
     * @param p_presenter
     *      A new game view presenter.
     *
     **********************************************************************************************/
    Gtkmm3NewPlayersList(
        const INewGameViewPresenter& p_presenter,
        const WidgetsFactories& p_widgetsFactories);

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    ~Gtkmm3NewPlayersList() override;

    /*******************************************************************************************//**
     * @brief Sets the delegate for widget common facilities.
     *
     * The delegate is reponsible to carry the implementation for generic `cxgui::IWidget` operations.
     * It is meant to avoid implementation duplication.
     *
     * @param p_delegate
     *      The widget delegate.
     *
     * @pre
     *      The widget delegate instance given as an argument is valid.
     * @post
     *      The registered widget delegate is valid.
     *
     **********************************************************************************************/
    void SetDelegate(std::unique_ptr<cxgui::IWidget> p_delegate);

    // cxgui::INewPlayersList:
    [[nodiscard]] size_t GetNbPlayers() const override;
    [[nodiscard]] cxmodel::ChipColor GetRowPlayerChipColor(
        const size_t p_index) const override;
    [[nodiscard]] std::string GetPlayerNameAtRow(
        const size_t p_index) const override;
    [[nodiscard]] std::vector<cxmodel::ChipColor> GetAllColors() const override;
    [[nodiscard]] std::vector<std::string> GetAllPlayerNames() const override;
    [[nodiscard]] std::vector<cxmodel::PlayerType> GetAllPlayerTypes() const override;
    [[nodiscard]] bool AddPlayer(
        size_t p_rowIndex) override;
    [[nodiscard]] bool RemovePlayer(
        const size_t p_index) override;
    [[nodiscard]] bool UpdatePlayer(
        const size_t p_index,
        cxmodel::PlayerType p_newPlayerType,
        const std::string& p_newPlayerNewName,
        const cxmodel::ChipColor& p_newPlayerNewChipColor) override;
    [[nodiscard]] std::unique_ptr<ISignal<void>> OnPlayerUpdated() override;

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(
        EnabledState p_enabled) override;
    void SetMargins(
        const Margins& p_newMarginSizes) override;
    void SetTooltip(
        const std::string& p_tooltipContents) override;
    [[nodiscard]] std::unique_ptr<ISignal<EventPropagation, KeyboardKeyPressedEvent>> OnKeyPressed() override;

private:

    void RegisterTitleRow();

    void RegisterNewPlayerRow(
        size_t p_rowIndex,
        const std::vector<cxmodel::ChipColor>& p_alreadyChosenColors,
        EnabledState p_enabled);

    bool RemovePlayerRow(
        const size_t p_index);

    bool UpdatePlayerRow(
        const size_t p_index,
        cxmodel::PlayerType p_playerNewType,
        const std::string& p_playerNewName,
        const cxmodel::ChipColor& p_playerNewChipColor);

    void InvariantsCheck() const;

private:

    std::unique_ptr<cxgui::IWidget> m_delegate;
    const INewGameViewPresenter& m_presenter;
    const WidgetsFactories& m_widgetsFactories;

    // Widget's main layout:
    std::unique_ptr<ILayout> m_layout;

    // Title row:
    std::unique_ptr<ILabel> m_isBotTitle;
    std::unique_ptr<ILabel> m_playerNameTitle;
    std::unique_ptr<ILabel> m_chipColorTitle;

    // Player rows:
    std::vector<std::unique_ptr<IOnOffSwitch>> m_playerTypes;
    std::vector<std::unique_ptr<IEditBox>> m_playerNames;
    std::vector<std::unique_ptr<IColorPicker>> m_playerChipColors;

};

} // namespace cxgui

#endif // GTKMM3NEWPLAYERSLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724
