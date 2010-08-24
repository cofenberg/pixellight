/*********************************************************\
 *  File: PerformanceTest.cpp                            *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <stdlib.h> // For 'rand()'
#include <PLGeneral/System/System.h>
#include <PLGeneral/Tools/Stopwatch.h>
#include <PLGeneral/Container/Array.h>
#include <PLGeneral/Container/HashMap.h>
#include "PLTestBase/General/PerformanceTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *PerformanceTest::GetName() const
{
	return "Performance";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void PerformanceTest::Test()
{
	Array<String> lstStrings;
	Stopwatch cStopwatch;
	String *pString;

// Array
	{
		String sDummy = "Dummy";
		cStopwatch.Start();
		for (int i=0; i<20000; i++)
			lstStrings.Add(sDummy);
		cStopwatch.Stop();
		Print("Array: Add 20000 elements with 0 initial slots and resize count 10: %d microseconds\n", cStopwatch.GetMicroseconds());
	}
	{
		cStopwatch.Start();
		lstStrings.Clear();
		cStopwatch.Stop();
		Print("Array: Clear (with 20000 elements): %d microseconds\n", cStopwatch.GetMicroseconds());
	}
	{
		String sDummy = "Dummy";
		cStopwatch.Start();
		lstStrings.SetResizeCount(1000);
		for (int i=0; i<20000; i++)
			lstStrings.Add(sDummy);
		cStopwatch.Stop();
		Print("Array: Add 20000 elements with 0 initial slots and resize count 1000: %d microseconds\n", cStopwatch.GetMicroseconds());
		lstStrings.Clear();
	}
	{
		String sDummy = "Dummy";
		cStopwatch.Start();
		lstStrings.Resize(20000, false);
		for (int i=0; i<20000; i++)
			lstStrings.Add(sDummy);
		cStopwatch.Stop();
		Print("Array: Add 20000 elements with 20000 initial slots: %d microseconds\n", cStopwatch.GetMicroseconds());
		lstStrings.Clear();
	}
	{
		cStopwatch.Start();
		lstStrings.Resize(20000, false);
		for (int i=0; i<20000; i++)
			lstStrings.Add(String::Format("%d_%d", i, rand() % 10000000));
		cStopwatch.Stop();
		Print("Array & String: Add 20000 random strings with 20000 initial slots: %d microseconds\n", cStopwatch.GetMicroseconds());
	}

// HashMap (is using lstStrings from above)
	{
		// Add
		cStopwatch.Start();
		HashMap<String, String*> mapStrings;
		for (int i=0; i<20000; i++) {
			pString = &lstStrings[i];
			mapStrings.Add(*pString, pString);
		}
		cStopwatch.Stop();
		Print("HashMap: Add 20000 elements with 199 initial slots: %d microseconds\n", cStopwatch.GetMicroseconds());

		{ // Clear
			cStopwatch.Start();
			mapStrings.Clear();
			cStopwatch.Stop();
			Print("HashMap: Clear (20000 elements): %d microseconds\n", cStopwatch.GetMicroseconds());
		}
	}
	{
		cStopwatch.Start();
		HashMap<String, String*> mapStrings(30000);
		for (int i=0; i<20000; i++) {
			pString = &lstStrings[i];
			mapStrings.Add(*pString, pString);
		}
		cStopwatch.Stop();
		Print("HashMap: Add 20000 elements with 30000 initial slots: %d microseconds\n", cStopwatch.GetMicroseconds());

		{ // Get
			cStopwatch.Start();
			for (int i=0; i<20000; i++)
				mapStrings.Get(lstStrings[i]);
			cStopwatch.Stop();
			Print("HashMap: Get (20000 elements): %d microseconds\n", cStopwatch.GetMicroseconds());
		}
	}
}
