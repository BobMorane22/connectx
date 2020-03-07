#!/bin/bash

#---------------------------------------------------------------------------------------------------
#
# This script prints header guards for C++ with a random GUID included for uniqueness. For example, 
# if you have a class named 'MyClass' and that you run this script with 'MyClass' as a parameter,
# you will get (printed on the terminal) header guards of the form:
#
#     #infdef MYCLASS_H_3F78DA02_6367_496E_B06D_5EC959329CC2
#     #define MYCLASS_H_3F78DA02_6367_496E_B06D_5EC959329CC2
#     #endif // MYCLASS_H_3F78DA02_6367_496E_B06D_5EC959329CC2
#
# Note that the GUID portion changes every time you invoke this script.
#
# @file     gen_guid.sh
# @date 2017
#
#---------------------------------------------------------------------------------------------------

# Creating GUID:
uuid=$(uuidgen)     # get random GUID
uuid=${uuid//-/_}   # replace '-' by '_'
uuid=${uuid^^}      # all caps!

# Dealing with the class name:
class="${1^^}_H_"

# Making header:
ifndef="#ifndef $class$uuid"
define="#define $class$uuid"
endif="#endif // $class$uuid"

# Printing header guards:
echo ${ifndef}
echo ${define}
echo ${endif}
