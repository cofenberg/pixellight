/*********************************************************\
 *  File: SNMPhysicsBody.cpp                             *
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
#include <PLCore/Container/Stack.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/World.h"
#include "PLPhysics/ElementHandler.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsBody)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
float SNMPhysicsBody::GetMass() const
{
	return m_fMass;
}

void SNMPhysicsBody::SetMass(float fValue)
{
	if (m_fMass != fValue) {
		m_fMass = fValue;

		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody) {
			// Do we need to recreate the physics body now?
			if (pBody->GetWorld().IsAlwaysStatic()) {
				if ((m_fMass && !pBody->GetMass()) || (!m_fMass && pBody->GetMass()))
					RecreatePhysicsBody();
			} else {
				pBody->SetMass(m_fMass);
			}
		}
	}
}

const Vector3 &SNMPhysicsBody::GetCenterOfMass() const
{
	return m_vCenterOfMass;
}

void SNMPhysicsBody::SetCenterOfMass(const Vector3 &vValue)
{
	if (m_vCenterOfMass != vValue) {
		m_vCenterOfMass = vValue;

		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody)
			pBody->SetCenterOfMass(m_vCenterOfMass);
	}
}

const Vector3 &SNMPhysicsBody::GetPositionOffset() const
{
	return m_vPositionOffset;
}

void SNMPhysicsBody::SetPositionOffset(const Vector3 &vValue)
{
	if (m_vPositionOffset != vValue) {
		m_vPositionOffset = vValue;
		OnPosition();
	}
}

uint8 SNMPhysicsBody::GetCollisionGroup() const
{
	return m_nCollisionGroup;
}

void SNMPhysicsBody::SetCollisionGroup(uint8 nValue)
{
	if (m_nCollisionGroup != nValue) {
		m_nCollisionGroup = nValue;

		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody)
			pBody->SetCollisionGroup(m_nCollisionGroup);
	}
}

void SNMPhysicsBody::SetFlags(uint32 nValue)
{
	// Auto freeze state change?
	if ((GetFlags() & NoAutoFreeze) != (nValue & NoAutoFreeze)) {
		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody)
			pBody->SetAutoFreeze(!(nValue & NoAutoFreeze));
	}

	// Gravity usage stage change?
	if ((GetFlags() & NoGravity) != (nValue & NoGravity)) {
		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody)
			pBody->SetUseGravity(!(nValue & NoGravity));
	}

	// Call base implementation
	SNMPhysics::SetFlags(nValue);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the PL physics world scene node container the physics body is in
*/
SCPhysicsWorld *SNMPhysicsBody::GetWorldContainer() const
{
	return m_pWorldContainer;
}

/**
*  @brief
*    Returns the PL physics body
*/
Body *SNMPhysicsBody::GetBody() const
{
	return static_cast<Body*>(m_pBodyHandler->GetElement());
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsBody::SNMPhysicsBody(SceneNode &cSceneNode) : SNMPhysics(cSceneNode),
	Mass(this),
	CenterOfMass(this),
	PositionOffset(this),
	CollisionGroup(this),
	Flags(this),
	SlotOnActive(this),
	SlotOnPosition(this),
	SlotOnRotation(this),
	SlotOnTransform(this),
	m_fMass(0.0f),
	m_nCollisionGroup(0),
	m_pWorldContainer(nullptr),
	m_pBodyHandler(new ElementHandler()),
	m_bListening(true)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsBody::~SNMPhysicsBody()
{
	// Destroy the PL physics body
	if (m_pBodyHandler->GetElement())
		delete m_pBodyHandler->GetElement();
	delete m_pBodyHandler;
}

/**
*  @brief
*    Recreates the PL physics body
*/
void SNMPhysicsBody::RecreatePhysicsBody()
{
	// Destroy the old physics body
	if (m_pBodyHandler->GetElement())
		delete m_pBodyHandler->GetElement();

	// Create the physics body
	CreatePhysicsBody();
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNodeModifier functions ]
//[-------------------------------------------------------]
void SNMPhysicsBody::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneNode &cSceneNode = GetSceneNode();
	if (bActivate) {
		// Connect event handler
		cSceneNode.SignalActive.Connect(SlotOnActive);
		cSceneNode.GetTransform().EventPosition.Connect(SlotOnPosition);
		cSceneNode.GetTransform().EventRotation.Connect(SlotOnRotation);
	} else {
		// Disconnect event handler
		cSceneNode.SignalActive. Disconnect(SlotOnActive);
		cSceneNode.GetTransform().EventPosition.Disconnect(SlotOnPosition);
		cSceneNode.GetTransform().EventRotation.Disconnect(SlotOnRotation);
	}

	// Is there a PL physics body?
	Body *pBody = GetBody();
	if (pBody) {
		// Active state changed?
		if (bActivate != pBody->IsActive()) {
			// Is the physics body now active?
			if (bActivate) {
				// Synchronize the position and rotation of the physics body with the scene node
				OnPosition();
				OnRotation();
			}

			// Set physics body state
			pBody->SetActive(bActivate);
		}
	}
}


//[-------------------------------------------------------]
//[ Protected virtual SNMPhysicsBody functions            ]
//[-------------------------------------------------------]
void SNMPhysicsBody::CreatePhysicsBody()
{
	// Is there a PL physics body?
	Body *pBody = GetBody();
	if (pBody) {
		// Setup body
		pBody->SetMass(m_fMass);
		pBody->SetCenterOfMass(m_vCenterOfMass);
		pBody->SetAutoFreeze(!(GetFlags() & NoAutoFreeze));
		pBody->SetUseGravity(!(GetFlags() & NoGravity));
		pBody->SetCollisionGroup(m_nCollisionGroup);
		OnPosition();
		OnRotation();

		// Unfreeze body by default?
		pBody->SetFrozen(!(GetFlags() & InitUnfrozen));

		// Connect event handler
		pBody->EventTransform.Connect(SlotOnTransform);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node active state changed
*/
void SNMPhysicsBody::OnActive()
{
	// Is there a PL physics body?
	Body *pBody = GetBody();
	if (pBody)
		pBody->SetActive(GetSceneNode().IsActive() && !(GetFlags() & Inactive));
}

/**
*  @brief
*    Called when the scene node position changed
*/
void SNMPhysicsBody::OnPosition()
{
	// Do listening?
	if (m_bListening) {
		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody) {
			// Get the scene node
			const SceneNode &cSceneNode = GetSceneNode();

			// Set the position of the PL physics body. If the physics takes place within another
			// container, we need to transform...
			Vector3 vPosition = cSceneNode.GetTransform().GetPosition();
			if (GetFlags() & NoRotation)
				vPosition += m_vPositionOffset;
			else
				vPosition += cSceneNode.GetTransform().GetRotation()*m_vPositionOffset;
			if (m_pWorldContainer != cSceneNode.GetContainer()) {
				SceneContainer *pContainer = cSceneNode.GetContainer();
				while (m_pWorldContainer != pContainer) {
					// Transform
					vPosition *= pContainer->GetTransform().GetMatrix();

					// Go into the next container, please
					pContainer = pContainer->GetContainer();
				}
			}

			// Set body position
			pBody->SetPosition(vPosition);
		}
	}
}

/**
*  @brief
*    Called when the scene node rotation changed
*/
void SNMPhysicsBody::OnRotation()
{
	// Do listening and use rotation?
	if (m_bListening && !(GetFlags() & NoRotation)) {
		// Is there a PL physics body?
		Body *pBody = GetBody();
		if (pBody) {
			// Get the scene node
			const SceneNode &cSceneNode = GetSceneNode();

			// Set the rotation of the PL physics body. If the physics takes place within another
			// container, we need to transform...
			if (m_pWorldContainer != cSceneNode.GetContainer()) {
				SceneContainer *pContainer = cSceneNode.GetContainer();
				Quaternion qRotation = cSceneNode.GetTransform().GetRotation();
				while (m_pWorldContainer != pContainer) {
					// Transform
					qRotation *= pContainer->GetTransform().GetMatrix();

					// Go into the next container, please
					pContainer = pContainer->GetContainer();
				}
				pBody->SetRotation(qRotation);

			// Else... PHA!, that's quite boring, Dude
			} else {
				pBody->SetRotation(cSceneNode.GetTransform().GetRotation());
			}
		}
	}
}

/**
*  @brief
*    Called when the transform was changed by the physics
*/
void SNMPhysicsBody::OnTransform()
{
	// Is there a PL physics body and is the simulation currently active?
	const Body *pBody = GetBody();
	if (pBody && pBody->GetWorld().IsSimulationActive()) {
		// Stop listening the scene node during setting new scene node states
		m_bListening = false;

		// Get the position of the scene node
		Vector3 vPosition;
		pBody->GetPosition(vPosition);

		// Get the scene node
		SceneNode &cSceneNode = GetSceneNode();

		// If the physics takes place within another container, we need to transform...
		if (cSceneNode.GetContainer() != m_pWorldContainer) {
			// First, create the stack
			SceneContainer *pContainer = cSceneNode.GetContainer();
			Stack<SceneContainer*> lstStack;
			while (m_pWorldContainer != pContainer) {
				// Push the container on the stack
				lstStack.Push(pContainer);

				// Go into the next container, please
				pContainer = pContainer->GetContainer();
			}

			// Use rotation? If yes, set the rotation of the scene node to the rotation of the PL physics body
			if (GetFlags() & NoRotation) {
				// Transform from 'world' into 'container' space...
				while (lstStack.GetNumOfElements()) {
					// Get container
					pContainer = lstStack.Top();
					lstStack.Pop();

					// Transform
					vPosition *= pContainer->GetTransform().GetInverseMatrix();
				}

				// Set position
				vPosition -= m_vPositionOffset;
				cSceneNode.MoveTo(vPosition);
			} else {
				// Transform from 'world' into 'container' space...
				Quaternion qRotation;
				pBody->GetRotation(qRotation);
				while (lstStack.GetNumOfElements()) {
					// Get container
					pContainer = lstStack.Top();
					lstStack.Pop();

					// Transform
					vPosition *= pContainer->GetTransform().GetInverseMatrix();
					qRotation *= pContainer->GetTransform().GetInverseMatrix();
				}

				// Set position and rotation
				vPosition -= qRotation*m_vPositionOffset;
				cSceneNode.MoveTo(vPosition);
				cSceneNode.GetTransform().SetRotation(qRotation);
			}

		// Else... hurray, the easy situation! :)
		} else {
			// Set position
			if (GetFlags() & NoRotation)
				vPosition -= m_vPositionOffset;
			else
				vPosition -= cSceneNode.GetTransform().GetRotation()*m_vPositionOffset;
			cSceneNode.MoveTo(vPosition);

			// Use rotation? If yes, set the rotation of the scene node to the rotation of the PL physics body
			if (!(GetFlags() & NoRotation)) {
				Quaternion qRotation;
				pBody->GetRotation(qRotation);
				cSceneNode.GetTransform().SetRotation(qRotation);
			}
		}

		// Resume listening
		m_bListening = true;
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNodeModifier functions ]
//[-------------------------------------------------------]
void SNMPhysicsBody::InformedOnInit()
{
	// Get the PL physics world this body is in
	SceneContainer *pContainer = GetSceneNode().GetContainer();
	while (pContainer && !pContainer->IsInstanceOf("PLPhysics::SCPhysicsWorld"))
		pContainer = pContainer->GetContainer();

	// Setup physics body
	if (pContainer) {
		// Backup pointer to the world container
		m_pWorldContainer = static_cast<SCPhysicsWorld*>(pContainer);
		if (m_pWorldContainer->GetWorld()) {
			// Create the PL physics body
			CreatePhysicsBody();
		} else {
			// ??
			m_pWorldContainer = nullptr;
		}
	} else {
		// No world, no physics...
		m_pWorldContainer = nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
