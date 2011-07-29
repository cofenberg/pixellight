/*********************************************************\
 *  File: SNPhysicsMouseInteraction.h                    *
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


#ifndef __PLENGINE_PICKING_SNPHYSICSMOUSEINTERACTION_H__
#define __PLENGINE_PICKING_SNPHYSICSMOUSEINTERACTION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2i.h>
#include <PLScene/Scene/SceneNodeHandler.h>
#include "PLEngine/PLEngine.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLPhysics {
	class Body;
}
namespace PLEngine {
	class PhysicsMouseInteraction;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLEngine {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mouse physics interaction scene node
*
*  @remarks
*    When using the unchanged virtual standard controller:
*    - Hold the third mouse button over an physics object to pick it, use the mouse wheel
*      to pull/push the object towards/away
*    - While picking, hold shift/strg-key to increase/decrease the picking force, hit the
*      t-key to 'throw away' the picked object
*
*  @note
*    - The main purpose of this scene node is easy physics debugging
*    - If there's a scene node for instance named 'PhysicsForceLine' (default value of the variable 'ForceLineName')
*      within the same scene container, it's variables 'StartPosition' and 'EndPosition' will be manipulated so you can see
*      the applied 'picking force'
*    - Please note that this scene node will be removed in the future
*/
class SNPhysicsMouseInteraction : public PLScene::SceneNode {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PL_RTTI_EXPORT, SNPhysicsMouseInteraction, "PLEngine", PLScene::SceneNode, "Mouse physics interaction scene node")
		// Attributes
		pl_attribute(InputSemantic,		PLCore::String,			"",					ReadWrite,	DirectValue,	"Semantic of this input controller (e.g. \"Camera\")",								"")
		pl_attribute(MaxPickingRange,	float,					0.0f,				ReadWrite,	DirectValue,	"Maximum picking range, if 0.0, there's no range limit (physics container space)",	"Min='0.0'")
		pl_attribute(ThrowForce,		float,					2.0f,				ReadWrite,	DirectValue,	"Throw force",																		"Min='0.0'")
		pl_attribute(ForceLineName,		PLCore::String,			"PhysicsForceLine",	ReadWrite,	GetSet,			"Name of the force visualization line node",										"")
			// Overwritten PLScene::SceneNode attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	NoCulling,			ReadWrite,	GetSet,			"Flags",																			"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PL_API PLCore::String GetForceLineName() const;
		PL_API void SetForceLineName(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PL_API SNPhysicsMouseInteraction();

		/**
		*  @brief
		*    Destructor
		*/
		PL_API virtual ~SNPhysicsMouseInteraction();

		/**
		*  @brief
		*    Returns whether or not picking is currently performed
		*
		*  @param[out] pvMousePos
		*    If picking is currently performed and pvMousePos is not a null pointer, it will receive the current mouse position used for picking
		*
		*  @return
		*    'true' if picking is currently performed, else 'false'
		*/
		PL_API bool IsPicking(PLMath::Vector2i *pvMousePos = nullptr) const;


	//[-------------------------------------------------------]
	//[ Public virtual PLScene::SceneNode functions           ]
	//[-------------------------------------------------------]
	public:
		PL_API virtual PLInput::Controller *GetInputController() const override;


	//[-------------------------------------------------------]
	//[ Protected virtual PLScene::SceneNode functions        ]
	//[-------------------------------------------------------]
	protected:
		PL_API virtual void InitFunction() override;
		PL_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void OnUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String				m_sForceLineName;		/**< Name of the force visualization line node */
		bool						m_bPicking;				/**< Are we currently picking? */
		PLMath::Vector2i			m_vPickingMousePos;		/**< Mouse position used for picking */
		PLPhysics::Body			   *m_pPickedPhysicsBody;	/**< The currently picked physics body, can be a null pointer */
		float						m_fPickedDistance;		/**< Picking distance */
		PLMath::Vector3				m_vAttachmentPoint;		/**< Picking attachment point */
		PLScene::SceneNodeHandler	m_cForceLineHandler;	/**< Scene handler for the physics force line */
		PhysicsMouseInteraction	   *m_pController;			/**< Physics mouse interaction input controller instance, always valid! */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLEngine


#endif // __PLENGINE_PICKING_SNPHYSICSMOUSEINTERACTION_H__
