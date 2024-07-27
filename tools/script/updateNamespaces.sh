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

# cxgui -> cx::cmn::ui
./tools/script/findReplace.sh "cx::gui::" "cx::cmn::ui::"
./tools/script/findReplace.sh "namespace cx::gui" "namespace cx::cmn::ui"
./tools/script/findReplace.sh "@namespace cx::gui" "@namespace cx::cmn::ui"
