/*********************************************************\
 *  File: SNLight.h                                      *
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


#ifndef __PLSCENE_LIGHT_H__
#define __PLSCENE_LIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color3.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract light scene node base class
*
*  @note
*    - Scene node scale is ignored
*/
class SNLight : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			Flares = 1<<10,	/**< Lens flares */
			Corona = 1<<11,	/**< Corona around the light */
			Blend  = 1<<12	/**< Brighten the screen (blend effect) */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(Flares,	"Lens flares")
			pl_enum_value(Corona,	"Corona around the light")
			pl_enum_value(Blend,	"Brighten the screen (blend effect)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNLight, "PLScene", PLScene::SceneNode, "Abstract light scene node base class")
		// Properties
		pl_properties
			pl_property("Icon",	"Data/Textures/IconLight.dds")
		pl_properties_end
		// Attributes
		pl_attribute(Color,				PLGraphics::Color3,		PLGraphics::Color3(1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Light color (r/g/b)",	"")
		pl_attribute(CoronaSize,		float,					0.2f,									ReadWrite,	DirectValue,	"Corona size",			"")
		pl_attribute(FlareSize,			float,					0.1f,									ReadWrite,	DirectValue,	"Lens flare size",		"")
		pl_attribute(ScreenBrighten,	float,					0.3f,									ReadWrite,	DirectValue,	"Screen brighten",		"")
			// Overwritten SceneNode attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,										ReadWrite,	GetSet,			"Flags",				"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public virtual functions                              ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns whether this is a render light or not
		*
		*  @return
		*    'true' if this is a render light, else 'false'
		*/
		PLS_API virtual bool IsRenderLight() const;

		/**
		*  @brief
		*    Returns whether this scene node is a effect light (SNEffectLight) or not
		*
		*  @return
		*    'true' if this scene node is a effect light, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNEffectLight")
		*/
		PLS_API virtual bool IsEffectLight() const;

		/**
		*  @brief
		*    Returns whether this scene node is a point light (SNPointLight) or not
		*
		*  @return
		*    'true' if this scene node is a point light, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNPointLight")
		*/
		PLS_API virtual bool IsPointLight() const;

		/**
		*  @brief
		*    Returns whether this scene node is a projective point light (SNProjectivePointLight) or not
		*
		*  @return
		*    'true' if this scene node is a projective point light, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNProjectivePointLight")
		*/
		PLS_API virtual bool IsProjectivePointLight() const;

		/**
		*  @brief
		*    Returns whether this scene node is a spot light (SNSpotLight) or not
		*
		*  @return
		*    'true' if this scene node is a spot light, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNSpotLight")
		*/
		PLS_API virtual bool IsSpotLight() const;

		/**
		*  @brief
		*    Returns whether this scene node is a projective spot light (SNProjectiveSpotLight) or not
		*
		*  @return
		*    'true' if this scene node is a projective spot light, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNProjectiveSpotLight")
		*/
		PLS_API virtual bool IsProjectiveSpotLight() const;

		/**
		*  @brief
		*    Returns whether this scene node is a directional light (SNDirectionalLight) or not
		*
		*  @return
		*    'true' if this scene node is a directional light, else 'false'
		*
		*  @note
		*    - More performant than IsInstanceOf("PLScene::SNDirectionalLight")
		*/
		PLS_API virtual bool IsDirectionalLight() const;


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNLight();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNLight();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_LIGHT_H__
