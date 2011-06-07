/*********************************************************\
 *  File: SNMPhysicsBodyEllipsoid.cpp                    *
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
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/FixedFunctions.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLMesh/MeshManager.h>
#include <PLScene/Scene/SceneContext.h>
#include <PLScene/Visibility/VisNode.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/World.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBodyEllipsoid.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLMesh;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsBodyEllipsoid)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
const Vector3 &SNMPhysicsBodyEllipsoid::GetRadius() const
{
	return m_vRadius;
}

void SNMPhysicsBodyEllipsoid::SetRadius(const Vector3 &vValue)
{
	if (m_vRadius != vValue) {
		m_vRadius = vValue;
		RecreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsBodyEllipsoid::SNMPhysicsBodyEllipsoid(SceneNode &cSceneNode) : SNMPhysicsBody(cSceneNode),
	Radius(this),
	SlotNotifyDrawDebug(this),
	m_vRadius(0.0f, 0.0f, 0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsBodyEllipsoid::~SNMPhysicsBodyEllipsoid()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called on scene node debug draw
*/
void SNMPhysicsBodyEllipsoid::NotifyDrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Is there a PL physics body?
	const Body *pBody = GetBody();
	if (pBody) {
		// Create the sphere mesh if required
		static MeshHandler cMeshHandler;
		if (!cMeshHandler.GetMesh())
			cMeshHandler.SetMesh(GetSceneNode().GetSceneContext()->GetMeshManager().CreateMesh("PLMesh::MeshCreatorSphere", true, "Radius=1 Detail=26"));
		if (cMeshHandler.GetMesh()) {
			// Fixed functions support required
			FixedFunctions *pFixedFunctions = cRenderer.GetFixedFunctions();
			if (pFixedFunctions) {
				// Get the scene node
				const SceneNode &cSceneNode = GetSceneNode();

				// Set world matrix
				Matrix3x4 mWorld = pVisNode->GetWorldMatrix();
				mWorld.SetTranslation(mWorld.GetTranslation() + cSceneNode.GetTransform().GetRotation()*m_vPositionOffset);
				Matrix3x4 mScale;
				mScale.SetScaleMatrix((1.0f/cSceneNode.GetTransform().GetScale().x)*m_vRadius.x,
									  (1.0f/cSceneNode.GetTransform().GetScale().y)*m_vRadius.y,
									  (1.0f/cSceneNode.GetTransform().GetScale().z)*m_vRadius.z);
				mWorld *= mScale;
				pFixedFunctions->SetTransformState(FixedFunctions::Transform::World, mWorld);

				// Setup render states
				cRenderer.GetRendererContext().GetEffectManager().Use();
				cRenderer.SetRenderState(RenderState::BlendEnable,  true);
				cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
				cRenderer.SetRenderState(RenderState::ZEnable,      false);
				pFixedFunctions->SetColor(Color4(1.0f, 0.5f, 0.5f, 0.5f));

				// Draw transparent
				cMeshHandler.Draw(false, false);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNodeModifier functions  ]
//[-------------------------------------------------------]
void SNMPhysicsBodyEllipsoid::OnActivate(bool bActivate)
{
	// Call base implementation
	SNMPhysicsBody::OnActivate(bActivate);

	// Connect/disconnect event handler
	if (bActivate)
		GetSceneNode().SignalDrawDebug.Connect(&SlotNotifyDrawDebug);
	else
		GetSceneNode().SignalDrawDebug.Disconnect(&SlotNotifyDrawDebug);
}


//[-------------------------------------------------------]
//[ Private virtual SNMPhysicsBody functions              ]
//[-------------------------------------------------------]
void SNMPhysicsBodyEllipsoid::CreatePhysicsBody()
{
	if (m_pWorldContainer && m_pWorldContainer->GetWorld()) {
		// Use a ellipsoid 'inside' the axis align bounding box in 'scene node space' as default?
		if (m_vRadius.IsNull()) {
			const Vector3 &vScale = GetSceneNode().GetTransform().GetScale();
			AABoundingBox cAABB = GetSceneNode().GetAABoundingBox();
			cAABB.vMin *= vScale;
			cAABB.vMax *= vScale;
			m_vRadius.SetXYZ(cAABB.GetWidth()*0.5f, cAABB.GetHeight()*0.5f, cAABB.GetDepth()*0.5f);
			m_vPositionOffset = cAABB.GetCenter();
		}

		// Create the PL physics body
		m_pBodyHandler->SetElement(m_pWorldContainer->GetWorld()->CreateBodyEllipsoid(m_vRadius, !m_fMass));

		// Call base implementation
		SNMPhysicsBody::CreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
