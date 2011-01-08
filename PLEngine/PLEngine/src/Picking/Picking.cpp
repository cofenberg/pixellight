/*********************************************************\
 *  File: Picking.cpp                                    *
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
#include <PLMesh/MeshHandler.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLScene/Scene/SceneContainer.h>
#include <PLScene/Scene/SceneQueries/SQLine.h>
#include "PLEngine/Picking/PickingResult.h"
#include "PLEngine/Picking/Picking.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLMesh;
using namespace PLScene;
namespace PLEngine {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Picking::Picking() :
	EventSceneNode(&Picking::NotifySceneNode, this),
	m_pPickingResult(nullptr)
{
}

/**
*  @brief
*    Destructor
*/
Picking::~Picking()
{
}

/**
*  @brief
*    Performs picking by using the given line start and end positions
*/
bool Picking::PerformPicking(PickingResult &cPickingResult, SceneContainer &cContainer, const Vector3 &vLineStartPos, const Vector3 &vLineEndPos)
{
	// Initialize the picking result
	m_pPickingResult = &cPickingResult;
	cPickingResult.m_pSceneNode				 = nullptr;
	cPickingResult.m_nGeometry				 = 0;
	cPickingResult.m_nTriangle				 = 0;
	cPickingResult.m_vPoint					 = Vector3::Zero;
	cPickingResult.m_pSceneContainer		 = &cContainer;
	cPickingResult.m_vLineStartPos			 = vLineStartPos;
	cPickingResult.m_fNearestSquaredDistance = -1.0f;

	// Trace line
	SQLine *pQuery = (SQLine*)cContainer.CreateQuery("PLScene::SQLine");
	if (pQuery) {
		pQuery->EventSceneNode.Connect(&EventSceneNode);
		pQuery->GetLine().Set(vLineStartPos, vLineEndPos);
		pQuery->PerformQuery();
		cContainer.DestroyQuery(*pQuery);
	}

	// Was something picked?
	if (cPickingResult.m_pSceneNode) {
		// Ensure that the picking distance is not greater than the possible maximum
		if ((vLineEndPos-vLineStartPos).GetSquaredLength() >= cPickingResult.m_fNearestSquaredDistance)
			return (cPickingResult.m_pSceneNode != nullptr);
	}

	// Nothing (in range) was picked
	return false;
}

/**
*  @brief
*    Performs picking using the mesh of the given scene node by using the given line start and end positions
*/
bool Picking::PerformPicking(PickingResult &cPickingResult, SceneNode &cSceneNode, const Vector3 &vLineStartPos, const Vector3 &vLineEndPos,
							 Array<uint32> *plstGeometries)
{
	// Initialize the picking result
	m_pPickingResult = &cPickingResult;
	cPickingResult.m_pSceneNode				 = nullptr;
	cPickingResult.m_nGeometry				 = 0;
	cPickingResult.m_nTriangle				 = 0;
	cPickingResult.m_vPoint					 = Vector3::Zero;
	cPickingResult.m_pSceneContainer		 = nullptr;
	cPickingResult.m_vLineStartPos			 = vLineStartPos;
	cPickingResult.m_fNearestSquaredDistance = -1.0f;

	// Perform mesh intersection
	MeshIntersection(cSceneNode, vLineStartPos, vLineEndPos, plstGeometries);

	// Ensure that the picking distance is not greater than the possible maximum
	if ((vLineEndPos-vLineStartPos).GetSquaredLength() >= cPickingResult.m_fNearestSquaredDistance)
		return (cPickingResult.m_pSceneNode != nullptr);

	// Nothing (in range) was picked
	return false;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a scene node was found
*/
void Picking::NotifySceneNode(SceneQuery &cQuery, SceneNode &cSceneNode)
{
	// First at all, call the picking filter function
	if (m_pPickingResult->m_pSceneContainer && OnPickingCandidate(cSceneNode) && cSceneNode.GetMeshHandler()) {
		// We KNOW that it's a SQLine!
		SQLine &cLineQuery = (SQLine&)cQuery;

		// Get line start/end position in node space
		const Vector3 vLineStartPos = cSceneNode.GetTransform().GetInverseMatrix()*cLineQuery.GetLine().vStart;
		const Vector3 vLineEndPos   = cSceneNode.GetTransform().GetInverseMatrix()*cLineQuery.GetLine().vEnd;

		// Perform mesh intersection
		MeshIntersection(cSceneNode, vLineStartPos, vLineEndPos, nullptr);
	}
}

/**
*  @brief
*    Perform mesh intersection
*/
void Picking::MeshIntersection(SceneNode &cSceneNode, const Vector3 &vLineStartPos, const Vector3 &vLineEndPos,
							   Array<uint32> *plstGeometries)
{
	// First of all, check the intersection distance against the axis aligned bounding box of the scene node
	float fIntersection;
	const AABoundingBox &cAABoundngBox = cSceneNode.GetAABoundingBox();
	if (Intersect::AABoxLine(cAABoundngBox.vMin, cAABoundngBox.vMax, vLineStartPos, vLineEndPos, &fIntersection) &&
		fIntersection >= 0.0f) {
		// Before we perform the expensive triangle intersection test we check the found axis aligned bounding box
		// intersection distance agains the current nearest intersection distance... maybe we're in luck and can
		// skip further tests if we detect that no triangle inside the box can be nearer than the current nearest
		// distance...

		// Get intersection point in node space
		Vector3 vIntersectionPos = vLineStartPos + (vLineEndPos-vLineStartPos).Normalize()*fIntersection;

		// Transform intersection point into container space
		vIntersectionPos *= cSceneNode.GetTransform().GetMatrix();

		// Bring the intersection point into the same container space the original line start position is in
		Matrix3x4 matTransform;
		if (cSceneNode.GetContainer() && m_pPickingResult->m_pSceneContainer)
			cSceneNode.GetContainer()->GetTransformMatrixTo(*m_pPickingResult->m_pSceneContainer, matTransform);
		vIntersectionPos *= matTransform;

		// Now, test!
		if (m_pPickingResult->m_fNearestSquaredDistance < 0.0f ||
			(m_pPickingResult->m_vLineStartPos-vIntersectionPos).GetSquaredLength() < m_pPickingResult->m_fNearestSquaredDistance) {
			// Get the mesh handler of the scene node
			MeshHandler *pMeshHandler = cSceneNode.GetMeshHandler();
			if (pMeshHandler) {
				// We ran out of possible early escape tests... now find intersection triangle - this may be quite slow...
				Vector3 vCollisionPoint;
				uint32 nTriangle, nGeometry;
				if (pMeshHandler->FindTriangle(vLineStartPos, vLineEndPos, nTriangle, &nGeometry, &vCollisionPoint, plstGeometries)) {
					// Backup the node space collision point
					const Vector3 vNodeSpaceCollisionPoint = vCollisionPoint;

					// Transform collision point into container space
					vCollisionPoint *= cSceneNode.GetTransform().GetMatrix();

					// Bring the collision point into the same container space the original line start position is in
					vCollisionPoint *= matTransform;

					// Calculate the squared distance between the two positions (that are now within the same vector space)
					const float fSquaredDistance = (m_pPickingResult->m_vLineStartPos-vCollisionPoint).GetSquaredLength();

					// Is this collision point nearer?
					if (m_pPickingResult->m_fNearestSquaredDistance < 0.0f || m_pPickingResult->m_fNearestSquaredDistance > fSquaredDistance) {
						m_pPickingResult->m_pSceneNode				= &cSceneNode;
						m_pPickingResult->m_nGeometry				= nGeometry;
						m_pPickingResult->m_nTriangle				= nTriangle;
						m_pPickingResult->m_vPoint					= vNodeSpaceCollisionPoint;
						m_pPickingResult->m_fNearestSquaredDistance = fSquaredDistance;
					}
				}
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual Picking functions                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called when a picking candidate has been found ("picking filter function")
*/
bool Picking::OnPickingCandidate(SceneNode &cSceneNode)
{
	// Nothing to do by default - just pass through the scene node candidate
	return true;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine
