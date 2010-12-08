/*********************************************************\
 *  File: SNMPhysicsUpdateVelocity.h                     *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_UPDATEVELOCITY_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_UPDATEVELOCITY_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLMath/Vector3.h>
#include <PLMath/Quaternion.h>
#include "PLPhysics/SceneNodeModifiers/SNMPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Updates the linear and angular velocity of physics bodies according to the scene node movement
*
*  @remarks
*    If there's a static (immobile) physics body which should for example move along a well defined path, this
*    static physics body will not interact properly with dynamic physics bodies because it's assumed to stay on one
*    and the same place. But when you have a moving platform or an escalator, this physics body should still be
*    static and therefore not influenced by other physics bodies, but other dynamic physics object should interact
*    correctly with the static moving physics body. (for example move with the platform) The static physics body is
*    in such a case called a kinematic physics body and can be realized within the scene graph by adding this scene
*    node modifier to your scene node which should be a kinematic physics body.
*
*  @note
*    - Keeps track of position changes and updates the linear velocity of the static physics bodies
*    - Keeps track of rotationn changes and updates the angular velocity of the static physics bodies
*    - Scene container ownership changes are not tracked
*/
class SNMPhysicsUpdateVelocity : public SNMPhysics {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsUpdateVelocity, "PLPhysics", PLPhysics::SNMPhysics, "Updates the linear and angular velocity of physics bodies according to the scene node movement")
		pl_constructor_1(ParameterConstructor, PLScene::SceneNode&, "Parameter constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLPHYSICS_API SNMPhysicsUpdateVelocity(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsUpdateVelocity();


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PLPHYSICS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node position changed
		*/
		void NotifyPosition();

		/**
		*  @brief
		*    Called when the scene node rotation changed
		*/
		void NotifyRotation();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerPosition;
		PLCore::EventHandler<> EventHandlerRotation;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool			   m_bPreviousPosition;	/**< Is there a previous scene node position? */
		PLMath::Vector3	   m_vPreviousPosition;	/**< Previous scene node position */
		bool			   m_bPreviousRotation;	/**< Is there a previous scene node rotation? */
		PLMath::Quaternion m_qPreviousRotation;	/**< Previous scene node rotation */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_UPDATEVELOCITY_H__
