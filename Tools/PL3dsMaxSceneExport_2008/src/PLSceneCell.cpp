/*********************************************************\
 *  File: PLSceneCell.cpp                                *
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
#include "PL3dsMaxSceneExport/PLLog.h"
#include "PL3dsMaxSceneExport/PLTools.h"
#include "PL3dsMaxSceneExport/PLSceneCellPortal.h"
#include "PL3dsMaxSceneExport/PLSceneCell.h"


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
PLSceneCell::PLSceneCell(PLSceneContainer &cContainer, const String &sName) :
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
void PLSceneCell::WriteToFile(XmlElement &cSceneElement, const String &sApplicationDrive, const String &sApplicationDir)
{
	static const String sSCCell = "PLScene::SCCell";
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
					static_cast<PLSceneCell*>(pNode)->m_lstIncomingCellPortals.push_back(pCellPortal);
				} else {
					g_pLog->LogFLine(PLLog::Error, "Cell-portal '%s': There's a scene node with the name '%s', but this is NO (valid target) cell node! (note: 'Parent.' is added automatically by the exporter if required...)", pCellPortal->GetMaxNode()->GetName(), pCellPortal->GetTargetCell().GetASCII());
				}
			} else {
				g_pLog->LogFLine(PLLog::Error, "Cell-portal '%s': There's no (target) cell with the name '%s'! (note: 'Parent.' is added automatically by the exporter if required...)", pCellPortal->GetMaxNode()->GetName(), pCellPortal->GetTargetCell().GetASCII());
			}
		}
	}
}
