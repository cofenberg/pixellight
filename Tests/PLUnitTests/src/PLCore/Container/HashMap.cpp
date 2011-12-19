//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/HashMap.h>

#include "MapTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(HashMap_Int_Int) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our List Test Fixture :)
	struct ConstructTestHashMap
	{
		ConstructTestHashMap() { 
			/* some setup */
			Hash.Add(1, 1);
			Hash.Add(2, 2);
			Hash.Add(3, 3);
			Hash.Add(4, 4);

			TestHash.Add(3, 3);
			TestHash.Add(2, 2);
			TestHash.Add(1, 1);
			TestHash.Add(0, 0);
		}
		~ConstructTestHashMap() {
			/* some teardown */
		}

		// Container for testing
		HashMap<int, int> Hash, EmptyHash, TestHash;
	};

	TEST_FIXTURE(ConstructTestHashMap, DerivedMapFunctions) {
		CheckDerivedMapFunctions<int,int>(Hash);
	}
}