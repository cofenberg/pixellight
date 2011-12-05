/*********************************************************\
 *  File: Main.cpp                                       *
 *    Program entry point for MS Windows, Linux, Mac OS X
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Main.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Global functions                                      ]
//[-------------------------------------------------------]
extern int UnitTestsPerformance();


//[-------------------------------------------------------]
//[ Program entry point                                   ]
//[-------------------------------------------------------]
// ... kind of first unit tests: Is our universal program entry point working?
int PLMain(const String &sExecutableFilename, const Array<String> &lstArguments)
{
	// Execute the unit tests (passing thru program arguments like "GetApplicationContext().GetExecutableFilename(), GetApplicationContext().GetArguments()" is not required in here)
	return UnitTestsPerformance();
}
