/*********************************************************\
 *  File: ArrayTest.cpp                                  *
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
#include <PLCore/Container/Array.h>
#include "PLTestBase/General/ArrayTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ArrayTest::GetName() const
{
	return "Array";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ArrayTest::Test()
{
	bool bResult;

	{ // Perform general tests
		Array<bool> lstArray;
		bResult = ContainerTestCase<bool>::Test(lstArray);
	}

	// Resize()
	bResult = true;
	Array<char> lstArray;
	StartTask("Resize()");
	lstArray.Resize(2, false, false);
	if (lstArray.GetMaxNumOfElements() != 2 || lstArray.GetNumOfElements() != 0) bResult = false;
	lstArray.Resize(2, true, false);
	if (lstArray.GetMaxNumOfElements() != 2 || lstArray.GetNumOfElements() != 2) bResult = false;
	lstArray.RemoveAtIndex(1);
	lstArray.Resize(2, true, true);
	if (lstArray.GetMaxNumOfElements() != 2 || lstArray.GetNumOfElements() != 2 ||
		lstArray[1] != 0) bResult = false;
	lstArray.Resize(0);
	if (lstArray.GetMaxNumOfElements() != 0 || lstArray.GetNumOfElements() != 0) bResult = false;
	EndTask(bResult);

	// Add(const AType Elements[], uint32 nCount) -> NOT the same test as in ContainerTestCase :)
	bResult = true;
	char szBuffer[] = { 'a', 'b', 'c' };
	StartTask("Add(const AType Elements[], uint32 nCount)");
	// Allow resize
	if (lstArray.Add(szBuffer, 3) != 3 || !lstArray[0] || lstArray[0] != 'a' ||
		!lstArray[1] || lstArray[1] != 'b' || !lstArray[2] || lstArray[2] != 'c')
		bResult = false;
	if (lstArray.Add(szBuffer, 2) != 2 || !lstArray[3] || lstArray[3] != 'a' ||
		!lstArray[4] || lstArray[4] != 'b')
		bResult = false;
	// Do NOT allow resize
	lstArray.Clear();
	lstArray.SetResizeCount(0);
	lstArray.Resize(2, false);
	if (lstArray.Add(szBuffer, 3) != 2 || !lstArray[0] || lstArray[0] != 'a' ||
		!lstArray[1] || lstArray[1] != 'b')
		bResult = false;
	EndTask(bResult);
}
