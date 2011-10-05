/*********************************************************\
 *  File: GraphPathTest.cpp                              *
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
#include "PLTestBase/Math/GraphPathTest.h"


//[-------------------------------------------------------]
//[ Namespaces                                            ]
//[-------------------------------------------------------]
using namespace PLMath;


//[-------------------------------------------------------]
//[ GraphPathTest implementation                          ]
//[-------------------------------------------------------]
const char *GraphPathTest::GetName() const
{
	return "GraphPath";
}

void GraphPathTest::Test()
{
	//	Test path:
	//	  /B-------------C\
	//	 /                 \
	//	A                   D
	//	 \                 /
	//	  \F-------------E/

	// Build path visualized above
	GraphPath cPath;
	GraphNode *pNode;

	// A
	pNode = new GraphNode("A");
	cPath.AddNode(*pNode);
	pNode->SetPos(0.0f, 0.0f, 2.0f);
	// B
	pNode = new GraphNode("B");
	cPath.AddNode(*pNode);
	pNode->SetPos(2.0f, 0.0f, 0.0f);
	// C
	pNode = new GraphNode("C");
	cPath.AddNode(*pNode);
	pNode->SetPos(16.0f, 0.0f, 0.0f);
	// D
	pNode = new GraphNode("D");
	cPath.AddNode(*pNode);
	pNode->SetPos(19.0f, 0.0f, 2.0f);
	// E
	pNode = new GraphNode("E");
	cPath.AddNode(*pNode);
	pNode->SetPos(16.0f, 0.0f, 4.0f);
	// F
	pNode = new GraphNode("F");
	cPath.AddNode(*pNode);
	pNode->SetPos(2.0f, 0.0f, 4.0f);

	// The path should be closed
	cPath.SetClosed(true);

	// Save the path
	cPath.SaveByFilename("Test.path");

	// Load and save it again
	cPath.LoadByFilename("Test.path");
	cPath.SaveByFilename("Test_.path");
}
