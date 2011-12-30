//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Pool.h>
#include <PLCore/Container/Container.h>

#include "ContainerTests.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Pool_PrimitiveInt) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Pool Test Fixture :)
	struct ConstructTestPool
	{
		ConstructTestPool() { 
			/* some setup */
			Pool.Add(1);
			Pool.Add(2);
			Pool.Add(3);
			Pool.Add(4);

			TestPool.Add(3);
			TestPool.Add(2);
			TestPool.Add(1);
			TestPool.Add(0);
		}
		~ConstructTestPool() {
			/* some teardown */
		}

		// Container for testing
		Pool<int> Pool, EmptyPool, TestPool;
	};

	TEST_FIXTURE(ConstructTestPool, DerivedContainerFunctions) {
		CheckDerivedContainerFunctions<int>(Pool);
	}

	TEST_FIXTURE(ConstructTestPool, FreeElementsFunctions) {
		CHECK_EQUAL(0U, Pool.GetNumOfFreeElements());

		Pool.Remove(2);
		CHECK_EQUAL(1U, Pool.GetNumOfFreeElements());

		Pool.FreeElements();
		CHECK_EQUAL(4U, Pool.GetNumOfFreeElements());

		Pool.RemoveAllFreeElements();
		CHECK_EQUAL(0U, Pool.GetNumOfFreeElements());
	}

	TEST_FIXTURE(ConstructTestPool, FreeSize) {
		CHECK_EQUAL(0U, Pool.GetFreeSize());

		Pool.Remove(2);
		CHECK_EQUAL(sizeof(int), Pool.GetFreeSize());
	}
}