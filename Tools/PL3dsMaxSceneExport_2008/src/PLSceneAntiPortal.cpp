/*********************************************************\
 *  File: PLSceneAntiPortal.cpp                          *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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
PLSceneAntiPortal::PLSceneAntiPortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName) :
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
void PLSceneAntiPortal::WriteToFile(XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName().c_str());
	pNodeElement->SetAttribute("Name",  GetName().c_str());

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
