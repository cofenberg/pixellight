//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Vector2.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Vector2) {
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
		PLMath::Vector2 vec;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		vec.ToString();

		CHECK(false);
	}
}