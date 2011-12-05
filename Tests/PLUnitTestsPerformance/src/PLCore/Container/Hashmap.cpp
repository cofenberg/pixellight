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
#include <fstream>
#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "PLCore/Tools/Stopwatch.h"
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
	Stopwatch Counter;

	TEST(PL_Hashmap_Add){

		Counter.Start();
		for (int i=0; i<testloops; i++)
			PLHashmap.Add(i+48, i);
		Counter.Stop();
		outputFile << "Counter: PLAdd: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(C_Hashmap_Add){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			CHashmap[i+48] = i;
		Counter.Stop();
		outputFile << "Counter: CAdd: \t\t" << Counter.GetMilliseconds() << endl;
	}

	TEST(PL_Hashmap_Replace){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			PLHashmap.Replace((char)48, i);
		Counter.Stop();
		outputFile << "Counter: PLReplace: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(C_Hashmap_Replace){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			CHashmap[48] = i;
		Counter.Stop();
		outputFile << "Counter: CReplace: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(PL_Hashmap_Set){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			PLHashmap.Set(48, i);
		Counter.Stop();
		outputFile << "Counter: PLSet: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(C_Hashmap_Set){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			CHashmap.insert(std::pair<char,int>(48,300));
		Counter.Stop();
		outputFile << "Counter: CSet: \t\t" << Counter.GetMilliseconds() << endl;
	}

	TEST(PL_Hashmap_Get){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			PLHashmap.Get(testloops-i);
		Counter.Stop();
		outputFile << "Counter: PLGet: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(C_Hashmap_Get){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			CHashmap.find(testloops-i);
		Counter.Stop();
		outputFile << "Counter: CGet: \t\t" << Counter.GetMilliseconds() << endl;
	}

	TEST(PL_Hashmap_RemoveV_Forwards){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			PLHashmap.RemoveValue (i);
		Counter.Stop();
		outputFile << "Counter: PLRemoveV Forwards: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(C_Hashmap_RemoveV_Forwards){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			CHashmap.erase(i);
		Counter.Stop();
		outputFile << "Counter: CRemoveV Forwards: \t" << Counter.GetMilliseconds() << endl;
	}

	TEST(PL_Hashmap_RemoveV_Backwards){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			PLHashmap.RemoveValue (testloops-i);
		Counter.Stop();
		outputFile << "Counter: PLRemoveV: Backwards\t" << Counter.GetMilliseconds() << endl;
	}

	TEST(C_Hashmap_RemoveV_Backwards){
		Counter.Start();
		for (int i=0; i<testloops; i++)
			CHashmap.erase(testloops-i);
		Counter.Stop();
		outputFile << "Counter: CRemoveV: Backwards\t" << Counter.GetMilliseconds() << endl;
		outputFile << endl;
	}
}