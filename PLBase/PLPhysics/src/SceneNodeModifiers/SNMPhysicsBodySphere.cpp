/*********************************************************\
 *  File: SNMPhysicsBodySphere.cpp                       *
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
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBodySphere.h"


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
pl_implement_class(SNMPhysicsBodySphere)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
float SNMPhysicsBodySphere::GetRadius() const
{
	return m_fRadius;
}

void SNMPhysicsBodySphere::SetRadius(float fValue)
{
	if (m_fRadius != fValue) {
		m_fRadius = fValue;
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
SNMPhysicsBodySphere::SNMPhysicsBodySphere(SceneNode &cSceneNode) : SNMPhysicsBody(cSceneNode),
	Radius(this),
	SlotOnDrawDebug(this),
	m_fRadius(0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsBodySphere::~SNMPhysicsBodySphere()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called on scene node debug draw
*/
void SNMPhysicsBodySphere::OnDrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
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
				mScale.SetScaleMatrix((1.0f/cSceneNode.GetTransform().GetScale().x)*m_fRadius,
									  (1.0f/cSceneNode.GetTransform().GetScale().y)*m_fRadius,
									  (1.0f/cSceneNode.GetTransform().GetScale().z)*m_fRadius);
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
void SNMPhysicsBodySphere::OnActivate(bool bActivate)
{
	// Call base implementation
	SNMPhysicsBody::OnActivate(bActivate);

	// Connect/disconnect event handler
	if (bActivate)
		GetSceneNode().SignalDrawDebug.Connect(SlotOnDrawDebug);
	else
		GetSceneNode().SignalDrawDebug.Disconnect(SlotOnDrawDebug);
}


//[-------------------------------------------------------]
//[ Private virtual SNMPhysicsBody functions              ]
//[-------------------------------------------------------]
void SNMPhysicsBodySphere::CreatePhysicsBody()
{
	if (m_pWorldContainer && m_pWorldContainer->GetWorld()) {
		// Use a sphere 'inside' the axis align bounding box in 'scene node space' as default?
		if (!m_fRadius) {
			const Vector3 &vScale = GetSceneNode().GetTransform().GetScale();
			AABoundingBox cAABB = GetSceneNode().GetAABoundingBox();
			cAABB.vMin *= vScale;
			cAABB.vMax *= vScale;
			m_fRadius         = cAABB.GetInsideRadius();
			m_vPositionOffset = cAABB.GetCenter();
		}

		// Create the PL physics body
		m_pBodyHandler->SetElement(m_pWorldContainer->GetWorld()->CreateBodySphere(m_fRadius, !m_fMass));

		// Call base implementation
		SNMPhysicsBody::CreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
