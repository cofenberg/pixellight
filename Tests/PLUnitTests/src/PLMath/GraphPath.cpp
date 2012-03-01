//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Graph/GraphPath.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(GraphPath) {
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
		PLMath::GraphPath graphpath;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		graphpath.IsClosed();

		CHECK(false);
	}
}