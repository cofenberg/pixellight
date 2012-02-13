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
			bUsePosition = true;
		}
		~ConstructTest() {
			/* some teardown */
		}

		// Container for testing
		PLMath::Graph graph;
		PLMath::GraphNode *pNodeA, *pNodeB, *pNodeC, *pNodeD, *pNodeE, *pNodeF;
		bool bUsePosition;
	};

	// TODO: use this as test?
	/*
	TEST_FIXTURE(ConstructTest, Test) {
		pNodeA = graph.Create("A");
		pNodeB = graph.Create("B");
		pNodeC = graph.Create("C");
		pNodeD = graph.Create("D");
		pNodeE = graph.Create("E");
		pNodeF = graph.Create("F");

		// Set node positions
		if (bUsePosition) {
			pNodeF->SetPos(19.0f, 0.0f, 2.0f);
			pNodeA->SetPos( 0.0f, 0.0f, 2.0f);
			pNodeB->SetPos( 6.0f, 0.0f, 0.0f);
			pNodeC->SetPos(12.0f, 0.0f, 0.0f);
			pNodeD->SetPos( 6.0f, 0.0f, 4.0f);
			pNodeE->SetPos(12.0f, 0.0f, 4.0f);
		}

		// Setup node neighbours
		// Node A (0)
		pNodeA->AddNeighbour(*pNodeC, bUsePosition ? -1.0f : 5.0f);
		pNodeA->AddNeighbour(*pNodeB, bUsePosition ? -1.0f : 2.0f);
		pNodeA->AddNeighbour(*pNodeD, bUsePosition ? -1.0f : 1.0f);

		// Node B (1)
		pNodeB->AddNeighbour(*pNodeA, bUsePosition ? -1.0f : 2.0f);
		pNodeB->AddNeighbour(*pNodeC, bUsePosition ? -1.0f : 3.0f);
		pNodeB->AddNeighbour(*pNodeD, bUsePosition ? -1.0f : 2.0f);

		// Node C (2)
		pNodeC->AddNeighbour(*pNodeA, bUsePosition ? -1.0f : 5.0f);
		pNodeC->AddNeighbour(*pNodeB, bUsePosition ? -1.0f : 3.0f);
		pNodeC->AddNeighbour(*pNodeD, bUsePosition ? -1.0f : 3.0f);
		pNodeC->AddNeighbour(*pNodeE, bUsePosition ? -1.0f : 1.0f);
		pNodeC->AddNeighbour(*pNodeF, bUsePosition ? -1.0f : 5.0f);

		// Node D (3)
		pNodeD->AddNeighbour(*pNodeA, bUsePosition ? -1.0f : 1.0f);
		pNodeD->AddNeighbour(*pNodeB, bUsePosition ? -1.0f : 2.0f);
		pNodeD->AddNeighbour(*pNodeC, bUsePosition ? -1.0f : 3.0f);
		pNodeD->AddNeighbour(*pNodeE, bUsePosition ? -1.0f : 1.0f);

		// Node E (4)
		pNodeE->AddNeighbour(*pNodeD, bUsePosition ? -1.0f : 1.0f);
		pNodeE->AddNeighbour(*pNodeC, bUsePosition ? -1.0f : 1.0f);
		pNodeE->AddNeighbour(*pNodeF, bUsePosition ? -1.0f : 2.0f);

		// Node F (5)
		pNodeF->AddNeighbour(*pNodeC, bUsePosition ? -1.0f : 5.0f);
		pNodeF->AddNeighbour(*pNodeE, bUsePosition ? -1.0f : 2.0f);

		// Save the graph
		graph.SaveByFilename("Test.graph");

		// Load and save it again
		graph.LoadByFilename("Test.graph");
		graph.SaveByFilename("Test_.graph");
	}
	*/
}