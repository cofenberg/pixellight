/*********************************************************\
 *  File: PLSceneCell.cpp                                *
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
#include "PL3dsMaxSceneExport/PLSceneExportOptions.h"
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLSceneCellPortal.h"
#include "PL3dsMaxSceneExport/PLSceneCell.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
PLSceneCell::PLSceneCell(PLSceneContainer &cContainer, const std::string &sName) :
	PLSceneContainer(&cContainer, sName, TypeCell)
{
}

/**
*  @brief
*    Destructor
*/
PLSceneCell::~PLSceneCell()
{
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneNode functions                 ]
//[-------------------------------------------------------]
void PLSceneCell::WriteToFile(XmlElement &cSceneElement, const std::string &sApplicationDrive, const std::string &sApplicationDir)
{
	static const std::string sSCCell = "PLScene::SCCell";
	PLSceneContainer::WriteToFile(cSceneElement, sApplicationDrive, sApplicationDir, sSCCell);
}


//[-------------------------------------------------------]
//[ Private virtual PLSceneContainer functions            ]
//[-------------------------------------------------------]
void PLSceneCell::PostProcess()
{
	// Call base implementation
	PLSceneContainer::PostProcess();

	// Loop through the list of outgoing cell-portals
	for (std::vector<PLSceneCellPortal*>::size_type i=0; i<m_lstOutgoingCellPortals.size(); i++) {
		// Get the cell-portal
		PLSceneCellPortal *pCellPortal = m_lstOutgoingCellPortals[i];
		if (pCellPortal) {
			// Get the target cell
			PLSceneNode *pNode = Get(pCellPortal->GetTargetCell());
			if (pNode) {
				if (pNode->GetType() == TypeCell) {
					// Add this cell-portal to the list of incoming cell-portals of the target cell
					((PLSceneCell*)pNode)->m_lstIncomingCellPortals.push_back(pCellPortal);
				} else {
					g_pLog->LogFLine(PLLog::Error, "Cell-portal '%s': There's a scene node with the name '%s', but this is NO (valid target) cell node! (note: 'Parent.' is added automatically by the exporter if required...)", pCellPortal->GetMaxNode()->GetName(), pCellPortal->GetTargetCell().c_str());
				}
			} else {
				g_pLog->LogFLine(PLLog::Error, "Cell-portal '%s': There's no (target) cell with the name '%s'! (note: 'Parent.' is added automatically by the exporter if required...)", pCellPortal->GetMaxNode()->GetName(), pCellPortal->GetTargetCell().c_str());
			}
		}
	}
}
