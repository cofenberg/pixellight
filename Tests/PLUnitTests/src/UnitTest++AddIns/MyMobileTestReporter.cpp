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

#include <PLCore/System/System.h>
#include <PLCore/System/Console.h>
#include <PLCore/String/String.h>
#include "UnitTest++AddIns/MyMobileTestReporter.h"

using namespace PLCore;

void MyMobileTestReporter::ReportTestStart(UnitTest::TestDetails const& test)
{
}
void MyMobileTestReporter::ReportFailure(UnitTest::TestDetails const& test, char const* failure)
{
	System::GetInstance()->GetConsole().Print(String("*!Failed: ") + test.suiteName + "/" + test.testName + " at line " + test.lineNumber + "\n\t*!Msg   : " + failure + "\n\n");
}
void MyMobileTestReporter::ReportTestFinish(UnitTest::TestDetails const& test, float secondsElapsed)
{
}
void MyMobileTestReporter::ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed)
{
	if (failureCount > 0)
		System::GetInstance()->GetConsole().Print(String("FAILURE: ") + failedTestCount + " out of " + totalTestCount + " tests failed (" + failureCount + " failures).\n");
	else
		System::GetInstance()->GetConsole().Print(String("Success: ") + totalTestCount + " tests passed.\n"); 

	System::GetInstance()->GetConsole().Print(String("Test time: ") + secondsElapsed + " seconds.\n\n"); 
}
