/*********************************************************\
 *  File: String.cpp                                      *
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
#include "PLCore/String/String.h"
#include <string>

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
SUITE(String_Performance) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	int testloops = 10000;	// number of iterations
	String* PLString = new String();
	string* CString = new string();
	
	TEST(PL_String_insert_begin){
		for (int i=0; i<testloops; i++)
			PLString->Insert(static_cast<char>(i+48),0);
	}

	TEST(C_String_insert_begin){
		char insert[2];
		insert[1] = '\0';
		for (int i=0; i<testloops; i++){
			insert[0] = char(i+48);
			CString->insert(0, insert);
		}
	}

	TEST(PL_String_insert_mid){
		for (int i=0; i<testloops; i++)
			PLString->Insert(static_cast<char>(i+48),i/2);
	}

	TEST(C_String_insert_mid){
		char insert[2];
		insert[1] = '\0';
		for (int i=0; i<testloops; i++){
			insert[0] = char(i+48);
			CString->insert(i/2, insert);
		}	
	}

	TEST(PL_String_insert_end){
		for (int i=0; i<testloops; i++)
			PLString->Insert(static_cast<char>(i+48),i);
	}

	TEST(C_String_insert_end){
		char insert[2];
		insert[1] = '\0';
		for (int i=0; i<testloops; i++){
			insert[0] = char(i+48);
			CString->insert(i, insert);
		}	
	}

	/*
	Tests for SubString
	*/
	TEST(PL_String_Substring){
		for (int i=0; i<testloops; i++)
			PLString->GetSubstring(i);
	}

	TEST(C_String_Substring){
		char insert[2];
		insert[1] = '\0';
		for (int i=0; i<testloops; i++){
			insert[0] = char(i+48);
			CString->substr(i, insert[0]);
		}	
	}

}