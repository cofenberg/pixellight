/*********************************************************\
 *  File: SNProjectiveSpotLight.h                        *
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


#ifndef __PLSCENE_PROJECTIVESPOTLIGHT_H__
#define __PLSCENE_PROJECTIVESPOTLIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLScene/Scene/SNSpotLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Projective spot light scene node
*
*  @note
*    - By default, the 'NoCone' flag is set meaning that the given outer and inner angles are
*      not used for lighting
*/
class SNProjectiveSpotLight : public SNSpotLight {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoProjection = 1<<14	/**< Disable texture projection */
		};
		pl_enum(EFlags)
			pl_enum_base(SNSpotLight::EFlags)
			pl_enum_value(NoProjection, "Disable texture projection")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNProjectiveSpotLight, "PLScene", PLScene::SNSpotLight, "Projective spot light scene node")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(ProjectedMaterial,	PLGeneral::String,		"Data/Textures/PLLogo.dds",	ReadWrite,	GetSet,	"Projected material",	"Type='Material Effect Image TextureAni'")
		// Overwritten SceneNode variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	NoCone,						ReadWrite,	GetSet,	"Flags",				"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLGeneral::String GetProjectedMaterial() const;
		PLS_API void SetProjectedMaterial(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNProjectiveSpotLight();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNProjectiveSpotLight();

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
		PLGeneral::String			m_sProjectedMaterial;	/**< Projected material */
		bool						m_bProjectedMaterial;	/**< Projected material loaded? */
		PLRenderer::MaterialHandler m_cProjectedMaterial;	/**< Projected material */


	//[-------------------------------------------------------]
	//[ Public virtual SNLight functions                      ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool IsProjectiveSpotLight() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_PROJECTIVESPOTLIGHT_H__
