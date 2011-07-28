/*********************************************************\
 *  File: SNMAnchor.h                                    *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_ANCHOR_H__
#define __PLSCENE_SCENENODEMODIFIER_ANCHOR_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLScene/Scene/SceneNodeHandler.h"
#include "PLScene/Scene/SceneNodeModifier.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene node anchor modifier class
*
*  @remarks
*    By using this modifier, you can link together scene nodes in multiple ways.
*/
class SNMAnchor : public SceneNodeModifier {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			NoPosition        = 1<<2,	/**< Do NOT manipulate the position */
			NoRotation        = 1<<3,	/**< Do NOT manipulate the rotation */
			NoContainerUpdate = 1<<4	/**< Do NOT change the container the attached node is in */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNodeModifier::EFlags)
			pl_enum_value(NoPosition,			"Do NOT manipulate the position")
			pl_enum_value(NoRotation,			"Do NOT manipulate the rotation")
			pl_enum_value(NoContainerUpdate,	"Do NOT change the container the attached node is in")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMAnchor, "PLScene", PLScene::SceneNodeModifier, "Scene node anchor modifier class")
		// Attributes
		pl_attribute(AttachedNode,			PLCore::String,			"",									ReadWrite,	GetSet,			"Name of the attached scene node",																				"")
		pl_attribute(PositionOffset,		PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Position offset (node space)",																					"")
		pl_attribute(RotationOffset,		PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Rotation offset in degree (node space)",																		"")
		pl_attribute(SkeletonJoint,			PLCore::String,			"",									ReadWrite,	DirectValue,	"If not empty, the attached node is relative to this skeleton joint (there must be a mesh handler + skeleton)",	"")
		pl_attribute(JointPositionOffset,	PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Joint position offset (joint space)",																			"")
		pl_attribute(JointRotationOffset,	PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Joint rotation offset in degree (joint space)",																"")
			// Overwritten SceneNodeModifier attributes
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,									ReadWrite,	GetSet,			"Flags",																										"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_0(OnContainer,				"Called when the scene node container changed",									"")
		pl_slot_0(OnPositionRotationUpdate,	"Called when the scene node position or rotation changed or on update request",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetAttachedNode() const;
		PLS_API void SetAttachedNode(const PLCore::String &sValue);


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
		PLS_API SNMAnchor(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMAnchor();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node container changed
		*/
		void OnContainer();

		/**
		*  @brief
		*    Called when the scene node position or rotation changed or on update request
		*/
		void OnPositionRotationUpdate();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sAttachedNode;
		SceneNodeHandler  m_cAttachedNodeHandler;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_ANCHOR_H__
