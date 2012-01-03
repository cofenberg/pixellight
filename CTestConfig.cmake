#*********************************************************#
#*  File: CTestConfig.cmake                              *
#*
#*  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


##################################################
## CTest
##################################################
set(CTEST_PROJECT_NAME "PixelLight")
set(CTEST_NIGHTLY_START_TIME "00:00:00 EST")

##################################################
## Dashboard
##################################################
set(CTEST_DROP_METHOD "http")
set(CTEST_DROP_SITE "developer.pixellight.org")
set(CTEST_DROP_LOCATION "/cdash/submit.php?project=PixelLight")
set(CTEST_DROP_SITE_CDASH TRUE)
