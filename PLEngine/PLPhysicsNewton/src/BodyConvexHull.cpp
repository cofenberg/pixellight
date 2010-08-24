/*********************************************************\
 *  File: BodyConvexHull.cpp                             *
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
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLMesh/Mesh.h>
#include <PLMesh/MeshManager.h>
#include <PLMesh/MeshLODLevel.h>
#include <PLMesh/MeshMorphTarget.h>
#include "PLPhysicsNewton/BodyImpl.h"
#include "PLPhysicsNewton/World.h"
#include "PLPhysicsNewton/BodyConvexHull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLPhysicsNewton {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
BodyConvexHull::~BodyConvexHull()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
BodyConvexHull::BodyConvexHull(PLPhysics::World &cWorld, MeshManager &cMeshManager, const String &sMesh, const Vector3 &vMeshScale) :
	PLPhysics::BodyConvexHull(cWorld, ((World&)cWorld).CreateBodyImpl(), sMesh, vMeshScale)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = ((World&)cWorld).GetNewtonWorld();

	// First at all: IS there already a collision convex hull with this name and scale?
	const String sMeshScale = m_sMesh + String::Format("_%g_%g_%g", vMeshScale.x, vMeshScale.y, vMeshScale.z);
	Newton::NewtonCollision *pCollision = ((World&)cWorld).GetCollisionConvexHullMap().Get(sMeshScale);

	// If not, create it NOW
	if (!pCollision) {
		// Get mesh data
		MeshHandler *pMeshHandler = new MeshHandler();
		pMeshHandler->SetMesh(cMeshManager.LoadMesh(m_sMesh));
		const Mesh *pMesh = pMeshHandler->GetResource();
		if (pMesh && pMesh->GetMorphTarget() && pMesh->GetMorphTarget()->GetVertexBuffer()) {
			VertexBuffer *pVertexBuffer = pMesh->GetMorphTarget()->GetVertexBuffer();

			// Setup tree collision
			static const float fTolerance = 0.01f; // (setting from Newton SDK samples)
			if (pVertexBuffer->Lock(Lock::ReadOnly)) {
				if (m_vMeshScale == Vector3::One) { // We can take the orginal vertex data
					pCollision = NewtonCreateConvexHull(pNewtonWorld, pVertexBuffer->GetNumOfElements(),
														(float*)pVertexBuffer->GetData(0, VertexBuffer::Position),
														pVertexBuffer->GetVertexSize(), fTolerance, 0, NULL);
				} else { // We have to use own scaled vertex data
					float *fVertices = new float[3*pVertexBuffer->GetNumOfElements()];
					float *fVertex = fVertices;

					// Fill our scaled vertex data
					for (uint32 i=0; i<pVertexBuffer->GetNumOfElements(); i++) {
						const float *fVertexT = (const float*)pVertexBuffer->GetData(i, VertexBuffer::Position);
						fVertex[Vector3::X] = fVertexT[Vector3::X]*m_vMeshScale.x;
						fVertex[Vector3::Y] = fVertexT[Vector3::Y]*m_vMeshScale.y;
						fVertex[Vector3::Z] = fVertexT[Vector3::Z]*m_vMeshScale.z;
						fVertex += 3;
					}

					// Create the convex hull
					pCollision = NewtonCreateConvexHull(pNewtonWorld, pVertexBuffer->GetNumOfElements(),
														fVertices, sizeof(float)*3, fTolerance, 0, NULL);

					// Cleanup
					delete [] fVertices;
				}

				// Unlock the vertex buffer
				pVertexBuffer->Unlock();
			}

			// Add to convex hull collision map
			if (pCollision)
				((World&)cWorld).GetCollisionConvexHullMap().Add(sMeshScale, pCollision);
		}

		// Cleanup
		delete pMeshHandler;
	}

	// Create the rigid body
	if (pCollision) {
		Newton::NewtonBody *pNewtonBody = NewtonCreateBody(pNewtonWorld, pCollision);

		// Initialize the Newton physics body
		((BodyImpl&)GetBodyImpl()).InitializeNewtonBody(*this, *pNewtonBody, 0.0f);
	}

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysicsNewton
