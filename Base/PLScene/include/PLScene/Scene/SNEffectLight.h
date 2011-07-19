/*********************************************************\
 *  File: SNEffectLight.h                                *
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


#ifndef __PLSCENE_EFFECTLIGHT_H__
#define __PLSCENE_EFFECTLIGHT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Material/MaterialHandler.h>
#include <PLRenderer/Material/MaterialManager.h>
#include "PLScene/Scene/SNLight.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Effect light scene node
*/
class SNEffectLight : public SNLight {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNEffectLight, "PLScene", PLScene::SNLight, "Effect light scene node")
		// Attributes
		pl_attribute(CoronaMaterial,	PLCore::String,	"Data/Effects/DefaultCorona.plfx",	ReadWrite,	GetSet,	"Corona material",	"Type='Material Effect Image TextureAni'")
		pl_attribute(FlareMaterial,		PLCore::String,	"Data/Effects/DefaultFlare.plfx",	ReadWrite,	GetSet,	"Flare material",	"Type='Material Effect Image TextureAni'")
		pl_attribute(BlendMaterial,		PLCore::String,	"Data/Effects/DefaultBlend.plfx",	ReadWrite,	GetSet,	"Blend material",	"Type='Material Effect Image TextureAni'")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API PLCore::String GetCoronaMaterial() const;
		PLS_API void SetCoronaMaterial(const PLCore::String &sValue);
		PLS_API PLCore::String GetFlareMaterial() const;
		PLS_API void SetFlareMaterial(const PLCore::String &sValue);
		PLS_API PLCore::String GetBlendMaterial() const;
		PLS_API void SetBlendMaterial(const PLCore::String &sValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNEffectLight();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNEffectLight();

		/**
		*  @brief
		*    Returns the handler of the corona material
		*
		*  @return
		*    Handler of the corona material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetCoronaMaterialHandler();

		/**
		*  @brief
		*    Returns the handler of the flare material
		*
		*  @return
		*    Handler of the flare material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetFlareMaterialHandler();

		/**
		*  @brief
		*    Returns the handler of the blend material
		*
		*  @return
		*    Handler of the blend material
		*/
		PLS_API const PLRenderer::MaterialHandler &GetBlendMaterialHandler();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool						m_bCoronaMaterial;	/**< Corona material loaded? */
		PLCore::String				m_sCoronaMaterial;	/**< Corona material */
		PLRenderer::MaterialHandler m_cCoronaMaterial;	/**< Corona material */
		bool						m_bFlareMaterial;	/**< Flare material loaded? */
		PLCore::String				m_sFlareMaterial;	/**< Flare material */
		PLRenderer::MaterialHandler m_cFlareMaterial;	/**< Flare material */
		bool						m_bBlendMaterial;	/**< Blend material loaded? */
		PLCore::String				m_sBlendMaterial;	/**< Blend material */
		PLRenderer::MaterialHandler m_cBlendMaterial;	/**< Blend material */


	//[-------------------------------------------------------]
	//[ Public virtual SNLight functions                      ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual bool IsEffectLight() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_EFFECTLIGHT_H__
