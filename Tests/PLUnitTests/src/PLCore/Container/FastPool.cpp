//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/FastPool.h>
#include <PLCore/Container/Container.h>

#include "ContainerTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(FastPool_PrimitiveInt) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// TODO: implement! How do i use this FastPool container?
	class MyElement : private FastPoolElement<int> {
	};

	MyElement ele;

	// Our FastPool Test Fixture :)
	struct ConstructTestFastPool
	{
		ConstructTestFastPool() {
			/* some setup */
			/*
			Pol.Add(1);
			Pol.Add(2);
			Pol.Add(3);
			Pol.Add(4);

			TestPol.Add(3);
			TestPol.Add(2);
			TestPol.Add(1);
			TestPol.Add(0);
			*/
		}
		~ConstructTestFastPool() {
			/* some teardown */
		}

		// Container for testing
		//FastPool<MyElement> Pol, EmptyPol, TestPol;
	};

	TEST_FIXTURE(ConstructTestFastPool, DerivedContainerFunctions) {
		// CheckDerivedContainerFunctions(Pol);
	}
}