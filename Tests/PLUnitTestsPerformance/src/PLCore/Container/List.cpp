/*********************************************************\
 *  File: List.cpp                                      *
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
#include <UnitTest++/UnitTest++.h>
#include "PLCore/Container/List.h"
#include <list>

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
SUITE(List_Performance) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	int testloops = 10000;	// number of iterations
	List<int>* PLList = new List<int>();
	list<int>* CList = new list<int>();

	TEST(PL_List_Add_front){
		for (int i=0; i<testloops; i++)
			PLList->AddAtIndex(char(i+48),0);
	}

	TEST(C_List_Add_front){
		for (int i=0; i<testloops; i++)
			CList->push_front(char(i+48));
	}

	TEST(PL_List_Remove_front){
		for (int i=0; i<testloops; i++)
			PLList->RemoveAtIndex(0);
	}

	TEST(C_List_pop_front){
		for (int i=0; i<testloops; i++)
			CList->pop_front();
	}

	TEST(PL_List_Add_back){
		for (int i=0; i<testloops; i++)
			PLList->Add(PLList->GetNumOfElements());
	}

	TEST(C_List_push_back){
		for (int i=0; i<testloops; i++)
			CList->push_back(char(i+48));
	}

	TEST(PL_List_Remove_back){
		for (int i=0; i<testloops; i++)
			PLList->RemoveAtIndex(testloops-i);
	}

	TEST(C_List_remove_back){
		for (int i=0; i<testloops; i++)
			CList->remove(testloops-i);
	}

	TEST(PL_List_Clear){
		for (int i=0; i<testloops; i++)
			PLList->Clear();
	}

	TEST(C_List_clear){
		for (int i=0; i<testloops; i++)
			CList->clear();
	}
	
	
}