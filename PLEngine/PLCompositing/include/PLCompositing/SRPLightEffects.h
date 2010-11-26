/*********************************************************\
 *  File: SRPLightEffects.h                              *
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


#ifndef __PLCOMPOSITING_LIGHTEFFECTS_H__
#define __PLCOMPOSITING_LIGHTEFFECTS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLScene/Compositing/SceneRendererPass.h>
#include "PLCompositing/PLCompositing.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGraphics {
	class Color4;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract scene renderer pass drawing light effects like lens flares
*/
class SRPLightEffects : public PLScene::SceneRendererPass {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoCorona    = 1<<1,	/**< Disable corona rendering */
			NoFlares    = 1<<2,	/**< Disable flares rendering */
			NoBlend     = 1<<3,	/**< Disable blend rendering */
			PrepareStep = 1<<4	/**< Is this a prepare step? */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneRendererPass::EFlags)
			pl_enum_value(NoCorona,		"Disable corona rendering")
			pl_enum_value(NoFlares,		"Disable flares rendering")
			pl_enum_value(NoBlend,		"Disable blend rendering")
			pl_enum_value(PrepareStep,	"Is this a prepare step?")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPLightEffects, "PLCompositing", PLScene::SceneRendererPass, "Abstract scene renderer pass drawing light effects like lens flares")
		pl_attribute(CoronaMaterial,	PLGeneral::String,		"Data/Effects/DefaultCorona.plfx",	ReadWrite,	GetSet,	"Corona material",	"Type='Material Effect Image TextureAni'")
		pl_attribute(FlareMaterial,		PLGeneral::String,		"Data/Effects/DefaultFlare.plfx",	ReadWrite,	GetSet,	"Flare material",	"Type='Material Effect Image TextureAni'")
		pl_attribute(BlendMaterial,		PLGeneral::String,		"Data/Effects/DefaultBlend.plfx",	ReadWrite,	GetSet,	"Blend material",	"Type='Material Effect Image TextureAni'")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,									ReadWrite,	GetSet,	"Flags",			"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API PLGeneral::String GetCoronaMaterial() const;
		PLCOM_API void SetCoronaMaterial(const PLGeneral::String &sValue);
		PLCOM_API PLGeneral::String GetFlareMaterial() const;
		PLCOM_API void SetFlareMaterial(const PLGeneral::String &sValue);
		PLCOM_API PLGeneral::String GetBlendMaterial() const;
		PLCOM_API void SetBlendMaterial(const PLGeneral::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the handler of the corona material
		*
		*  @return
		*    Handler of the corona material
		*/
		PLCOM_API const PLRenderer::MaterialHandler &GetCoronaMaterialHandler();

		/**
		*  @brief
		*    Returns the handler of the flare material
		*
		*  @return
		*    Handler of the flare material
		*/
		PLCOM_API const PLRenderer::MaterialHandler &GetFlareMaterialHandler();

		/**
		*  @brief
		*    Returns the handler of the blend material
		*
		*  @return
		*    Handler of the blend material
		*/
		PLCOM_API const PLRenderer::MaterialHandler &GetBlendMaterialHandler();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPLightEffects();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPLightEffects();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool						m_bCoronaMaterial;	/**< Corona material loaded? */
		PLGeneral::String			m_sCoronaMaterial;	/**< Corona material */
		PLRenderer::MaterialHandler m_cCoronaMaterial;	/**< Corona material */
		bool						m_bFlareMaterial;	/**< Flare material loaded? */
		PLGeneral::String			m_sFlareMaterial;	/**< Flare material */
		PLRenderer::MaterialHandler m_cFlareMaterial;	/**< Flare material */
		bool						m_bBlendMaterial;	/**< Blend material loaded? */
		PLGeneral::String			m_sBlendMaterial;	/**< Blend material */
		PLRenderer::MaterialHandler m_cBlendMaterial;	/**< Blend material */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_LIGHTEFFECTS_H__
