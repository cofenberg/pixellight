//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/List.h>
#include <PLCore/Container/Container.h>

#include "ContainerFunctions.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(List_PrimitiveInt) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our List Test Fixture :)
	struct ConstructTestList
	{
		ConstructTestList() { 
			/* some setup */
			Lst.Add('1');
			Lst.Add('2');
			Lst.Add('3');
			Lst.Add('4');

			TestLst.Add('3');
			TestLst.Add('2');
			TestLst.Add('1');
			TestLst.Add('0');
		}
		~ConstructTestList() {
			/* some teardown */
		}

		// Container for testing
		List<int> Lst, EmptyLst, TestLst;
	};

	TEST_FIXTURE(ConstructTestList, DerivedContainerFunctions) {
		CheckDerivedContainerFuncs(Lst);
	}
}