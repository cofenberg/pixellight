//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/FibonacciHeap.h>

#include "HeapTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(FibonacciHeap_Int_Int) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our List Test Fixture :)
	struct ConstructTestFibonacciHeap
	{
		ConstructTestFibonacciHeap() { 
			/* some setup */
			FiboHeap.Add(1, 1);
			FiboHeap.Add(2, 2);
			FiboHeap.Add(3, 3);
			FiboHeap.Add(4, 4);

			TestFiboHeap.Add(3, 3);
			TestFiboHeap.Add(2, 2);
			TestFiboHeap.Add(1, 1);
			TestFiboHeap.Add(0, 0);
		}
		~ConstructTestFibonacciHeap() {
			/* some teardown */
		}

		// Container for testing
		FibonacciHeap<int, int> FiboHeap, EmptyFiboHeap, TestFiboHeap;
	};

	TEST_FIXTURE(ConstructTestFibonacciHeap, DerivedContainerFunctions) {
		CheckDerivedHeapFunctions(FiboHeap);
	}
}