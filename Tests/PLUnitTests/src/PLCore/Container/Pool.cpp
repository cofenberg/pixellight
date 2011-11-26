//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Pool.h>
#include <PLCore/Container/Container.h>

#include "ContainerFunctions.h"

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
			Pol.Add('1');
			Pol.Add('2');
			Pol.Add('3');
			Pol.Add('4');

			TestPol.Add('3');
			TestPol.Add('2');
			TestPol.Add('1');
			TestPol.Add('0');
		}
		~ConstructTestPool() {
			/* some teardown */
		}

		// Container for testing
		Pool<int> Pol, EmptyPol, TestPol;
	};

	TEST_FIXTURE(ConstructTestPool, DerivedContainerFunctions) {
		CheckDerivedContainerFuncs(Pol);
	}
}