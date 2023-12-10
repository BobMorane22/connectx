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
 * @file Gtkmm3NewPlayersList.h
 * @date 2020
 *
 *************************************************************************************************/

#ifndef GTKMM3NEWPLAYERSLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724
#define GTKMM3NEWPLAYERSLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724

#include <gtkmm/listbox.h>

#include <cxgui/INewPlayersList.h>

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
class Gtkmm3NewPlayersList final : public INewPlayersList,
                                   public Gtk::ListBox
{
public:

    // cxgui::IWidget:
    [[nodiscard]] size_t GetWidth() const override;
    [[nodiscard]] size_t GetHeight() const override;
    void SetEnabled(EnabledState p_enabled) override;
    void SetMargins(const Margins& p_newMarginSizes) override;

public:

    /*******************************************************************************************//**
     * @brief Default constructor.
     *
     * Constructs a list of two players with different colors. This is the basic Connect X
     * configuration, and is equivalent to the classic Connect 4 requirements.
     *
     * @param p_presenter A new game view presenter.
     *
     **********************************************************************************************/
    Gtkmm3NewPlayersList(const INewGameViewPresenter& p_presenter);

    /*******************************************************************************************//**
     * @brief Default destructor.
     *
     **********************************************************************************************/
    ~Gtkmm3NewPlayersList() override;

    // cxgui::INewPlayersList:
    [[nodiscard]] std::size_t GetSize() const override;
    [[nodiscard]] cxmodel::ChipColor GetRowPlayerDiscColor(const std::size_t p_index) const override;
    [[nodiscard]] std::string GetPlayerNameAtRow(const std::size_t p_index) const override;
    [[nodiscard]] std::vector<cxmodel::ChipColor> GetAllColors() const override;
    [[nodiscard]] std::vector<std::string> GetAllPlayerNames() const override;
    [[nodiscard]] std::vector<cxmodel::PlayerType> GetAllPlayerTypes() const override;
    [[nodiscard]] bool AddRow(const INewGameViewPresenter& p_presenter, size_t p_rowIndex) override;
    [[nodiscard]] bool RemoveRow(const std::size_t p_index) override;
    [[nodiscard]] bool UpdateRow(const std::size_t p_index,
                                 const std::string& p_newPlayerNewName,
                                 const cxmodel::ChipColor& p_newPlayerNewDiscColor,
                                 cxmodel::PlayerType p_newPlayerType) override;
    void Clear() override; 
    void RowUpdatedSignalConnect(const std::function<void()>& p_slot) override;

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

    std::function<void()> m_rowUpdatedSlot = [](){};

};

} // namespace cxgui

#endif // GTKMM3NEWPLAYERSLIST_H_FDB93AF1_A5AC_4484_9857_0B207BAE8724