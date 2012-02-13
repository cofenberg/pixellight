/*********************************************************\
 *  File: UnitTestsPerformance.cpp                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
#include <time.h>
#include <string>
#include <fstream>
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include <UnitTest++AddIns/RunAllTests.h>
#include "../include/UnitTest++AddIns/MyPerformanceReporter.h"
#include <PLCore/PLCore.h>	// For "nullptr" in case the compiler doesn't support this C++11 feature


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
std::ofstream outputFile;


//[-------------------------------------------------------]
//[ Unit tests program entry point                        ]
//[-------------------------------------------------------]
int UnitTestsPerformance()
{
	// Get the current time as ASCII string
	char szTime[9];
	#ifdef WIN32
		_strtime(szTime);
		// replace ':' (not valid within filenames) by '-'
		szTime[2] = szTime[5] = '-';
	#else
		struct tm sTime;
		struct timeval sNow;
		gettimeofday(&sNow, nullptr);
		localtime_r(&sNow.tv_sec, &sTime);
		sprintf(szTime, "%2d_%2d_%2d", sTime.tm_hour, sTime.tm_min, sTime.tm_sec);
	#endif

	// Open the results output file
	char szFilename[256];
	sprintf(szFilename, "PLUnitTestsPerformance_Result_%s.csv", szTime);
	outputFile.open(szFilename);

	// Create an reporter instance
	MyPerformanceReporter cReporter;

	// Run all unit tests
	const int nResult = UnitTest::RunAllTests(cReporter);

	// Close the results output file
	outputFile.close();

	system("Pause");
	// Done
	return nResult;
}
