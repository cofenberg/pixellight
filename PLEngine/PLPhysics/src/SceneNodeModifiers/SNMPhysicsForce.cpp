/*********************************************************\
 *  File: SNMPhysicsForce.cpp                            *
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
#include <PLScene/Scene/SceneNode.h>
#include <PLScene/Scene/SceneContext.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBody.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsForce.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsForce)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsForce::SNMPhysicsForce(SceneNode &cSceneNode) : SNMPhysics(cSceneNode),
	Force(this),
	EventHandlerUpdate(&SNMPhysicsForce::NotifyUpdate, this)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsForce::~SNMPhysicsForce()
{
}


//[-------------------------------------------------------]
//[ Protected virtual PLScene::SceneNodeModifier functions ]
//[-------------------------------------------------------]
void SNMPhysicsForce::OnActivate(bool bActivate)
{
	// Connect/disconnect event handler
	SceneContext *pSceneContext = GetSceneContext();
	if (pSceneContext) {
		if (bActivate)
			pSceneContext->EventUpdate.Connect(&EventHandlerUpdate);
		else
			pSceneContext->EventUpdate.Disconnect(&EventHandlerUpdate);
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMPhysicsForce::NotifyUpdate()
{
	const SNMPhysicsBody *pModifier = static_cast<SNMPhysicsBody*>(GetSceneNode().GetModifier("PLPhysics::SNMPhysicsBody"));
	if (pModifier) {
		Body *pBody = pModifier->GetBody();
		if (pBody)
			pBody->SetForce(Force.Get());
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics
