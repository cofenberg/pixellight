/*********************************************************\
 *  File: Stack.cpp                                      *
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
#include <fstream>
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "PLCore/Container/Stack.h"
#include <stack>

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
SUITE(Stack_Performance) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	int testloops = 10000;	// number of iterations
	Stack<int>* PLStack = new Stack<int>();
	stack<int>* CStack = new stack<int>();

	TEST(PL_Stack_Push){
		for (int i=0; i<testloops; i++)
			PLStack->Push(i+48);
	}

	TEST(C_Stack_Push){
		for (int i=0; i<testloops; i++)
			CStack->push(i+48);
	}

	TEST(PL_Stack_GetNumOfElements){
		for (int i=0; i<testloops; i++)
			PLStack->GetNumOfElements();
	}

	TEST(C_Stack_size){
		for (int i=0; i<testloops; i++)
			CStack->size();
	}

	TEST(PL_Stack_Pop){
		for (int i=0; i<testloops; i++)
			PLStack->Pop();
	}

	TEST(C_Stack_Pop){
		for (int i=0; i<testloops; i++)
			CStack->pop();
	}

}