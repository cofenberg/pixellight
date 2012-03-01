/*********************************************************\
*  File: PLChecks.cpp
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

#include "UnitTest++AddIns/PLChecks.h"

namespace UnitTest {
	void CheckMatrix3x3(TestResults& results, PLMath::Matrix3x3 const& expected, PLMath::Matrix3x3 const& actual, float const& tolerance,
		TestDetails const& details) {

			bool bFailed = false;
			UnitTest::MemoryOutStream stream;
			stream << std::endl;

			for (int row=0; row<3; row++) {
				for (int col=0; col<3; col++){
					if (fabs(expected(row,col)-actual(row,col))>tolerance){
						// CHECK failed here! prepare error-message
						stream << "\t\tMatrix3x3(row/col): " << row << "/" << col << " Expected: " << expected(row,col) << " +/- " << tolerance << " but was " << actual(row,col) << std::endl;

						if (!bFailed)
							bFailed = true;
					}
				}
			}

			if (bFailed)
				results.OnTestFailure(details, stream.GetText());
	}

	void CheckMissingImplementation(TestResults& results, TestDetails const& details) {
		UnitTest::MemoryOutStream stream;

		// missing implementation message
		stream << "Implement this test!";

		results.OnTestFailure(details, stream.GetText());
	}

	void CheckStringsNotEqual(TestResults& results, char const* expected, char const* actual,
		TestDetails const& details)
	{
		using namespace std;

		if (!strcmp(expected, actual))
		{
			UnitTest::MemoryOutStream stream;
			stream << "Expected not equal: expected " << expected << " == " << actual;

			results.OnTestFailure(details, stream.GetText());
		}
	}


	void CheckNotEqual(TestResults& results, char const* expected, char const* actual,
		TestDetails const& details)
	{
		CheckStringsNotEqual(results, expected, actual, details);
	}

	void CheckNotEqual(TestResults& results, char* expected, char* actual,
		TestDetails const& details)
	{
		CheckStringsNotEqual(results, expected, actual, details);
	}

	void CheckNotEqual(TestResults& results, char* expected, char const* actual,
		TestDetails const& details)
	{
		CheckStringsNotEqual(results, expected, actual, details);
	}

	void CheckNotEqual(TestResults& results, char const* expected, char* actual,
		TestDetails const& details)
	{
		CheckStringsNotEqual(results, expected, actual, details);
	}
}