/*********************************************************\
 *  File: SQAABoundingBox.cpp                            *
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
#include <PLMath/Intersect.h>
#include "PLScene/Scene/SNCellPortal.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneContainer.h"
#include "PLScene/Scene/SceneHierarchy.h"
#include "PLScene/Scene/SceneHierarchyNode.h"
#include "PLScene/Scene/SceneHierarchyNodeItem.h"
#include "PLScene/Scene/SceneQueries/SQAABoundingBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SQAABoundingBox)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SQAABoundingBox::SQAABoundingBox()
{
}

/**
*  @brief
*    Destructor
*/
SQAABoundingBox::~SQAABoundingBox()
{
}

/**
*  @brief
*    Returns the used axis aligned bounding box
*/
AABoundingBox &SQAABoundingBox::GetAABoundingBox()
{
	return m_cAABoundingBox;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Recursive part of PerformQuery()
*/
bool SQAABoundingBox::PerformQueryRec(SceneHierarchyNode &cHierarchyNode)
{
	// Is this scene hierarchy node intersecting the axis aligned bounding box?
	if (!Intersect::AABoxAABox(cHierarchyNode.GetAABoundingBox(), m_cAABoundingBox))
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
				if (Intersect::AABoxAABox(pSceneNode->GetContainerAABoundingBox(), m_cAABoundingBox)) {
					// Touch the node
					pSceneContext->TouchNode(*pSceneNode);

					// Emit signal
					SignalSceneNode(*this, *pSceneNode);
					if (m_nFlags & StopQuery)
						return false; // Stop the query right now

					// Continue recursive?
					if (m_nFlags & Recursive) {
						// Is this a container and is recursion allowed?
						if (pSceneNode->IsContainer() && !(pSceneNode->GetFlags() & SceneContainer::NoRecursion)) {
							// Backup current axis aligned bounding box
							const AABoundingBox cAABoundingBox = m_cAABoundingBox;

							// Transform the axis aligned bounding box into container space
							const Vector3 &vMin = cAABoundingBox.vMin, &vMax = cAABoundingBox.vMax;
							const Matrix3x4 &mTrans = pSceneNode->GetTransform().GetInverseMatrix();
							// Transform ALL eight corners bounding box corners into 'scene container space'
							// and get min/max values of the 'scene container space' bounding box
							Vector3 vT = vMin;
							vT *= mTrans;
							m_cAABoundingBox.vMin = m_cAABoundingBox.vMax = vT;
							vT.SetXYZ(vMax.x, vMin.y, vMin.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);
							vT.SetXYZ(vMax.x, vMax.y, vMin.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);
							vT.SetXYZ(vMin.x, vMax.y, vMin.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);
							vT.SetXYZ(vMin.x, vMin.y, vMax.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);
							vT.SetXYZ(vMax.x, vMin.y, vMax.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);
							vT.SetXYZ(vMax.x, vMax.y, vMax.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);
							vT.SetXYZ(vMin.x, vMax.y, vMax.z);
							vT *= mTrans;
							m_cAABoundingBox.AppendToCubicHull(vT);

							// Container recursion
							const bool bContinue = PerformQueryRec(static_cast<SceneContainer*>(pSceneNode)->GetHierarchyInstance()->GetRootNode());

							// Restore axis aligned bounding box
							m_cAABoundingBox = cAABoundingBox;

							// Stop the query right now?
							if (!bContinue)
								return false;

						// Is this a cell-portal?
						} else if (pSceneNode->IsPortal() && pSceneNode->IsInstanceOf("PLScene::SNCellPortal") && !(pSceneNode->GetFlags() & SNCellPortal::NoPassThrough)) {
							// Get the target cell
							SNCellPortal   &cCellPortal	= static_cast<SNCellPortal&>(*pSceneNode);
							SceneContainer *pCell		= reinterpret_cast<SceneContainer*>(cCellPortal.GetTargetCellInstance());
							if (pCell && pCell != pSceneNode->GetContainer()) {
								// Backup current axis aligned bounding box
								const AABoundingBox cAABoundingBox = m_cAABoundingBox;

								// Transform the axis aligned bounding box into container space
								const Vector3 &vMin = cAABoundingBox.vMin, &vMax = cAABoundingBox.vMax;
								const Matrix3x4 &mTrans = cCellPortal.GetWarpMatrix();
								// Transform ALL eight corners bounding box corners into 'scene container space'
								// and get min/max values of the 'scene container space' bounding box
								Vector3 vT = vMin;
								vT *= mTrans;
								m_cAABoundingBox.vMin = m_cAABoundingBox.vMax = vT;
								vT.SetXYZ(vMax.x, vMin.y, vMin.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);
								vT.SetXYZ(vMax.x, vMax.y, vMin.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);
								vT.SetXYZ(vMin.x, vMax.y, vMin.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);
								vT.SetXYZ(vMin.x, vMin.y, vMax.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);
								vT.SetXYZ(vMax.x, vMin.y, vMax.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);
								vT.SetXYZ(vMax.x, vMax.y, vMax.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);
								vT.SetXYZ(vMin.x, vMax.y, vMax.z);
								vT *= mTrans;
								m_cAABoundingBox.AppendToCubicHull(vT);

								// Container recursion
								const bool bContinue = PerformQueryRec(pCell->GetHierarchyInstance()->GetRootNode());

								// Restore axis aligned bounding box
								m_cAABoundingBox = cAABoundingBox;

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
bool SQAABoundingBox::PerformQuery()
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
