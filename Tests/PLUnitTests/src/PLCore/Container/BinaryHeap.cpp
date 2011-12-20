//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/BinaryHeap.h>
#include <PLCore/Container/Container.h>

#include "HeapTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(BinaryHeap_Int_Int) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our List Test Fixture :)
	struct ConstructTestBinaryHeap
	{
		ConstructTestBinaryHeap() { 
			/* some setup */
			byHeap.Add(1, 1);
			byHeap.Add(2, 2);
			byHeap.Add(3, 3);
			byHeap.Add(4, 4);

			TestbyHeap.Add(3, 3);
			TestbyHeap.Add(2, 2);
			TestbyHeap.Add(1, 1);
			TestbyHeap.Add(0, 0);
		}
		~ConstructTestBinaryHeap() {
			/* some teardown */
		}

		// Container for testing
		BinaryHeap<int, int> byHeap, EmptybyHeap, TestbyHeap;
	};

	TEST_FIXTURE(ConstructTestBinaryHeap, DerivedContainerFunctions) {
		CheckDerivedHeapFunctions(byHeap);
	}
}