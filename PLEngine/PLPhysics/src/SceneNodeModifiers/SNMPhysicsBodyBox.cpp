/*********************************************************\
 *  File: SNMPhysicsBodyBox.cpp                          *
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
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLRenderer/Effect/EffectManager.h>
#include <PLScene/Visibility/VisNode.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/World.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBodyBox.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLGraphics;
using namespace PLRenderer;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsBodyBox)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
const Vector3 &SNMPhysicsBodyBox::GetDimension() const
{
	return m_vDimension;
}

void SNMPhysicsBodyBox::SetDimension(const Vector3 &vValue)
{
	if (m_vDimension != vValue) {
		m_vDimension = vValue;
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
SNMPhysicsBodyBox::SNMPhysicsBodyBox(SceneNode &cSceneNode) : SNMPhysicsBody(cSceneNode),
	Dimension(this),
	SlotNotifyDrawDebug(this),
	m_vDimension(0.0f, 0.0f, 0.0f)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsBodyBox::~SNMPhysicsBodyBox()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called on scene node debug draw
*/
void SNMPhysicsBodyBox::NotifyDrawDebug(Renderer &cRenderer, const VisNode *pVisNode)
{
	// Is there a PL physics body?
	const Body *pBody = GetBody();
	if (pBody && pVisNode) {
		// Get the scene node
		const SceneNode &cSceneNode = GetSceneNode();

		// Calculate the world matrix
		Matrix3x4 mWorld = pVisNode->GetWorldMatrix();
		mWorld.SetTranslation(mWorld.GetTranslation() + cSceneNode.GetTransform().GetRotation()*m_vPositionOffset);
		Matrix3x4 mScale;
		mScale.SetScaleMatrix((1.0f/cSceneNode.GetTransform().GetScale().x)*m_vDimension.x*0.5f,
							  (1.0f/cSceneNode.GetTransform().GetScale().y)*m_vDimension.y*0.5f,
							  (1.0f/cSceneNode.GetTransform().GetScale().z)*m_vDimension.z*0.5f);
		mWorld *= mScale;

		// Calculate the world view projection matrix
		const Matrix4x4 mWorldViewProjection = pVisNode->GetViewProjectionMatrix()*mWorld;

		// Setup render states
		cRenderer.GetRendererContext().GetEffectManager().Use();

		// Draw wireframe
		cRenderer.GetDrawHelpers().DrawBox(Color4::White, Vector3::NegativeOne, Vector3::One, mWorldViewProjection, 1.0f);

		// Setup render states
		cRenderer.SetRenderState(RenderState::BlendEnable,  true);
		cRenderer.SetRenderState(RenderState::ZWriteEnable, false);
		cRenderer.SetRenderState(RenderState::ZEnable,      false);

		// Draw transparent
		cRenderer.GetDrawHelpers().DrawBox(Color4(1.0f, 0.5f, 0.5f, 0.5f), Vector3::NegativeOne, Vector3::One, mWorldViewProjection, 0.0f);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLScene::SceneNodeModifier functions  ]
//[-------------------------------------------------------]
void SNMPhysicsBodyBox::OnActivate(bool bActivate)
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
void SNMPhysicsBodyBox::CreatePhysicsBody()
{
	if (m_pWorldContainer && m_pWorldContainer->GetWorld()) {
		// Use the axis align bounding box in 'scene node space' as default?
		if (m_vDimension.IsNull()) {
			const Vector3 &vScale = GetSceneNode().GetTransform().GetScale();
			AABoundingBox cAABB = GetSceneNode().GetAABoundingBox();
			cAABB.vMin *= vScale;
			cAABB.vMax *= vScale;
			m_vDimension.SetXYZ(cAABB.GetWidth(), cAABB.GetHeight(), cAABB.GetDepth());
			m_vPositionOffset = cAABB.GetCenter();
		}

		// Create the PL physics body
		m_pBodyHandler->SetElement(m_pWorldContainer->GetWorld()->CreateBodyBox(m_vDimension, !m_fMass));

		// Call base implementation
		SNMPhysicsBody::CreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
