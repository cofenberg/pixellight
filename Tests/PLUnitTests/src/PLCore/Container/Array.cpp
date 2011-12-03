//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLCore/Container/Array.h>
#include <PLCore/Container/Container.h>

#include "ContainerFunctions.h"

using namespace PLCore;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Array_PrimitiveInt) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Array Test Fixture :)
	struct ConstructTestArray
	{
		ConstructTestArray() { 
			/* some setup */
			Arr.Add('1');
			Arr.Add('2');
			Arr.Add('3');
			Arr.Add('4');

			TestArr.Add('3');
			TestArr.Add('2');
			TestArr.Add('1');
			TestArr.Add('0');
		}
		~ConstructTestArray() {
			/* some teardown */
		}

		// Container for testing
		Array<int> Arr, EmptyArr, TestArr;
	};

	TEST_FIXTURE(ConstructTestArray, DerivedContainerFunctions) {
		CheckDerivedContainerFuncs(Arr);
	}

	TEST_FIXTURE(ConstructTestArray, SetResizeCount_Zero) {
		// initial resizecount==10
		CHECK_EQUAL(10U, Arr.GetResizeCount());

		Arr.SetResizeCount(0U);
		CHECK_EQUAL(0U, Arr.GetResizeCount());
	}

	TEST_FIXTURE(ConstructTestArray, SetResizeCount_100) {
		Arr.SetResizeCount(100U);
		CHECK_EQUAL(100U, Arr.GetResizeCount());
	}	

	TEST_FIXTURE(ConstructTestArray, SetResizeCount_4byte) {
		Arr.SetResizeCount(4294967295U);
		CHECK_EQUAL(4294967295U, Arr.GetResizeCount());
	}

	TEST_FIXTURE(ConstructTestArray, Reset) {
		CHECK(Arr.GetNumOfElements()>0U);

		Arr.Reset();
		CHECK_EQUAL(0U, Arr.GetNumOfElements());
	}

	TEST_FIXTURE(ConstructTestArray, Resize) {
		// TODO: implement
	}
}