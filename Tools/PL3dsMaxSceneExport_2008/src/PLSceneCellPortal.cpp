/*********************************************************\
 *  File: PLSceneCellPortal.cpp                          *
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
#include "PL3dsMaxSceneExport/PLSceneCellPortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the name of the target cell
*/
String PLSceneCellPortal::GetTargetCell() const
{
	return m_sTargetCell;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneCellPortal::PLSceneCellPortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const String &sName, const String &sTargetCell) :
	PLScenePortal(cContainer, cIGameNode, sName, TypeCellPortal, "PLScene::SNCellPortal"),
	m_sTargetCell(sTargetCell)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneCellPortal::~PLSceneCellPortal()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneCellPortal::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName());
	pNodeElement->SetAttribute("Name",  GetName());

	// Write position, rotation, scale, bounding box and flags
	WriteToFilePosRotScaleBoxFlags(*pNodeElement);

	// Target cell
	pNodeElement->SetAttribute("TargetCell", m_sTargetCell);

	// [TODO] Check this again, within the Dungeon-Demo scene, this test fails for one portal...
	// Check cell-portal direction and write a warning into the log if the direction looks wrong
	float             fDot       = 0.0f;
	PLSceneContainer *pContainer = GetContainer();
	if (pContainer) {
		// Get world space direction vector from cell-portal to owner cell
		Point3 vDir = pContainer->GetWorldSpaceCenter() - m_vCenter;
		vDir.Unify();

		// Check whether the cell-portal looks into the owner cell
		fDot = DotProd(m_vNormal, vDir);
		if (fDot < 0.0f)
			g_pLog->LogFLine(PLLog::Warning, "%s: The cell-portal doesn't look INTO the cell (%s) it is in!!", GetIGameNode()->GetName(), pContainer->GetName().GetASCII());
	}

	// Vertices
	std::vector<Point3>::size_type nNumOfVertices = m_lstVertices.size();
	String sVertices;
	if (fDot < 0.0f && g_SEOptions.bCorrectPortals) {
		// Invert vertex order
		for (std::vector<Point3>::size_type i=nNumOfVertices; i>0; i--) {
			const Point3 &vVertex = m_lstVertices[i-1];
			if (i)
				sVertices += String::Format("%f %f %f ", vVertex.x, vVertex.y, vVertex.z);
			else
				sVertices += String::Format("%f %f %f",  vVertex.x, vVertex.y, vVertex.z);
		}
	} else {
		for (std::vector<Point3>::size_type i=0; i<nNumOfVertices; i++) {
			const Point3 &vVertex = m_lstVertices[i];
			if (i < nNumOfVertices-1)
				sVertices += String::Format("%f %f %f ", vVertex.x, vVertex.y, vVertex.z);
			else
				sVertices += String::Format("%f %f %f", vVertex.x, vVertex.y, vVertex.z);
		}
	}
	pNodeElement->SetAttribute("Vertices", sVertices);

	// Write flexible variables
	WriteVariables(*pNodeElement);

	// Write modifiers
	WriteModifiers(*pNodeElement, sApplicationDrive, sApplicationDir);

	// Link node element
	cSceneElement.LinkEndChild(*pNodeElement);
}
