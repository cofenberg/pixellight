/*********************************************************\
 *  File: MyTestReporter.cpp                                 *
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

#include <cstdio>
#include "UnitTest++AddIns/MyTestReporter.h"


void MyTestReporter::ReportTestStart(UnitTest::TestDetails const& test)
{
}
void MyTestReporter::ReportFailure(UnitTest::TestDetails const& test, char const* failure)
{
	printf("*!Failed: %s/%s at line %d\n\t*!Msg   : %s\n\n", test.suiteName, test.testName, test.lineNumber, failure);
}
void MyTestReporter::ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed)
{
}
void MyTestReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
{
	if (failureCount > 0)
		printf("FAILURE: %d out of %d tests failed (%d failures).\n", failedTestCount, totalTestCount, failureCount);
	else
		printf("Success: %d tests passed.\n", totalTestCount);

	printf("Test time: %.4f seconds.\n\n", secondsElapsed);
}
