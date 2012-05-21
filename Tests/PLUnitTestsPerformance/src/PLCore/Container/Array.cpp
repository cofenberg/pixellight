/*********************************************************\
 *  File: Array.cpp                                      *
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
#include "PLCore/Container/Array.h"
#include <vector>

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
SUITE(Array_Performance) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	int testloops = 10000;	// number of iterations
	Array<int>* PLArray = new Array<int>();
	vector<int>* CArray = new vector<int>();

	TEST(PL_Array_Add_at_end){
		for (int i=0; i<testloops; i++)
			PLArray->Add(char(i+48));
	}

	TEST(C_Array_Add_at_end){
		for (int i=0; i<testloops; i++)
			CArray->push_back(char(i+48));
	}

	TEST(PL_Array_Add_at_Index){
		for (int i=0; i<testloops; i++)
			PLArray->AddAtIndex(char(i+48), i);
	}

	TEST(C_Array_Add_at_Index){
		vector<int>::iterator it;
		for (int i=0; i<testloops; i++){
			CArray->insert(it, 0, char(i+48));
			it++;
		}
	}
	
	TEST(PL_Array_GetSize){
		for (int i=0; i<testloops; i++)
			PLArray->GetSize();
	}

	TEST(C_Array_GetSize){
		for (int i=0; i<testloops; i++)
			CArray->size();
	}

	// No real C function for swapping two ELEMENTS of an array/vector
	/*TEST(PL_Array_ReplaceAtIndex){
		for (int i=0; i<testloops; i++)
			PLArray->ReplaceAtIndex(testloops-i, i);
	}*/

	/*TEST(C_Array_swap){
		for (int i=0; i<testloops; i++)
			swap(CArray[testloops-i-1], CArray[i]);
	}*/

	TEST(PL_Array_Reset){
		for (int i=0; i<testloops; i++)
			PLArray->Reset();
	}

	TEST(C_Array_clear){
		for (int i=0; i<testloops; i++)
			CArray->clear();
	}

}