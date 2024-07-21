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
