/*********************************************************\
 *  File: BitsetTest.cpp                                 *
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
#include <PLCore/Container/Bitset.h>
#include <PLCore/Container/BitsetIterator.h>
#include "PLTestBase/General/BitsetTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *BitsetTest::GetName() const
{
	return "Bitset";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void BitsetTest::Test()
{
	bool bResult;

	{ // Perform general tests
		Bitset lstBitset;
		bResult = ContainerTestCase<bool>::Test(lstBitset);
	}

	{ // GetNumOfSetBits()
		Bitset cBitset(3, true, true);
		cBitset.Set(1);
		StartTask("GetNumOfSetBits()");
		EndTask(cBitset.GetNumOfSetBits() == 1);
	}

	// Resize()
	StartTask("Resize()");
	bResult = true;
	Bitset cBitset(1000, true, true);
	for (uint32 i=0; i<1000; i++) {
		if (cBitset.IsSet(i)) {
			bResult = false;
			break;
		}
	}
	cBitset.Clear();
	cBitset.Resize(1000, true);
	cBitset.Resize(1500, true, true);
	// We start at 1000 to check because the other bits are not initialized :)
	for (uint32 i=1000; i<1500; i++) {
		if (cBitset.IsSet(i)) {
			bResult = false;
			break;
		}
	}
	cBitset.Clear();
	cBitset.Resize(2, false, false);
	if (cBitset.GetMaxNumOfElements() != 2 || cBitset.GetNumOfElements() != 0) bResult = false;
	cBitset.Resize(2, true, false);
	if (cBitset.GetMaxNumOfElements() != 2 || cBitset.GetNumOfElements() != 2) bResult = false;
	cBitset.RemoveAtIndex(1);
	cBitset.Resize(2, true, true);
	if (cBitset.GetMaxNumOfElements() != 2 || cBitset.GetNumOfElements() != 2 ||
		cBitset[1] != 0) bResult = false;
	cBitset.Resize(0);
	if (cBitset.GetMaxNumOfElements() != 0 || cBitset.GetNumOfElements() != 0) bResult = false;
	EndTask(bResult);
}
