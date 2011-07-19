/*********************************************************\
 *  File: MapTestCase.cpp                                *
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
#include <PLCore/Container/Map.h>
#include <PLCore/Container/List.h>
#include "PLTestBase/General/MapTestCase.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tests a map implementation
*/
bool MapTestCase::Test(Map<String, int> &cMap)
{
	bool bResult;

	// Map must be empty
	StartTask("IsEmpty()");
	EndTask(cMap.IsEmpty());

	// Add some elements
	StartTask("Add()");
	EndTask(cMap.Add("One", 1) && cMap.Add("Two", 2) && cMap.Add("Three", 3) &&
			!cMap.IsEmpty() && cMap.GetNumOfElements() == 3);

	// Get elements
	StartTask("Get()");
	EndTask( cMap.Get("One")   == 1 &&
			 cMap.Get("Two")   == 2 &&
			 cMap.Get("Three") == 3 &&
			&cMap.Get("Four")  == &Map<String, int>::Null);

	// Iterator
	List<int> lstValues; // Backup of the values to check whether 0 -> (NumOfElements-1)
						 // has the same order as (NumOfElements-1) -> 0
	List<String> lstKeys;	 // Backup of the keys to check whether 0 -> (NumOfElements-1)
							 // has the same order as (NumOfElements-1) -> 0

	{ // Check iterator from 0 -> (NumOfElements-1)
		StartTask("Iterator from 0 -> (NumOfElements-1)");
		Iterator<int> cIterator = cMap.GetIterator();
		bResult = true;

		// There should be no previous element...
		if (cIterator.HasPrevious()) bResult = false;

		bool bOne = false, bTwo = false, bThree = false;
		while (cIterator.HasNext()) {
			int nValue = cIterator.Next();
			lstValues.Add(nValue);
			switch (nValue) {
				case 1:
					if (bOne) bResult = false; // ?!!
					else	  bOne = true;
					break;

				case 2:
					if (bTwo) bResult = false; // ?!!
					else	  bTwo = true;
					break;

				case 3:
					if (bThree)	bResult = false; // ?!!
					else		bThree = true;
					break;

				default:
					bResult = false; // ?!!
					break;
			}
		}
		if (lstValues.GetNumOfElements() != 3 || !bOne || !bTwo || !bThree) bResult = false;

		// There should be a previous element...
		if (!cIterator.HasPrevious()) bResult = false;

		EndTask(bResult);
	}

	{ // Check key iterator from 0 -> (NumOfElements-1)
		StartTask("Key iterator from 0 -> (NumOfElements-1)");
		Iterator<String> cIterator = cMap.GetKeyIterator();
		bResult = true;

		// There should be no previous element...
		if (cIterator.HasPrevious()) bResult = false;

		bool bOne = false, bTwo = false, bThree = false;
		while (cIterator.HasNext()) {
			const String sValue = cIterator.Next();
			lstKeys.Add(sValue);
			if (sValue == "One") {
				if (bOne) bResult = false; // ?!!
				else	  bOne = true;
			} else if (sValue == "Two") {
				if (bTwo) bResult = false; // ?!!
				else	  bTwo = true;
			} else if (sValue == "Three") {
				if (bThree)	bResult = false; // ?!!
				else		bThree = true;
			} else {
				bResult = false; // ?!!
			}
		}
		if (lstKeys.GetNumOfElements() != 3 || !bOne || !bTwo || !bThree) bResult = false;

		// There should be a previous element...
		if (!cIterator.HasPrevious()) bResult = false;

		EndTask(bResult);
	}

	{ // Check iterator from (NumOfElements-1) -> 0
		StartTask("Iterator from (NumOfElements-1) -> 0");
		Iterator<int> cIterator = cMap.GetEndIterator();
		bResult = true;

		// There should be no next element...
		if (cIterator.HasNext()) bResult = false;

		int nNumOfElements = 0;
		while (cIterator.HasPrevious()) {
			// Get value
			int nValue = cIterator.Previous();

			// Check element order
			if (lstValues[lstValues.GetNumOfElements()-nNumOfElements-1] != nValue) bResult = false;

			// Increase the number of elements
			nNumOfElements++;
		}
		if (nNumOfElements != static_cast<int>(lstValues.GetNumOfElements())) bResult = false;

		// There should be a next element...
		if (!cIterator.HasNext()) bResult = false;

		EndTask(bResult);
	}

	{ // Check key iterator from (NumOfElements-1) -> 0
		StartTask("Key iterator from (NumOfElements-1) -> 0");
		Iterator<String> cIterator = cMap.GetEndKeyIterator();
		bResult = true;

		// There should be no next element...
		if (cIterator.HasNext()) bResult = false;

		int nNumOfElements = 0;
		while (cIterator.HasPrevious()) {
			// Get value
			String sValue = cIterator.Previous();

			// Check element order
			if (lstKeys[lstKeys.GetNumOfElements()-nNumOfElements-1] != sValue) bResult = false;

			// Increase the number of elements
			nNumOfElements++;
		}
		if (nNumOfElements != static_cast<int>(lstKeys.GetNumOfElements())) bResult = false;

		// There should be a next element...
		if (!cIterator.HasNext()) bResult = false;

		EndTask(bResult);
	}

	// Replace
	StartTask("Replace()");
	EndTask(cMap.Replace("Three", 4) && cMap.GetNumOfElements() == 3 && cMap.Get("Three") == 4);

	// Set
	bResult = true;
	StartTask("Set()");
	// 'Add'
	if (cMap.Set("Five", 5) != false) bResult = false;
	// 'Replace'
	if (cMap.Set("Three", 3) != true) bResult = false;
	EndTask(bResult && cMap.GetNumOfElements() == 4 && cMap.Get("Three") == 3);

	// Remove
	StartTask("Remove()");
	EndTask(cMap.Remove("Two") && cMap.GetNumOfElements() == 3 && !cMap.Get("Two"));

	// Clear the map
	StartTask("Clear()");
	cMap.Clear();
	EndTask(cMap.IsEmpty() && !cMap.GetNumOfElements());

	{ // Check GetIterator() if there are NO elements within the map
		StartTask("Check GetIterator() if there are NO elements within the map");
		Iterator<int> cIterator = cMap.GetIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetKeyIterator() if there are NO elements within the map
		StartTask("Check GetKeyIterator() if there are NO elements within the map");
		Iterator<String> cIterator = cMap.GetKeyIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndIterator() if there are NO elements within the map
		StartTask("Check GetEndIterator() if there are NO elements within the map");
		Iterator<int> cIterator = cMap.GetEndIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndKeyIterator() if there are NO elements within the map
		StartTask("Check GetEndKeyIterator() if there are NO elements within the map");
		Iterator<String> cIterator = cMap.GetEndKeyIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Add one element to the map
	cMap.Add("One", 1);

	{ // Check GetIterator() if there is only ONE element within the map
		StartTask("Check GetIterator() if there is only ONE element within the map");
		Iterator<int> cIterator = cMap.GetIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (!cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetKeyIterator() if there is only ONE element within the map
		StartTask("Check GetKeyIterator() if there is only ONE element within the map");
		Iterator<String> cIterator = cMap.GetKeyIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (!cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndIterator() if there is only ONE element within the map
		StartTask("Check GetEndIterator() if there is only ONE element within the map");
		Iterator<int> cIterator = cMap.GetEndIterator();
		bResult = true;
		if (!cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndKeyIterator() if there is only ONE element within the map
		StartTask("Check GetEndKeyIterator() if there is only ONE element within the map");
		Iterator<String> cIterator = cMap.GetEndKeyIterator();
		bResult = true;
		if (!cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Done
	return true;
}
