/*********************************************************\
 *  File: SNCellPortal.cpp                               *
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
#include "PLScene/Scene/SceneNodeHandler.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SNCellPortal.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNCellPortal)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNCellPortal::GetTargetCell() const
{
	return m_sTargetCell;
}

void SNCellPortal::SetTargetCell(const String &sValue)
{
	if (m_sTargetCell != sValue) {
		// Remove the current target cell
		SceneNode *pCell = m_pTargetCell->GetElement();
		if (pCell) {
			// Disconnect event handlers
			pCell->EventContainer.Disconnect(&EventHandlerCellContainerPositionRotationScale);
			pCell->GetTransform().EventPosition.Disconnect(&EventHandlerCellContainerPositionRotationScale);
			pCell->GetTransform().EventRotation.Disconnect(&EventHandlerCellContainerPositionRotationScale);
			pCell->GetTransform().EventScale.   Disconnect(&EventHandlerCellContainerPositionRotationScale);

			// Clear target cell handler
			m_pTargetCell->SetElement();
		}

		// Set the new target cell name
		m_sTargetCell = sValue;

		// We need to recalculate the warp matrix
		m_nInternalPortalFlags |= RecalculateWarpMatrix;
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SNCellPortal::SNCellPortal() :
	TargetCell(this),
	Flags(this),
	EventHandlerCellContainerPositionRotationScale(&SNCellPortal::NotifyCellContainerPositionRotationScale, this),
	m_pTargetCell(new SceneNodeHandler())
{
	// Set the internal portal flag
	m_nInternalPortalFlags |= RecalculateWarpMatrix;
}

/**
*  @brief
*    Destructor
*/
SNCellPortal::~SNCellPortal()
{
	delete m_pTargetCell;
}

/**
*  @brief
*    Returns the cell the cell-portal links to
*/
SCCell *SNCellPortal::GetTargetCellInstance()
{
	if (!m_pTargetCell->GetElement() && m_sTargetCell.GetLength()) {
		SceneNode *pCell = GetContainer()->Get(m_sTargetCell);
		if (pCell && pCell->IsCell()) {
			m_pTargetCell->SetElement(pCell);

			// Connect event handlers
			pCell->EventContainer.Connect(&EventHandlerCellContainerPositionRotationScale);
			pCell->GetTransform().EventPosition. Connect(&EventHandlerCellContainerPositionRotationScale);
			pCell->GetTransform().EventRotation. Connect(&EventHandlerCellContainerPositionRotationScale);
			pCell->GetTransform().EventScale.    Connect(&EventHandlerCellContainerPositionRotationScale);
		}
	}

	// Return the target cell
	return (SCCell*)m_pTargetCell->GetElement();
}

/**
*  @brief
*    Returns the warp matrix
*/
const Matrix3x4 &SNCellPortal::GetWarpMatrix()
{
	// Calculate warp matrix if required
	if (m_nInternalPortalFlags & RecalculateWarpMatrix) {
		// Get the scene container this portal is in
		SceneContainer *pContainer = GetContainer();
		if (pContainer) {
			// Get the target cell
			SceneNode *pTargetNode = pContainer->Get(m_sTargetCell);
			if (pTargetNode && pTargetNode->IsCell()) {
				// Get transform matrix
				pContainer->GetTransformMatrixTo((SceneContainer&)*pTargetNode, m_mWarp);
			}
		}

		// Recalculation done
		m_nInternalPortalFlags &= ~RecalculateWarpMatrix;
	}

	// Return the warp matrix
	return m_mWarp;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the target cell container, position, rotation or scale changed
*/
void SNCellPortal::NotifyCellContainerPositionRotationScale()
{
	// We need to recalculate the warp matrix
	m_nInternalPortalFlags |= RecalculateWarpMatrix;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
