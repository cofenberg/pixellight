/*********************************************************\
 *  File: LogTest.cpp                                    *
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
#include <PLCore/Log/Log.h>
#include "PLTestBase/General/LogTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *LogTest::GetName() const
{
	return "LogTest";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void LogTest::Test()
{
	// Get log instance
	Print("Get log instance\n");
	Log *pLog = Log::GetInstance();
	if (pLog) {
		// Open the log
		Print("Open the log\n");
		if (pLog->Open("Test.txt")) {
			// Some log output tests
			Print("Some log output tests:\n");
			PL_LOG(Info, "Log-system started")
			PL_LOG(Error, "Failed to reach the end of the world")

			// Close the log
			Print("Close the log\n");
			if (!Log::GetInstance()->Close())
				Print("Failed to close the log!\n");
		} else Print("Failed to open the log!\n");
	} else Print("Failed to get log instance!\n");
}
