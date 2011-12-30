//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/EulerAngles.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(EulerAngles) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Array Test Fixture :)
	struct ConstructTest
	{
		ConstructTest() { 
			/* some setup */
		}
		~ConstructTest() {
			/* some teardown */
		}

		// Container for testing
		PLMath::EulerAngles eul;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		eul.XYXr;

		CHECK(false);
	}
}