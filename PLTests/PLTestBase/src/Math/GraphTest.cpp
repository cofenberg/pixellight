/*********************************************************\
 *  File: GraphTest.cpp                                  *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Graph/Graph.h>
#include <PLMath/Graph/GraphNode.h>
#include <PLMath/Graph/GraphPath.h>
#include "PLTestBase/Math/GraphTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ GraphTest implementation                              ]
//[-------------------------------------------------------]
const char *GraphTest::GetName() const
{
	return "Graph";
}

void GraphTest::Test()
{
	//	Test graph:                  Shortest paths: ('source'->'target' = nodes to pass)
	//
	//	+------5------+              A->A: A
	//	|             |              A->B: A->B
	//	|  /-2--B--3--C--5-\         A->C: A->D->C
	//	| /     |    /|     \        A->D: A->D
	//	+-A     2 /3/ 1      F       A->E: A->D->E
	//	  \     |/    |     /        A->F: A->D->E->F
	//	   \-1--D--1--E--2-/

	// Build graph visualized above
	Graph cGraph;
	GraphNode *pNodeA, *pNodeB, *pNodeC, *pNodeD, *pNodeE, *pNodeF;

	// Using this flag you can toggle between positions or fixed distances you can 
	// see in the diagram above
	bool bUsePosition = true;

	// Create and add nodes to graph
	pNodeA = cGraph.Create("A");
	pNodeB = cGraph.Create("B");
	pNodeC = cGraph.Create("C");
	pNodeD = cGraph.Create("D");
	pNodeE = cGraph.Create("E");
	pNodeF = cGraph.Create("F");

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
	cGraph.Save("Test.graph");

	// Load and save it again
	cGraph.Load("Test.graph");
	cGraph.Save("Test_.graph");

	// [TODO]
	// Find shortest path
/*	GraphPath *pPath = cGraph.FindShortestPath(1, 5);
	if (pPath) {
		delete pPath;
	}*/
}
