/*********************************************************\
 *  File: QueueTest.cpp                                  *
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
#include <PLGeneral/Container/Queue.h>
#include "PLTestBase/General/QueueTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public virtual TestCase functions                     ]
//[-------------------------------------------------------]
const char *QueueTest::GetName() const
{
	return "Queue";
}


//[-------------------------------------------------------]
//[ Private virtual TestCase functions                    ]
//[-------------------------------------------------------]
void QueueTest::Test()
{
	Queue<int> cQueue;
	bool bResult;
	int i;

	// GetNumOfElements()
	StartTask("GetNumOfElements()");
	EndTask(!cQueue.GetNumOfElements());

	// Push()
	StartTask("Push()");
	bResult = true;
	// Push '0'
	i = 0;
	if (!cQueue.Push(i)) bResult = false;
	// Push '1'
	i = 1;
	if (!cQueue.Push(i)) bResult = false;
	// Push '2'
	i = 2;
	if (!cQueue.Push(i)) bResult = false;
	EndTask(bResult && cQueue.GetNumOfElements() == 3);

	// Copy
	StartTask("Copy");
	Queue<int> cQueueT(cQueue);
	bResult = true;
	// Check number of elements
	if (cQueue.GetNumOfElements() != cQueueT.GetNumOfElements()) bResult = false;
	// Pop '0'
	cQueueT.Pop(&i);
	if (i != 0) bResult = false;
	// Pop '1'
	cQueueT.Pop(&i);
	if (i != 1) bResult = false;
	// Pop '2'
	cQueueT.Pop(&i);
	if (i != 2) bResult = false;
	EndTask(bResult && !cQueueT.GetNumOfElements());

	// Pop()
	StartTask("Pop()");
	bResult = true;
	// Pop '0'
	cQueue.Pop(&i);
	if (i != 0) bResult = false;
	// Pop '1'
	cQueue.Pop(&i);
	if (i != 1) bResult = false;
	// Pop '2'
	cQueue.Pop(&i);
	if (i != 2) bResult = false;
	EndTask(bResult && !cQueue.GetNumOfElements());
}
