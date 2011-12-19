//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/BinominalHeap.h>

#include "HeapTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(BinominalHeap_Int_Int) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our List Test Fixture :)
	struct ConstructTestBinominalHeap
	{
		ConstructTestBinominalHeap() { 
			/* some setup */
			biHeap.Add(1, 1);
			biHeap.Add(2, 2);
			biHeap.Add(3, 3);
			biHeap.Add(4, 4);

			TestbiHeap.Add(3, 3);
			TestbiHeap.Add(2, 2);
			TestbiHeap.Add(1, 1);
			TestbiHeap.Add(0, 0);
		}
		~ConstructTestBinominalHeap() {
			/* some teardown */
		}

		// Container for testing
		BinominalHeap<int, int> biHeap, EmptybiHeap, TestbiHeap;
	};

	TEST_FIXTURE(ConstructTestBinominalHeap, DerivedContainerFunctions) {
		CheckDerivedHeapFunctions(biHeap);
	}
}