/*********************************************************\
 *  File: SNMPhysicsJoint.h                              *
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


#ifndef __PLPHYSICS_SCENENODEMODIFIERS_JOINT_H__
#define __PLPHYSICS_SCENENODEMODIFIERS_JOINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLPhysics/SceneNodeModifiers/SNMPhysics.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Joint;
class ElementHandler;
class SCPhysicsWorld;
class SNMPhysicsBody;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract physics joint scene node modifier
*
*  @note
*    - There MUST be already a 'Body'-modifier within the scene node else the joint has
*      no effect. Further this body can NOT have an infinity (zero = static, the default value) mass.
*      Internally, this physics body is used as the child body the joint is attached to.
*    - By default joint disables collision with the linked bodies
*    - The scene node 'Parent' MUST already exist, else the joint can not be attached to it!
*/
class SNMPhysicsJoint : public SNMPhysics {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNMPhysicsJoint, "PLPhysics", PLPhysics::SNMPhysics, "Abstract physics joint scene node modifier")
		pl_attribute(Child,	PLGeneral::String,	"",	ReadWrite,	GetSet,	"Name of the child scene node (which must have a 'SNMPhysicsBody' modifier!), can left undefined",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API PLGeneral::String GetChild() const;
		PLPHYSICS_API void SetChild(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the PL physics world scene node container the physics joint is in
		*
		*  @return
		*    The PL physics world scene node container the physics joint is in, a null pointer on error
		*    (if that's the case, something went totally wrong :)
		*
		*  @note
		*    - This PL physics world scene node container can be another as the scene node container this scene node is in
		*/
		PLPHYSICS_API SCPhysicsWorld *GetWorldContainer() const;

		/**
		*  @brief
		*    Returns the PL physics joint
		*
		*  @return
		*    The PL physics joint, a null pointer on error (if that's the case, something went totally wrong :)
		*/
		PLPHYSICS_API Joint *GetJoint() const;

		/**
		*  @brief
		*    Returns the parent PL physics body scene node modifier the joint is attached to
		*
		*  @return
		*    The parent PL physics body scene node modifier, a null pointer if there's no such body
		*/
		PLPHYSICS_API SNMPhysicsBody *GetParentBodyModifier() const;

		/**
		*  @brief
		*    Returns the child PL physics body scene node modifier the joint is attached to
		*
		*  @return
		*    The child PL physics body scene node modifier, a null pointer if there's no such body
		*/
		PLPHYSICS_API SNMPhysicsBody *GetChildBodyModifier() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cSceneNode
		*    Owner scene node
		*/
		PLPHYSICS_API SNMPhysicsJoint(PLScene::SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNMPhysicsJoint();

		/**
		*  @brief
		*    Recreates the PL physics joint
		*/
		PLPHYSICS_API void RecreatePhysicsJoint();


	//[-------------------------------------------------------]
	//[ Protected virtual functions                           ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Creates the PL physics joint
		*/
		virtual void CreatePhysicsJoint() = 0;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::String  m_sChild;			/**< Name of the child scene node (which must have a 'SNMPhysicsBody' modifier!), can left undefined */
		SCPhysicsWorld    *m_pWorldContainer;	/**< The PL physics world scene node container the physics joint is in, can be a null pointer */
		ElementHandler    *m_pJointHandler;		/**< Holds the PL physics joint (ALWAYS valid!) */


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNodeModifier functions ]
	//[-------------------------------------------------------]
	protected:
		PLPHYSICS_API virtual void InformedOnInit();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODEMODIFIERS_JOINT_H__
