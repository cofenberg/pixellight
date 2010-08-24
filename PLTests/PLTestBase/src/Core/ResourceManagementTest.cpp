/*********************************************************\
 *  File: ResourceManagementTest.cpp                     *
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
#include <PLGeneral/Base/RefCount.h>
#include <PLGeneral/Base/SmartPtr.h>
#include "PLTestBase/Core/ResourceManagementTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
class TestClass : public RefCount<TestClass> {
	public:
		TestClass() : i(0) {}
		int i;
};


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *ResourceManagementTest::GetName() const
{
	return "ResourceManagement";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void ResourceManagementTest::Test()
{
// RefCount tests
	bool bResult = true;
	StartTask("RefCount tests");
	TestClass *pTest = new TestClass();
	if (pTest->GetPointer() != pTest || pTest->GetRefCount()) bResult = false;
	if (pTest->Release()) bResult = false;
	pTest = new TestClass();
	if (pTest->AddReference() != 1 || pTest->GetRefCount() != 1) bResult = false;
	if (pTest->AddReference() != 2 || pTest->GetRefCount() != 2) bResult = false;
	if (pTest->Release() != 1 || pTest->GetRefCount() != 1) bResult = false;
	if (pTest->Release()) bResult = false;
	EndTask(bResult);

// SmartPtr tests
	StartTask("SmartPtr basic tests");
	SmartPtr<TestClass> cPtr, cPtr2;
	EndTask(!cPtr.GetPointer() && !cPtr && cPtr == cPtr2 && !(cPtr != cPtr2));

	// RefCount pointer
	bResult = true;
	StartTask("SmartPtr with RefCount pointer");
	cPtr = new TestClass();
	if (!cPtr.GetPointer() || !cPtr || cPtr == cPtr2 || !(cPtr != cPtr2) ||
		cPtr.GetPointer()->GetRefCount() != 1) bResult = false;
	cPtr = cPtr;
	if (!cPtr.GetPointer() || !cPtr || cPtr == cPtr2 || !(cPtr != cPtr2) ||
		cPtr.GetPointer()->GetRefCount() != 1) bResult = false;
	cPtr2 = cPtr2;
	if (cPtr2.GetPointer() || !cPtr2 == false || cPtr == cPtr2 || !(cPtr != cPtr2)) bResult = false;
	cPtr2 = cPtr;
	if (!cPtr2.GetPointer() || !cPtr2 || !(cPtr == cPtr2) || cPtr != cPtr2 ||
		cPtr.GetPointer()->GetRefCount() != 2) bResult = false;
	cPtr = NULL;
	if (cPtr2.GetPointer()->GetRefCount() != 1) bResult = false;
	cPtr = new TestClass();
	cPtr->i = 1;
	*cPtr2 = *cPtr;
	if (cPtr->i != cPtr2->i) bResult = false;
	EndTask(bResult);

	// Raw pointer
	bResult = true;
	StartTask("SmartPtr with raw pointer");
	SmartPtr<int> cRawPtr, cRawPtr2;
	int *pI = new int;
	*pI = 55;
	cRawPtr = pI;
	if (!cRawPtr.GetPointer() || !cRawPtr || cRawPtr == cRawPtr2 || !(cRawPtr != cRawPtr2) ||
		!(cRawPtr == pI) || cRawPtr != pI || *cRawPtr.GetPointer() != 55) bResult = false;
	cRawPtr = cRawPtr;
	if (!cRawPtr.GetPointer() || !cRawPtr || cRawPtr == cRawPtr2 || !(cRawPtr != cRawPtr2) ||
		*cRawPtr.GetPointer() != 55) bResult = false;
	cRawPtr2 = cRawPtr2;
	if (cRawPtr2.GetPointer() || !cRawPtr2 == false || cRawPtr == cRawPtr2 || !(cRawPtr != cRawPtr2)) bResult = false;
	cRawPtr2 = cRawPtr;
	if (!cRawPtr2.GetPointer() || !cRawPtr2 || !(cRawPtr == cRawPtr2) || cRawPtr != cRawPtr2 ||
		*cRawPtr.GetPointer() != 55) bResult = false;
	*pI = 56;
	if (*cRawPtr.GetPointer() != 56 || *cRawPtr2.GetPointer() != 56) bResult = false;
	cRawPtr = NULL;
	if (cRawPtr.GetPointer() || !cRawPtr == false || cRawPtr == cRawPtr2 || !(cRawPtr != cRawPtr2) ||
		*cRawPtr2.GetPointer() != 56) bResult = false;
	EndTask(bResult);
}
