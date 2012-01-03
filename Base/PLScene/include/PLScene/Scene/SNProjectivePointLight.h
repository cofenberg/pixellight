/*********************************************************\
 *  File: SNProjectivePointLight.h                       *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSCENE_PROJECTIVEPOINTLIGHT_H__
#define __PLSCENE_PROJECTIVEPOINTLIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLScene/Scene/SNPointLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Omni directional projective point light scene node
*/
class SNProjectivePointLight : public SNPointLight {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoProjection = 1<<13	/**< Disable texture projection */
		};
		pl_enum(EFlags)
			pl_enum_base(SNPointLight::EFlags)
			pl_enum_value(NoProjection, "Disable texture projection")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNProjectivePointLight, "PLScene", PLScene::SNPointLight, "Omni directional projective point light scene node")
		// Attributes
		pl_attribute(ProjectedMaterial,	PLCore::String,			"Data/Textures/DefaultCubeMap.dds",	ReadWrite,	GetSet,	"Projected material",	"Type='Material Effect Image TextureAni'")
			// Overwritten SceneNode attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,									ReadWrite,	GetSet,	"Flags",				"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetProjectedMaterial() const;
		PLS_API void SetProjectedMaterial(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNProjectivePointLight();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNProjectivePointLight();

		/**
		*  @brief
		*    Returns the handler of the projected material
		*
		*  @return
		*    Handler of the projected material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetProjectedMaterialHandler();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String				m_sProjectedMaterial;	/**< Projected material */
		bool						m_bProjectedMaterial;	/**< Projected material loaded? */
		PLRenderer::MaterialHandler m_cProjectedMaterial;	/**< Projected material */


	//[-------------------------------------------------------]
	//[ Public virtual SNLight functions                      ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool IsProjectivePointLight() const override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_PROJECTIVEPOINTLIGHT_H__
