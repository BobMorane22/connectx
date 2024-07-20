#!/bin/bash

# Replacements:
#
# cxfoo::            cx::foo::
# namespace cxfoo    namespace cx::foo

./tools/script/findReplace.sh "cxinv::" "cx::inv::"
./tools/script/findReplace.sh "namespace cxinv" "namespace cx::inv"
./tools/script/findReplace.sh "@namespace cxinv" "@namespace cx::inv"
