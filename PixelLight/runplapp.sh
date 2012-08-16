#!/bin/sh
# Change to game directory
CANONPATH="$0"
apppath=`dirname "${CANONPATH}"`
appname=`basename "${CANONPATH}"`-bin

# path to the pixellight runtime
PLRuntimePath="@CMAKE_INSTALL_PREFIX@/share/pixellight/Runtime/@CMAKETOOLS_TARGET_ARCHBITSIZE@"

shift
cd $apppath > /dev/null
# the env var PL_RUNTIME is read by pixellight itself to get the path to its runtime directory
# LD_LIBRARY_PATH must be set to the pl runtime path also, otherwise the linux lib loader wont find all pl libs on app start
PL_RUNTIME=${PLRuntimePath} LD_LIBRARY_PATH=${PLRuntimePath} ./${appname} $@