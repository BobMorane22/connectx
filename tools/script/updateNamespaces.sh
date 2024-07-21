#!/bin/bash

# Replacements:
#
# cxfoo::            cx::foo::
# namespace cxfoo    namespace cx::foo

# cxinv -> cx::inv
./tools/script/findReplace.sh "cxinv::" "cx::inv::"
./tools/script/findReplace.sh "namespace cxinv" "namespace cx::inv"
./tools/script/findReplace.sh "@namespace cxinv" "@namespace cx::inv"

# cxstd/ -> cxcmn/
#./tools/script/findReplace.sh "<cxstd" "<cxcmn"
./tools/script/findReplace.sh "PRIVATE cxstd" "PRIVATE cxcmn"
