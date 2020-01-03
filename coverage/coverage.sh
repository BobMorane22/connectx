#*************************************************************************************************
#  This file is part of Connect X.
#
#  Connect X is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  Connect X is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with Connect X. If not, see <https://www.gnu.org/licenses/>.
#
#************************************************************************************************/
#
#*************************************************************************************************
# This script generates coverage HTML reports.
#
# @file coverage.sh
# @date 2020
#
#************************************************************************************************/

#!/bin/sh

for sourceFile in $(find . -name '*Tests.cpp') ; do
    dir=$(dirname "${sourceFile}")
    gcov --relative-only $sourceFile -o $dir
done

mv *.gcov coverage

lcov --no-external --capture --directory . --output-file coverage/coverage.info
genhtml coverage/coverage.info --output-directory coverage/report