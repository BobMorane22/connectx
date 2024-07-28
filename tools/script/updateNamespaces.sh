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
