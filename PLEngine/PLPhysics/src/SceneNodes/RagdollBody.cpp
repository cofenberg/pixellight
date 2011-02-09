/*********************************************************\
 *  File: RagdollBody.cpp                                *
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
#include <PLMath/Matrix3x4.h>
#include <PLMath/Matrix4x4.h>
#include <PLRenderer/Renderer/Renderer.h>
#include <PLRenderer/Renderer/DrawHelpers.h>
#include <PLScene/Visibility/VisNode.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/World.h"
#include "PLPhysics/ElementHandler.h"
#include "PLPhysics/SceneNodes/SNRagdoll.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodes/RagdollBody.h"


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
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RagdollBody::RagdollBody(SNRagdoll *pParent) :
	bEnabled(true),
	fMass(0.1f),
	m_pParentRagdoll(pParent),
	m_pBodyHandler(new ElementHandler())
{
}

/**
*  @brief
*    Destructor
*/
RagdollBody::~RagdollBody()
{
	DestroyPhysicsBody();
	delete m_pBodyHandler;
}

/**
*  @brief
*    Returns the PL physics body
*/
Body *RagdollBody::GetBody() const
{
	return static_cast<Body*>(m_pBodyHandler->GetElement());
}

/**
*  @brief
*    Sets the name of the body
*/
bool RagdollBody::SetName(const String &sName)
{
	// Is this the current name?
	if (this->sName != sName) {
		// Is there a parent ragdoll and is this body name already used within the ragdoll?
		if (!m_pParentRagdoll || m_pParentRagdoll->m_mapBodies.Get(sName))
			return false; // Error!

		// Set the new name
		m_pParentRagdoll->m_mapBodies.Remove(this->sName);
		this->sName = sName;
		m_pParentRagdoll->m_mapBodies.Add(this->sName, this);
	}

	// Done
	return true;
}

/**
*  @brief
*    Draws the physics body
*/
void RagdollBody::Draw(Renderer &cRenderer, const Color4 &cColor, const VisNode &cVisNode) const
{
	// Calculate the world view projection matrix
	Matrix3x4 mTrans;
	GetTransformMatrix(mTrans);
	const Matrix4x4 mWorldViewProjection = cVisNode.GetViewProjectionMatrix()*mTrans;

	// Draw
	const Vector3 &vNodeScale = m_pParentRagdoll->GetTransform().GetScale();
	const Vector3  vRealSize  = vSize*vNodeScale;
	cRenderer.GetDrawHelpers().DrawBox(cColor,
									   Vector3(-vRealSize.x*0.5f, -vRealSize.y*0.5f, -vRealSize.z*0.5f),
									   Vector3( vRealSize.x*0.5f,  vRealSize.y*0.5f,  vRealSize.z*0.5f),
									   mWorldViewProjection, 0.0f);
}

/**
*  @brief
*    Creates the physics body
*/
void RagdollBody::CreatePhysicsBody()
{
	// Is there a parent ragdoll?
	if (m_pParentRagdoll) {
		// Destroy the old physics body
		DestroyPhysicsBody();

		// Create the PL physics body
		SCPhysicsWorld *pWorldContainer = m_pParentRagdoll->GetWorldContainer();
		if (pWorldContainer && pWorldContainer->GetWorld()) {
			const Vector3    &vNodePosition = m_pParentRagdoll->GetTransform().GetPosition();
			const Quaternion &qNodeRotation = m_pParentRagdoll->GetTransform().GetRotation();
			const Vector3    &vNodeScale    = m_pParentRagdoll->GetTransform().GetScale();
			const Vector3	  vRealSize		= vSize*vNodeScale;
			Body *pBody = pWorldContainer->GetWorld()->CreateBodyBox(vRealSize);
			if (pBody) {
				m_pBodyHandler->SetElement(pBody);

				// Setup body
				pBody->SetMass(fMass);
				pBody->SetPosition(qNodeRotation*(vPos*vNodeScale) + vNodePosition);
				pBody->SetRotation(qNodeRotation*qRot);
			}
		}
	}
}

/**
*  @brief
*    Destroys the physics body
*/
void RagdollBody::DestroyPhysicsBody()
{
	if (m_pBodyHandler->GetElement())
		delete m_pBodyHandler->GetElement();
}

/**
*  @brief
*    Returns the current rotation of the physics body
*/
void RagdollBody::GetRotation(Quaternion &qQ) const
{
	const Body *pBody = static_cast<const Body*>(m_pBodyHandler->GetElement());
	if (pBody)
		pBody->GetRotation(qQ);
}

/**
*  @brief
*    Returns the current transform matrix of the physics body
*/
void RagdollBody::GetTransformMatrix(Matrix3x4 &mTrans) const
{
	const Body *pBody = static_cast<const Body*>(m_pBodyHandler->GetElement());
	if (pBody) {
		Quaternion qQ;
		pBody->GetRotation(qQ);

		Vector3 vPos;
		pBody->GetPosition(vPos);

		mTrans.FromQuatTrans(qQ, vPos);
	}
}

/**
*  @brief
*    Adds a force to the body
*/
void RagdollBody::AddForce(const Vector3 &vForce)
{
	// Nothing do to in here
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
