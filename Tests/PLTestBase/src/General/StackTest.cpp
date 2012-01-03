/*********************************************************\
 *  File: StackTest.cpp                                  *
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
#include <PLCore/Container/Stack.h>
#include "PLTestBase/General/StackTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *StackTest::GetName() const
{
	return "Stack";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void StackTest::Test()
{
	Stack<int> cStack;
	bool bResult;
	int i;

	// GetNumOfElements()
	StartTask("GetNumOfElements()");
	EndTask(!cStack.GetNumOfElements());

	// Push()
	StartTask("Push()");
	bResult = true;
	// Push '0'
	i = 0;
	if (!cStack.Push(i)) bResult = false;
	// Push '1'
	i = 1;
	if (!cStack.Push(i)) bResult = false;
	// Push '2'
	i = 2;
	if (!cStack.Push(i)) bResult = false;
	EndTask(bResult && cStack.GetNumOfElements() == 3);

	// Copy
	StartTask("Copy");
	bResult = true;
	Stack<int> cStackT(cStack);
	// Check number of elements
	if (cStack.GetNumOfElements() != cStackT.GetNumOfElements()) bResult = false;
	// Pop '2'
	cStackT.Pop(&i);
	if (i != 2) bResult = false;
	// Pop '1'
	cStackT.Pop(&i);
	if (i != 1) bResult = false;
	// Pop '0'
	cStackT.Pop(&i);
	if (i != 0) bResult = false;
	EndTask(bResult && !cStackT.GetNumOfElements());

	// Pop()
	StartTask("Pop()");
	bResult = true;
	// Pop '2'
	cStack.Pop(&i);
	if (i != 2) bResult = false;
	// Pop '1'
	cStack.Pop(&i);
	if (i != 1) bResult = false;
	// Pop '0'
	cStack.Pop(&i);
	if (i != 0) bResult = false;
	EndTask(bResult && !cStackT.GetNumOfElements());
}
