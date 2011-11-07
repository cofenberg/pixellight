/*********************************************************\
 *  File: wchar_template.cpp                                *
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
#include "UnitTest++AddIns/wchar_template.h"

namespace UnitTest {
	void CheckWcharEqual(TestResults& results, wchar_t const* expected, wchar_t const* actual, 
		TestDetails const& details){
			using namespace std;

			if (wcscmp(expected, actual))
			{
				UnitTest::MemoryOutStream stream;
				stream << "Expected wchar_t: " << expected << " but was wchar_t: " << actual;

				results.OnTestFailure(details, stream.GetText());
			}
	}

	void CheckEqual(TestResults& results, wchar_t const* expected, wchar_t const* actual, TestDetails const& details){
		CheckWcharEqual(results, expected, actual, details);
	}

	void CheckEqual(TestResults& results, wchar_t* expected, wchar_t* actual, TestDetails const& details){
		CheckWcharEqual(results, expected, actual, details);
	}

	void CheckEqual(TestResults& results, wchar_t* expected, wchar_t const* actual, TestDetails const& details){
		CheckWcharEqual(results, expected, actual, details);
	}

	void CheckEqual(TestResults& results, wchar_t const* expected, wchar_t* actual, TestDetails const& details){
		CheckWcharEqual(results, expected, actual, details);
	}
}