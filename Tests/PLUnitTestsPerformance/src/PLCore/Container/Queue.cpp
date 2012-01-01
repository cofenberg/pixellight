/*********************************************************\
 *  File: Queue.cpp                                    *
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
#include <fstream>
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "PLCore/Container/Queue.h"
#include <queue>

//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace std;
using namespace PLCore;


//[-------------------------------------------------------]
//[ Global variables                                      ]
//[-------------------------------------------------------]
extern ofstream outputFile;


/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Queue_Performance) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	int testloops = 10000;	// number of iterations
	Queue<int>* PLQueue = new Queue<int>();
	queue<int>* CQueue = new queue<int>();

	TEST(PL_Queue_Push){
		for (int i=0; i<testloops; i++)
			PLQueue->Push(i+48);
	}

	TEST(C_Queue_Push){
		for (int i=0; i<testloops; i++)
			CQueue->push(i+48);
	}

	TEST(PL_Queue_GetNumOfElements){
		for (int i=0; i<testloops; i++)
			PLQueue->GetNumOfElements();
	}

	TEST(C_Queue_size){
		for (int i=0; i<testloops; i++)
			CQueue->size();
	}

	TEST(PL_Queue_Pop){
		for (int i=testloops-1; i>=0; i--)
			PLQueue->Pop();
	}

	TEST(C_Queue_Pop){
		for (int i=0; i<testloops; i++)
			CQueue->pop();
	}
}