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
