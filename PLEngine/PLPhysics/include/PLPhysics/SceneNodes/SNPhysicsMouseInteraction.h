/*********************************************************\
 *  File: SNPhysicsMouseInteraction.h                    *
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


#ifndef __PLPHYSICS_SCENENODES_MOUSEINTERACTION_H__
#define __PLPHYSICS_SCENENODES_MOUSEINTERACTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNodeHandler.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLPhysics {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class Body;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mouse physics interaction scene node
*
*  @note
*    - The main purpose of this scene node is easy physics debugging
*    - Hold the third mouse button over an physics object to pick it, use the mouse wheel
*      to pull/push the object towards/away
*    - While picking, hold shift/strg-key to increase/decrease the picking force, hit the
*      alt key to 'kick away' the picked object
*    - If there's a scene node for instance named 'PhysicsForceLine' (default value of the variable 'ForceLineName')
*      within the same scene container, it's variables 'StartPosition' and 'EndPosition' will be manipulated so you can see
*      the applied 'picking force'
*/
class SNPhysicsMouseInteraction : public PLScene::SceneNode {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPHYSICS_RTTI_EXPORT, SNPhysicsMouseInteraction, "PLPhysics", PLScene::SceneNode, "Mouse physics interaction scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(MaxPickingRange,	float,					0.0f,				ReadWrite,	DirectValue,	"Maximum picking range, if 0.0, there's no range limit (physics container space)",	"Min='0.0'")
		pl_attribute(ThrowForce,		float,					0.2f,				ReadWrite,	DirectValue,	"Throw force",																		"Min='0.0'")
		pl_attribute(ForceLineName,		PLGeneral::String,		"PhysicsForceLine",	ReadWrite,	GetSet,			"Name of the force visualization line node",										"")
		// Overwritten PLScene::SceneNode variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	NoCulling,			ReadWrite,	GetSet,			"Flags",																			"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLPHYSICS_API PLGeneral::String GetForceLineName() const;
		PLPHYSICS_API void SetForceLineName(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPHYSICS_API SNPhysicsMouseInteraction();

		/**
		*  @brief
		*    Destructor
		*/
		PLPHYSICS_API virtual ~SNPhysicsMouseInteraction();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String			m_sForceLineName;		/**< Name of the force visualization line node */
		bool						m_bPicking;				/**< Are we currently picking? */
		Body					   *m_pPickedPhysicsBody;	/**< The currently picked physics body, can be NULL */
		float						m_fPickedDistance;		/**< Picking distance */
		PLMath::Vector3				m_vAttachmentPoint;		/**< Picking attachment point */
		PLScene::SceneNodeHandler	m_cForceLineHandler;	/**< Scene handler for the physics force line */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void UpdateFunction();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics


#endif // __PLPHYSICS_SCENENODES_MOUSEINTERACTION_H__
