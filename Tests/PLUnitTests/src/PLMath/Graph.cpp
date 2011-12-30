//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Graph/Graph.h>

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Graph) {
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
		PLMath::Graph graph;
	};

	TEST_FIXTURE(ConstructTest, Dummy) {
		graph.Clear();

		CHECK(false);
	}
}