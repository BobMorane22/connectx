#!/bin/bash

#---------------------------------------------------------------------------------------------------
# This script launches valgrind on Connect X.
#
# Parameters:
#   $1 : The program to execute under valgring.
#
# @file valgrind.sh
# @date 2021
#
#---------------------------------------------------------------------------------------------------

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=./valgrind-out.txt $1
