//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/SimpleMap.h>

#include "MapTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(SimpleMap_Int_Int) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our List Test Fixture :)
	struct ConstructTestSimpleMap
	{
		ConstructTestSimpleMap() { 
			/* some setup */
			SimMap.Add(1, 1);
			SimMap.Add(2, 2);
			SimMap.Add(3, 3);
			SimMap.Add(4, 4);

			TestSimMap.Add(3, 3);
			TestSimMap.Add(2, 2);
			TestSimMap.Add(1, 1);
			TestSimMap.Add(0, 0);
		}
		~ConstructTestSimpleMap() {
			/* some teardown */
		}

		// Container for testing
		SimpleMap<int, int> SimMap, EmptySimMap, TestSimMap;
	};

	TEST_FIXTURE(ConstructTestSimpleMap, DerivedMapFunctions) {
		CheckDerivedMapFunctions<int,int>(SimMap);
	}
}