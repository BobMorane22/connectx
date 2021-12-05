#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script launches valgrind on Connect X.
#
# @file valgrind.sh
# @date 2021
#
#---------------------------------------------------------------------------------------------------

make
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./valgrind-out.txt ./connectx/connectx
