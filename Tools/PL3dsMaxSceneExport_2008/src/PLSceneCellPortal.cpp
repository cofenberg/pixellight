/*********************************************************\
 *  File: PLSceneCellPortal.cpp                          *
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
#include <PLGeneral/Xml/Xml.h>
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLScene.h"
#include "PL3dsMaxSceneExport/PLSceneCellPortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the name of the target cell
*/
const std::string &PLSceneCellPortal::GetTargetCell() const
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
PLSceneCellPortal::PLSceneCellPortal(PLSceneContainer &cContainer, IGameNode &cIGameNode, const std::string &sName, const std::string &sTargetCell) :
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
void PLSceneCellPortal::WriteToFile(XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	// Add scene node
	XmlElement *pNodeElement = new XmlElement("Node");
	pNodeElement->SetAttribute("Class", GetClassName().c_str());
	pNodeElement->SetAttribute("Name",  GetName().c_str());

	// Write position, rotation, scale, bounding box and flags
	WriteToFilePosRotScaleBoxFlags(*pNodeElement);

	// Target cell
	pNodeElement->SetAttribute("TargetCell", m_sTargetCell.c_str());

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
			g_pLog->LogFLine(PLLog::Warning, "%s: The cell-portal doesn't look INTO the cell (%s) it is in!!", GetIGameNode()->GetName(), pContainer->GetName().c_str());
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
