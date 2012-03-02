//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Matrix4x4.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Matrix4x4) {
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
		PLMath::Matrix4x4 mat;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		mat.IsZero();

		CHECK(false);
	}
}