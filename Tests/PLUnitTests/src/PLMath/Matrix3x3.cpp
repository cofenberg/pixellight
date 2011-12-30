//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Matrix3x3.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Matrix3x3) {
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
		PLMath::Matrix3x3 mat;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		mat.IsZero();

		CHECK(false);
	}
}