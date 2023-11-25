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
 * @file StdActionIcon.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <cxinv/assertion.h>
#include <cxgui/StdActionIcon.h>

std::string cxgui::FreeDesktop::StdNameGet(StdActionIcon p_icon)
{
    switch(p_icon)
    {
        case StdActionIcon::ADDRESS_BOOK_NEW:          return "address-book-new";
        case StdActionIcon::APPLICATION_EXIT:          return "application-exit";
        case StdActionIcon::APPOINTMENT_NEW:           return "appointment-new";
        case StdActionIcon::CONTACT_NEW:               return "contact-new";
        case StdActionIcon::DIALOG_CANCEL:             return "dialog-cancel";
        case StdActionIcon::DIALOG_CLOSE:              return "dialog-close";
        case StdActionIcon::DIALOG_OK:                 return "dialog-ok";
        case StdActionIcon::DOCUMENT_NEW:              return "document-new";
        case StdActionIcon::DOCUMENT_OPEN:             return "document-open";
        case StdActionIcon::DOCUMENT_OPEN_RECENT:      return "document-open-recent";
        case StdActionIcon::DOCUMENT_PAGE_SETUP:       return "document-page-setup";
        case StdActionIcon::DOCUMENT_PRINT:            return "document-print";
        case StdActionIcon::DOCUMENT_PRINT_PREVIEW:    return "document-print-preview";
        case StdActionIcon::DOCUMENT_PROPERTIES:       return "document-properties";
        case StdActionIcon::DOCUMENT_REVERT:           return "document-revert";
        case StdActionIcon::DOCUMENT_SAVE:             return "document-save";
        case StdActionIcon::DOCUMENT_SAVE_AS:          return "document-save-as";
        case StdActionIcon::EDIT_COPY:                 return "edit-copy";
        case StdActionIcon::EDIT_CUT:                  return "edit-cut";
        case StdActionIcon::EDIT_DELETE:               return "edit-delete";
        case StdActionIcon::EDIT_FIND:                 return "edit-find";
        case StdActionIcon::EDIT_FIND_REPLACE:         return "edit-find-replace";
        case StdActionIcon::EDIT_PASTE:                return "edit-paste";
        case StdActionIcon::EDIT_REDO:                 return "edit-redo";
        case StdActionIcon::EDIT_SELECT_ALL:           return "edit-select-all";
        case StdActionIcon::EDIT_UNDO:                 return "edit-undo";
        case StdActionIcon::FOLDER_NEW:                return "folder-new";
        case StdActionIcon::FORMAT_INDENT_LESS:        return "format-indent-less";
        case StdActionIcon::FORMAT_INDENT_MORE:        return "format-indent-more";
        case StdActionIcon::FORMAT_JUSTIFY_CENTER:     return "format-justify-center";
        case StdActionIcon::FORMAT_JUSTIFY_FILL:       return "format-justify-fill";
        case StdActionIcon::FORMAT_JUSTIFY_LEFT:       return "format-justify-left";
        case StdActionIcon::FORMAT_JUSTIFY_RIGHT:      return "format-justify-right";
        case StdActionIcon::FORMAT_TEXT_DIRECTION_LTR: return "format-text-direction-ltr";
        case StdActionIcon::FORMAT_TEXT_DIRECTION_RTL: return "format-text-direction-rtl";
        case StdActionIcon::FORMAT_TEXT_BOLD:          return "format-text-bold";
        case StdActionIcon::FORMAT_TEXT_ITALIC:        return "format-text-italic";
        case StdActionIcon::FORMAT_TEXT_UNDERLINE:     return "format-text-underline";
        case StdActionIcon::FORMAT_TEXT_STRIKETHROUGH: return "format-text-strikethrough";
        case StdActionIcon::GO_BOTTOM:                 return "go-bottom";
        case StdActionIcon::GO_DOWN:                   return "go-down";
        case StdActionIcon::GO_FIRST:                  return "go-first";
        case StdActionIcon::GO_HOME:                   return "go-home";
        case StdActionIcon::GO_JUMP:                   return "go-jump";
        case StdActionIcon::GO_LAST:                   return "go-last";
        case StdActionIcon::GO_NEXT:                   return "go-next";
        case StdActionIcon::GO_PREVIOUS:               return "go-previous";
        case StdActionIcon::GO_TOP:                    return "go-top";
        case StdActionIcon::GO_UP:                     return "go-up";
        case StdActionIcon::HELP_ABOUT:                return "help-about";
        case StdActionIcon::HELP_CONTENTS:             return "help-contents";
        case StdActionIcon::HELP_FAQ:                  return "help-faq";
        case StdActionIcon::INSERT_IMAGE:              return "insert-image";
        case StdActionIcon::INSERT_LINK:               return "insert-link";
        case StdActionIcon::INSERT_OBJECT:             return "insert-object";
        case StdActionIcon::INSERT_TEXT:               return "insert-text";
        case StdActionIcon::LIST_ADD:                  return "list-add";
        case StdActionIcon::LIST_REMOVE:               return "list-remove";
        case StdActionIcon::MAIL_FORWARD:              return "mail-forward";
        case StdActionIcon::MAIL_MARK_IMPORTANT:       return "mail-mark-important";
        case StdActionIcon::MAIL_MARK_JUNK:            return "mail-mark-junk";
        case StdActionIcon::MAIL_MARK_NOTJUNK:         return "mail-mark-notjunk";
        case StdActionIcon::MAIL_MARK_READ:            return "mail-mark-read";
        case StdActionIcon::MAIL_MARK_UNREAD:          return "mail-mark-unread";
        case StdActionIcon::MAIL_MESSAGE_NEW:          return "mail-message-new";
        case StdActionIcon::MAIL_REPLY_ALL:            return "mail-reply-all";
        case StdActionIcon::MAIL_REPLY_SENDER:         return "mail-reply-sender";
        case StdActionIcon::MAIL_SEND:                 return "mail-send";
        case StdActionIcon::MAIL_SEND_RECEIVE:         return "mail-send-receive";
        case StdActionIcon::MEDIA_EJECT:               return "media-eject";
        case StdActionIcon::MEDIA_PLAYBACK_PAUSE:      return "media-playback-pause";
        case StdActionIcon::MEDIA_PLAYBACK_START:      return "media-playback-start";
        case StdActionIcon::MEDIA_PLAYBACK_STOP:       return "media-playback-stop";
        case StdActionIcon::MEDIA_RECORD:              return "media-record";
        case StdActionIcon::MEDIA_SEEK_BACKWARD:       return "media-seek-backward";
        case StdActionIcon::MEDIA_SEEK_FORWARD:        return "media-seek-forward";
        case StdActionIcon::MEDIA_SKIP_BACKWARD:       return "media-skip-backward";
        case StdActionIcon::MEDIA_SKIP_FORWARD:        return "media-skip-forward";
        case StdActionIcon::OBJECT_FLIP_HORIZONTAL:    return "object-flip-horizontal";
        case StdActionIcon::OBJECT_FLIP_VERTICAL:      return "object-flip-vertical";
        case StdActionIcon::OBJECT_ROTATE_LEFT:        return "object-rotate-left";
        case StdActionIcon::OBJECT_ROTATE_RIGHT:       return "object-rotate-right";
        case StdActionIcon::SYSTEM_LOCK_SCREEN:        return "system-lock-screen";
        case StdActionIcon::SYSTEM_LOG_OUT:            return "system-log-out";
        case StdActionIcon::SYSTEM_RUN:                return "system-run";
        case StdActionIcon::SYSTEM_SEARCH:             return "system-search";
        case StdActionIcon::TOOLS_CHECK_SPELLING:      return "tools-check-spelling";
        case StdActionIcon::VIEW_FULLSCREEN:           return "view-fullscreen";
        case StdActionIcon::VIEW_REFRESH:              return "view-refresh";
        case StdActionIcon::VIEW_SORT_ASCENDING:       return "view-sort-ascending";
        case StdActionIcon::VIEW_SORT_DESCENDING:      return "view-sort-descending";
        case StdActionIcon::WINDOW_CLOSE:              return "window-close";
        case StdActionIcon::WINDOW_NEW:                return "window-new";
        case StdActionIcon::ZOOM_BEST_FIT:             return "zoom-best-fit";
        case StdActionIcon::ZOOM_IN:                   return "zoom-in";
        case StdActionIcon::ZOOM_ORIGINAL:             return "zoom-original";
        case StdActionIcon::ZOOM_OUT:                  return "zoom-out";
    }

    ASSERT_ERROR_MSG("Unknown action icon.");
    return {};
}
