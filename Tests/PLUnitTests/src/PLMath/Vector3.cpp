//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Vector3.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Vector3) {
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
		PLMath::Vector3 vec;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		vec.ToString();

		CHECK(false);
	}
}