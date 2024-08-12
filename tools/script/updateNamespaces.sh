#!/bin/bash

# Find and replace globally.
cx -f h   \<cxuicmn \<cxcmnui
cx -f cpp \<cxuicmn \<cxcmnui
cx -f dox \<cxuicmn \<cxcmnui
cx -f in  \<cxuicmn \<cxcmnui

# Find and replace in specific directory.
## find /path/to/files -type f -exec sed -i 's/oldstring/new string/g' {} \;

