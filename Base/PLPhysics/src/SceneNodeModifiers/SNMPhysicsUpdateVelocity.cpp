/*********************************************************\
 *  File: SNMPhysicsUpdateVelocity.cpp                   *
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
#include <PLMath/EulerAngles.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsUpdateVelocity.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsUpdateVelocity)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsUpdateVelocity::SNMPhysicsUpdateVelocity(SceneNode &cSceneNode) : SNMPhysics(cSceneNode),
	EventHandlerPosition(&SNMPhysicsUpdateVelocity::OnPosition, this),
	EventHandlerRotation(&SNMPhysicsUpdateVelocity::OnRotation, this),
	m_bPreviousPosition(false),
	m_bPreviousRotation(false)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsUpdateVelocity::~SNMPhysicsUpdateVelocity()
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNodeModifier functions ]
//[-------------------------------------------------------]
void SNMPhysicsUpdateVelocity::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneNode &cSceneNode = GetSceneNode();
	if (bActivate) {
		// Connect event handler
		cSceneNode.GetTransform().EventPosition.Connect(EventHandlerPosition);
		cSceneNode.GetTransform().EventRotation.Connect(EventHandlerRotation);
	} else {
		// Disconnect event handler
		cSceneNode.GetTransform().EventPosition.Disconnect(EventHandlerPosition);
		cSceneNode.GetTransform().EventRotation.Disconnect(EventHandlerRotation);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node position changed
*/
void SNMPhysicsUpdateVelocity::OnPosition()
{
	// Get the scene node
	const SceneNode &cSceneNode = GetSceneNode();

	// Is there a previous scene node position?
	if (m_bPreviousPosition) {
		// Get the time difference between the previous and the current frame
		const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

		// Calculate the difference between the previous and the current scene node position
		const Vector3 vPositionDifference = cSceneNode.GetTransform().GetPosition() - m_vPreviousPosition;

		// Calculate the current linear velocity of the scene node
		const Vector3 vVelocity = vPositionDifference*(1/fTimeDiff);

		// Get the number of physics body scene node modifiers
		static const String sSNMPhysicsBody = "PLPhysics::SNMPhysicsBody";
		const uint32 nNumOfModifiers = cSceneNode.GetNumOfModifiers(sSNMPhysicsBody);

		// Loop through all scene node modifiers and update the velocities of all static physics bodies
		for (uint32 i=0; i<nNumOfModifiers; i++) {
			// Get the physics body scene node modifier
			const SNMPhysicsBody *pSNMPhysicsBody = static_cast<SNMPhysicsBody*>(cSceneNode.GetModifier(sSNMPhysicsBody, i));
			if (pSNMPhysicsBody) {
				// Get the physics body, mass of 0 = static body
				Body *pBody = pSNMPhysicsBody->GetBody();
				if (pBody && pBody->GetMass() == 0.0f) {
					// Set the current linear velocity of the physics body
					pBody->SetLinearVelocity(vVelocity);
				}
			}
		}

		// Update the previous scene node position
		m_vPreviousPosition = cSceneNode.GetTransform().GetPosition();
	} else {
		// We now have a previous scene node position
		m_bPreviousPosition = true;
		m_vPreviousPosition = cSceneNode.GetTransform().GetPosition();
	}
}

/**
*  @brief
*    Called when the scene node rotation changed
*/
void SNMPhysicsUpdateVelocity::OnRotation()
{
	// Get the scene node
	const SceneNode &cSceneNode = GetSceneNode();

	// Is there a previous scene node rotation?
	if (m_bPreviousRotation) {
		// Get the time difference between the previous and the current frame
		const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

		// Calculate the difference between the previous and the current scene node rotation
		const Quaternion qRotationDifference = cSceneNode.GetTransform().GetRotation()*m_qPreviousRotation.GetInverted();

		// Calculate the current angular velocity of the scene node
		Vector3 vVelocity;
		EulerAngles::FromQuaternion(qRotationDifference, vVelocity.x, vVelocity.y, vVelocity.z);
		vVelocity *= (1/fTimeDiff);

		// Get the number of physics body scene node modifiers
		static const String sSNMPhysicsBody = "PLPhysics::SNMPhysicsBody";
		const uint32 nNumOfModifiers = cSceneNode.GetNumOfModifiers(sSNMPhysicsBody);

		// Loop through all scene node modifiers and update the velocities of all static physics bodies
		for (uint32 i=0; i<nNumOfModifiers; i++) {
			// Get the physics body scene node modifier
			const SNMPhysicsBody *pSNMPhysicsBody = static_cast<SNMPhysicsBody*>(cSceneNode.GetModifier(sSNMPhysicsBody, i));
			if (pSNMPhysicsBody) {
				// Get the physics body, mass of 0 = static body
				Body *pBody = pSNMPhysicsBody->GetBody();
				if (pBody && pBody->GetMass() == 0.0f) {
					// Set the current angular velocity of the physics body
					pBody->SetAngularVelocity(vVelocity);
				}
			}
		}

		// Update the previous scene node rotation
		m_qPreviousRotation = cSceneNode.GetTransform().GetRotation();
	} else {
		// We now have a previous scene node rotation
		m_bPreviousRotation = true;
		m_qPreviousRotation = cSceneNode.GetTransform().GetRotation();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
