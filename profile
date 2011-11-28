#*********************************************************#
#*  File: profile                                        *
#*
#*  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
#*
#*  This file is part of PixelLight.
#*
#*  PixelLight is free software: you can redistribute it and/or modify
#*  it under the terms of the GNU Lesser General Public License as published by
#*  the Free Software Foundation, either version 3 of the License, or
#*  (at your option) any later version.
#*
#*  PixelLight is distributed in the hope that it will be useful,
#*  but WITHOUT ANY WARRANTY; without even the implied warranty of
#*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#*  GNU Lesser General Public License for more details.
#*
#*  You should have received a copy of the GNU Lesser General Public License
#*  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
#*********************************************************#


# This script can be used to set the path to the local (not installed)
# PixelLight runtime, which is stored in the environment variable
# PL_RUNTIME. If that variable is set, it will be prefered by the
# PixelLight runtime and used instead of searching for an installed
# runtime in /usr/ or /usr/local/.
# 
# Please note that this script must be 'sources' rather than invoked directly,
# in order to export the variables to the current shell. Also make sure that
# the current directory is the root directory of the PixelLight source
# tree, otherwise the path will be wrong.
#
# Execute this script:
#   source ./profile     (OR:)
#   . ./profile

# Detect the used OS
if [ $OSTYPE == "linux-gnu" ] ; then
	PLATFORM="Linux"
elif [ $OSTYPE == "darwin10.0" ] ; then
	PLATFORM="MacOSX"
elif [ $OSTYPE == "darwin11" ] ; then
	PLATFORM="MacOSX"
else
	PLATFORM="Unknown"
fi

# Export the environment variable pointing to the PixelLight runtime directory
export PL_RUNTIME="$PWD/Bin-$PLATFORM/Runtime/x86"

# Print the value of the environment variable
echo "PixelLight runtime variable set to:"
echo "  PL_RUNTIME = '$PL_RUNTIME'"
