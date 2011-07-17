/*********************************************************\
 *  File: HeapTestCase.cpp                               *
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
#include <PLGeneral/Container/Heap.h>
#include <PLGeneral/Container/List.h>
#include "PLTestBase/General/HeapTestCase.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tests a heap implementation
*/
bool HeapTestCase::Test(Heap<int, String> &cHeap)
{
	bool bResult;

	// Heap must be empty
	StartTask("IsEmpty()");
	EndTask(cHeap.IsEmpty());

	// Add some elements
	StartTask("Add()");
	EndTask(cHeap.Add(5, "Fifth") && cHeap.Add(2, "Second") && cHeap.Add(1, "First") &&
			cHeap.Add(4, "Fourth") && cHeap.Add(3, "Third") && !cHeap.IsEmpty() && cHeap.GetNumOfElements() == 5);

	List<String> lstElements; // Backup of the elements to check whether 0 -> (NumOfElements-1)
							  // has the same order as (NumOfElements-1) -> 0

	{ // Check iterator from 0 -> (NumOfElements-1)
		StartTask("Iterator order from 0 -> (NumOfElements-1)");
		Iterator<String> cIterator = cHeap.GetIterator();
		bResult = true;

		// There should be no previous element...
		if (cIterator.HasPrevious()) bResult = false;

		// We do NOT know the order of the other elements...
		bool bFirst = false, bSecond = false, bThird = false, bFourth = false, bFifth = false;
		while (cIterator.HasNext()) {
			String sString = ++cIterator;
			lstElements.Add(sString);
			if (sString == "First") {
				if (bFirst) bResult = false;
				else		bFirst = true;
			} else if (sString == "Second") {
				if (bSecond) bResult = false;
				else		 bSecond = true;
			} else if (sString == "Third") {
				if (bThird) bResult = false;
				else		bThird  = true;
			} else if (sString == "Fourth") {
				if (bFourth) bResult = false;
				else		 bFourth = true;
			} else if (sString == "Fifth") {
				if (bFifth) bResult = false;
				else		bFifth = true;
			} else bResult = false;
		}
		if (lstElements.GetNumOfElements() != 5 || !bFirst || !bSecond || !bThird || !bFourth || !bFifth) bResult = false;

		// There should be a previous element...
		if (!cIterator.HasPrevious()) bResult = false;

		EndTask(bResult);
	}

	{ // Check iterator from (NumOfElements-1) -> 0
		StartTask("Iterator order from (NumOfElements-1) -> 0");
		Iterator<String> cIterator = cHeap.GetEndIterator();
		bResult = true;

		// There should be no next element...
		if (cIterator.HasNext()) bResult = false;

		int nNumOfElements = 0;
		while (cIterator.HasPrevious()) {
			// Get value
			String sValue = cIterator.Previous();

			// Check element order
			if (lstElements[lstElements.GetNumOfElements()-nNumOfElements-1] != sValue) bResult = false;

			// Increase the number of elements
			nNumOfElements++;
		}
		if (nNumOfElements != static_cast<int>(lstElements.GetNumOfElements())) bResult = false;

		// There should a next element...
		if (!cIterator.HasNext()) bResult = false;

		EndTask(bResult);
	}

	// ExtractTop() and check order
	StartTask("ExtractTop() and check order");
	String sTemp;
	int nTemp;
	bResult = true;
	// Extract 'First/1'
	cHeap.ExtractTop(&sTemp, &nTemp);
	if (sTemp != "First" || nTemp != 1) bResult = false;
	// Extract 'Second/2'
	cHeap.ExtractTop(&sTemp, &nTemp);
	if (sTemp != "Second" || nTemp != 2) bResult = false;
	// Extract 'Third/3'
	cHeap.ExtractTop(&sTemp, &nTemp);
	if (sTemp != "Third" || nTemp != 3) bResult = false;
	// Extract 'Fourth/4'
	cHeap.ExtractTop(&sTemp, &nTemp);
	if (sTemp != "Fourth" || nTemp != 4) bResult = false;
	// Extract 'Fifth/5'
	cHeap.ExtractTop(&sTemp, &nTemp);
	if (sTemp != "Fifth" || nTemp != 5) bResult = false;
	// End task
	EndTask(bResult && cHeap.IsEmpty() && !cHeap.GetNumOfElements() &&
			!cHeap.GetTop() && !cHeap.ExtractTop());

	// Clear the heap
	StartTask("Clear()");
	// Add some elements...
	cHeap.Add(5, "Fifth");
	cHeap.Add(2, "Second");
	cHeap.Add(1, "First");
	// ... and clear the heap
	cHeap.Clear();
	EndTask(cHeap.IsEmpty() && !cHeap.GetNumOfElements());

	{ // Check GetIterator() if there are NO elements within the heap
		StartTask("Check GetIterator() if there are NO elements within the heap");
		Iterator<String> cIterator = cHeap.GetIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndIterator() if there are NO elements within the heap
		StartTask("Check GetEndIterator() if there are NO elements within the heap");
		Iterator<String> cIterator = cHeap.GetEndIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Add one element to the heap
	cHeap.Add(1, "First");

	{ // Check GetIterator() if there is only ONE element within the heap
		StartTask("Check GetIterator() if there is only ONE element within the heap");
		Iterator<String> cIterator = cHeap.GetIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (!cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndIterator() if there is only ONE element within the heap
		StartTask("Check GetEndIterator() if there is only ONE element within the heap");
		Iterator<String> cIterator = cHeap.GetEndIterator();
		bResult = true;
		if (!cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Done
	return true;
}
