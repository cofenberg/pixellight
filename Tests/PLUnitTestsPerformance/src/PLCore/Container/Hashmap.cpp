/*********************************************************\
 *  File: Hashmap.cpp                                    *
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
#include <map>
#include <UnitTest++/UnitTest++.h>
#include "PLCore/Container/HashMap.h"


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
SUITE(Hashmap_Performance) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/
	// general objects for testing
	int testloops = 10000;	// number of iterations
	HashMap<char, int> PLHashmap;
	std::map<char, int> CHashmap;
	

	TEST(PL_Hashmap_Add){
		for (int i=0; i<testloops*10; i++)
			PLHashmap.Add(static_cast<char>(i+48), i);
	}

	TEST(C_Hashmap_Add){
		for (int i=0; i<testloops; i++)
			CHashmap[static_cast<char>(i+48)] = i;
	}

	TEST(PL_Hashmap_Replace){
		for (int i=0; i<testloops; i++)
			PLHashmap.Replace(static_cast<char>(48), i);
	}

	TEST(C_Hashmap_Replace){
		for (int i=0; i<testloops; i++)
			CHashmap[48] = i;
	}

	TEST(PL_Hashmap_Set){
		for (int i=0; i<testloops; i++)
			PLHashmap.Set(48, i);
	}

	TEST(C_Hashmap_Set){
		for (int i=0; i<testloops*10; i++)
			CHashmap.insert(std::pair<char,int>(48,300));
	}

	TEST(PL_Hashmap_Get){
		for (int i=0; i<testloops; i++)
			PLHashmap.Get(static_cast<char>(testloops-i));
	}

	TEST(C_Hashmap_Get){
		for (int i=0; i<testloops; i++)
			CHashmap.find(static_cast<char>(testloops-i));
	}

	TEST(PL_Hashmap_RemoveV_Forwards){
		for (int i=0; i<testloops; i++)
			PLHashmap.RemoveValue (i);
	}

	TEST(C_Hashmap_RemoveV_Forwards){
		for (int i=0; i<testloops; i++)
			CHashmap.erase(static_cast<char>(i));
	}

	TEST(PL_Hashmap_RemoveV_Backwards){
		for (int i=0; i<testloops; i++)
			PLHashmap.RemoveValue (testloops-i);
	}

	TEST(C_Hashmap_RemoveV_Backwards){
		for (int i=0; i<testloops; i++)
			CHashmap.erase(static_cast<char>(testloops-i));
	}
}