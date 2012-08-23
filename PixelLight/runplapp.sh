#!/bin/sh
# Change to game directory
CANONPATH=`readlink -f $0`
apppath=`dirname "${CANONPATH}"`
appname=`basename "${CANONPATH}"`
basepath=`readlink -f ${apppath}@CMAKETOOLS_BASEPATH_GO_UPS@`

appPath32=${apppath}/x86
appPath64=${apppath}/x64

#default to 32Bit
runtimeArch=x86
apppath=${appPath32}

MACHINE=`uname -m`
if [ "$MACHINE" = "x86_64" -a -e "${appPath64}/${appname}" ]
then
	runtimeArch=x64
	apppath=${appPath64}
fi

# path to the pixellight runtime
PLRuntimePath="${basepath}/Runtime/${runtimeArch}"

shift
cd $apppath > /dev/null
# the env var PL_RUNTIME is read by pixellight itself to get the path to its runtime directory
# LD_LIBRARY_PATH must be set to the pl runtime path also, otherwise the linux lib loader wont find all pl libs on app start
PL_RUNTIME=${PLRuntimePath} LD_LIBRARY_PATH=${PLRuntimePath} ./${appname} $@