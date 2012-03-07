/*********************************************************\
 *  File: SimpleMapTest.cpp                              *
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
#include <PLCore/Container/SimpleMap.h>
#include "PLTestBase/General/SimpleMapTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *SimpleMapTest::GetName() const
{
	return "Simple map";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void SimpleMapTest::Test()
{
	bool bResult;

	{ // Perform general tests
		SimpleMap<String, int> mapSimpleMap;
		bResult = MapTestCase::Test(SimpleMap<String, int>::Null, mapSimpleMap);
	}

	// Test hash map
	SimpleMap<String, int> mapHashMap;
	mapHashMap.Add("One",   1);
	mapHashMap.Add("Two",   2);
	mapHashMap.Add("Three", 3);

	// Copy constructor
	StartTask("Copy constructor");
	bResult = true;
	SimpleMap<String, int> mapHashMapCopy = mapHashMap;
	if (mapHashMapCopy.Get("One")   != 1)
		bResult = false;
	if (mapHashMapCopy.Get("Two")   != 2)
		bResult = false;
	if (mapHashMapCopy.Get("Three") != 3)
		bResult = false;
	EndTask(bResult && mapHashMapCopy.GetNumOfElements() == 3);

	// Copy operator
	StartTask("Copy operator");
	bResult = true;
	mapHashMapCopy.Clear();
	mapHashMapCopy = mapHashMap;
	if (mapHashMapCopy.Get("One")   != 1)
		bResult = false;
	if (mapHashMapCopy.Get("Two")   != 2)
		bResult = false;
	if (mapHashMapCopy.Get("Three") != 3)
		bResult = false;
	EndTask(bResult && mapHashMapCopy.GetNumOfElements() == 3);
}
