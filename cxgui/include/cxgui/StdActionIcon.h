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
 * @file StdActionIcon.h
 * @date 2023
 *
 *************************************************************************************************/

#ifndef STDACTIONICON_H_0C3D0B5F_2E98_498A_9B07_15166FE0EC0D
#define STDACTIONICON_H_0C3D0B5F_2E98_498A_9B07_15166FE0EC0D

#include <string>

namespace cxgui::FreeDesktop
{

/**********************************************************************************************//**
 * @brief Standard action icons as described by the FreeDesktop.org standard.
 *
 * For more information, see:
 *
 *        https://specifications.freedesktop.org/icon-naming-spec/0.8/ar01s04.html
 *
 *************************************************************************************************/
enum class StdActionIcon
{
    /** The icon used for the action to create a new address book.*/
    ADDRESS_BOOK_NEW, 
    
    /** The icon used for exiting an application. Typically this is seen in the application's menus as File->Quit.*/
    APPLICATION_EXIT, 
    
    /** The icon used for the action to create a new appointment in a calendaring application.*/
    APPOINTMENT_NEW,  
    
    /** The icon used for the action to create a new contact in an address book application.*/
    CONTACT_NEW, 
    
    /** The icon used for the “Cancel” button that might appear in dialog windows.*/
    DIALOG_CANCEL, 
    
    /** The icon used for the “Close” button that might appear in dialog windows.*/
    DIALOG_CLOSE, 
    
    /** The icon used for the “OK” button that might appear in dialog windows.*/
    DIALOG_OK, 
    
    /** The icon used for the action to create a new document.*/
    DOCUMENT_NEW, 
    
    /** The icon used for the action to open a document.*/
    DOCUMENT_OPEN, 
    
    /** The icon used for the action to open a document that was recently opened.*/
    DOCUMENT_OPEN_RECENT,   
    
    /** The icon for the page setup action of a document editor.*/
    DOCUMENT_PAGE_SETUP,    
    
    /** The icon for the print action of an application.*/
    DOCUMENT_PRINT,         
    
    /** The icon for the print preview action of an application.*/
    DOCUMENT_PRINT_PREVIEW, 
    
    /** The icon for the action to view the properties of a document in an application.*/
    DOCUMENT_PROPERTIES, 
    
    /** The icon for the action of reverting to a previous version of a document.*/
    DOCUMENT_REVERT, 
    
    /** The icon for the save action.*/
    DOCUMENT_SAVE, 
    
    /** The icon for the save as action.*/
    DOCUMENT_SAVE_AS, 
    
    /** The icon for the copy action.*/
    EDIT_COPY, 
    
    /** The icon for the cut action.*/
    EDIT_CUT, 
    
    /** The icon for the delete action.*/
    EDIT_DELETE, 
    
    /** The icon for the find action.*/
    EDIT_FIND, 
    
    /** The icon for the find and replace action.*/
    EDIT_FIND_REPLACE, 
    
    /** The icon for the paste action.*/
    EDIT_PASTE, 
    
    /** The icon for the redo action.*/
    EDIT_REDO, 
    
    /** The icon for the select all action.*/
    EDIT_SELECT_ALL, 
    
    /** The icon for the undo action.*/
    EDIT_UNDO, 
    
    /** The icon for creating a new folder.*/
    FOLDER_NEW, 
    
    /** The icon for the decrease indent formatting action.*/
    FORMAT_INDENT_LESS, 
    
    /** The icon for the increase indent formatting action.*/
    FORMAT_INDENT_MORE, 
    
    /** The icon for the center justification formatting action.*/
    FORMAT_JUSTIFY_CENTER, 
    
    /** The icon for the fill justification formatting action.*/
    FORMAT_JUSTIFY_FILL, 
    
    /** The icon for the left justification formatting action.*/
    FORMAT_JUSTIFY_LEFT, 
    
    /** The icon for the right justification action.*/
    FORMAT_JUSTIFY_RIGHT, 
    
    /** The icon for the left-to-right text formatting action.*/
    FORMAT_TEXT_DIRECTION_LTR, 
    
    /** The icon for the right-to-left formatting action.*/
    FORMAT_TEXT_DIRECTION_RTL, 
    
    /** The icon for the bold text formatting action.*/
    FORMAT_TEXT_BOLD, 
    
    /** The icon for the italic text formatting action.*/
    FORMAT_TEXT_ITALIC, 
    
    /** The icon for the underlined text formatting action.*/
    FORMAT_TEXT_UNDERLINE, 
    
    /** The icon for the strikethrough text formatting action.*/
    FORMAT_TEXT_STRIKETHROUGH, 
    
    /** The icon for the go to bottom of a list action.*/
    GO_BOTTOM, 
    
    /** The icon for the go down in a list action.*/
    GO_DOWN, 
    
    /** The icon for the go to the first item in a list action.*/
    GO_FIRST, 
    
    /** The icon for the go to home location action.*/
    GO_HOME, 
    
    /** The icon for the jump to action.*/
    GO_JUMP, 
    
    /** The icon for the go to the last item in a list action.*/
    GO_LAST, 
    
    /** The icon for the go to the next item in a list action.*/
    GO_NEXT, 
    
    /** The icon for the go to the previous item in a list action.*/
    GO_PREVIOUS, 

    /** The icon for the go to the top of a list action.*/
    GO_TOP, 
    
    /** The icon for the go up in a list action.*/
    GO_UP, 
    
    /** The icon for the About item in the Help menu.*/
    HELP_ABOUT, 
    
    /** The icon for Contents item in the Help menu.*/
    HELP_CONTENTS, 
    
    /** The icon for the FAQ item in the Help menu.*/
    HELP_FAQ, 
    
    /** The icon for the insert image action of an application.*/
    INSERT_IMAGE, 
    
    /** The icon for the insert link action of an application.*/
    INSERT_LINK, 
    
    /** The icon for the insert object action of an application.*/
    INSERT_OBJECT, 
    
    /** The icon for the insert text action of an application.*/
    INSERT_TEXT, 
    
    /** The icon for the add to list action.*/
    LIST_ADD, 
    
    /** The icon for the remove from list action.*/
    LIST_REMOVE, 
    
    /** The icon for the forward action of an electronic mail application.*/
    MAIL_FORWARD, 
    
    /** The icon for the mark as important action of an electronic mail application.*/
    MAIL_MARK_IMPORTANT, 
    
    /** The icon for the mark as junk action of an electronic mail application.*/
    MAIL_MARK_JUNK, 
    
    /** The icon for the mark as not junk action of an electronic mail application.*/
    MAIL_MARK_NOTJUNK, 
    
    /** The icon for the mark as read action of an electronic mail application.*/
    MAIL_MARK_READ, 
    
    /** The icon for the mark as unread action of an electronic mail application.*/
    MAIL_MARK_UNREAD, 
    
    /** The icon for the compose new mail action of an electronic mail application.*/
    MAIL_MESSAGE_NEW, 
    
    /** The icon for the reply to all action of an electronic mail application.*/
    MAIL_REPLY_ALL, 
    
    /** The icon for the reply to sender action of an electronic mail application.*/
    MAIL_REPLY_SENDER, 
    
    /** The icon for the send action of an electronic mail application.*/
    MAIL_SEND, 
    
    /** The icon for the send and receive action of an electronic mail application.*/
    MAIL_SEND_RECEIVE, 
    
    /** The icon for the eject action of a media player or file manager.*/
    MEDIA_EJECT, 
    
    /** The icon for the pause action of a media player.*/
    MEDIA_PLAYBACK_PAUSE, 
    
    /** The icon for the start playback action of a media player.*/
    MEDIA_PLAYBACK_START, 
    
    /** The icon for the stop action of a media player.*/
    MEDIA_PLAYBACK_STOP, 
    
    /** The icon for the record action of a media application.*/
    MEDIA_RECORD, 
    
    /** The icon for the seek backward action of a media player.*/
    MEDIA_SEEK_BACKWARD, 
    
    /** The icon for the seek forward action of a media player.*/
    MEDIA_SEEK_FORWARD, 
    
    /** The icon for the skip backward action of a media player.*/
    MEDIA_SKIP_BACKWARD, 
    
    /** The icon for the skip forward action of a media player.*/
    MEDIA_SKIP_FORWARD, 
    
    /** The icon for the action to flip an object horizontally.*/
    OBJECT_FLIP_HORIZONTAL, 
    
    /** The icon for the action to flip an object vertically.*/
    OBJECT_FLIP_VERTICAL, 
    
    /** The icon for the rotate left action performed on an object.*/
    OBJECT_ROTATE_LEFT, 
    
    /** The icon for the rotate rigt action performed on an object.*/
    OBJECT_ROTATE_RIGHT, 
    
    /** The icon used for the “Lock Screen” item in the desktop's panel application.*/
    SYSTEM_LOCK_SCREEN, 
    
    /** The icon used for the “Log Out” item in the desktop's panel application.*/
    SYSTEM_LOG_OUT, 
    
    /** The icon used for the “Run Application...” item in the desktop's panel application.*/
    SYSTEM_RUN, 
    
    /** The icon used for the “Search” item in the desktop's panel application.*/
    SYSTEM_SEARCH, 
    
    /** The icon used for the “Check Spelling” item in the application's “Tools” menu.*/
    TOOLS_CHECK_SPELLING, 
    
    /** The icon used for the “Fullscreen” item in the application's “View” menu.*/
    VIEW_FULLSCREEN, 
    
    /** The icon used for the “Refresh” item in the application's “View” menu.*/
    VIEW_REFRESH, 
    
    /** The icon used for the “Sort Ascending” item in the application's “View” menu, or in a button for changing the sort method for a list.*/
    VIEW_SORT_ASCENDING, 
    
    /** The icon used for the “Sort Descending” item in the application's “View” menu, or in a button for changing the sort method for a list.*/
    VIEW_SORT_DESCENDING, 
    
    /** The icon used for the “Close Window” item in the application's “Windows” menu.*/
    WINDOW_CLOSE, 
    
    /** The icon used for the “New Window” item in the application's “Windows” menu.*/
    WINDOW_NEW, 
    
    /** The icon used for the “Best Fit” item in the application's “View” menu.*/
    ZOOM_BEST_FIT, 
    
    /** The icon used for the “Zoom in” item in the application's “View” menu.*/
    ZOOM_IN, 
    
    /** The icon used for the “Original Size” item in the application's “View” menu.*/
    ZOOM_ORIGINAL, 
    
    /** The icon used for the “Zoom Out” item in the application's “View” menu.*/
    ZOOM_OUT 
};

/**********************************************************************************************//**
 * @brief Gets the standard action icon name as defined by the FreeDesktop.org standard.
 *
 * For more information, see:
 *
 *        https://specifications.freedesktop.org/icon-naming-spec/0.8/ar01s04.html
 *
 * @param p_icon
 *      The icon to get the name of.
 *
 * @return
 *      The associated standard name.
 *
 *************************************************************************************************/
[[nodiscard]] std::string StdNameGet(StdActionIcon p_icon);

} // namespace cxgui::FreeDesktop

#endif // STDACTIONICON_H_0C3D0B5F_2E98_498A_9B07_15166FE0EC0D
