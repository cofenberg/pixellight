/*********************************************************\
 *  File: SNMOrbiting.h                                  *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_ORBITING_H__
#define __PLSCENE_SCENENODEMODIFIER_ORBITING_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include "PLScene/Scene/SceneNodeModifier.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLMath {
	class Vector3;
}
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
*    Scene node modifier class for orbiting around a target scene node
*
*  @remarks
*    This scene node modifier is for comfortable orbiting without the need to combine
*    multiple scene node modifiers. (for example 'SNMRotationTarget', 'SNMMoveController' and 'SNMRotationFixRoll')
*/
class SNMOrbiting : public SceneNodeModifier {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMOrbiting, "PLScene", PLScene::SceneNodeModifier, "Scene node modifier class for orbiting around a target scene node")
		// Attributes
		pl_attribute(Target,		PLCore::String,		"",									ReadWrite,	DirectValue,	"Target scene node to 'look at', if empty nothing happens",								"")
		pl_attribute(MinDistance,	float,				-1.0f,								ReadWrite,	GetSet,			"Minimum distance to the target, negative = no minimum, always <= 'MaxDistance'",		"")
		pl_attribute(MaxDistance,	float,				-1.0f,								ReadWrite,	GetSet,			"Maximum distance to the target, negative = no maximum, always >= 'MinDistance'",		"")
		pl_attribute(Distance,		float,				-1.0f,								ReadWrite,	GetSet,			"Distance to the target, negative = not initialized yet",								"")
		pl_attribute(Offset,		PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Target scene node position offset (same scene container space as target scene node)",	"")
		pl_attribute(UpVector,		PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Up vector (null vector for no limitation)",											"")
		pl_attribute(Pan,			PLMath::Vector3,	PLMath::Vector3(0.0f, 0.0f, 0.0f),	ReadWrite,	DirectValue,	"Pan",																					"")
		// Constructors
		pl_constructor_1(ParameterConstructor,	SceneNode&,	"Parameter constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API float GetMinDistance() const;
		PLS_API void SetMinDistance(float fValue);
		PLS_API float GetMaxDistance() const;
		PLS_API void SetMaxDistance(float fValue);
		PLS_API float GetDistance();
		PLS_API void SetDistance(float fValue);


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
		PLS_API SNMOrbiting(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMOrbiting();


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
		*    Validates the minimum, maximum and distance settings
		*/
		void ValidateSettings();

		/**
		*  @brief
		*    Returns the target position within the container space of the owner node
		*
		*  @param[out] vPos
		*    Will receive the position of the target scene node, not manipulated on error
		*
		*  @return
		*    'true' if all went fine, else 'false' (invalid target?)
		*/
		bool GetTargetPosition(PLMath::Vector3 &vPos) const;

		/**
		*  @brief
		*    Called on scene node position or rotation change or update request
		*/
		void OnPositionRotationUpdate();

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
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLRenderer::Renderer &, const VisNode *> EventHandlerDrawDebug;
		PLCore::EventHandler<>										  EventHandlerPositionRotationUpdate;


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		float m_fMinDistance;		/**< Minimum distance to the target, negative = no minimum, always <= 'MaxDistance' */
		float m_fMaxDistance;		/**< Maximum distance to the target, negative = no maximum, always >= 'MinDistance' */
		float m_fDistance;			/**< Distance to the target, negative = not initialized yet */
		bool  m_bPositionListening;	/**< Listen for position events? */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_ORBITING_H__
