//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Quaternion.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Quaternion) {
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
		PLMath::Quaternion quat;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		quat.ToString();

		CHECK(false);
	}
}