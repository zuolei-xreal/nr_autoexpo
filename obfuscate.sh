#!/bin/bash
set -e
BIN=${OBFUSCATE_BIN}
find example -name "*.cc" -o -name "*.cpp" -o -name "*.h" -o -name "*.hpp"|xargs $BIN > obfuscate.log
