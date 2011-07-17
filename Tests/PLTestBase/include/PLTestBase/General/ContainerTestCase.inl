/*********************************************************\
 *  File: ContainerTestCase.inl                          *
 *       Container test case inline implementation
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
#include <PLGeneral/Container/Container.h>
#include "PLTestBase/General/ContainerTestCase.h"


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Tests a container implementation
*/
template <class AType>
bool ContainerTestCase<AType>::Test(PLGeneral::Container<AType> &cContainer)
{
	bool bResult;

	// Container must be empty
	StartTask("IsEmpty()");
	EndTask(cContainer.IsEmpty());

	// Add
	StartTask("Add() & Clear()");
	bResult = true;
	cContainer.Add(0);
	if (cContainer.GetNumOfElements() != 1 || cContainer[0] != 0) bResult = true;
	cContainer.Clear();
	if (cContainer.GetNumOfElements()) bResult = true;
	cContainer.Add(1);
	if (cContainer.GetNumOfElements() != 1 || cContainer[0] != 1) bResult = true;
	cContainer.Clear();
	EndTask(bResult);

	// Add some elements
	StartTask("+=");
	cContainer += 1;
	cContainer += 0;
	cContainer += 1;
	EndTask(cContainer.GetNumOfElements() == 3 && cContainer[0] == 1 &&
			cContainer[1] == 0 && cContainer[2] == 1);

	// Add element at index 2
	StartTask("AddAtIndex()");
	EndTask(cContainer.AddAtIndex(0, 2) && cContainer.GetNumOfElements() == 4 && cContainer[0] == 1 &&
			cContainer[1] == 0 && cContainer[2] == 0 && cContainer[3] == 1);

	{ // Check iterator from 0 -> (NumOfElements-1)
		StartTask("Iterator from 0 -> (NumOfElements-1)");
		PLGeneral::Iterator<AType> cIterator = cContainer.GetIterator();
		bResult = true;

		// There should be no previous element...
		if (cIterator.HasPrevious()) bResult = false;

		if (!cIterator.HasNext()) bResult = false;
		else {
			if (++cIterator != 1) bResult = false;
		}
		if (!cIterator.HasNext()) bResult = false;
		else {
			if (++cIterator != 0) bResult = false;
		}
		if (!cIterator.HasNext()) bResult = false;
		else {
			if (++cIterator != 0) bResult = false;
		}
		if (!cIterator.HasNext()) bResult = false;
		else {
			if (++cIterator != 1) bResult = false;
		}

		// There should be a previous element...
		if (!cIterator.HasPrevious()) bResult = false;
		EndTask(bResult);
	}

	{ // Check iterator from (NumOfElements-1) -> 0
		StartTask("Iterator from (NumOfElements-1) -> 0");
		PLGeneral::Iterator<AType> cIterator = cContainer.GetEndIterator();
		bResult = true;

		// There should be no next element...
		if (cIterator.HasNext()) bResult = false;

		if (!cIterator.HasPrevious()) bResult = false;
		else {
			if (--cIterator != 1) bResult = false;
		}
		if (!cIterator.HasPrevious()) bResult = false;
		else {
			if (--cIterator != 0) bResult = false;
		}
		if (!cIterator.HasPrevious()) bResult = false;
		else {
			if (--cIterator != 0) bResult = false;
		}
		if (!cIterator.HasPrevious()) bResult = false;
		else {
			if (--cIterator != 1) bResult = false;
		}

		// There should be a next element...
		if (!cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Remove element
	StartTask("RemoveAtIndex()");
	EndTask(cContainer.RemoveAtIndex(0) && cContainer.GetNumOfElements() == 3 && cContainer[0] == 0 && 
			cContainer[1] == 0 && cContainer[2] == 1);

	// Clear the container
	cContainer.Clear();

	{ // Check GetIterator() if there are NO elements within the container
		StartTask("Check GetIterator() if there are NO elements within the container");
		PLGeneral::Iterator<AType> cIterator = cContainer.GetIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndIterator() if there are NO elements within the container
		StartTask("Check GetEndIterator() if there are NO elements within the container");
		PLGeneral::Iterator<AType> cIterator = cContainer.GetEndIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Add one element to the container
	cContainer += 1;

	{ // Check GetIterator() if there is only ONE element within the container
		StartTask("Check GetIterator() if there is only ONE element within the container");
		PLGeneral::Iterator<AType> cIterator = cContainer.GetIterator();
		bResult = true;
		if (cIterator.HasPrevious()) bResult = false;
		if (!cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	{ // Check GetEndIterator() if there is only ONE element within the container
		StartTask("Check GetEndIterator() if there is only ONE element within the container");
		PLGeneral::Iterator<AType> cIterator = cContainer.GetEndIterator();
		bResult = true;
		if (!cIterator.HasPrevious()) bResult = false;
		if (cIterator.HasNext()) bResult = false;
		EndTask(bResult);
	}

	// Add(const AType Elements[], uint32 nCount)
	bResult = true;
	cContainer.Clear();
	AType bBuffer[] = {0, 1, 0};
	StartTask("Add(const AType Elements[], uint32 nCount)");
	if (cContainer.Add(bBuffer, 3) != 3 || cContainer[0] != 0 || cContainer[1] != 1 || cContainer[2] != 0)
		bResult = false;
	if (cContainer.Add(bBuffer, 2) != 2 || cContainer[3] != 0 || cContainer[4] != 1)
		bResult = false;
	EndTask(bResult);

	// Done
	return true;
}
