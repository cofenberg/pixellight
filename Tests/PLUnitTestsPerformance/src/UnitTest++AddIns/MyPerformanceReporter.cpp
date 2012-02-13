/*********************************************************\
 *  File: MyTestReporter.cpp                                 *
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
#include <iostream>
#include <fstream>
#include "PLCore/Container/HashMap.h"
#include "UnitTest++AddIns/MyPerformanceReporter.h"
#include "PLCore/Tools/Stopwatch.h"

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace std;
using namespace PLCore;

//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
extern ofstream outputFile;
string lastsuitename;
Stopwatch Counter;

void MyPerformanceReporter::ReportTestStart(UnitTest::TestDetails const& test)
{
	Counter.Start();
}
void MyPerformanceReporter::ReportFailure(UnitTest::TestDetails const& test, char const* failure)
{
	printf("*!Failed: %s/%s at line %d\n\t*!Msg   : %s\n\n", test.suiteName, test.testName, test.lineNumber, failure);
}
void MyPerformanceReporter::ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed)
{
	Counter.Stop();

	if (lastsuitename != test.suiteName){
		outputFile << endl << endl << test.suiteName <<endl;
		lastsuitename = test.suiteName;
	}
	outputFile << test.testName << ";" << (secondsElapsed*1000) << "ms" << endl;
	
}
void MyPerformanceReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
{
	outputFile << endl;
	if (failureCount > 0)
		outputFile << "FAILURE: " << failedTestCount << " out of " << totalTestCount << " tests failed ("<< failureCount <<" failures).\n";
	else
		outputFile << "Success: "<< totalTestCount <<" tests passed.\n";

	outputFile << "Test time: "<< secondsElapsed <<" seconds.\n\n";
}
