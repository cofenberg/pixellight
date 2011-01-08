/*********************************************************\
 *  File: QuickSortTest.cpp                              *
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
#include <PLGeneral/Tools/QuickSort.h>
#include "PLTestBase/General/QuickSortTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    QuickSort test class
*/
class QuickSortTestClass : public QuickSort {


	//[-------------------------------------------------------]
	//[ Private virtual private PLGeneral::QuickSort functions]
	//[-------------------------------------------------------]
	private:
		virtual char Compare(void *pElement1, void *pElement2) const
		{
			if (*((int*)pElement1)  < *((int*)pElement2)) return -1;
			if (*((int*)pElement1) == *((int*)pElement2)) return  0;
			else										  return  1;
		};


};


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *QuickSortTest::GetName() const
{
	return "QuickSort";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void QuickSortTest::Test()
{
	// Create
	QuickSortTestClass cQuickSort;
	int nTest[10];

	// Fill
	nTest[0] = 45;
	nTest[1] = 3465;
	nTest[2] = 25;
	nTest[3] = 25;
	nTest[4] = 47;
	nTest[5] = 0;
	nTest[6] = -630;
	nTest[7] = 7;
	nTest[8] = -99;
	nTest[9] = 9;

	// Sort
	StartTask("Sort");
	cQuickSort.Sort(nTest, 10, sizeof(int));
	EndTask(nTest[0] == -630 && nTest[1] == -99 && nTest[2] == 0 &&
			nTest[3] == 7 && nTest[4] == 9 && nTest[5] == 25 &&
			nTest[6] == 25 && nTest[7] == 45 && nTest[8] == 47 && nTest[9] == 3465);
}
