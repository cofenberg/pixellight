/*********************************************************\
 *  File: SNMMeshUpdate.cpp                              *
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
#include <PLGeneral/Tools/Timing.h>
#include <PLRenderer/Renderer/VertexBuffer.h>
#include <PLMesh/MeshHandler.h>
#include <PLMesh/SkeletonHandler.h>
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMMeshUpdate.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLRenderer;
using namespace PLMesh;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMMeshUpdate)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMMeshUpdate::SNMMeshUpdate(SceneNode &cSceneNode) : SNMMesh(cSceneNode),
	Flags(this),
	EventHandlerAddedToVisibilityTree(&SNMMeshUpdate::OnAddedToVisibilityTree, this),
	EventHandlerUpdate(&SNMMeshUpdate::OnUpdate, this),
	m_bUpdate(true),	// Should be true so for example a valid bounding box, used for visibility detection, is calculated
	m_bFirstUpdate(true)
{
}

/**
*  @brief
*    Destructor
*/
SNMMeshUpdate::~SNMMeshUpdate()
{
}


//[-------------------------------------------------------]
//[ Protected virtual SceneNodeModifier functions         ]
//[-------------------------------------------------------]
void SNMMeshUpdate::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate) {
			GetSceneNode().SignalAddedToVisibilityTree.Connect(&EventHandlerAddedToVisibilityTree);
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		} else {
			GetSceneNode().SignalAddedToVisibilityTree.Disconnect(&EventHandlerAddedToVisibilityTree);
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the owner scene node was added to a visibility tree
*/
void SNMMeshUpdate::OnAddedToVisibilityTree(VisNode &cVisNode)
{
	m_bUpdate = true;
}

/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMMeshUpdate::OnUpdate()
{
	// If this scene node wasn't drawn at the last frame, we can skip some update stuff
	MeshHandler *pMeshHandler = GetSceneNode().GetMeshHandler();
	if (pMeshHandler && (m_bUpdate || (GetFlags() & UpdateUnseen))) {
		m_bUpdate = false;

		// Do we need a frequent bounding box update?
		const bool bJointAABoundingBox = (pMeshHandler->GetVertexBuffer() && pMeshHandler->GetSkeletonHandler());

		// Lock the vertex buffer once to avoid many internal locks...
		if (bJointAABoundingBox)
			pMeshHandler->GetVertexBuffer()->Lock(Lock::ReadWrite);

		// Update mesh handler
		pMeshHandler->Update(Timing::GetInstance()->GetTimeDifference());

		if (bJointAABoundingBox) {
			if (m_bFirstUpdate) {
				m_bFirstUpdate = false;

				// Set default mesh axis align bounding box
				m_cDefaultMeshAABoundingBox = GetSceneNode().GetAABoundingBox();

				// Set default joint axis align bounding box
				pMeshHandler->CalculateJointBoundingBox(m_cDefaultJointAABoundingBox);
			}

			// Unlock the vertex buffer
			pMeshHandler->GetVertexBuffer()->Unlock();

			// Get current joint axis align bounding box
			AABoundingBox cJointBB;
			pMeshHandler->CalculateJointBoundingBox(cJointBB);

			// Update the bounding box of the scene node
			// [TODO] Remove 'm_cDefaultMeshAABoundingBox'
			GetSceneNode().SetAABoundingBox(cJointBB);
//			SetAABoundingBox(AABoundingBox(m_cDefaultMeshAABoundingBox.vMin + (cJointBB.vMin - m_cDefaultJointAABoundingBox.vMin),
//										   m_cDefaultMeshAABoundingBox.vMax + (cJointBB.vMax - m_cDefaultJointAABoundingBox.vMax)));
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
