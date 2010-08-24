/*********************************************************\
 *  File: SQPoint.cpp                                    *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLMath/Intersect.h>
#include "PLScene/Scene/SNCellPortal.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneHierarchy.h"
#include "PLScene/Scene/SceneHierarchyNode.h"
#include "PLScene/Scene/SceneHierarchyNodeItem.h"
#include "PLScene/Scene/SceneQueries/SQPoint.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SQPoint)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SQPoint::SQPoint()
{
}

/**
*  @brief
*    Destructor
*/
SQPoint::~SQPoint()
{
}

/**
*  @brief
*    Returns the used point
*/
Vector3 &SQPoint::GetPoint()
{
	return m_vPoint;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive part of PerformQuery()
*/
bool SQPoint::PerformQueryRec(SceneHierarchyNode &cHierarchyNode)
{
	// Is this scene hierarchy node intersecting the point?
	if (!Intersect::AABoxPoint(cHierarchyNode.GetAABoundingBox().vMin,
							   cHierarchyNode.GetAABoundingBox().vMax,
							   m_vPoint))
		return true; // Continue the query

	// Touch this node
	cHierarchyNode.Touch();

	// Get the scene context
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		// Inform all listeners
		const SceneHierarchyNodeItem *pItem = cHierarchyNode.GetFirstItem();
		while (pItem) {
			// Get the linked scene node
			SceneNode *pSceneNode = pItem->GetSceneNode();

			// Was this scene node already processed?
			if (pSceneNode && !pSceneContext->IsNodeTouched(*pSceneNode)) {
				// Check scene node
				const AABoundingBox &cAABB = pSceneNode->GetContainerAABoundingBox();
				if (Intersect::AABoxPoint(cAABB.vMin, cAABB.vMax, m_vPoint)) {
					// Touch this node
					pSceneContext->TouchNode(*pSceneNode);

					// Emit event
					EventSceneNode.Emit(*this, *pSceneNode);
					if (m_nFlags & StopQuery)
						return false; // Stop the query right now

					// Continue recursive?
					if (m_nFlags & Recursive) {
						// Is this a container and is recursion allowed?
						if (pSceneNode->IsContainer() && !(pSceneNode->GetFlags() & SceneContainer::NoRecursion)) {
							// Backup current point
							const Vector3 vPoint = m_vPoint;

							// Transform the point into container space
							m_vPoint *= pSceneNode->GetTransform().GetInverseMatrix();

							// Container recursion
							const bool bContinue = PerformQueryRec(((SceneContainer*)pSceneNode)->GetHierarchyInstance()->GetRootNode());

							// Restore point
							m_vPoint = vPoint;

							// Stop the query right now?
							if (!bContinue)
								return false;

						// Is this a cell-portal?
						} else if (pSceneNode->IsPortal() && pSceneNode->IsInstanceOf("PLScene::SNCellPortal") && !(pSceneNode->GetFlags() & SNCellPortal::NoPassThrough)) {
							// Get the target cell
							SNCellPortal   &cCellPortal	= (SNCellPortal&)*pSceneNode;
							SceneContainer *pCell		= (SceneContainer*)cCellPortal.GetTargetCellInstance();
							if (pCell && pCell != pSceneNode->GetContainer()) {
								// Backup current point
								const Vector3 vPoint = m_vPoint;

								// Transform the point into container space
								m_vPoint *= cCellPortal.GetWarpMatrix();

								// Container recursion
								const bool bContinue = PerformQueryRec(pCell->GetHierarchyInstance()->GetRootNode());

								// Restore point
								m_vPoint = vPoint;

								// Stop the query right now?
								if (!bContinue)
									return false;
							}
						}
					}
				}
			}

			// Next item, please
			pItem = pItem->GetNextItem();
		}
	}

	// Check all sub-hierarchies
	for (uint32 i=0; i<cHierarchyNode.GetNumOfNodes(); i++) {
		if (!PerformQueryRec(*cHierarchyNode.GetNode(i)))
			return false; // Stop the query right now
	}

	// Done, continue the query
	return true;
}


//[-------------------------------------------------------]
//[ Public virtual SceneQuery functions                   ]
//[-------------------------------------------------------]
bool SQPoint::PerformQuery()
{
	// Get the hierarchy we are working on
	const SceneHierarchy *pHierarchy = GetSceneContainer().GetHierarchyInstance();
	if (!pHierarchy)
		return true; // Error, but not cancelled by the user

	// Perform the query recursive...
	m_nFlags &= ~StopQuery;

	// ... get the scene context
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		pSceneContext->StartProcess();
		const bool bResult = PerformQueryRec(pHierarchy->GetRootNode());
		pSceneContext->EndProcess();

		// Done
		return bResult;
	} else {
		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
