/*********************************************************\
 *  File: PLSceneAntiPortal.cpp                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the “Software”), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Xml/Xml.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneAntiPortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneAntiPortal::PLSceneAntiPortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const String &sName) :
	PLScenePortal(cContainer, cIGameNode, sName, TypeAntiPortal, "PLScene::SNAntiPortal")
{
}

/**
*  @brief
*    Destructor
*/
PLSceneAntiPortal::~PLSceneAntiPortal()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneAntiPortal::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName());
	pNodeElement->SetAttribute("Name",  GetName());

	// Write position, rotation, scale, bounding box and flags
	WriteToFilePosRotScaleBoxFlags(*pNodeElement);

	// Vertices
	std::vector<Point3>::size_type nNumOfVertices = m_lstVertices.size();
	String sVertices;
	for (std::vector<Point3>::size_type i=0; i<nNumOfVertices; i++) {
		const Point3 &vVertex = m_lstVertices[i];
		if (i < nNumOfVertices-1)
			sVertices += String::Format("%f %f %f ", vVertex.x, vVertex.y, vVertex.z);
		else
			sVertices += String::Format("%f %f %f", vVertex.x, vVertex.y, vVertex.z);
	}
	pNodeElement->SetAttribute("Vertices", sVertices);

	// Write flexible variables
	WriteVariables(*pNodeElement);

	// Write modifiers
	WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

	// Link node element
	cSceneElement.LinkEndChild(*pNodeElement);
}
