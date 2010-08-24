/*********************************************************\
 *  File: SNMLightRandomAnimation.h                      *
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


#ifndef __PLSCENE_SCENENODEMODIFIER_LIGHTRANDOMANIMATION_H__
#define __PLSCENE_SCENENODEMODIFIER_LIGHTRANDOMANIMATION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Base/Event/EventHandler.h>
#include <PLGraphics/Color/Color3.h>
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
*    Scene node modifier class for a random light color animation
*
*  @remarks
*    Animates the color of the light scene node over time.
*/
class SNMLightRandomAnimation : public SceneNodeModifier {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Flags (SceneNodeModifier flags extension)
		*/
		enum EFlags {
			Multiply = 1<<2,	/**< Multiply the color to the fix color, if not set, the color is added to the fix color */
			NR       = 1<<3,	/**< Do NOT manipulate the red color component */
			NG       = 1<<4,	/**< Do NOT manipulate the green color componen */
			NB       = 1<<5		/**< Do NOT manipulate the blue color component */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNodeModifier::EFlags)
			pl_enum_value(Multiply,	"Multiply the color to the fix color, if not set, the color is added to the fix color")
			pl_enum_value(NR,		"Do NOT manipulate the red color component")
			pl_enum_value(NG,		"Do NOT manipulate the green color componen")
			pl_enum_value(NB,		"Do NOT manipulate the blue color component")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNMLightRandomAnimation, "PLScene", PLScene::SceneNodeModifier, "Scene node modifier class for a random light color animation")
		pl_properties
			pl_property("SceneNodeClass", "PLScene::SNLight")
		pl_properties_end
		pl_constructor_1(ParameterConstructor, SceneNode&, "Parameter constructor", "")
		pl_attribute(Speed,		float,					2.0f,									ReadWrite,	DirectValue,	"Animation speed",	"")
		pl_attribute(Radius,	float,					0.5f,									ReadWrite,	DirectValue,	"Animation radius",	"")
		pl_attribute(FixColor,	PLGraphics::Color3,		PLGraphics::Color3(0.5f, 0.5f, 0.5f),	ReadWrite,	DirectValue,	"Fix color",		"")
		pl_attribute(Color,		PLGraphics::Color3,		PLGraphics::Color3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Color to apply",	"")
		// Overwritten SceneNodeModifier variables
		pl_attribute(Flags,		pl_flag_type(EFlags),	0,										ReadWrite,	GetSet,			"Flags",			"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual void SetFlags(PLGeneral::uint32 nValue);


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
		PLS_API SNMLightRandomAnimation(SceneNode &cSceneNode);

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNMLightRandomAnimation();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void NotifyUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		float m_fTimer;	/**< Animation timer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODEMODIFIER_LIGHTRANDOMANIMATION_H__
