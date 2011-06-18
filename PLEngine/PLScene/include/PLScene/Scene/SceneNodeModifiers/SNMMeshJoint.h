/*********************************************************\
 *  File: SNMMeshJoint.h                                 *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_MESHJOINT_H__
#define __PLSCENE_SCENENODEMODIFIER_MESHJOINT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector3.h>
#include "PLScene/Scene/SceneNodeModifiers/SNMMesh.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Renderer;
}
namespace PLScene {
	class VisNode;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh scene node joint modifier class
*
*  @note
*    - Adds automatically a "PLScene::SNMMeshUpdate" scene node modifier (if there's not yet one) in order to frequently update the mesh
*    - If the node has no mesh with a skeleton, this modifier will have no effect
*/
class SNMMeshJoint : public SNMMesh {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			UseFallbackRotation = 1<<2	/**< Use fallback rotation if the target is 'out of rotation range' */
		};
		pl_enum(EFlags)
			pl_enum_base(SNMMesh::EFlags)
			pl_enum_value(UseFallbackRotation, "Use fallback rotation if the target is 'out of rotation range'")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMMeshJoint, "PLScene", PLScene::SNMMesh, "Mesh scene node joint modifier class")
		// Attributes
		pl_attribute(Name,				PLGeneral::String,		"",									ReadWrite,	GetSet,			"Name of the joint to modifiy",															"")
		pl_attribute(Rotation,			PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,			"Joint rotation in degree (joint space)",												"")
		pl_attribute(RotationFrom,		PLGeneral::String,		"",									ReadWrite,	DirectValue,	"Name of the scene node to take the rotation from (transformed into joint space)",		"")
		pl_attribute(Min,				PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,			"Minimum joint rotation in in degree, if min = max -> no limitation, per component",	"")
		pl_attribute(Max,				PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	GetSet,			"Maximum joint rotation in in degree, if min = max -> no limitation, per component",	"")
		pl_attribute(Speed,				float,					5.0f,								ReadWrite,	DirectValue,	"Rotation speed",																		"")
		pl_attribute(MaxDifference,		float,					50.0f,								ReadWrite,	DirectValue,	"Maximum rotation difference in degree, use it to void TO fast rotations",				"")
		pl_attribute(FallbackRotation,	PLMath::Vector3,		PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Rotation that is used if the target is 'out of rotation range'",						"")
			// Overwritten SceneNodeModifier attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,									ReadWrite,	GetSet,			"Flags",																				"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
		// Slots
		pl_slot_0(OnUpdate,												"Called when the scene node modifier needs to be updated",																												"")
		pl_slot_2(OnDrawDebug,	PLRenderer::Renderer&,	const VisNode*,	"Called on scene node debug draw, the used renderer as first parameter, the current visibility node of this scene node (can be a null pointer) as second parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetName() const;
		PLS_API void SetName(const PLGeneral::String &sValue);
		PLS_API const PLMath::Vector3 &GetRotation() const;
		PLS_API void SetRotation(const PLMath::Vector3 &vValue);
		PLS_API const PLMath::Vector3 &GetMin() const;
		PLS_API void SetMin(const PLMath::Vector3 &vValue);
		PLS_API const PLMath::Vector3 &GetMax() const;
		PLS_API void SetMax(const PLMath::Vector3 &vValue);


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
		PLS_API SNMMeshJoint(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMMeshJoint();


	//[-------------------------------------------------------]
	//[ Protected virtual SceneNodeModifier functions         ]
	//[-------------------------------------------------------]
	protected:
		PLS_API virtual void OnActivate(bool bActivate);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Returns the target rotation within the container space of the owner node
		*
		*  @param[out] qRot
		*    Will receive the rotation of the target scene node
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid target?)
		*/
		bool GetTargetRotation(PLMath::Quaternion &qRot) const;

		/**
		*  @brief
		*    Updates the joint
		*/
		void UpdateJoint();

		/**
		*  @brief
		*    Called when the scene node modifier needs to be updated
		*/
		void OnUpdate();

		/**
		*  @brief
		*    Called on scene node debug draw
		*
		*  @param[in] cRenderer
		*    The used renderer
		*  @param[in] pVisNode
		*    The current visibility node of this scene node, can be a null pointer
		*/
		void OnDrawDebug(PLRenderer::Renderer &cRenderer, const VisNode *pVisNode);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::String m_sName;		/**< Name of the joint to modifiy */
		PLMath::Vector3   m_vRotation;	/**< Joint rotation in degree (joint space) */
		PLMath::Vector3   m_vMin;		/**< Minimum joint rotation in in degree, if min = max -> no limitation, per component */
		PLMath::Vector3   m_vMax;		/**< Maximum joint rotation in in degree, if min = max -> no limitation, per component */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_MESHJOINT_H__
