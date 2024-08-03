#!/bin/bash

# cxstd -> cx::cmn
./tools/script/findReplace.sh "cxstd::" "cx::cmn::"
./tools/script/findReplace.sh "namespace cxstd" "namespace cx::cmn"
./tools/script/findReplace.sh "@namespace cxstdinv" "@namespace cx::cmn"
./tools/script/findReplace.sh "<cxstd" "<cxcmn"
./tools/script/findReplace.sh "PRIVATE cxstd" "PRIVATE cxcmn"

# cxinv -> cx::inv
./tools/script/findReplace.sh "cxinv::" "cx::inv::"
./tools/script/findReplace.sh "namespace cxinv" "namespace cx::inv"
./tools/script/findReplace.sh "@namespace cxinv" "@namespace cx::inv"

# cxmath -> cx::math
./tools/script/findReplace.sh "cxmath::" "cx::math::"
./tools/script/findReplace.sh "namespace cxmath" "namespace cx::math"
./tools/script/findReplace.sh "@namespace cxmath" "@namespace cx::math"

# cxlog -> cx::log
./tools/script/findReplace.sh "cxlog::" "cx::log::"
./tools/script/findReplace.sh "namespace cxlog" "namespace cx::log"
./tools/script/findReplace.sh "@namespace cxlog" "@namespace cx::log"

# cxunit -> cx::unit
./tools/script/findReplace.sh "cxunit::" "cx::unit::"
./tools/script/findReplace.sh "namespace cxunit" "namespace cx::unit"
./tools/script/findReplace.sh "@namespace cxunit" "@namespace cx::unit"

# model -> cx::model
./tools/script/findReplace.sh "cxmodel::" "cx::model::"
./tools/script/findReplace.sh "namespace cxmodel" "namespace cx::model"
./tools/script/findReplace.sh "@namespace cxmodel" "@namespace cx::model"

# cxgui -> cx::gui
./tools/script/findReplace.sh "cxgui::" "cx::gui::"
./tools/script/findReplace.sh "namespace cxgui" "namespace cx::gui"
./tools/script/findReplace.sh "@namespace cxgui" "@namespace cx::gui"

# cxgui -> cx:ui::cmn
./tools/script/findReplace.sh "cx::gui::" "cx::ui::cmn::"
./tools/script/findReplace.sh "namespace cx::gui" "namespace cx::ui::cmn"
./tools/script/findReplace.sh "@namespace cx::gui" "@namespace cx::ui::cmn"
./tools/script/findReplace.sh "<cxgui" "<cxuicmn"
./tools/script/findReplace.sh "\"cxgui" "\"cxuicmn"
./tools/script/findReplace.sh "PRIVATE cxgui" "PRIVATE cxuicmn"

# Added cxuicmngtkmm3 library
./tools/script/findReplace.sh "cx::cmn::ui::" "cx::ui::cmn::"
./tools/script/findReplace.sh "namespace cx::cmn::ui" "namespace cx::ui::cmn"
./tools/script/findReplace.sh "@namespace cx::cmn::ui" "@namespace cx::ui::cmn"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3AbstractWidgetsFactory.h" "include <cxuicmngtkmm3\/Gtkmm3AbstractWidgetsFactory.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Button.h" "include <cxuicmngtkmm3\/Gtkmm3Button.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Connection.h" "include <cxuicmngtkmm3\/Gtkmm3Connection.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Dialog.h" "include <cxuicmngtkmm3\/Gtkmm3Dialog.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3EditBox.h" "include <cxuicmngtkmm3\/Gtkmm3EditBox.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Label.h" "include <cxuicmngtkmm3\/Gtkmm3Label.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Layout.h" "include <cxuicmngtkmm3\/Gtkmm3Layout.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Menu.h" "include <cxuicmngtkmm3\/Gtkmm3Menu.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3MenuBar.h" "include <cxuicmngtkmm3\/Gtkmm3MenuBar.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3MenuItem.h" "include <cxuicmngtkmm3\/Gtkmm3MenuItem.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3OnOffSwitch.h" "include <cxuicmngtkmm3\/Gtkmm3OnOffSwitch.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3SpinBox.h" "include <cxuicmngtkmm3\/Gtkmm3SpinBox.h"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3WidgetDelegate.h" "include <cxuicmngtkmm3\/Gtkmm3WidgetDelegate.h"
./tools/script/findReplace.sh "include <cxuicmn\/gtkmmConversions.h" "include <cxuicmngtkmm3\/gtkmmConversions.h"

# Added cxuigtkmm3 library
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3AboutWindow.h>" "include <cxuigtkmm3\/Gtkmm3AboutWindow.h>"                        
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3AbstractConnectXWidgetsFactory.h>" "include <cxuigtkmm3\/Gtkmm3AbstractConnectXWidgetsFactory.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3AnimatedBoard.h>" "include <cxuigtkmm3\/Gtkmm3AnimatedBoard.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3AnimatedBoardTimerRAII.h>" "include <cxuigtkmm3\/Gtkmm3AnimatedBoardTimerRAII.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3BoardElementCache.h>" "include <cxuigtkmm3\/Gtkmm3BoardElementCache.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3Chip.h>" "include <cxuigtkmm3\/Gtkmm3Chip.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3ColorPicker.h>" "include <cxuigtkmm3\/Gtkmm3ColorPicker.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3ContextRestoreRAII.h>" "include <cxuigtkmm3\/Gtkmm3ContextRestoreRAII.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3DiscChip.h>" "include <cxuigtkmm3\/Gtkmm3DiscChip.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3GameResolutionDialog.h>" "include <cxuigtkmm3\/Gtkmm3GameResolutionDialog.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3GameView.h>" "include <cxuigtkmm3\/Gtkmm3GameView.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3MainWindow.h>" "include <cxuigtkmm3\/Gtkmm3MainWindow.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3NewGameView.h>" "include <cxuigtkmm3\/Gtkmm3NewGameView.h>"
./tools/script/findReplace.sh "include <cxuicmn\/Gtkmm3NewPlayersList.h>" "include <cxuigtkmm3\/Gtkmm3NewPlayersList.h>"
