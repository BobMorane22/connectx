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
 * @file StdActionIconTests.cpp
 * @date 2023
 *
 *************************************************************************************************/

#include <gtest/gtest.h>

#include <cxunit/DisableStdStreamsRAII.h>
#include <cxgui/StdActionIcon.h>

TEST(StdNameGet, FunctionCall_ActionIconGiven_ValidNameReturned)
{
    using namespace cxgui::FreeDesktop;

    ASSERT_TRUE(StdNameGet(StdActionIcon::ADDRESS_BOOK_NEW) == "address-book-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::APPLICATION_EXIT) == "application-exit");
    ASSERT_TRUE(StdNameGet(StdActionIcon::APPOINTMENT_NEW) == "appointment-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::CONTACT_NEW) == "contact-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DIALOG_CANCEL) == "dialog-cancel");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DIALOG_CLOSE) == "dialog-close");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DIALOG_OK) == "dialog-ok");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_NEW) == "document-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_OPEN) == "document-open");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_OPEN_RECENT) == "document-open-recent");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_PAGE_SETUP) == "document-page-setup");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_PRINT) == "document-print");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_PRINT_PREVIEW) == "document-print-preview");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_PROPERTIES) == "document-properties");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_REVERT) == "document-revert");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_SAVE) == "document-save");
    ASSERT_TRUE(StdNameGet(StdActionIcon::DOCUMENT_SAVE_AS) == "document-save-as");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_COPY) == "edit-copy");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_CUT) == "edit-cut");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_DELETE) == "edit-delete");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_FIND) == "edit-find");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_FIND_REPLACE) == "edit-find-replace");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_PASTE) == "edit-paste");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_REDO) == "edit-redo");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_SELECT_ALL) == "edit-select-all");
    ASSERT_TRUE(StdNameGet(StdActionIcon::EDIT_UNDO) == "edit-undo");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FOLDER_NEW) == "folder-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_INDENT_LESS) == "format-indent-less");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_INDENT_MORE) == "format-indent-more");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_JUSTIFY_CENTER) == "format-justify-center");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_JUSTIFY_FILL) == "format-justify-fill");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_JUSTIFY_LEFT) == "format-justify-left");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_JUSTIFY_RIGHT) == "format-justify-right");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_TEXT_DIRECTION_LTR) == "format-text-direction-ltr");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_TEXT_DIRECTION_RTL) == "format-text-direction-rtl");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_TEXT_BOLD) == "format-text-bold");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_TEXT_ITALIC) == "format-text-italic");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_TEXT_UNDERLINE) == "format-text-underline");
    ASSERT_TRUE(StdNameGet(StdActionIcon::FORMAT_TEXT_STRIKETHROUGH) == "format-text-strikethrough");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_BOTTOM) == "go-bottom");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_DOWN) == "go-down");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_FIRST) == "go-first");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_HOME) == "go-home");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_JUMP) == "go-jump");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_LAST) == "go-last");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_NEXT) == "go-next");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_PREVIOUS) == "go-previous");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_TOP) == "go-top");
    ASSERT_TRUE(StdNameGet(StdActionIcon::GO_UP) == "go-up");
    ASSERT_TRUE(StdNameGet(StdActionIcon::HELP_ABOUT) == "help-about");
    ASSERT_TRUE(StdNameGet(StdActionIcon::HELP_CONTENTS) == "help-contents");
    ASSERT_TRUE(StdNameGet(StdActionIcon::HELP_FAQ) == "help-faq");
    ASSERT_TRUE(StdNameGet(StdActionIcon::INSERT_IMAGE) == "insert-image");
    ASSERT_TRUE(StdNameGet(StdActionIcon::INSERT_LINK) == "insert-link");
    ASSERT_TRUE(StdNameGet(StdActionIcon::INSERT_OBJECT) == "insert-object");
    ASSERT_TRUE(StdNameGet(StdActionIcon::INSERT_TEXT) == "insert-text");
    ASSERT_TRUE(StdNameGet(StdActionIcon::LIST_ADD) == "list-add");
    ASSERT_TRUE(StdNameGet(StdActionIcon::LIST_REMOVE) == "list-remove");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_FORWARD) == "mail-forward");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_MARK_IMPORTANT) == "mail-mark-important");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_MARK_JUNK) == "mail-mark-junk");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_MARK_NOTJUNK) == "mail-mark-notjunk");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_MARK_READ) == "mail-mark-read");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_MARK_UNREAD) == "mail-mark-unread");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_MESSAGE_NEW) == "mail-message-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_REPLY_ALL) == "mail-reply-all");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_REPLY_SENDER) == "mail-reply-sender");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_SEND) == "mail-send");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MAIL_SEND_RECEIVE) == "mail-send-receive");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_EJECT) == "media-eject");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_PLAYBACK_PAUSE) == "media-playback-pause");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_PLAYBACK_START) == "media-playback-start");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_PLAYBACK_STOP) == "media-playback-stop");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_RECORD) == "media-record");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_SEEK_BACKWARD) == "media-seek-backward");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_SEEK_FORWARD) == "media-seek-forward");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_SKIP_BACKWARD) == "media-skip-backward");
    ASSERT_TRUE(StdNameGet(StdActionIcon::MEDIA_SKIP_FORWARD) == "media-skip-forward");
    ASSERT_TRUE(StdNameGet(StdActionIcon::OBJECT_FLIP_HORIZONTAL) == "object-flip-horizontal");
    ASSERT_TRUE(StdNameGet(StdActionIcon::OBJECT_FLIP_VERTICAL) == "object-flip-vertical");
    ASSERT_TRUE(StdNameGet(StdActionIcon::OBJECT_ROTATE_LEFT) == "object-rotate-left");
    ASSERT_TRUE(StdNameGet(StdActionIcon::OBJECT_ROTATE_RIGHT) == "object-rotate-right");
    ASSERT_TRUE(StdNameGet(StdActionIcon::SYSTEM_LOCK_SCREEN) == "system-lock-screen");
    ASSERT_TRUE(StdNameGet(StdActionIcon::SYSTEM_LOG_OUT) == "system-log-out");
    ASSERT_TRUE(StdNameGet(StdActionIcon::SYSTEM_RUN) == "system-run");
    ASSERT_TRUE(StdNameGet(StdActionIcon::SYSTEM_SEARCH) == "system-search");
    ASSERT_TRUE(StdNameGet(StdActionIcon::TOOLS_CHECK_SPELLING) == "tools-check-spelling");
    ASSERT_TRUE(StdNameGet(StdActionIcon::VIEW_FULLSCREEN) == "view-fullscreen");
    ASSERT_TRUE(StdNameGet(StdActionIcon::VIEW_REFRESH) == "view-refresh");
    ASSERT_TRUE(StdNameGet(StdActionIcon::VIEW_SORT_ASCENDING) == "view-sort-ascending");
    ASSERT_TRUE(StdNameGet(StdActionIcon::VIEW_SORT_DESCENDING) == "view-sort-descending");
    ASSERT_TRUE(StdNameGet(StdActionIcon::WINDOW_CLOSE) == "window-close");
    ASSERT_TRUE(StdNameGet(StdActionIcon::WINDOW_NEW) == "window-new");
    ASSERT_TRUE(StdNameGet(StdActionIcon::ZOOM_BEST_FIT) == "zoom-best-fit");
    ASSERT_TRUE(StdNameGet(StdActionIcon::ZOOM_IN) == "zoom-in");
    ASSERT_TRUE(StdNameGet(StdActionIcon::ZOOM_ORIGINAL) == "zoom-original");
    ASSERT_TRUE(StdNameGet(StdActionIcon::ZOOM_OUT) == "zoom-out");
}

TEST(StdNameGet, FunctionCall_InvalidActionGiven_AssertAndEmptyNameReturned)
{
    using namespace cxgui::FreeDesktop;

    cxunit::DisableStdStreamsRAII streamDisabler;
    const auto invalid = static_cast<StdActionIcon>(-1);
    const std::string iconName = StdNameGet(invalid);

    ASSERT_ASSERTION_FAILED(streamDisabler);
    ASSERT_TRUE(iconName == "");
}
